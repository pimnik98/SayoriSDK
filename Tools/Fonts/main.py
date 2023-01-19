# https://stackoverflow.com/questions/2672144/dump-characters-glyphs-from-truetype-font-ttf-into-bitmaps

from PIL import Image, ImageFont, ImageDraw

Alphabet = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯйцукенгшщзхъфывапролджэячсмитьбюё!«№;%:?*()_+-=@#$^&[]{}<>|\\/QWERTYUIOPASDFGHJKLZXCVBNMqwertyuiopasdfghjklzxcvbnm1234567890.,";

# use a truetype font
font = ImageFont.truetype("font.ttf", 16)

size = font.getsize(Alphabet)

im = Image.new("RGB", size)
draw = ImageDraw.Draw(im)

draw.rectangle([0, 0, *size], fill=(0xff, 0xff, 0xff));

print(dir(font))

draw.text((0, 0), Alphabet, font=font, fill=(0, 0, 0))

# remove unneccessory whitespaces if needed
# im=im.crop(im.getbbox())

# write into file
im.save("font.png")
