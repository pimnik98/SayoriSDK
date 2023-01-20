# https://stackoverflow.com/questions/2672144/dump-characters-glyphs-from-truetype-font-ttf-into-bitmaps
# Duke to SFF font converter by NDRAEY 2023

from PIL import Image, ImageFont, ImageDraw
import sys
sys.path.insert(0, "../Duke/DukePy/")  # To import DukeLIB
import dukelib
import struct
import os

<<<<<<< HEAD:Tools/Fonts/main.py
ENG = ''.join([chr(i) for i in range(ord('A'), ord('Z')+1)])
ENG_low = ENG.lower()

RUS = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
RUS_low = RUS.lower()

SYMBOLS = ".,!«№;%:?*()_+-=@#$^&[]{}<>|\\/~"

Alphabet = ENG + ENG_low + RUS + RUS_low + SYMBOLS 
=======
Alphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯйцукенгшщзхъфывапролджэячсмитьбюё!«№;%:?*()_+-=@#$^&[]{}<>|\\/QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890.,";
VERSION  = 1

if not sys.argv[1:]:
    print("No arguments: .ttf file")
    exit(1)
>>>>>>> d21935d316a5da74fea35e8d4a1d48b40dee00a5:Tools/Fonts/ttf2sff1.py

# use a truetype font
font = ImageFont.truetype(sys.argv[1], 16)

size = font.getbbox(Alphabet)[2:]

glyph_box = (8, size[1])  # edit ASAP

im = Image.new("RGB", size)
draw = ImageDraw.Draw(im)

draw.rectangle([0, 0, *size], fill=(0xff, 0xff, 0xff));


draw.text((0, 0), Alphabet, font=font, fill=(0, 0, 0))

<<<<<<< HEAD:Tools/Fonts/main.py
im.save("font.png")
=======
# remove unneccessory whitespaces if needed
# im=im.crop(im.getbbox())

# write into file
im.save("tmp_font.png")

fontdata = dukelib.png2duke("tmp_font.png")

with open("font.sff1", "wb") as dk:
    dk.write(struct.pack("<3bbbb", *("SFF".encode("utf-8")), VERSION, *glyph_box))
    dk.write(fontdata)
    dk.close()

os.remove("tmp_font.png")

print("OK")
>>>>>>> d21935d316a5da74fea35e8d4a1d48b40dee00a5:Tools/Fonts/ttf2sff1.py
