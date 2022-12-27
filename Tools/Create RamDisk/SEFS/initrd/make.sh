#!/bin/bash
echo "    --------- C Programs"
cd src/c
make
cd ..
echo "    --------- ASM Programs"
if [ -x "$(command -v nasm)" ]; then
	nasm -felf32 src/start.asm && ld.lld-13 -Tlink.ld start.o -o start
fi
