typedef struct Slot16 {
    int a;
    int b;
    int c;
    int d;
} Slot16;

extern int D_800AAEF4;
extern int D_800AAEFC;
extern int D_800AAF04;
extern int D_800AAF0C;
extern int D_800AAF14;
extern int D_800AAF1C;
extern int D_800AAF24;
extern int D_800AAF28;
extern int D_800AAF2C;
extern int D_800AAF30;
extern Slot16 D_800E4D4C[];

void func_80063DB8(unsigned short player) {
    switch (player) {
    case 0:
        D_800AAEF4 = 0;
        D_800AAF04 = 0;
        D_800AAF14 = 0;
        D_800AAF24 = 0;
        D_800AAF2C = 0;
        break;
    case 1:
        D_800AAEFC = 0;
        D_800AAF0C = 0;
        D_800AAF1C = 0;
        D_800AAF28 = 0;
        D_800AAF30 = 0;
        break;
    default:
        D_800AAEF4 = 0;
        D_800AAF04 = 0;
        D_800AAF14 = 0;
        D_800AAF24 = 0;
        D_800AAF2C = 0;
        break;
    }
    D_800E4D4C[player].b = 0;
}
