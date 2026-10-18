typedef struct PadState {
    unsigned char ready;
    unsigned char port;
} PadState;

extern unsigned int D_800EBC3C;
extern unsigned short D_800EE02E;
extern int D_800AEB34;
extern int D_800EBC38;
extern int D_800EBC40;
extern int D_800EBC48;
extern unsigned char D_800EBC4C;
extern unsigned char D_800AEB38;
extern PadState D_800EBBB4;
extern void func_80054A30(int);

void func_80077E88(void) {
    unsigned short pad = D_800EE02E;

    switch (D_800EBC3C) {
    case 1:
        if (pad & 0x10) {
            func_80054A30(3);
            if (D_800AEB34 == 0) {
                D_800AEB34 = 2;
            } else {
                D_800AEB34--;
            }
        } else if (pad & 0x40) {
            func_80054A30(3);
            if (D_800AEB34 == 2) {
                D_800AEB34 = 0;
            } else {
                D_800AEB34++;
            }
        } else if (pad & 0x4000) {
            func_80054A30(3);
            if (D_800AEB34 == 0) {
                D_800EBC40 = 1;
                D_800AEB38 = 20;
                D_800EBBB4.port = 0;
                D_800EBC3C = 2;
            } else if (D_800AEB34 == 1) {
                D_800EBC40 = 1;
                D_800AEB38 = 20;
                D_800EBBB4.port = 16;
                D_800EBC3C = 2;
            } else {
                D_800EBC3C = 14;
            }
        }
        break;
    case 3:
        if (pad & 0xA0) {
            func_80054A30(3);
            D_800EBC38 = D_800EBC38 == 0;
        } else if (pad & 0x4000) {
            func_80054A30(3);
            if (D_800EBC38 != 0) {
                D_800EBC40 = 3;
                D_800AEB38 = 20;
                D_800EBC3C = 4;
                D_800EBC38 = 0;
            } else {
                D_800EBC3C = 1;
            }
        }
        break;
    case 5:
    case 6:
    case 9:
        if (pad & 0x4000) {
            func_80054A30(3);
            D_800EBC3C = 1;
            D_800EBC4C = 1;
        }
        break;
    case 13:
        if (pad & 0x4000) {
            func_80054A30(3);
            D_800EBC48 = 0;
            D_800EBC3C = 14;
        }
        break;
    case 0:
    case 14:
        break;
    }
}
