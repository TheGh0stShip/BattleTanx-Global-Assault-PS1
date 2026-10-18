extern int D_800A4B20;
extern char D_800DE068[];
extern int D_800DE0C8;
void func_8008314C(void *, int);
void func_80082798(void *, int, int);
void func_80082854(void *, int, int);

void func_8003DF4C(void) {
    if (D_800A4B20 == 0) {
        func_8008314C(D_800DE068, 1);
        func_80082798(D_800DE068, 0, 0);
        func_80082854(D_800DE068, D_800DE0C8, 0x70830);
        D_800A4B20++;
    }
}
