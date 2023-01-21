#!/bin/bash

set -e

BASEDIR=`dirname $0`
PROJECT_PATH=`cd $BASEDIR; pwd`
SEFS_PATH=`cd $PROJECT_PATH"/Tools/Create RamDisk/SEFS/"; pwd`
SAYORI_PATH=`cd $PROJECT_PATH/; pwd`
APPS_INSTALL="python3 clang llvm grub-pc-bin xorriso mtools lld git fasm libvirt-daemon libvirt-clients bridge-utils virt-manager qemu-kvm qemu virt-manager libpng-dev"
SUDO_USER=""
PKG_MGR=""

function __noComplete(){
    if (whiptail --title  "SayoriSDK > Ошибка" --msgbox  "Извините, но данный функционал еще не реализован." 7 60); then
        $1
    else
        $1
    fi
}

function __noSayoriOSDetected(){
    if (whiptail --title  "SayoriSDK > Ошибка" --msgbox  "Извините,  но папка с SayoriOS не найдена." 7 60); then
        __menuHome
    else
        __menuHome
    fi
}

function __completeRetry(){
    if (whiptail --title  "SayoriSDK > Задача выполнена" --yes-button  "Да" --no-button  "Нет" --yesno  "Задача успешно выполнена. Выполнить другую?" 7 60); then
        __menuHome
    else
        echo "Пока"
    fi
}

function __checkSayoriOS(){
    if [ -d $PROJECT_PATH/../Sayori/ ]; then
        SAYORI_PATH=`cd $PROJECT_PATH/../Sayori/; pwd`
    elif [ -d $PROJECT_PATH/../SayoriOS/ ]; then
        SAYORI_PATH=`cd $PROJECT_PATH/../SayoriOS/; pwd`
    else
        __noSayoriOSDetected
    fi
}

function __firstFinale(){
    if (whiptail --title  "SayoriSDK > Первая настройка" --yes-button  "Да" --no-button  "Нет" --yesno  "Вроде все получилось! Попробуем запустить ОС?" 10 60); then
        __checkSayoriOS
        cd "$SAYORI_PATH"
        if ! [ -f $SAYORI_PATH/iso/boot/kernel.elf ]; then
            make bir
        else
            make run
        fi
    else
        __completeRetry
    fi
}

function __firstGit(){
    if (whiptail --title  "SayoriSDK > Первая настройка" --yes-button  "Да" --no-button  "Нет" --yesno  "Клонируем репозиторий с GitHub'a? Требуется для запуска SayoriOS " 10 60); then
        if ! [ -x "$(command -v git)" ]; then
            if (whiptail --title  "SayoriSDK > Ошибка" --msgbox  "Извините, но похоже git не установлен." 7 60); then
                echo "!!!"
            fi
        else
            if [ -d $PROJECT_PATH/../SayoriOS/ ]; then
                if (whiptail --title  "SayoriSDK > Папка найдена" --msgbox  "Мы обнаружили локальную папку." 7 60); then
                    echo "Detected SayoriOS"
                    __firstFinale
                else
                    __firstFinale
                fi
            else

                cd "$PROJECT_PATH/../"
                git clone https://github.com/pimnik98/SayoriOS.git
                __firstFinale
            fi
        fi
    else
        __firstInstallApps
    fi
}

function __checkSUDO(){
        if [ -x "$(command -v sudo)" ]; then
            SUDO="sudo"
            echo "SUDO"
        else
            SUDO=""
            echo "NOSUDO"
        fi
}

function __checkPKGMgr(){
    if [ -f /etc/debian_version ]; then
        echo "APT PKG MGR"
        $SUDO apt-get update -y
        $SUDO apt-get install -y $APPS_INSTALL
    elif [ -f /etc/redhat-release ] || [ -f /etc/centos-release ]; then
        echo "YUM PKG MGR"
        $SUDO yum update -y
        $SUDO yum install -y $APPS_INSTALL
    else
        if (whiptail --title  "SayoriSDK > Ошибка" --msgbox  "Извините, но нам не удалось определить вам менеджер пакетов." 7 60); then
            echo "!!!"
        fi
        echo "ERROR! Detect PKG-MGR"
        $SUDO apt-get update -y
        $SUDO apt-get install -y $APPS_INSTALL
    fi

}

function __firstInstallApps(){
    if (whiptail --title  "SayoriSDK > Первая настройка" --yes-button  "Да" --no-button  "Нет" --yesno  "Установим необходимое ПО? На это может потребоваться некоторое время, а также интернет соединение. " 10 60); then
        __checkSUDO
        __checkPKGMgr
        __firstGit
    else
        __menuHome
    fi
}

function __first1(){
    if (whiptail --title  "SayoriSDK > Первая настройка" --yes-button  "Да" --no-button  "Нет" --yesno  "Данную настройку рекомендуется запустить всего один. Вы готовы?" 10 60); then
        __firstInstallApps
    else
        __menuHome
    fi
}

function __sefs_build_img(){
    cd "$SEFS_PATH"
    ./scrd --dir "./initrd/"
    __completeRetry
}

function __sefs_build_app_img(){
    cd "$SEFS_PATH"
    chmod 0777 make_initrd.sh
    ./make_initrd.sh
    __completeRetry
}

