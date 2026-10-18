typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

extern Color D_800BFC84;
extern Color D_800BFC88;
extern Color D_800BFC8C;
extern char D_800BFC90[];
extern unsigned char D_800AACEC;
extern short D_800AACEA;
extern unsigned char D_800AACED;
extern unsigned char D_800AEA45;
extern signed char D_800A606C;
extern int D_800AE9D4[];
extern int D_800E488C;
extern int D_800AE290[];
extern int func_800229F8(void);
extern void func_800201F8(int);
extern void func_80079CE4(int);
extern void func_80057C30(void *, int, int, int, int, int, Color *);
extern void func_80056160(void *, int, int, int, int, Color *);
extern int func_80056E48(int, int, int, int, int, int, int, int, int, Color *);

void func_8005EB6C(int index) {
    Color shade;
    Color bright;
    Color text;
    unsigned char count;

    shade = D_800BFC84;
    bright = D_800BFC88;
    text = D_800BFC8C;
    if ((unsigned char)func_800229F8() == 0) {
        count = D_800AACEC;
        D_800AACEC = count + 255;
        if (count == 0) {
            D_800AACEC = 2;
            D_800AACEA++;
        }
    }
    if (D_800AEA45 == 1) {
        func_80057C30(D_800BFC90, 3, 230, 215, 4096, 4096, &shade);
    } else if (D_800AEA45 == 2) {
        func_800201F8(D_800A606C);
        func_80079CE4((unsigned char)func_800229F8());
        shade.b = 120;
        shade.r = 120;
        shade.g = 120;
        bright.r = 250;
        bright.g = 250;
        bright.b = 250;
        shade.a = 255;
        bright.a = 255;
        func_80057C30((void *)D_800AE9D4[0], 3, 182, 215, 4096, 4096, &shade);
        func_80056160(&D_800E488C, 226, 214, 4096, 4096, &bright);
        func_80057C30((void *)D_800AE9D4[1], 3, 240, 215, 4096, 4096, &shade);
        func_80057C30((void *)D_800AE9D4[2], 3, 259, 215, 4096, 4096, &shade);
    }
    if (D_800AACED == 0) {
        if ((unsigned short)func_80056E48(D_800AE290[index + 209], 3, 30, 70, 5324, 5324, 200, 0, D_800AACEA,
                                          &text)) {
            D_800AACED = 1;
        }
    } else {
        func_80056E48(D_800AE290[index + 209], 3, 30, 70, 5324, 5324, 200, 0, -1, &text);
        D_800AACED = 0;
    }
}
