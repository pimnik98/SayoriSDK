import sys
sys.path.insert(0, ".")
import alphabet

cbody = "uint16_t alphabet_sff1[%d] = {%s\n};"

symtable = []

for i in alphabet.Alphabet:
    if ord(i) > 255:
        i = ord(i)
    if i == "\\":
        i *= 2
    
    i = ("\'" + i + "\'") if type(i) is str else str(i)
    symtable.append(i)

def symbol2c(symbol):
    if symbol == "\\":
        symbol *= 2
    return symbol

def pretty_make(st):
    a = ""
    width = 8
    i = 0

    while i < len(st):
        if i % width == 0:
            a += "\n"
        a += symbol2c(st[i]) + (", " if i < len(st) - 1 else " ")
        i += 1
    return a

print(cbody % (len(symtable), pretty_make(symtable)))