function __menuSayori(){
    __checkSayoriOS
    OPTION=$(whiptail --title "SayoriSDK Лаунчер >> SayoriOS" --menu "Сделайте ваш выбор" 20 60 10 \
    "1" "Запустить SayoriOS" \
    "2" "Собрать && Запустить SayoriOS" \
    "3" "Пересобрать SayoriOS && Запустить" \
    "4" "Запустить SayoriOS Live" \
    "5" "Запустить SayoriOS UEFI" \
    "6" "Запустить SayoriOS Milla" \
    "9" "Назад" \
    "10" "Выход" 3>&1 1>&2 2>&3)
    exitstatus=$?
    if [ $exitstatus = 0 ]; then
    echo "Вы выбрали:" $OPTION
        if [ $OPTION -eq 10 ]; then
            echo "Прощайте!";
        elif [ $OPTION -eq 9 ]; then
            __menuHome
        elif [ $OPTION -eq 1 ]; then
            cd "$SAYORI_PATH"
            if ! [ -f $SAYORI_PATH/iso/boot/kernel.elf ]; then
                make bir
            else
                make run
            fi
        elif [ $OPTION -eq 2 ]; then
            cd "$SAYORI_PATH"
            make bir
        elif [ $OPTION -eq 3 ]; then
            cd "$SAYORI_PATH"
            make cir
        elif [ $OPTION -eq 4 ]; then
            cd "$SAYORI_PATH"
            make runlive
        elif [ $OPTION -eq 5 ]; then
            cd "$SAYORI_PATH"
            make genuefi && make uefilive
        elif [ $OPTION -eq 6 ]; then
            cd "$SAYORI_PATH"
            make cir && make milla
        else
            __noComplete __menuSayori
        fi
    else
    __menuHome
    fi

}

function __blank(){
    OPTION=$(whiptail --title "SayoriSDK Лаунчер" --menu "Сделайте ваш выбор" 20 60 10 \
    "1" "Собрать образ SEFS" \
    "2" "Собрать и запустить SayoriOS" \
    "3" "???" \
    "4" "???" \
    "5" "???" \
    "6" "???" \
    "7" "???" \
    "8" "???" \
    "9" "???" \
    "10" "Выход" 3>&1 1>&2 2>&3)
    exitstatus=$?
    if [ $exitstatus = 0 ]; then
    echo "Вы выбрали:" $OPTION
        if [ $OPTION -eq 10 ]; then
            echo "Прощайте!";
        elif [ $OPTION -eq 1 ]; then
            echo "2";
        else
            __noComplete __blank
        fi
    else
    __menuHome
    fi
}

function __menuSEFS(){
    OPTION=$(whiptail --title "SayoriSDK Лаунчер > Собрать образ SEFS" --menu "Сделайте ваш выбор" 20 60 10 \
    "1" "Сборка образа" \
    "2" "Скомпилировать && Сборка SEFS" \
    "3" "Скомпилировать && Сборка && Копирование" \
    "4" "Все && Запуск" \
    "10" "Назад" 3>&1 1>&2 2>&3)
    exitstatus=$?
    if [ $exitstatus = 0 ]; then
    echo "Вы выбрали:" $OPTION
        if [ $OPTION -eq 10 ]; then
            __menuHome
        elif [ $OPTION -eq 1 ]; then
            __sefs_build_img
        elif [ $OPTION -eq 2 ]; then
            __sefs_build_app_img
        elif [ $OPTION -eq 3 ]; then
            echo $SEFS_PATH
            __checkSayoriOS
            cd "$SEFS_PATH"
            chmod 0777 make_initrd.sh
            ./make_initrd.sh
            cp "$SEFS_PATH/sayori_sefs.img" "$SAYORI_PATH/iso/boot/sayori_sefs.img"
            __completeRetry
        elif [ $OPTION -eq 4 ]; then
            echo $SEFS_PATH
            __checkSayoriOS
            cd "$SEFS_PATH"
            chmod 0777 make_initrd.sh
            ./make_initrd.sh
            cp "$SEFS_PATH/sayori_sefs.img" "$SAYORI_PATH/iso/boot/sayori_sefs.img"
            cd "$SAYORI_PATH"
            make cir
        else
            __noComplete __menuSEFS
        fi
    else
    __menuHome
    fi
}

function __menuHome(){
    cd "$PROJECT_PATH"
    OPTION=$(whiptail --title "SayoriSDK Лаунчер" --menu "Сделайте ваш выбор" 20 60 10 \
    "1" "Собрать образ SEFS" \
    "2" "Собрать и запустить SayoriOS" \
    "9" "Первый запуск" \
    "10" "Выход" 3>&1 1>&2 2>&3)
    exitstatus=$?
    if [ $exitstatus = 0 ]; then
    echo "Вы выбрали:" $OPTION
        if [ $OPTION -eq 10 ]; then
            echo "Прощайте!";
        elif [ $OPTION -eq 1 ]; then
            __menuSEFS
        elif [ $OPTION -eq 2 ]; then
            __menuSayori
        elif [ $OPTION -eq 9 ]; then
            __first1
        else
            __noComplete __menuHome
            echo "3";
        fi
    else
    echo "Вы нажали отмену."
    fi
}

echo $APPS_INSTALL
__menuHome
