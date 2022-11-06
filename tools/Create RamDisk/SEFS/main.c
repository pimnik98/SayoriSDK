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
#include <errno.h>

/* 64-bit types */
typedef	unsigned long long	uint64_t;
typedef	unsigned int	uint32_t;
typedef	unsigned char	uint8_t;
struct sefs_file_header
{
   uint8_t index;             ///< Индекс
   uint32_t magic;       ///< Магическое число для проверки ошибок.
   char name[128];            ///< Имя файла
   uint32_t offset;           ///< Смещение в sefs, указывающее откуда начинается файл.
   uint32_t length;           ///< Длина файла
   uint8_t types;             ///< Тип (0 - файл/1 - Папка)
   uint8_t parentDir;         ///< Родительская папка (0 - значит root)
};

char dirs[2048][128];
int dirs_count = 0;
int cf = 0;
struct sefs_file_header headers[2048];
unsigned int off = sizeof(struct sefs_file_header) * 2048 + sizeof(int);
char sl[2] = "/\0";
char folder[128] = {0};
int indDir[128] = {0};

int __regDir(char* path){
    for(int i = 0;i < 2048; i++){
        if (strcmp(path,dirs[i]) == 0){
            return i;
        }
    }
    strcpy(dirs[dirs_count], path);
    dirs_count++;
    return (dirs_count-1);
}

/**
 * @brief Регистрация папки
 *
 * @param char* dir - Полный путь к папке
 * @param char* dir - Старый путь к папке
 *
 * @return int - Индекс папки
 */
int regDir(char* dir,char* odir){
    int Index   = __regDir(dir);
    int Index2  = __regDir(odir);
    if (Index != Index2){
        //printf("[regDir] Dir: %s | Old: %s\n",dir,odir);
        //printf("[*] regDir\n");
        //printf("|-- [%d] %s\n",Index2,odir);
        //printf("  |-- [%d] %s\n\n",Index,dir);
        indDir[Index] = Index2;
    }
    return Index;
}

/**
 * @brief Добавляет файл на запись
 *
 * @param char* name - Имя файла
 * @param char* path - Путь к файлу
 * @param char* vpath - Виртуальный путь
 */
void fileWrite(char* name, char* path, char* vpath){
    printf("| |-- [File] %s%s\n",vpath,name);
    if (cf > 2048){
        printf("| | |-- [X] [ERROR] %s\n","File limit exceeded");
        printf("| |\n");
        return;
    }
    char file[128] = {0};
    strcpy(file,path);
    strcat(file,"/");
    strcat(file,name);
    int i = cf;
    headers[i].index = i;
    headers[i].types = 0;
    headers[i].parentDir = regDir(vpath,vpath);
    strcpy(headers[i].name, name);
    headers[i].offset = off;
    FILE *stream = fopen(file, "r");
    if(stream == 0){
        printf("| | |-- [X] [ERROR] [%d] %s\n",errno,"File no found");
        printf("| |\n");
        return;
    }
    fseek(stream, 0, SEEK_END);
    headers[i].length = ftell(stream);
    printf("| | |-- Index: %d\n",cf);
    printf("| | |-- Size: %d %s\n",(headers[i].length > 1024?
        (headers[i].length/1024):headers[i].length),
        (headers[i].length > 1024?"kb":"byte")
    );
    off += headers[i].length;
    fclose(stream);
    headers[i].magic = 0xBF;
    cf++;
    printf("| |\n");
}

/**
 * @brief Рекурсивное чтение папки
 *
 * @param char* path - Старый путь
 * @param char* newpath - Новый путь
 */
void rDir(char* path,char* newpath,char* spath){
    char file[128] = {0};
    strcpy(file,folder);
    strcat(file,newpath);

    if (cf > 2048){
        printf("[!] Folder `%s` skipped due to limit\n",newpath);
        return;
    }
    //printf("\n[rDir]\n");
    //printf("|-- Path: %s\n",path);
    //printf("|-- New: %s\n",newpath);
    //printf("|-- Complete: %s\n",file);
    //printf("|-- sPath: %s\n\n",spath);
    regDir(newpath,spath);
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
            rDir(file,fp,newpath);
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
    regDir("/","/");
    char file[128] = {0};
    strcpy(file,path);
    strcat(file,sl);
    printf("[!] Folder scan mode set...\n");
    printf("| [Files]\n");
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
            regDir(fp,"/");
            rDir(path,fp,"/");
            //printf("\t Путь: %s -> %s\n",path,fp);
        } else if (de->d_type == 8){
            fileWrite(de->d_name,path,"/");
        }
    }
    closedir(dir);
    if (cf+dirs_count > 2048){
        printf("[!] [Error] Sorry, but the limit (2048) is full, choose a directory with fewer files.\n");
        return -1;
    }
    printf("| [Folder]\n");
    for(int i = 0; i < dirs_count;i++){

        headers[cf+i].index = (cf+i);
        headers[cf+i].types = 1;
        headers[cf+i].length = 0;
        off += headers[cf+i].length;
        headers[cf+i].offset = off;
        headers[cf+i].magic = 0xBF;
        headers[cf+i].parentDir = indDir[i];
        strcpy(headers[cf+i].name, dirs[(i)]);
        printf("| |-- [Folder] %s\n",dirs[(i)]);
        printf("| | |-- Local index: %d\n",i);
        printf("| | |-- Global index: %d\n",cf+i);
        printf("| | |-- Parent folder: \n");
        printf("| | | |-- Index: %d\n",indDir[i]);
        printf("| | | |-- Parent path: %s\n",dirs[indDir[i]]);
        printf("| |\n");
    }
    cf += dirs_count;
    FILE *wstream = fopen("./sayori_sefs.img", "w");
    unsigned char *data = (unsigned char *)malloc(off);
    fwrite(&cf, sizeof(int), 1, wstream);
    fwrite(headers, sizeof(struct sefs_file_header), 2048, wstream);
    cf -= dirs_count;
    printf("|-- [Write files]\n");
    for(int i = 0; i < cf; i++){
        char files[128] = {0};
        strcpy(files,path);
        strcat(files,dirs[headers[i].parentDir]);
        strcat(files,headers[i].name);
        printf("| |-- %s\n",files);
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
    printf("SayoriOS SDK - Create RamDisk (SEFS)\n\n");
    if (argc > 1 && strcmp(argv[1],"--dir") == 0){
        return dirPath(argv[2]);
    }
    printf("To use the program, specify a folder to scan.\n");
    printf("Example:\n");
    printf("  %s --dir ./initrd/ - %s\n",argv[0],"All files will be added from the initrd folder.");
    printf("\n");
    printf("The authors:\n");
    printf("* The guys from the SayoriOS team:\n");
    printf("  * pimnik98 \n");
    printf("  * NDRAEY \n");
    printf("\n");
    return 0;
}
