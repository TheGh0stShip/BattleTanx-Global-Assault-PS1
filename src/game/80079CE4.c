typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char code;
} Color;

extern int D_800AEC48;
extern int D_800C60CC;
extern short D_800DDC58;
extern char *D_800AE958;
extern char *D_800AE95C;
extern char *D_800AE960;
extern void *func_8008AA48(void *, int, int);
extern void func_80057C30(char *, int, int, int, int, int, Color *);
extern void func_80054F8C(int, int, int, int, Color *);

void func_80079CE4(int mask) {
    Color bright = {120, 120, 0, 255};
    Color dim = {160, 24, 8, 255};
    Color black;

    func_8008AA48(&black, 0, 4);
    black.code = 255;
    {
    Color box = {24, 24, 24, 255};
    Color clear;
    register int m asm("$19");

    func_8008AA48(&clear, 0, 4);
    m = mask;
    __asm__("" : "+r"(m));
    D_800AEC48++;
    if (D_800C60CC == 0 || D_800DDC58 == 320) {
        if (mask & 1) {
            func_80057C30(D_800AE958, 2, 89, 42, 3891, 3891, (D_800AEC48 & 0x20) ? &bright : &dim);
            func_80057C30(D_800AE960, 2, 73, 60, 3891, 3891, (D_800AEC48 & 0x20) ? &bright : &dim);
            func_80054F8C(63, 40, 187, 36, &box);
        }
        if (m & 2) {
            func_80057C30(D_800AE95C, 2, 89, 162, 3891, 3891, (D_800AEC48 & 0x20) ? &bright : &dim);
            func_80057C30(D_800AE960, 2, 73, 180, 3891, 3891, (D_800AEC48 & 0x20) ? &bright : &dim);
            func_80054F8C(63, 160, 187, 36, &box);
        }
        if ((unsigned char)m) {
            func_80054F8C(0, 0, 320, 256, &clear);
            func_80054F8C(0, 0, 320, 256, &clear);
        }
    } else {
        if (mask & 1) {
            func_80057C30(D_800AE958, 2, 143, 42, 3891, 3891, (D_800AEC48 & 0x20) ? &bright : &dim);
            func_80057C30(D_800AE960, 2, 118, 60, 3891, 3891, (D_800AEC48 & 0x20) ? &bright : &dim);
            func_80054F8C(102, 40, 300, 36, &black);
        }
        if (m & 2) {
            func_80057C30(D_800AE95C, 2, 143, 162, 3891, 3891, (D_800AEC48 & 0x20) ? &bright : &dim);
            func_80057C30(D_800AE960, 2, 118, 180, 3891, 3891, (D_800AEC48 & 0x20) ? &bright : &dim);
            func_80054F8C(102, 160, 300, 36, &black);
        }
    }
    __asm__("" : : "r"(m));
    }
}
