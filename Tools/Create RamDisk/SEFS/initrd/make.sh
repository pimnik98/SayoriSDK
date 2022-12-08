#!/bin/bash
echo "    --------- C Programs"
cd test
make
cd ..
echo "    --------- ASM Programs"
if ! [ -x "$(command -v nasm)" ]; then
  echo 'Error: nasm is not installed.' >&2
  exit 1
fi
nasm -felf32 start.asm && ld.lld-13 -Tlink.ld start.o -o start
nasm -felf32 justexit.asm && ld.lld-13 -Tlink.ld justexit.o -o justexit
