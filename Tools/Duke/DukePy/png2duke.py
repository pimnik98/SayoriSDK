import png
import sys
import struct

if not sys.argv[1:]:
    print("python3 png2duke.py image.png")
    exit(1)

image = png.Reader(sys.argv[-1])
(width,height,data,meta) = image.read_flat()

print("Meta:", meta)

print("Width:", width)
print("Height:", height)
print("Data length:", len(data))

print("Alpha:", meta['alpha'])

with open(sys.argv[-1]+".duke", 'wb') as img:
    byteng = []
    alpha = meta['alpha']
    i = 0

    # Stage 1
    datanew = data
    if 'palette' in meta:
        if len(meta['palette'][data[i]])==4:
            alpha = True
        datanew = []
        i = 0
        while i<len(data):
            datanew.extend(meta['palette'][data[i]])
            i+=1
    # Stage 2
    #if alpha:
    #    del datanew[3::4]

    img.write(b"DUKE")
    img.write(struct.pack("<HHIc", width, height, len(datanew), bytes([int(alpha)])))
    img.write(bytes(datanew))
    img.close()
