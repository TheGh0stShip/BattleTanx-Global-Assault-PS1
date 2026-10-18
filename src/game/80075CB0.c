typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char code;
} Color;

extern unsigned char D_800AACE0;
extern signed char D_800A606C;
extern unsigned short D_800EE02E;
extern unsigned char D_800AEA41;
extern unsigned char D_800AEA42;
extern unsigned char D_800AEA43;
extern void *func_8008AA48(void *, int, int);
extern void func_800201F8(int);
extern int func_800229F8(void);
extern void func_80079CE4(int);
extern void func_80057D60(char *, int, int, int, int, int, void *);
extern void func_80057C30(char *, int, int, int, int, int, void *);
extern void func_80054A30(int);

void func_80075CB0(void) {
    Color shadow = {50, 150, 14, 255};
    Color black;

    func_8008AA48(&black, 0, 4);
    black.code = 255;
    if (D_800AACE0 != 0) {
        func_800201F8(D_800A606C);
        func_80079CE4(func_800229F8() & 0xFF);
        func_80057D60("Press START button", 2, 160, 190, 4096, 4096, &shadow);
        func_80057D60("Press START button", 2, 160, 188, 4096, 4096, &black);
        if (D_800EE02E & 0x4008) {
            func_80054A30(4);
            D_800AEA42 = 1;
            D_800AEA43 = 0;
        }
    } else if (D_800AEA41 == 2) {
        if (D_800AEA43 >= 31) {
            D_800AEA43 = 0;
        } else if (D_800AEA43 < 20) {
            func_80057C30("LOADING . . .", 2, 92, 190, 4096, 4096, &shadow);
            func_80057C30("LOADING . . .", 2, 95, 188, 4096, 4096, &black);
        }
        D_800AEA43++;
    }
}
