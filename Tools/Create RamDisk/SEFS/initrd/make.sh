#!/bin/bash
set -e 

echo "    --------- C Programs"
cd src/c
make
cd ../..
echo "    --------- C++ Programs"
cd src/cpp
make
cd ../..
echo "    --------- ASM Programs"
if [ -x "$(command -v nasm)" ]; then
	nasm -felf32 src/start.asm && ld.lld-13 -Tsrc/link.ld src/start.o -o start
fi
