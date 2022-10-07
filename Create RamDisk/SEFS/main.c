/**
 * @file main.c
 * @author Пиминов Никита (nikita.piminoff@yandex,ru)
 * @brief SayoriOS SDK - Create RamDisk (SEFS)
 * @version 0.1.0
 * @date 2022-10-07
 * @copyright Copyright SayoriOS Team (c) 2022
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
struct sefs_file_header
{
    int index;                      ///< Индекс
    unsigned char magic;            ///< Магическое число для проверки ошибок.
    char name[128];                 ///< Имя файла
    unsigned char offset;           ///< Смещение в sefs, указывающее откуда начинается файл.
    unsigned int length;            ///< Длина файла
    int types;                      ///< Тип (0 - файл/1 - Папка)
    int parentDir;                  ///< Родительская папка (0 - значит root)
};

char dirs[2048][128];
int dirs_count = 0;
int cf = 0;
struct sefs_file_header headers[2048];
unsigned int off = sizeof(struct sefs_file_header) * 2048 + sizeof(int);
char sl[2] = "/\0";
char folder[128] = {0};

/**
 * @brief Регистрация папки
 *
 * @param char* dir - Полный путь к папке
 *
 * @return int - Индекс папки
 */
int regDir(char* dir){
    for(int i = 0;i < 2048; i++){
        if (strcmp(dir,dirs[i]) == 0){
            return i;
        }
    }
    strcpy(dirs[dirs_count], dir);
    dirs_count++;
    return (dirs_count-1);
}

/**
 * @brief Добавляет файл на запись
 *
 * @param char* name - Имя файла
 * @param char* path - Путь к файлу
 * @param char* vpath - Виртуальный путь
 */
void fileWrite(char* name, char* path, char* vpath){
    if (cf > 2048){
        printf("[!] Файл проигнорирован: %s%s (Лимит)\n",vpath,name);
        return;
    }
    char file[128] = {0};
    strcpy(file,path);
    strcat(file,name);
    int i = cf;
    headers[i].index = i;
    headers[i].types = 0;
    headers[i].parentDir = regDir(vpath);
    strcpy(headers[i].name, name);
    headers[i].offset = off;
    FILE *stream = fopen(file, "r");
    if(stream == 0){
        printf("[!] Файл проигнорирован: %s%s (404)\n",vpath,name);
        return;
    }
    fseek(stream, 0, SEEK_END);
    headers[i].length = ftell(stream);
    printf("[*] [%d] Файл: %s%s (%d кб) \n",i,vpath,name,(headers[i].length)/1024);
    off += headers[i].length;
    fclose(stream);
    headers[i].magic = 0xBF;
    cf++;
}

/**
 * @brief Рекурсивное чтение папки
 *
 * @param char* path - Старый путь
 * @param char* newpath - Новый путь
 */
void rDir(char* path,char* newpath){
    char file[128] = {0};
    strcpy(file,folder);
    strcat(file,newpath);
    if (cf > 2048){
        printf("[!] Папка `%s` пропущена из-за лимита\n",newpath);
        return;
    }
    //printf("\t\t Path: %s | New: %s | Complete: %s\n",path,newpath,file);
    DIR *dir;
    struct dirent *de;

    dir = opendir(file);
    while(dir){
        de = readdir(dir);
        if (!de) break;
        if (strcmp(de->d_name,".") == 0 || strcmp(de->d_name,"..") == 0){
            continue;
        }
        char fp[128];                   ///< Виртуальный путь
        strcpy(fp,newpath);             ///< Делаем обратный шлеф
        strcat(fp,de->d_name);          ///< Дополняем имя папки
        if (de->d_type == 4){
            strcat(fp,sl);              ///< Дописываем флеш
            rDir(file,fp);
        } else if (de->d_type == 8){
            fileWrite(de->d_name,file,newpath);
        }
    }
    closedir(dir);
}

/**
 * @brief Режим работы через папку
 *
 * @param char* path - Путь к папке
 *
 * @return int - Результат работы
 */
