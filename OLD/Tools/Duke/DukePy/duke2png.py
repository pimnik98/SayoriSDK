import png
import sys
import struct

if not sys.argv[1:]:
    print("python3 raw2png.py image.png")
    exit(1)

with open(sys.argv[-1], "rb") as file:
    magic = file.read(4)

    if magic != b'DUKE':
        print("Not a DUKE file!!!")
        exit(1)
    
    width = int.from_bytes(file.read(2), "little")
    height = int.from_bytes(file.read(2), "little")
    length = int.from_bytes(file.read(4), "little")
    alpha = int.from_bytes(file.read(1), "little")
    print(width, height, length)
    data = file.read(length)

    normdata = []

    for y in range(height):
        if alpha:
            normdata.append(list(data[y*4*width:(y+1)*4*width]))
        else:
            normdata.append(list(data[y*3*width:(y+1)*3*width]))

    f = open(sys.argv[1]+"1.png", 'wb')
    w = png.Writer(width, height, greyscale=False, alpha=bool(alpha))
    w.write(f, normdata)
    f.close()
    file.close()
