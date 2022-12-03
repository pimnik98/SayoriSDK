nasm -felf32 start.asm && ld.lld-13 -Tlink.ld start.o -o start
nasm -felf32 justexit.asm && ld.lld-13 -Tlink.ld justexit.o -o justexit