int dirPath(char* path){
    strcpy(folder,path);
    regDir("/");
    char file[128] = {0};
    strcpy(file,path);
    strcat(file,sl);
    printf("[!] Установлен режим сканирования папки...\n");
    //printf("Путь: %s\n",file);
    DIR *dir;
    struct dirent *de;

    dir = opendir(path);
    while(dir){
        de = readdir(dir);
        if (!de) break;
        if (strcmp(de->d_name,".") == 0 || strcmp(de->d_name,"..") == 0){
            continue;
        }
        char fp[128];               ///< Виртуальный путь
        strcpy(fp,sl);              ///< Делаем обратный шлеф
        strcat(fp,de->d_name);      ///< Дополняем имя папки
        if (de->d_type == 4){
            strcat(fp,sl);          ///< Дописываем флеш
            rDir(path,fp);
            //printf("\t Путь: %s -> %s\n",path,fp);
        } else if (de->d_type == 8){
            fileWrite(de->d_name,path,"/");
        }
    }
    closedir(dir);
    if (cf+dirs_count > 2048){
        printf("[!] [ОШИБКА] Извините, но лимит (2048) переполнен, выберите дирикторию с меньшим объемом файлов.\n");
        return -1;
    }
    for(int i = 0; i < dirs_count;i++){

        headers[cf+i].index = (cf+i);
        headers[cf+i].types = 1;
        headers[cf+i].length = 0;
        off += headers[cf+i].length;
        headers[cf+i].offset = off;
        headers[cf+i].magic = 0xBF;
        strcpy(headers[cf+i].name, dirs[(i)]);
        printf("[*] [%d] Папка (%d): %s \n",cf+i,i,dirs[(i)]);
    }
    cf += dirs_count;
    FILE *wstream = fopen("./sayori_sefs.img", "w");
    unsigned char *data = (unsigned char *)malloc(off);
    fwrite(&cf, sizeof(int), 1, wstream);
    fwrite(headers, sizeof(struct sefs_file_header), 2048, wstream);
    cf -= dirs_count;
    for(int i = 0; i < cf; i++){

        char files[128] = {0};
        strcpy(files,path);
        strcat(files,dirs[headers[i].parentDir]);
        strcat(files,headers[i].name);
        printf("[W] Пишим в файл: %s\n",files);
        if (headers[i].types == 1){
            continue;
        }
        FILE *stream = fopen(files, "r");
        unsigned char *buf = (unsigned char *)malloc(headers[i].length);
        fread(buf, 1, headers[i].length, stream);
        fwrite(buf, 1, headers[i].length, wstream);
        fclose(stream);
        free(buf);
    }
    fclose(wstream);
    free(data);
    printf("\n");
    return 0;
}

/**
 * @brief SayoriOS SDK - Create RamDisk (SEFS)
 *
 * @param int argc - Кол-во аргементов
 * @param char** argv - Аргументы
 *
 * @return int - Результат работы программы
 */
int main(int argc, char **argv){
    if (argc > 1 && strcmp(argv[1],"--dir") == 0){
        return dirPath(argv[2]);
    }
    int nheaders = (argc-1)/3;
    printf("Размер заголовка: %d\n", (int) sizeof(struct sefs_file_header));
    printf("Начинаем запись файлов (%d)...\n",nheaders);
    for(int i = 0; i < nheaders; i++){
        headers[i].index = i;
        printf("Индекс: %d\n",i);
        printf("\t * Файл: `%s` -> `%s`\n",argv[i*3+1], argv[i*3+2]);
        printf("\t * Папка: [%d] `%s`\n",regDir(argv[i*3+3]),argv[i*3+3]);
        printf("\t * Позиция: 0x%x\n",off);
        headers[i].types = 0;
        headers[i].parentDir = regDir(argv[i*3+3]);
        strcpy(headers[i].name, argv[i*3+2]);
        headers[i].offset = off;
        FILE *stream = fopen(argv[i*3+1], "r");
        if(stream == 0){
            printf("ОШИБКА: Файл не найден: %s\n", argv[i*2+1]);
            return 1;
        }
        fseek(stream, 0, SEEK_END);
        headers[i].length = ftell(stream);
        printf("\t * Вес: %d kb\n",(headers[i].length)/1024);
        off += headers[i].length;
        fclose(stream);
        headers[i].magic = 0xBF;
    }
    printf("Начинаем запись папок (%d)...\n",dirs_count);
    for(int i = 0; i < dirs_count;i++){
        headers[nheaders+i].index = (nheaders+i);
        headers[nheaders+i].types = 1;
        headers[nheaders+i].length = 64;
        off += headers[nheaders+i].length;
        headers[nheaders+i].offset = off;
        headers[nheaders+i].magic = 0xBF;
        strcpy(headers[nheaders+i].name, dirs[(i)]);
        printf("Индекс: %d\n",(nheaders+i));
        printf("\t * Вес: %d kb\n",(headers[nheaders+i].length)/1024);
        printf("\t * Папка: [%d] %s\n",(i),dirs[(i)]);
        printf("\t * Позиция: 0x%x\n",off);
    }
    FILE *wstream = fopen("./sayori_sefs.img", "w");
    unsigned char *data = (unsigned char *)malloc(off);
    fwrite(&nheaders, sizeof(int), 1, wstream);
    fwrite(headers, sizeof(struct sefs_file_header), 64, wstream);

    for(int i = 0; i < nheaders; i++){
        FILE *stream = fopen(argv[i*3+1], "r");
        unsigned char *buf = (unsigned char *)malloc(headers[i].length);
        fread(buf, 1, headers[i].length, stream);
        fwrite(buf, 1, headers[i].length, wstream);
        fclose(stream);
        free(buf);
    }
    fclose(wstream);
    free(data);
    printf("\n");
    return 0;
}
