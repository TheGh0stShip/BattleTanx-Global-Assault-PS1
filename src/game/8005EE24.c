typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

typedef struct Card {
    int state;
    union {
        int count;
        unsigned char slot;
    } u;
} Card;

extern Color D_800BFC84;
extern char D_800BFC9C[];
extern char D_800BFCB0[];
extern unsigned char D_800AE9EA;
extern int D_800A6070;
extern int D_800C60E4;
extern int D_800C60C8;
extern int D_800C60DC;
extern signed char D_800A606C;
extern unsigned char D_800AACEE;
extern unsigned short D_800EE02E;
extern unsigned char D_800E4838;
extern int D_800AE290[];
extern Card *func_8006A7FC(void);
extern void func_80076060(char *, int);
extern void func_80068E70(void);
extern void func_80076504(void);
extern void func_800201F8(int);
extern int func_800229F8(void);
extern void func_80079CE4(int);
extern void func_8006AF1C(int, int);
extern void func_8006AFFC(int);
extern int func_800577B4(int, int, int, int, int, Color *);
extern void func_800203E0(void);

void func_8005EE24(void) {
    Card *card;
    int count;
    Color color;
    unsigned char done;
    unsigned char finished;

    card = func_8006A7FC();
    if (card->state == 0) {
        if (D_800AE9EA == 0) {
            func_80076060(D_800BFC9C, (unsigned char)(card->u.slot + 1));
        }
        D_800A6070 = 1;
        D_800C60E4 = -1;
        D_800C60C8 = 1;
        D_800C60DC = 5;
        func_80068E70();
    } else if (card->state == 3) {
        func_80076060(D_800BFCB0, card->u.slot);
        func_80076504();
        func_800201F8(D_800A606C);
        func_80079CE4((unsigned char)func_800229F8());
        count = card->u.count;
        color = D_800BFC84;
        if (D_800AACEE == 0 && count != 2) {
            func_8006AF1C(3, (unsigned char)(count - 1));
            D_800AACEE = 1;
        }
        if (D_800EE02E == 0x4000) {
            func_8006AFFC(1);
            done = 1;
        } else {
            finished = func_800577B4(D_800AE290[count + 294], 3, 35, 5324, 5324, &color);
            if (D_800E4838 != 0 && finished) {
                D_800E4838 = 0;
                D_800AACEE = 0;
                done = 1;
            } else {
                done = 0;
            }
        }
        if (done) {
            func_800203E0();
        }
    }
}
