# SayoriOS SDK - Duke - DukeC
### Инструмент для SayoriOS - Утилита преобразования DukeC - PNG to DUKE

Данная программа требует наличие `libpng` в системе

Установить можно следующим образом:

`sudo apt install libpng libpng-dev pkg-config`

Для генерации файла

`cc png2duke.c -lpng16 -o png2duke`

Пример использования:

`png2duke "../../../Files/sayori.png"`
