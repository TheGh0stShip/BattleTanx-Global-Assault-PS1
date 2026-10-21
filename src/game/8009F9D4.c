typedef struct {
    unsigned char sync;
    unsigned char ready;
    unsigned char c;
} CdIntr;

extern volatile unsigned char *D_800B8FEC;
extern volatile unsigned char *D_800B8FF0;
extern volatile unsigned char *D_800B8FF4;
extern volatile unsigned char *D_800B8FF8;
extern unsigned char D_800B8D45;
extern int D_800B8D30;
extern int D_800B8D34;
extern int D_800B8D38;
extern int D_800B8D3C;
extern int D_800B8DEC[];
extern int D_800B8EEC[];
extern char *D_800B8D4C[];
extern volatile CdIntr D_800B9004;
extern unsigned char D_800EFCD8[8];
extern unsigned char D_800EFCE0[8];
extern unsigned char D_800EFCE8[8];
extern char D_800C5EB0[];
extern char D_800C5EBC[];
extern char D_800C5ED8[];
extern char D_800C5EEC[];
extern int func_80096F9C(char *s);
extern int func_800943B0(char *fmt, ...);

static inline void copy_result(void *dst, void *src, unsigned int n) {
    char *d = dst;
    char *s = src;

    if (d == 0) {
        return;
    }
    while (n--) {
        *d++ = *s++;
    }
}

int func_8009F9D4(void) {
    volatile unsigned char reg;
    volatile unsigned char buf[8];
    int i;
    int j;
    int err;

    *D_800B8FEC = 1;
    reg = *D_800B8FF8 & 7;
    if (reg == 0) {
        return 0;
    }
    err = 0;
    while (reg != (*D_800B8FF8 & 7)) {
        reg = *D_800B8FF8 & 7;
    }
    for (i = 0; i < 8; i++) {
        if ((*D_800B8FEC & 0x20) == 0) {
            break;
        }
        buf[i] = *D_800B8FF0;
    }
    for (j = i; j < 8; j++) {
        buf[j] = 0;
    }
    *D_800B8FEC = 1;
    *D_800B8FF8 = 7;
    *D_800B8FF4 = 7;
    if (reg != 3 || D_800B8EEC[D_800B8D45]) {
        if (!(D_800B8D34 & 0x10) && (buf[0] & 0x10)) {
            D_800B8D3C++;
        }
        D_800B8D34 = buf[0];
        D_800B8D38 = buf[1];
        err = D_800B8D34;
        err &= 0x1D;
    }
    if (reg == 5 && D_800B8D30 > 0) {
        func_800943B0(D_800C5EB0);
        if (D_800B8D30 > 0) {
            func_800943B0(D_800C5EBC, D_800B8D4C[D_800B8D45], D_800B8D34, D_800B8D38);
        }
    }
    switch (reg) {
    case 3:
        if (err) {
            D_800B9004.sync = 5;
            copy_result(D_800EFCD8, (void *)buf, 8);
            return 2;
        }
        if (D_800B8DEC[D_800B8D45]) {
            D_800B9004.sync = 3;
            copy_result(D_800EFCD8, (void *)buf, 8);
            return 1;
        }
        D_800B9004.sync = 2;
        copy_result(D_800EFCD8, (void *)buf, 8);
        return 2;
    case 2:
        D_800B9004.sync = err ? 5 : 2;
        copy_result(D_800EFCD8, (void *)buf, 8);
        return 2;
    case 1:
        if (err && i == 1) {
            err = 0;
        }
        {
            volatile CdIntr *p = &D_800B9004;
            p->ready = err ? 5 : 1;
        }
        copy_result(D_800EFCE0, (void *)buf, 8);
        *D_800B8FEC = 0;
        *D_800B8FF8 = 0;
        return 4;
    case 4:
        {
            volatile CdIntr *p = &D_800B9004;
            p->ready = p->c = 4;
        }
        copy_result(D_800EFCE8, (void *)buf, 8);
        copy_result(D_800EFCE0, (void *)buf, 8);
        return 4;
    case 5:
        D_800B9004.sync = D_800B9004.ready = 5;
        copy_result(D_800EFCD8, (void *)buf, 8);
        copy_result(D_800EFCE0, (void *)buf, 8);
        return 6;
    default:
        func_80096F9C(D_800C5ED8);
        func_800943B0(D_800C5EEC, reg);
        return 0;
    }
}
