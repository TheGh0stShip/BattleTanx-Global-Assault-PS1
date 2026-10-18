typedef struct {
    int texture;
    char pad[0xCC];
} Vehicle;

typedef struct {
    char pad[0xC];
    int value;
} Hud;

extern unsigned char D_800D2FEC;
extern int D_800C60D0;
extern short D_800D326C;
extern int D_800AE94C;
extern int D_800AE950;
extern short D_800ADE90;
extern short D_800ADE9C;
extern short D_800ADEA8;
extern short D_800ADE54;
extern short D_800ADE60;
extern short D_800ADE6C;
extern short D_800ADE78;
extern short D_800ADE84;
extern int D_800ADEB4;
extern int D_800ADEC0;
extern int D_800ADECC;
extern int D_800ADED0;
extern int D_800ADED4;
extern int D_800ADED8;
extern int D_800ADE4C;
extern int D_800ADE50;
extern Hud *D_800E3E74;
extern Vehicle D_800A4EF4[];
extern int func_80022814(void);
extern void func_80057C30(int tex, int mode, int x, int y, int sx, int sy, int *pal);
extern void func_80057A0C(int value, int mode, int x, int y, int sx, int sy, int digits, int *pal);
extern void func_80054F8C(short x, short y, int w, int h, int *pal);

void func_8006C06C(void) {
    int show;

    if (D_800D2FEC == 1 || D_800C60D0 != 5) {
        return;
    }
    if (func_80022814() != 0 && D_800D326C != -1) {
        func_80057C30(D_800AE94C, 2, D_800ADE90, D_800ADEA8, 4096, 4096, &D_800ADE4C);
        func_80057A0C(D_800E3E74->value, 2, D_800ADE9C, D_800ADEA8, 4096, 4096, 1, &D_800ADE4C);
        func_80054F8C(D_800ADE90 - 5, D_800ADEA8 - 1, 228, 17, &D_800ADE50);
    }
    show = D_800ADED8;
    if (show == 1) {
        func_80057C30(D_800A4EF4[D_800ADECC].texture, 2, D_800ADE54, D_800ADE60, D_800ADEB4, D_800ADEC0, &D_800ADE4C);
        if (func_80022814() != 0) {
            func_80057C30(D_800AE950, 2, D_800ADE6C, D_800ADE84, D_800ADEB4, D_800ADEC0, &D_800ADE4C);
            func_80057A0C(D_800ADED0, 2, D_800ADE78, D_800ADE84, D_800ADEB4, D_800ADEC0, show, &D_800ADE4C);
            func_80057C30(D_800AE94C, 2, D_800ADE90, D_800ADEA8, 4096, 4096, &D_800ADE4C);
            func_80057A0C(D_800ADED4, 2, D_800ADE9C, D_800ADEA8, 4096, 4096, show, &D_800ADE4C);
        }
    }
}
