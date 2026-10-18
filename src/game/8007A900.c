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
extern unsigned char D_800AED48;
extern unsigned char D_800AED49;
extern unsigned char D_800AED4A;
extern unsigned char D_800AED4B;
extern unsigned char D_800AED4C;
extern unsigned char D_800AED4D;
extern unsigned char D_800AED4E;
extern unsigned char D_800AED4F;
extern unsigned char D_800AED50;
extern unsigned char D_800AED51;
extern unsigned char D_800AED52;
extern unsigned char D_800AED53;
extern unsigned char D_800AED54;
extern unsigned char D_800AED55;
extern unsigned char D_800AED56;
extern unsigned char D_800AED57;
extern unsigned char D_800AED58;
extern unsigned char D_800AED59;

int func_8007A900(char *name) {
    if (name == D_800AE830) {
        return D_800A60D8 ^= 1;
    }
    if (name == D_800AE850) {
        D_800AED48 ^= 1;
        return D_800AED48;
    }
    if (name == D_800AE860) {
        D_800AED49 ^= 1;
        return D_800AED49;
    }
    if (name == D_800AE86C) {
        D_800AED4A ^= 1;
        return D_800AED4A;
    }
    if (name == D_800AE878) {
        D_800AED4B ^= 1;
        return D_800AED4B;
    }
    if (name == D_800AE884) {
        D_800AED4C ^= 1;
        return D_800AED4C;
    }
    if (name == D_800AE898) {
        D_800AED4D ^= 1;
        return D_800AED4D;
    }
    if (name == D_800AE8A8) {
        D_800AED4E ^= 1;
        return D_800AED4E;
    }
    if (name == D_800AE8B8) {
        D_800AED4F ^= 1;
        return D_800AED4F;
    }
    if (name == D_800AE8C4) {
        D_800AED50 ^= 1;
        return D_800AED50;
    }
    if (name == D_800AE8D0) {
        D_800AED51 ^= 1;
        return D_800AED51;
    }
    if (name == D_800AE8DC) {
        D_800AED52 ^= 1;
        return D_800AED52;
    }
    if (name == D_800AE8E8) {
        D_800AED53 ^= 1;
        return D_800AED53;
    }
    if (name == D_800AE8F4) {
        D_800AED54 ^= 1;
        return D_800AED54;
    }
    if (name == D_800AE900) {
        D_800AED55 ^= 1;
        return D_800AED55;
    }
    if (name == D_800AE910) {
        D_800AED56 ^= 1;
        return D_800AED56;
    }
    if (name == D_800AE91C) {
        D_800AED57 ^= 1;
        return D_800AED57;
    }
    if (name == D_800AE92C) {
        D_800AED58 ^= 1;
        return D_800AED58;
    }
    if (name == D_800AE940) {
        D_800AED59 ^= 1;
        return D_800AED59;
    }
    return 0;
}
