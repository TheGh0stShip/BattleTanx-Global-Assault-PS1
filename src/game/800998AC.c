extern int func_800A2CB8(void *, int);
extern void func_800A2DC8(void *);
extern void func_8009940C(void *, int, int *, int, int);
extern int D_800EF170;

void func_800998AC(void *p, int a1, int a2) {
    if (func_800A2CB8(p, 0) == 0) {
        func_800A2DC8(p);
    }
    D_800EF170 = a1;
    func_8009940C(p, 10, &D_800EF170, 4, a2);
}
