import png
import struct

def png2duke(filename: str) -> bytes:
    image = png.Reader(filename)
    (width,height,data,meta) = image.read_flat()
    
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

    ret = b"DUKE"
    ret += struct.pack("<HHIc", width, height, len(datanew), bytes([int(alpha)]))
    ret += bytes(datanew)

    return ret
