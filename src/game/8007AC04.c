extern char D_800AE830[];
extern char D_800AE850[];
extern char D_800AE860[];
extern char D_800AE86C[];
extern char D_800AE878[];
extern char D_800AE884[];
extern char D_800AE898[];
extern char D_800AE8A8[];
extern char D_800AE8B8[];
extern char D_800AE8C4[];
extern char D_800AE8D0[];
extern char D_800AE8DC[];
extern char D_800AE8E8[];
extern char D_800AE8F4[];
extern char D_800AE900[];
extern char D_800AE910[];
extern char D_800AE91C[];
extern char D_800AE92C[];
extern char D_800AE940[];
extern short D_800A60D8;
extern unsigned char D_800AED48[];

int func_8007AC04(char *name) {
    if (name == D_800AE830) {
        return D_800A60D8;
    }
    if (name == D_800AE850) {
        return D_800AED48[0];
    }
    if (name == D_800AE860) {
        return D_800AED48[1];
    }
    if (name == D_800AE86C) {
        return D_800AED48[2];
    }
    if (name == D_800AE878) {
        return D_800AED48[3];
    }
    if (name == D_800AE884) {
        return D_800AED48[4];
    }
    if (name == D_800AE898) {
        return D_800AED48[5];
    }
    if (name == D_800AE8A8) {
        return D_800AED48[6];
    }
    if (name == D_800AE8B8) {
        return D_800AED48[7];
    }
    if (name == D_800AE8C4) {
        return D_800AED48[8];
    }
    if (name == D_800AE8D0) {
        return D_800AED48[9];
    }
    if (name == D_800AE8DC) {
        return D_800AED48[10];
    }
    if (name == D_800AE8E8) {
        return D_800AED48[11];
    }
    if (name == D_800AE8F4) {
        return D_800AED48[12];
    }
    if (name == D_800AE900) {
        return D_800AED48[13];
    }
    if (name == D_800AE910) {
        return D_800AED48[14];
    }
    if (name == D_800AE91C) {
        return D_800AED48[15];
    }
    if (name == D_800AE92C) {
        return D_800AED48[16];
    }
    if (name == D_800AE940) {
        return D_800AED48[17];
    }
    return 0;
}
