#!/bin/bash
echo "    --------- C Programs"
cd test
make
cd ..
echo "    --------- ASM Programs"
if [ -x "$(command -v nasm)" ]; then
	nasm -felf32 start.asm && ld.lld-13 -Tlink.ld start.o -o start
fi
