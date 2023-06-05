# https://stackoverflow.com/questions/2672144/dump-characters-glyphs-from-truetype-font-ttf-into-bitmaps
# Duke to SFF font converter by NDRAEY 2023

<<<<<<< HEAD
from PIL import Image, ImageFont, ImageDraw
import sys
sys.path.insert(0, "../Duke/DukePy/")  # To import DukeLIB
import dukelib
import struct
import os

ENG = ''.join([chr(i) for i in range(ord('A'), ord('Z')+1)])
ENG_low = ENG.lower()

RUS = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
RUS_low = RUS.lower()

SYMBOLS = ".,!«№;%:?*()_+-=@#$^&[]{}<>|\\/~"

Alphabet = ENG + ENG_low + RUS + RUS_low + SYMBOLS 
VERSION  = 1

=======
# !!!: USED ONLY FOR MONO-WIDTH FONTS

from PIL import Image, ImageFont, ImageDraw
import sys
sys.path.insert(0, ".")  # To import some external libs
sys.path.insert(0, "../Duke/DukePy/")  # To import DukeLIB
import dukelib
import alphabet
import struct
import os

Alphabet = alphabet.Alphabet
VERSION  = 1

print(Alphabet)

>>>>>>> 6b40875c0261107c794fdef5c1ec27acfe84a01e
if not sys.argv[1:]:
    print("No arguments: .ttf file")
    exit(1)

# use a truetype font
<<<<<<< HEAD
font = ImageFont.truetype(sys.argv[1], 16)

size = font.getbbox(Alphabet)[2:]

glyph_box = (8, size[1])  # edit ASAP
=======
font = ImageFont.truetype(sys.argv[1], 32)

size = font.getbbox(Alphabet)[2:]

glyph_box = (size[0] // len(Alphabet), size[1])
>>>>>>> 6b40875c0261107c794fdef5c1ec27acfe84a01e

im = Image.new("RGB", size)
draw = ImageDraw.Draw(im)

<<<<<<< HEAD
draw.rectangle([0, 0, *size], fill=(0xff, 0xff, 0xff));

=======
draw.fontmode = "1"  # Disable antialiasing

draw.rectangle([0, 0, *size], fill=(0xff, 0xff, 0xff));
>>>>>>> 6b40875c0261107c794fdef5c1ec27acfe84a01e

draw.text((0, 0), Alphabet, font=font, fill=(0, 0, 0))

# remove unneccessory whitespaces if needed
# im=im.crop(im.getbbox())

# write into file
im.save("tmp_font.png")

fontdata = dukelib.png2duke("tmp_font.png")

<<<<<<< HEAD
with open("font.sff1", "wb") as dk:
=======
wfn = '.'.join(sys.argv[1].split("/")[-1].split(".")[:-1] + ["sff1"]) 

with open(wfn, "wb") as dk:
>>>>>>> 6b40875c0261107c794fdef5c1ec27acfe84a01e
    dk.write(struct.pack("<3bbbb", *("SFF".encode("utf-8")), VERSION, *glyph_box))
    dk.write(fontdata)
    dk.close()

<<<<<<< HEAD
os.remove("tmp_font.png")

=======
# os.remove("tmp_font.png")

print(wfn)
>>>>>>> 6b40875c0261107c794fdef5c1ec27acfe84a01e
print("OK")
