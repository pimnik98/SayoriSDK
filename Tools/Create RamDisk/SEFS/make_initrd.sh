#!/bin/bash

set -e

BASEDIR=`dirname $0`
PROJECT_PATH=`cd $BASEDIR; pwd`

#echo 'Using path: ' $PROJECT_PATH

<<<<<<< HEAD
echo "--------- Building Programs"
cd initrd && bash make.sh
rm initrd/start.o || true
=======
# echo "--------- Building Programs"
# cd initrd && bash make.sh
# rm initrd/start.o || true
>>>>>>> 6b40875c0261107c794fdef5c1ec27acfe84a01e
echo "--------- Building Initrd Builder"
cd "$PROJECT_PATH"
make
echo "--------- Packing..."
./scrd --dir ./initrd
