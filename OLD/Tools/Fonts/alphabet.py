ENG = ''.join([chr(i) for i in range(ord('A'), ord('Z')+1)])
ENG_low = ENG.lower()

RUS = "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"
RUS_low = RUS.lower()

SYMBOLS = ".,!№;%:?*()_+-=@#$^&[]{}<>|\\/~"

Alphabet = ENG + ENG_low + RUS + RUS_low + SYMBOLS
