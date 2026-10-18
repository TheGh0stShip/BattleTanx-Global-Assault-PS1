extern int D_800C60C4;
extern int D_800C60C8;
extern int D_800C60CC;
extern int D_800C60D0;
extern int D_800C60D4;
extern int D_800C60D8;
extern int D_800C60DC;
extern int D_800C60E4;
extern unsigned char D_800AAD00;
extern unsigned char D_800AE9EA;
extern int D_800DDDEC;
extern int D_800EAFBC;
extern int D_800EBC3C;
extern signed char D_800A606C;
void func_80075AEC(void);
void func_80078CF0(void);
void func_800851E4(int, int, int, int);
void func_80068E30(void);
int func_80068DA4(int);
void func_8007F708(int, int);
void func_8007F740(int);
void func_8003A200(int);
void func_80084898(int);
void func_800201F8(int);
void func_8003A610(void);
unsigned char func_800229F8(void);
void func_80079CE4(int);
void func_8003A744(void);
void func_8007586C(int);
void func_8005A08C(void);
void func_8003A8F4(void);
void func_8007646C(void);
void func_80068E70(void);

void func_800141F8(void) {
    int heap;

    if (D_800C60D0 != 3 && D_800C60D0 != 4) {
        if (D_800AAD00 == 0) {
            func_80075AEC();
        }
        func_80078CF0();
        func_800851E4(0, 0xFFFB, 800, 400);
        func_800851E4(1, 0xFFFB, 800, 400);
        func_80068E30();
        heap = func_80068DA4(50000);
        D_800DDDEC = heap;
        func_8007F708(heap, 50000);
        func_8007F740(2);
    }
    func_8003A200(5);
    if (D_800AAD00 == 2) {
        D_800AAD00 = 1;
    }
    while (D_800C60CC == 0) {
        func_80084898(100);
        func_800201F8(D_800A606C);
        func_8003A610();
        func_80079CE4(func_800229F8());
        func_8003A744();
        if (D_800AE9EA != 0) {
            func_8007586C(D_800EAFBC);
            if (D_800AE9EA != 0 && D_800EAFBC != 4) {
                D_800EBC3C = 0;
            }
        }
        func_8005A08C();
        if (D_800AAD00 != 0) {
            func_80075AEC();
            D_800AAD00 = 0;
        } else {
            func_8003A8F4();
        }
        if (D_800C60CC != D_800C60C8) {
            D_800C60C4 = D_800C60CC;
            D_800C60CC = D_800C60C8;
            D_800C60E4 = 0;
        } else {
            D_800C60E4 = 1;
        }
        if (D_800C60D0 != D_800C60DC) {
            D_800C60D4 = D_800C60D0;
            D_800C60D0 = D_800C60DC;
            D_800C60D8 = 0;
        } else {
            D_800C60D8 = 1;
        }
    }
    if (D_800AE9EA != 0) {
        func_8007646C();
    }
    func_80068E70();
}
