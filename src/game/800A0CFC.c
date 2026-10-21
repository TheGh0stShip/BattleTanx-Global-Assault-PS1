typedef struct CdMode {
    unsigned char a;
    unsigned char b;
    unsigned char c;
} CdMode;

extern int func_80088870(int);
extern void func_80096F9C(char *);
extern void func_800943B0(char *, ...);
extern void func_800A090C(void);
extern int D_800EFCF0;
extern int D_800EFCF4;
extern char *D_800EFCF8;
extern char D_800C5F8C[];
extern char D_800C5E84[];
extern char D_800C5E94[];
extern char *D_800B8D4C[];
extern char *D_800B8DCC[];
extern unsigned char D_800B8D45;
extern volatile CdMode D_800B9004;
extern volatile unsigned int *D_800B9030;

static inline int cd_check_timeout(int limit, char **comstr, volatile CdMode *st, char **intstr) {
    if (func_80088870(-1) > D_800EFCF0 || D_800EFCF4++ > limit) {
        func_80096F9C(D_800C5E84);
        {
            register unsigned char ia asm("$4") = st->a;
            char *sb = intstr[st->b];

            func_800943B0(D_800C5E94, D_800EFCF8, comstr[D_800B8D45], intstr[ia], sb);
        }
        func_800A090C();
        return -1;
    }
    return 0;
}

int func_800A0CFC(int mode_arg) {
    register int mode asm("$18") = mode_arg;

    D_800EFCF0 = func_80088870(-1) + 960;
    D_800EFCF4 = 0;
    D_800EFCF8 = D_800C5F8C;
    do {
        if (cd_check_timeout(0x3C0000, D_800B8D4C, &D_800B9004, D_800B8DCC) != 0) {
            return -1;
        }
        if (!(*D_800B9030 & 0x01000000)) {
            return 0;
        }
    } while (mode == 0);
    return 1;
}
