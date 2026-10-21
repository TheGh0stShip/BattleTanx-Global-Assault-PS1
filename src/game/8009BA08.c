typedef unsigned short SectorHeader;

extern SectorHeader *D_800EF1E8;
extern int D_800EF22C;
extern void (*D_800EF1FC)(void);
extern int D_800EF200;
extern int D_800EF204;
extern int D_800EF208;
extern int D_800EF20C;
extern int D_800EF210;
extern int D_800EF214;
extern int D_800EF218;
extern int D_800EF21C;
extern int D_800EF220;
extern short D_800EF224;
extern int D_800EF228;
extern SectorHeader *D_800EF230;
extern int D_800EF234;
extern int D_800EF238;
extern int D_800EF240;
extern int D_800EF244;

typedef struct Loc4 {
    unsigned char b[4];
} Loc4;

extern volatile unsigned int *D_800B8A2C;
extern int D_800B8A54;
extern volatile unsigned char *D_800B8A0C;
extern volatile unsigned char *D_800B8A18;
extern volatile unsigned int *D_800B8A1C;
extern volatile unsigned int *D_800B8A20;
extern int D_800EFD08;
extern volatile unsigned char *D_800B8A14;
extern volatile unsigned int *D_800B8A3C;

extern int func_800970F4(int mode, unsigned char *result);
extern void func_8009C324(void *dst, void *src, int count, int last);
extern void func_8009C350(int ch, void *dst, int a, int count, int mode, int last, int c);
extern void func_800A2FB0(int start, int count);
extern void func_800A2FF0(void);

