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
	nasm -felf32 -O1 src/start.asm
	nasm -felf32 -O1 src/nothing.asm
	ld.lld-13 -Tsrc/link.ld src/start.o -o start
	ld.lld-13 -Tsrc/link.ld src/nothing.o -o nothing
fi
