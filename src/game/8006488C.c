typedef struct Rgb {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Rgb;

typedef struct Row {
    int pad[2];
    int *style;
    int pad2[5];
} Row;

typedef struct Dialog {
    Row rows[1];
} Dialog;

typedef struct Object {
    char pad0[0x58];
    int human;
    char pad1[0x70 - 0x5C];
    int score;
    char pad2[0xD0 - 0x74];
    unsigned short kills;
    unsigned short deaths;
    char pad3[0x114 - 0xD4];
} Object;

typedef struct Swatch {
    int pad;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char pad2;
} Swatch;

typedef struct Rows4 {
    int index[4];
} Rows4;

extern Rows4 D_800BFEF0;
extern int D_800ABA84;
extern unsigned char D_800D2FEC;
extern unsigned char D_800D2FED;
extern char D_800AC480[];
extern char D_800AC884[];
extern char D_800AD080[];
extern char D_800AD664[];
extern char D_800AC8A0[];
extern char D_800AD064[];
extern int D_800EAF2C;
extern int D_800EADC4;
extern int D_800EADA4;
extern short D_800E52CC;
extern Object D_800E3E68[];
extern unsigned int D_800A6084[];
extern Rgb D_800ABA6C[];
extern Swatch D_800ABB00[];
extern Swatch D_800ABB20[];
extern int D_800E52F8[];
extern unsigned short D_800E5344[];
extern unsigned short D_800E5318[];
extern void func_8005A888(void);
extern void func_8006AE50(int, int, int);
extern void func_80059550(void *, void *, int);

void func_8006488C(void) {
    Rows4 rows;
    unsigned char r;
    unsigned char g;
    unsigned char b;
    char *dialog;
    char *group;
    int i;
    Object *object;

    rows = D_800BFEF0;
    r = 0;
    g = r;
    b = r;
    dialog = 0;
    group = 0;
    D_800ABA84 = 0;
    func_8005A888();
    switch (D_800D2FED) {
    case 2:
        dialog = D_800AC480;
        group = D_800AC884;
        dialog[0x3E0] = 1;
        break;
    case 3:
        dialog = D_800AD080;
        group = D_800AD664;
        dialog[0x5C0] = 1;
        break;
    case 4:
        dialog = D_800AC8A0;
        group = D_800AD064;
        dialog[0x7A0] = 1;
        break;
    }
    if (D_800D2FEC == 1) {
        *(int **)(dialog + 0x168) = &D_800EAF2C;
    } else {
        *(int **)(dialog + 0x168) = &D_800EADC4;
    }
    D_800E52CC = 1;
    for (i = 0; i < D_800D2FED; i++) {
        if (i == 127) {
            object = 0;
        } else {
            object = &D_800E3E68[i];
        }
        switch (D_800A6084[i]) {
        case 1:
            r = D_800ABA6C[5].r;
            g = D_800ABA6C[5].g;
            b = D_800ABA6C[5].b;
            break;
        case 2:
            r = D_800ABA6C[3].r;
            g = D_800ABA6C[3].g;
            b = D_800ABA6C[3].b;
            break;
        case 3:
            r = D_800ABA6C[1].r;
            g = D_800ABA6C[1].g;
            b = D_800ABA6C[1].b;
            break;
        case 4:
            r = D_800ABA6C[4].r;
            g = D_800ABA6C[4].g;
            b = D_800ABA6C[4].b;
            break;
        }
        D_800ABB00[i].r = r;
        D_800ABB00[i].g = g;
        D_800ABB00[i].b = b;
        D_800ABB20[i].r = r;
        D_800ABB20[i].g = g;
        D_800ABB20[i].b = b;
        if (object->human == 1) {
            ((Row *)(dialog + rows.index[i] * 32))->style = &D_800EADA4;
        } else {
            ((Row *)(dialog + rows.index[i] * 32))->style = 0;
        }
        D_800E52F8[i] = object->score;
        D_800E5344[i] = object->kills;
        {
            unsigned short *d = &D_800E5318[i];

            *d = object->deaths;
        }
    }
    if (D_800D2FEC == 1) {
        if (D_800E3E68[0].human == 1) func_8006AE50(2, 4, 0); else func_8006AE50(2, 3, 0);
    }
    func_80059550(group, 0, 1);
}
