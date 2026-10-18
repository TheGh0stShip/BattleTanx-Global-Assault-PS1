extern int D_800C60CC;
extern int D_800AEB34;
extern char *D_800AE964;
extern char *D_800AE304;
extern char D_800C3E4C[];
extern char D_800C3E50[];
extern char D_800AEA50[];
extern char D_800AEA58[];
extern char *func_8008DA04(char *, char *);
extern char *func_8008D954(char *, char *);
extern void func_80057D60(char *, int, int, int, int, int, void *);
extern void func_80057C30(char *, int, int, int, int, int, void *);

void func_800770B8(void) {
    char line1[24];
    char line2[24];
    void *color1;
    void *color2;
    void *color3;

    func_8008DA04(line1, D_800AE964);
    func_8008D954(line1, D_800C3E4C);
    func_8008DA04(line2, D_800AE964);
    func_8008D954(line2, D_800C3E50);
    if (D_800AEB34 == 0) {
        color1 = D_800AEA58;
        color2 = D_800AEA50;
        color3 = D_800AEA50;
    } else if (D_800AEB34 == 1) {
        color1 = D_800AEA50;
        color2 = D_800AEA58;
        color3 = D_800AEA50;
    } else {
        color1 = D_800AEA50;
        color2 = D_800AEA50;
        color3 = D_800AEA58;
    }
    if (D_800C60CC == 1) {
        func_80057D60(line1, 2, 256, 110, 4096, 4096, color1);
        func_80057D60(line2, 2, 256, 130, 4096, 4096, color2);
        func_80057D60(D_800AE304, 2, 256, 150, 4096, 4096, color3);
    } else {
        func_80057C30(line1, 2, 30, 110, 4096, 4096, color1);
        func_80057C30(line2, 2, 30, 130, 4096, 4096, color2);
        func_80057C30(D_800AE304, 2, 30, 150, 4096, 4096, color3);
    }
}
