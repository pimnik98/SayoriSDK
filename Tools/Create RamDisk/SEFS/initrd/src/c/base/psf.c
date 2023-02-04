#include <psf.h>

uint32_t psf_font_version = 0;

static psf_t *_font_ptr = NULL;
static bool _init = false;
static uint8_t _w = 8;
static uint8_t _h = 0;
uint8_t* first_glyph = 0;

uint16_t *unicode;

bool text_init(char* psf){
    FILE* psf_file = fopen(psf,"r");
    if (ferror(psf_file) != 0){
        qemu_log("[Core] [PSF] Не удалось найти файл `%s`. \n",psf);
        return false;
    }

    fseek(psf_file, 0, SEEK_END);
    size_t rfsize = ftell(psf_file);
    fseek(psf_file, 0, SEEK_SET);

    char* buffer = kmalloc(rfsize);
    fread_c(psf_file, rfsize, 1, buffer);
    fclose(psf_file);

    psf_t *header = (psf_t*)buffer;
    _init = false;
    _w = 0;
    _h = 0;
    if (header->magic[0] != PSF1_MAGIC0 || header->magic[1] != PSF1_MAGIC1){
        qemu_log("PSF Header Error");
        return false;
    }
    _font_ptr = (psf_t*)buffer;
    _w = 8;
    _h = header->charHeight;
    _init = true;
    first_glyph = (uint8_t*)_font_ptr+sizeof(psf_t);
    return _init;
}

size_t psf1_get_w(){
    return _w;
}

size_t psf1_get_h(){
    return _h;
}

uint16_t psf1_rupatch(uint16_t c,uint16_t c2){
    if (!isUTF(c)) return c;
    if ((c & 0x1F) != 16 && (c & 0x1F) != 17) return c;
    uint16_t x = (c2 & 0x3F);
    uint16_t lS = 224;
    uint16_t bS = 128;
     switch(x){
        case  1: return ((c & 0x1F) == 16?lS+16:lS+1);
        case 17: return ((c & 0x1F) == 17?lS+17:bS+1);
        case  0: return lS+0;     case 22: return bS+6;     case 42: return bS+26;
        case  2: return lS+2;     case 23: return bS+7;     case 43: return bS+27;
        case  3: return lS+3;     case 24: return bS+8;     case 44: return bS+28;
        case  4: return lS+4;     case 25: return bS+9;     case 45: return bS+29;
        case  5: return lS+5;     case 26: return bS+10;    case 46: return bS+30;
        case  6: return lS+6;     case 27: return bS+11;    case 47: return bS+31;
        case  7: return lS+7;     case 28: return bS+12;    case 48: return bS+32;
        case  8: return lS+8;     case 29: return bS+13;    case 49: return bS+33;
        case  9: return lS+9;     case 30: return bS+14;    case 50: return bS+34;
        case 10: return lS+10;    case 31: return bS+15;    case 51: return bS+35;
        case 11: return lS+11;    case 32: return bS+16;    case 52: return bS+36;
        case 12: return lS+12;    case 33: return bS+17;    case 53: return bS+37;
        case 13: return lS+13;    case 34: return bS+18;    case 54: return bS+38;
        case 14: return lS+14;    case 35: return bS+19;    case 55: return bS+39;
        case 15: return lS+15;    case 36: return bS+20;    case 56: return bS+40;
        case 16: return bS+0;     case 37: return bS+21;    case 57: return bS+41;
        case 18: return bS+2;     case 38: return bS+22;    case 58: return bS+42;
        case 19: return bS+3;     case 39: return bS+23;    case 59: return bS+43;
        case 20: return bS+4;     case 40: return bS+24;    case 60: return bS+44;
        case 21: return bS+5;     case 41: return bS+25;    case 61: return bS+45;
        case 62: return bS+46;    case 63: return bS+47;
        default: return 1;
    }
}

uint8_t *psf1_get_glyph(uint16_t ch){
    psf_t *header = (psf_t*)_font_ptr;

    if ((ch > 511) || (ch > 255 && (header->mode == 0 || header->mode == 2))){
        qemu_log("[PSF] DEAD >>> %d (returning nullptr)", ch);
        return 0;
    }
    //qemu_log("\t\t >[PSF] C:%c=%d p:%d h:%d a:%d",ch,ch,ch*_h,_h,((ch*_h)/8));
    return ((uint8_t*)_font_ptr+sizeof(psf_t)+(ch*_h));
}

void draw_vga_ch(uint16_t c, uint16_t c2, int pos_x, int pos_y, int color) {
    char mask[8] = {128,64,32,16,8,4,2,1};
    uint8_t *glyph = psf1_get_glyph(psf1_rupatch(c, c2));

    for (size_t y = 0; y < _h; y++){
        for (size_t x = 0; x < _w; x++){
            if (glyph[y] & mask[x]) {
                set_pixel(pos_x+x, pos_y+y, color);
            }
        }
    }
}

void draw_vga_str(const char* text, size_t len, int x, int y, int color){
    size_t scrwidth = getWidthScreen();
    for(int i = 0; i < len; i++){
        if (x+8 <= scrwidth){
            if (isUTF(text[i])){
                draw_vga_ch(text[i], text[i+1], x, y, color);
                i++;
            } else {
                draw_vga_ch(text[i], 0, x, y, color);
            }
            x+= 8;
        } else {
            break;
        }
    }
}
