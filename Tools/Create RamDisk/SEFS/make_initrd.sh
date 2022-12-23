#!/bin/bash

set -e

BASEDIR=`dirname $0`
PROJECT_PATH=`cd $BASEDIR; pwd`

#echo 'Using path: ' $PROJECT_PATH

echo "--------- Building Programs"
cd initrd && bash make.sh
rm initrd/start.o || true
echo "--------- Building Initrd Builder"
cd "$PROJECT_PATH"
make
echo "--------- Packing..."
./scrd --dir ./initrd
