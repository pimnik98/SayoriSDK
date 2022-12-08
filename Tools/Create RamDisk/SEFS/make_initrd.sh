echo "--------- Building Programs"
cd initrd && bash make.sh && cd ..
echo "--------- Building Initrd Builder"
make
echo "--------- Packing..."
./scrd --dir initrd
