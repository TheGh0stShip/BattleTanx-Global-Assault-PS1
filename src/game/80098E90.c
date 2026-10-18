extern int func_800A2A98(void *, int, int, int, int, int, void *);
extern void func_80098D50(void *, int, int);
extern void func_800991E8(void);

void func_80098E90(int *p, int a1, int a2, int a3) {
    if (a3 != 0) {
        p[19] = 8;
        if (func_800A2A98(p, 0, 0, 0, 0, 1, func_800991E8) != 0) {
            return;
        }
    }
    func_80098D50(p, 1, 0);
}
