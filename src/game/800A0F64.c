typedef struct CdMode {
    unsigned char a;
    unsigned char b;
    unsigned char c;
} CdMode;

typedef void (*CdCallback)(int, unsigned char *);

extern volatile unsigned char *D_800B8FEC;
extern volatile unsigned char *D_800B8FF8;
extern volatile unsigned int *D_800B8FFC;
extern volatile unsigned int *D_800B9020;
extern volatile unsigned int *D_800B9024;
extern volatile unsigned int *D_800B9028;
extern volatile unsigned int *D_800B902C;
extern volatile unsigned int *D_800B9030;
extern int D_800B8FD0;
extern CdCallback D_800B8D28;
extern CdCallback D_800B8D24;
extern unsigned char D_800EFCE0[];
extern unsigned char D_800EFCD8[];
extern CdMode D_800B9004;
extern int func_8009F9D4(void);

int func_800A0F64(unsigned int *buf, int words) {
    volatile unsigned int dummy;

    *D_800B8FEC = 0;
    *D_800B8FF8 = 0x80;
    *D_800B9020 = 0x21020843;
    *D_800B8FFC = 0x1325;
    *D_800B9024 |= 0x8000;
    *D_800B9028 = (unsigned int)buf;
    *D_800B902C = words | 0x10000;
    while (!(*D_800B8FEC & 0x40)) {
    }
    *D_800B9030 = 0x11400100;
    dummy = *D_800B9030;
    return 0;
}

void func_800A1050(int value) {
    D_800B8FD0 = value;
}

void func_800A105C(void) {
    unsigned char *intr = &D_800B9004.b;
    unsigned char *sync = &D_800B9004.a;
    int saved = *D_800B8FEC & 3;
    int flags;

    while ((flags = func_8009F9D4()) != 0) {
        if (flags & 4) {
            if (D_800B8D28 != 0) {
                D_800B8D28(*intr, D_800EFCE0);
            }
        }
        if (flags & 2) {
            if (D_800B8D24 != 0) {
                D_800B8D24(*sync, D_800EFCD8);
            }
        }
    }
    *D_800B8FEC = saved;
}
