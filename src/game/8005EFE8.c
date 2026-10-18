typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

extern Color D_800BFC8C;
extern char D_800BFCC4[];
extern char D_800BFCD4[];
extern unsigned char D_800AEA43;
extern char ***D_800E4860;
extern unsigned char D_800AACE2;
extern char *D_800AE290[];
extern void func_8008AA48(void *, int, int);
extern void func_80057C30(char *, int, int, int, int, int, Color *);
extern void func_8008DA04(char *, char *);
extern void func_8008D954(char *, char *);

void func_8005EFE8(void) {
    Color text;
    Color black;
    char line[56];

    text = D_800BFC8C;
    func_8008AA48(&black, 0, 4);
    black.a = 255;
    if (D_800AEA43 >= 31) {
        D_800AEA43 = 0;
    } else if (D_800AEA43 < 20) {
        func_80057C30(D_800BFCC4, 3, 25, 60, 4505, 4505, &text);
    }
    D_800AEA43++;
    func_8008DA04(line, **D_800E4860);
    func_8008D954(line, D_800BFCD4);
    func_8008D954(line, D_800AE290[D_800AACE2]);
    func_80057C30(line, 3, 25, 80, 4505, 4505, &text);
}
