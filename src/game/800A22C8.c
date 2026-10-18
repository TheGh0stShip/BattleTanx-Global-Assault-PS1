extern int func_8008FF1C(int, int, int, void *, int, void *);
extern void func_800A19E4(int);
extern char D_800EFE0F[];
extern void func_800A1994(void);

void func_800A22C8(int *p) {
    p[2] = 5;
    p[8] = 0;
    if (func_8008FF1C(10, p[0], 0, D_800EFE0F, 1, func_800A1994) == 0) {
        func_800A19E4(0);
    }
}
