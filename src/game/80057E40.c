typedef struct {
    unsigned short tpage;
    unsigned short clut;
    unsigned char u;
    unsigned char v;
    unsigned char w;
    unsigned char h;
} Image;
typedef struct {
    unsigned char type;
    unsigned char color;
    unsigned short x;
    unsigned short y;
    short pad6;
    void *data;
    char padC[0x20 - 0xC];
} MenuItem;
typedef struct {
    unsigned short *lock;
    MenuItem *items;
    unsigned char *palette;
    char padC[0x16 - 0xC];
    unsigned short x;
    unsigned short y;
} Menu;
typedef struct {
    short font;
    short pad2;
    int scale_x;
    int scale_y;
} FontSelect;
typedef struct {
    unsigned short w;
    unsigned short h;
    char data[3];
    unsigned char enabled;
} Panel;
typedef struct {
    void *value;
    unsigned short format;
} NumberField;
typedef struct {
    unsigned char *text;
    unsigned short width;
    unsigned short align;
} TextBox;
typedef struct {
    void *image;
    short left;
    short top;
    short right;
    short bottom;
} Clip;
extern unsigned short D_800E4748;
extern unsigned short D_800A5FEC;
extern int D_800E47EC;
extern int D_800E47F0;
extern unsigned short D_800E47FC;
extern short func_80057420(unsigned char *, unsigned short, int);
extern void func_80057C30(unsigned char *, unsigned short, short, short, int, int, unsigned char *);
extern void func_80057A0C(int, unsigned short, short, short, int, int, int, unsigned char *);
extern int func_80056E48(unsigned char *, unsigned short, short, short, int, int, unsigned short, unsigned short, short, unsigned char *);
extern void func_80054F8C(short, short, unsigned short, unsigned short, void *);
extern void func_80056160(void *, short, short, int, int, unsigned char *);
extern void func_80055EA0(void *, short, short, int, int, unsigned char *);
extern void func_80056550(void *, short, short, short, short, short, short, int, int, unsigned char *);
extern void func_80056914(void *, short, short, int, int, unsigned char *);

static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult %2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high)
                     : "r"(a), "r"(b));
    return low;
}

static inline int round_fixed(int x) {
    return x >= 0 ? (x + 2048 >= 0 ? (x + 2048) >> 12 : -(-(x + 2048) >> 12))
                  : (x - 2048 >= 0 ? (x - 2048) >> 12 : -(-(x - 2048) >> 12));
}

static inline int to_int(int x) {
    return x >= 0 ? x >> 12 : -(-x >> 12);
}

static inline void draw_text(unsigned char *text, short x, short y, unsigned char *color) {
    func_80057C30(text, D_800E4748, x, y, D_800E47EC, D_800E47F0, color);
}

static inline void draw_sprite(void *image, short x, short y, unsigned char *color) {
    func_80056160(image, x, y, D_800E47EC, D_800E47F0, color);
}

static inline void draw_panel(Panel *panel, int x, int y) {
    if (panel->enabled != 0) {
        func_80054F8C(x, y, panel->w, panel->h, panel->data);
    }
}

static inline void draw_number(NumberField *field, int x, int y, unsigned char *color) {
    int value;
    void *p;

    if (field->value == 0) {
        return;
    }
    p = field->value;
    switch (field->format & 0xF0) {
    case 0:
        value = *(int *)p;
        break;
    case 48:
        value = *(unsigned short *)p;
        break;
    case 32:
        value = *(short *)p;
        break;
    case 80:
        value = *(unsigned char *)p;
        break;
    case 64:
        value = *(signed char *)p;
        break;
    case 16:
    default:
        value = *(int *)field->value;
        break;
    }
    func_80057A0C(value, D_800E4748, x, y, D_800E47EC, D_800E47F0, field->format & 3, color);
}

static inline void draw_textbox(TextBox *box, int x, int y, unsigned char *color) {
    if (box->text == 0) {
        return;
    }
    func_80056E48(box->text, D_800E4748, x, y, D_800E47EC, D_800E47F0, box->width, box->align, -1, color);
}

