extern void func_8008AA48(void *, int, int);
extern int func_800A2C10(void *, int, int, int, void *);
extern void func_80098D50(void *, int, int);
extern void func_80099104(void *, unsigned char, int, int);
extern void func_800990E0(void *, unsigned char, int, int);
extern void func_80099044(void *, unsigned char, int, int);
extern void func_80098FBC(void *, unsigned char, int, int);
extern void func_80098EFC(void *, unsigned char, int, int);
extern void func_80098E90(void *, unsigned char, int, int);
extern void func_80098E30(void *, unsigned char, int, int);
extern void func_80098E0C(void *, unsigned char, int, int);

typedef struct Req80099164 {
    char pad0[76];
    unsigned int state;
    char pad80[4];
    int flushed;
    unsigned char kind;
    char pad89[11];
    int arg100;
    char pad104[4];
    int arg108;
    void (*flush)(struct Req80099164 *, int, int);
} Req80099164;
extern Req80099164 *D_800EF124;

void func_800991E8(int unused, unsigned char kind, int a2, int a3, int a4);

void func_80099164(Req80099164 *p, unsigned char kind, int a2, int go) {
    if (go != 0) {
        if (p->flush != 0) {
            p->flush(p, 1, 0);
            p->flushed = 1;
        }
        p->state = 2;
        if (func_800A2C10(p, p->kind, p->arg100, p->arg108, func_800991E8) != 0) {
            return;
        }
    }
    func_80098D50(p, 0, 0);
}

void func_800991E8(int unused, unsigned char kind, int a2, int a3, int a4) {
    Req80099164 *p = D_800EF124;

    if (p == 0) {
        return;
    }
    switch (p->state) {
    case 1:
        func_80099164(p, kind, a3, a4);
        break;
    case 2:
        func_80099104(p, kind, a3, a4);
        break;
    case 3:
        func_800990E0(p, kind, a3, a4);
        break;
    case 4:
        func_80099044(p, kind, a3, a4);
        break;
    case 5:
        func_80098FBC(p, kind, a3, a4);
        break;
    case 6:
        func_80098EFC(p, kind, a3, a4);
        break;
    case 7:
        func_80098E90(p, kind, a3, a4);
        break;
    case 8:
        func_80098E30(p, kind, a3, a4);
        break;
    case 9:
        func_80098E0C(p, kind, a3, a4);
        break;
    case 0:
    default:
        func_80098D50(p, 2, 0);
        break;
    }
}

void func_800992E0(void) {
    func_8008AA48(&D_800EF124, 0, 88);
}
