typedef struct Panel {
    int pad0[2];
    int *style;
    int pad1[5];
    short pad2;
    short width;
    short height;
} Panel;

extern int D_800AB974;
extern int D_800AB97C;
extern Panel D_800AB9F4;
extern signed char D_800A606C;
extern int D_800AAD64;
extern int D_800AAD70;
extern int D_800AAD7C;
extern int D_800ABA38;
extern void func_80059550(void *, int, int);

void func_80063E3C(int a, int b, unsigned short wide) {
    D_800AB974 = a;
    D_800AB97C = b;
    if (wide) {
        D_800AB9F4.width = 80;
        D_800AB9F4.height = 30;
        D_800AB9F4.style = &D_800AAD70;
    } else if (D_800A606C == 1) {
        D_800AB9F4.height = 70;
        D_800AB9F4.style = &D_800AAD64;
    } else {
        D_800AB9F4.height = 35;
        D_800AB9F4.style = &D_800AAD7C;
    }
    func_80059550(&D_800ABA38, 0, 1);
}