void func_8009BA08(void) {
    volatile unsigned short spare;
    volatile unsigned short status;
    volatile unsigned short status2;
    Loc4 loc;
    unsigned char result[8];
    unsigned int i;
    int mode;
    SectorHeader *hdr;

    if (D_800EF228 == 1) {
        return;
    }
    if (D_800EF214 != 0 && (*D_800B8A2C & 0x01000000)) {
        D_800EF204 = 1;
        if (D_800EF200 != 0) {
            D_800EF220++;
        }
        D_800B8A54 = 1;
        return;
    }
    if (func_800970F4(1, result) == 5) {
        return;
    }
    status = result[0];
    status2 = result[1];
    if (status & 4) {
        D_800B8A54 = 3;
        return;
    }
    hdr = &D_800EF230[D_800EF234 * 16];
    D_800EF1E8 = hdr;
    if (hdr[0] != 0) {
        if (D_800EF200 != 0) {
            D_800EF220++;
        }
        D_800B8A54 = 4;
        return;
    }
    *D_800B8A0C = 0;
    *D_800B8A18 = 0;
    *D_800B8A0C = 0;
    *D_800B8A18 = 0x80;
    *D_800B8A1C = 0x20943;
    *D_800B8A20 = 0x1323;
    i = 0;
    if (D_800EFD08 == 0) {
        for (; i < 4; i++) {
            loc.b[i] = *D_800B8A14;
        }
        for (i = 0; i < 8; i++) {
            *D_800B8A14;
        }
    }
    mode = 0x11000000;
    if (D_800EF200 != 0) {
        func_8009C324(D_800EF1E8, (char *)D_800EF200 + (D_800EF220 << 11), 8, 0);
    } else {
        func_8009C350(3, D_800EF1E8, 0, 8, mode, 0, 0);
    }
    while (*D_800B8A3C & 0x01000000) {
    }
    {
        volatile unsigned int *r = D_800B8A1C;
        *(Loc4 *)(D_800EF1E8 + 14) = loc;
        *r = 0x20843;
    }
    *D_800B8A20 = 0x1325;
    if (D_800EF21C == 1 && D_800EF244 != 0) {
        if (D_800EF244 != D_800EF1E8[4]) {
            D_800EF1E8[0] = 0;
            if (D_800EF200 != 0) {
                D_800EF220++;
            }
            return;
        }
        D_800EF21C = 0;
    }
    if (D_800EF1E8[0] != 0x160 || ((D_800EF1E8[1] >> 10) & 0x1F) != D_800EF208) {
        if (D_800EF200 != 0) {
            D_800EF220 = 0;
        } else {
            *(volatile unsigned short *)D_800EF1E8;
        }
        D_800B8A54 = 5;
        D_800EF1E8[0] = 0;
        return;
    }
    if (D_800EF224 != D_800EF1E8[2] || (D_800EF210 != 0 && D_800EF210 != D_800EF1E8[4])) {
        D_800EF210 = 0;
        D_800EF224 = 0;
        func_800A2FB0(D_800EF238, D_800EF234 - D_800EF238);
        D_800EF234 = D_800EF238;
        D_800EF1E8[0] = 0;
        if (D_800EF200 != 0) {
            D_800EF220++;
        }
        D_800B8A54 = 6;
        return;
    }
    if (D_800EF1E8[2] == 0) {
        D_800EF224 = 0;
        D_800EF210 = ((volatile unsigned short *)D_800EF1E8)[4];
        if (D_800EF218 != 0 && !((unsigned int)D_800EF210 < (unsigned int)D_800EF218)) {
            D_800EF210 = 0;
            D_800EF224 = 0;
            func_800A2FB0(D_800EF238, D_800EF234 - D_800EF238);
            D_800EF234 = D_800EF238;
            D_800EF1E8[0] = 0;
            D_800EF21C = 1;
            if (D_800EF1FC != 0) {
                D_800EF1FC();
            }
            if (D_800EF200 != 0) {
                D_800EF220++;
            }
            D_800B8A54 = 7;
            return;
        }
        if ((unsigned int)(D_800EF240 - D_800EF234 - 1) < D_800EF1E8[3]) {
            if (D_800EF218 == 0) {
                D_800EF1E8[0] = 1;
                D_800EF21C = 1;
                if (D_800EF1FC != 0) {
                    D_800EF1FC();
                }
                if (D_800EF200 != 0) {
                    D_800EF220++;
                }
                D_800B8A54 = 8;
                return;
            }
            if (*(short *)D_800EF230 != 0) {
                D_800EF1E8[0] = 0;
                if (D_800EF200 != 0) {
                    D_800EF220++;
                }
                D_800B8A54 = 9;
                return;
            }
            {
                unsigned int *dst;
                unsigned int *src;
                D_800EF1E8[0] = 1;
                dst = (unsigned int *)D_800EF230;
                src = (unsigned int *)D_800EF1E8;
                D_800EF234 = 0;
                for (i = 0; i < 8; i++) {
                    *dst++ = *src++;
                }
                D_800EF1E8 = D_800EF230;
            }
        }
        D_800EF238 = D_800EF234;
    }
    D_800B8A54 = 10;
    D_800EF224++;
    D_800EF22C = (int)D_800EF230 + (D_800EF240 << 5) + D_800EF234 * 0x7E0;
    mode = 0x11000000;
    if (D_800EF214 != 0) {
        *D_800B8A1C = 0x20943;
        *D_800B8A20 = 0x1323;
    } else {
        *D_800B8A1C = 0x21020843;
        mode = 0x11400100;
    }
    if (D_800EF1E8[3] - 1 == D_800EF1E8[2]) {
        D_800EF228 = 1;
        if (D_800EF200 != 0) {
            func_8009C324((void *)D_800EF22C, (char *)D_800EF200 + (D_800EF220 << 11) + 32, 504, 1);
            D_800EF220++;
        } else {
            func_8009C350(3, (void *)D_800EF22C, 0, 504, mode, 1, 0);
        }
        D_800EF224 = 0;
        D_800EF210 = 0;
        D_800EF208 = D_800EF20C;
    } else {
        if (D_800EF200 != 0) {
            func_8009C324((void *)D_800EF22C, (char *)D_800EF200 + (D_800EF220 << 11) + 32, 504, 0);
            D_800EF220++;
        } else {
            func_8009C350(3, (void *)D_800EF22C, 0, 504, mode, 0, 0);
        }
    }
    *D_800B8A20 = 0x1325;
    D_800EF1E8[0] = 3;
    D_800EF234++;
    if (D_800EF200 != 0 && D_800EF228 != 0) {
        func_800A2FF0();
    }
}
