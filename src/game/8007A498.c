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
extern char D_800AE840[];
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
extern char *D_800AECF8[];
extern void func_80060B54(int);
extern int func_8006A388(char *);

char *func_8007A498(char *code) {
    unsigned short i;
    unsigned short match;
    char *p;
    char *q;

    for (i = 0; i < 19; i++) {
        p = code;
        q = D_800AECF8[i];
        match = 1;
        while (*p != 0) {
            if (*q == 0) {
                break;
            }
            if (*p != *q) {
                match = 0;
                break;
            }
            p++;
            q++;
        }
        if (!match || *p != 0 || *q != 0) {
            continue;
        }
        switch (i) {
        case 0:
            D_800A60D8 = (D_800A60D8 ^ 1) | 4;
            func_80060B54((unsigned char)D_800A60D8);
            return D_800AE830;
        case 1:
            D_800AED48 = (D_800AED48 ^ 1) | 4;
            func_80060B54(D_800AED48);
            return D_800AE850;
        case 2:
            D_800AED49 = (D_800AED49 ^ 1) | 4;
            func_80060B54(D_800AED49);
            return D_800AE860;
        case 3:
            D_800AED4A = (D_800AED4A ^ 1) | 4;
            func_80060B54(D_800AED4A);
            return D_800AE86C;
        case 4:
            D_800AED4B = (D_800AED4B ^ 1) | 4;
            func_80060B54(D_800AED4B);
            return D_800AE878;
        case 5:
            D_800AED4C = (D_800AED4C ^ 1) | 4;
            func_80060B54(D_800AED4C);
            return D_800AE884;
        case 6:
            D_800AED4D = D_800AED4D ^ 1;
            func_80060B54(D_800AED4D);
            return D_800AE898;
        case 7:
            D_800AED4E = D_800AED4E ^ 1;
            func_80060B54(D_800AED4E);
            return D_800AE8A8;
        case 8:
            D_800AED4F = (D_800AED4F ^ 1) | 4;
            func_80060B54(D_800AED4F);
            return D_800AE8B8;
        case 9:
            D_800AED50 = (D_800AED50 ^ 1) | 4;
            func_80060B54(D_800AED50);
            return D_800AE8C4;
        case 10:
            D_800AED51 = (D_800AED51 ^ 1) | 4;
            func_80060B54(D_800AED51);
            return D_800AE8D0;
        case 11:
            D_800AED52 = (D_800AED52 ^ 1) | 4;
            func_80060B54(D_800AED52);
            return D_800AE8DC;
        case 12:
            D_800AED53 = (D_800AED53 ^ 1) | 4;
            func_80060B54(D_800AED53);
            return D_800AE8E8;
        case 13:
            D_800AED54 = (D_800AED54 ^ 1) | 4;
            func_80060B54(D_800AED54);
            return D_800AE8F4;
        case 14:
            D_800AED55 = (D_800AED55 ^ 1) | 4;
            func_80060B54(D_800AED55);
            return D_800AE900;
        case 15:
            D_800AED56 = (D_800AED56 ^ 1) | 4;
            func_80060B54(D_800AED56);
            return D_800AE910;
        case 16:
            D_800AED57 = (D_800AED57 ^ 1) | 4;
            func_80060B54(D_800AED57);
            return D_800AE91C;
        case 17:
            D_800AED58 = (D_800AED58 ^ 1) | 4;
            func_80060B54(D_800AED58);
            return D_800AE92C;
        case 18:
            D_800AED59 = (D_800AED59 ^ 1) | 4;
            func_80060B54(D_800AED59);
            return D_800AE940;
        }
        return 0;
    }
    for (i = 0; i < 10; i++) {
        if (*code == 0) {
            return 0;
        }
    }
    if (func_8006A388(code)) {
        return D_800AE840;
    }
    return 0;
}
