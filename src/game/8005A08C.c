typedef struct {
    unsigned short flags;
    char pad2[0x10 - 2];
} Channel;
typedef struct {
    char pad0[6];
    unsigned short pressed;
    char pad8[0x8C - 8];
} Pad;
typedef struct {
    int state;
} Result;
extern Channel D_800E474C[];
extern int D_800C60E4;
extern int D_800C60D8;
extern unsigned int D_800C60D0;
extern int D_800C60C8;
extern int D_800C60DC;
extern unsigned char D_800AE9EA;
extern unsigned char D_800AEA46;
extern unsigned char D_800AACD9;
extern unsigned char D_800AACDA;
extern unsigned char D_800AAD00;
extern Pad D_800EE028[];
extern Result *func_8006A7FC(void);
extern void func_8003A200(int);
extern void func_8005ACC4(void);
extern void func_8007646C(void);
extern void func_8006AAA0(void);
extern void func_8005EE24(void);
extern unsigned char func_800229F8(void);
extern void func_80059BB8(void);
extern void func_80059DB4(void);

void func_8005A08C(void) {
    if (D_800C60E4 == 0 || D_800C60D8 == 0) {
        unsigned short i;

        for (i = 0; i < 10; i++) {
            D_800E474C[i].flags = 0;
        }
        switch (D_800C60D0) {
        case 4:
            if (func_8006A7FC()->state == 3) {
                func_8003A200(5);
            }
            break;
        case 2:
            func_8005ACC4();
            break;
        case 0:
        case 1:
        case 3:
            break;
        }
    }
    if (D_800C60D0 - 3 < 2 || D_800C60D0 == 10) {
        if (D_800AE9EA != 0) {
            func_8007646C();
        }
        switch (D_800C60D0) {
        case 3:
            func_8006AAA0();
            break;
        case 4:
            func_8005EE24();
            break;
        case 10:
            D_800C60C8 = 0;
            D_800C60DC = 2;
            D_800AEA46 = 100;
            break;
        }
        return;
    }
    {
        Pad *pad = D_800EE028;

        if (pad[0].pressed & 0x2000) {
            D_800AACD9 ^= 1;
        }
        if (pad[1].pressed & 0x2000) {
            D_800AACDA ^= 1;
        }
    }
    if (D_800AAD00 == 0) {
        if (func_800229F8() == 0) {
            func_80059BB8();
        }
        func_80059DB4();
    }
}
