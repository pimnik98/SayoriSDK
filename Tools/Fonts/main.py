# https://stackoverflow.com/questions/2672144/dump-characters-glyphs-from-truetype-font-ttf-into-bitmaps

from PIL import Image, ImageFont, ImageDraw

ENG = ''.join([chr(i) for i in range(ord('A'), ord('Z')+1)])
ENG_low = ENG.lower()

RUS = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
RUS_low = RUS.lower()

SYMBOLS = ".,!«№;%:?*()_+-=@#$^&[]{}<>|\\/~"

Alphabet = ENG + ENG_low + RUS + RUS_low + SYMBOLS 

# use a truetype font
font = ImageFont.truetype("font.ttf", 16)

size = font.getsize(Alphabet)

im = Image.new("RGB", size)
draw = ImageDraw.Draw(im)

draw.rectangle([0, 0, *size], fill=(0xff, 0xff, 0xff));

print(dir(font))

draw.text((0, 0), Alphabet, font=font, fill=(0, 0, 0))

im.save("font.png")