void func_80057E40(Menu *menu) {
    unsigned char color[4];
    MenuItem *item;
    unsigned short prev;
    unsigned short w;
    short ix;

    if (menu->lock != 0 && *menu->lock != 0) {
        return;
    }
    color[3] = 255;
    color[2] = 255;
    color[1] = 255;
    color[0] = 255;
    D_800E4748 = 0;
    D_800E47F0 = 4096;
    D_800E47EC = 4096;
    D_800E47FC = 0xFFFF;
    prev = 0xFFFF;
    for (item = menu->items; item->type != 0; item++) {
        if (item->color != 0 && item->color != prev) {
            switch (item->color) {
            case 16:
                color[0] = menu->palette[0];
                color[1] = menu->palette[1];
                color[2] = menu->palette[2];
                color[3] = menu->palette[3];
                break;
            case 144:
                color[0] = menu->palette[4];
                color[1] = menu->palette[5];
                color[2] = menu->palette[6];
                color[3] = menu->palette[7];
                break;
            case 1:
                color[0] = menu->palette[8];
                color[1] = menu->palette[9];
                color[2] = menu->palette[10];
                color[3] = menu->palette[11];
                break;
            case 2:
                color[0] = menu->palette[12];
                color[1] = menu->palette[13];
                color[2] = menu->palette[14];
                color[3] = menu->palette[15];
                break;
            case 3:
                color[0] = menu->palette[16];
                color[1] = menu->palette[17];
                color[2] = menu->palette[18];
                color[3] = menu->palette[19];
                break;
            case 4:
            default:
                color[0] = menu->palette[20];
                color[1] = menu->palette[21];
                color[2] = menu->palette[22];
                color[3] = menu->palette[23];
                break;
            }
            prev = item->color;
        }
        switch (item->type) {
        case 1:
            break;
        case 2: {
            FontSelect *sel = item->data;

            if (sel->font < 0) {
                D_800E4748 = ~sel->font;
                D_800A5FEC = 1;
            } else {
                D_800E4748 = sel->font;
                D_800A5FEC = 0;
            }
            D_800E47EC = sel->scale_x;
            D_800E47F0 = sel->scale_y;
            break;
        }
        case 3:
            draw_panel(item->data, menu->x + item->x, menu->y + item->y);
            prev = 0xFFFF;
            break;
        case 4: {
            unsigned char *text;

            if (item->data == 0) {
                break;
            }
            text = **(unsigned char ***)item->data;
            if (text == 0) {
                break;
            }
            draw_text(text, menu->x + item->x, menu->y + item->y, color);
            break;
        }
        case 24: {
            unsigned char *text = item->data;

            if (text == 0) {
                break;
            }
            draw_text(text, menu->x + item->x, menu->y + item->y, color);
            break;
        }
        case 5: {
            short px;
            unsigned char *text;

            if (item->data == 0 || **(unsigned char ***)item->data == 0) {
                break;
            }
            ix = item->x;
            px = ix - func_80057420(**(unsigned char ***)item->data, D_800E4748, D_800E47EC);
            text = **(unsigned char ***)item->data;
            draw_text(text, menu->x + px, menu->y + item->y, color);
            break;
        }
        case 6: {
            short px;
            unsigned char *text;

            if (item->data == 0 || **(unsigned char ***)item->data == 0) {
                break;
            }
            ix = item->x;
            px = ix - (func_80057420(**(unsigned char ***)item->data, D_800E4748, D_800E47EC) >> 1);
            text = **(unsigned char ***)item->data;
            draw_text(text, menu->x + px, menu->y + item->y, color);
            break;
        }
        case 23: {
            short px;
            unsigned char *text;

            if (item->data == 0) {
                break;
            }
            ix = item->x;
            px = ix - (func_80057420(item->data, D_800E4748, D_800E47EC) >> 1);
            draw_text(item->data, menu->x + px, menu->y + item->y, color);
            break;
        }
        case 7: {
            NumberField *field = item->data;

            if (field == 0) {
                break;
            }
            draw_number(field, menu->x + item->x, menu->y + item->y, color);
            break;
        }
        case 8:
            if (item->data == 0) {
                break;
            }
            draw_textbox(item->data, menu->x + item->x, menu->y + item->y, color);
            break;
        case 9: {
            void *img = item->data;

            if (img == 0) {
                break;
            }
            draw_sprite(img, menu->x + item->x, menu->y + item->y, color);
            break;
        }
        case 25: {
            void *img = item->data;

            if (img == 0) {
                break;
            }
            func_80056550(img, menu->x + item->x, menu->y + item->y, 0, 0, 159, 110, D_800E47EC,
                          D_800E47F0, color);
            break;
        }
        case 13: {
            void *img;

            if (item->data == 0) {
                break;
            }
            color[3] = 150;
            draw_sprite(item->data, menu->x + item->x, menu->y + item->y, color);
            break;
        }
        case 11: {
            void *img;

            if (item->data == 0 || (img = *(void **)item->data) == 0) {
                break;
            }
            draw_sprite(img, menu->x + item->x, menu->y + item->y, color);
            break;
        }
        case 10: {
            short px;
            void *img;

            if (item->data == 0) {
                break;
            }
            ix = item->x;
            w = round_fixed(fixed_mul(6553, (*(Image **)item->data)->w << 12));
            px = ix - (to_int(D_800E47EC * w) >> 1);
            draw_sprite(item->data, menu->x + px, menu->y + item->y, color);
            break;
        }
        case 12: {
            short px;
            void *img;

            if (item->data == 0 || *(Image **)item->data == 0) {
                break;
            }
            ix = item->x;
            w = round_fixed(fixed_mul(6553, (*(Image **)item->data)->w << 12));
            px = ix - (to_int(D_800E47EC * w) >> 1);
            img = *(Image **)item->data;
            draw_sprite(img, menu->x + px, menu->y + item->y, color);
            break;
        }
        case 22: {
            short px;
            void *img;

            if (item->data == 0 || *(Image **)item->data == 0) {
                break;
            }
            ix = item->x;
            px = ix - (to_int(D_800E47EC * (*(Image **)item->data)->w) >> 1);
            img = *(Image **)item->data;
            func_80055EA0(img, menu->x + px, menu->y + item->y, D_800E47EC, D_800E47F0, color);
            break;
        }
        case 14: {
            Clip *clip = item->data;

            if (clip == 0) {
                break;
            }
            func_80056550(clip->image, menu->x + item->x, menu->y + item->y, clip->left, clip->top, clip->right,
                          clip->bottom, D_800E47EC, D_800E47F0, color);
            break;
        }
        case 16: {
            void *img = item->data;

            if (img == 0) {
                break;
            }
            func_80056914(img, menu->x + item->x, menu->y + item->y, D_800E47EC, D_800E47F0, color);
            break;
        }
        case 21:
            if (item->data != 0) {
                ((void (*)(Menu *, MenuItem *))item->data)(menu, item);
            }
            break;
        }
    }
}
