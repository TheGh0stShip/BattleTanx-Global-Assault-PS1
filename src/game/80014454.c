extern int D_800C60C0;
extern int D_800C60C4;
extern int D_800C60C8;
extern int D_800C60CC;
extern int D_800C60D0;
extern int D_800C60D4;
extern int D_800C60D8;
extern int D_800C60DC;
extern int D_800C60E4;
extern unsigned char D_800C60EC;
extern int D_800C60F0;
extern unsigned char D_800D302D;
extern int D_800A4358;
extern int D_800A48DC;
extern int D_800DDDEC;
extern unsigned char D_800AEA41;
extern unsigned char D_800AEA42;
extern unsigned char D_800AEA46;
extern unsigned char D_800AACE0;
extern char D_800BD494[];
extern char D_800BD4A8[];
extern char D_800BD4BC[];
void func_800861B0(void);
void func_8007F80C(int);
int func_80014074(void);
void func_80054970(void);
int func_80088870(int);
void func_80086C74(int);
void func_8003A860(void);
void func_800686D4(void);
int func_8003DCAC(char *);
void func_80074B8C(void);
void func_8003A200(int);
void func_8006ABF4(char *);
int func_80068F34(int);
void func_8007F708(int, int);
void func_8007F740(int);
void func_80076060(char *, int);
void func_80086270(int, int);
void func_8003DC20(void);
void func_8003C638(void);
void func_8007FA74(int);
void func_80068F9C(int);
void func_800851E4(int, int, int, int);
void func_80068E30(void);
int func_80068DA4(int);
void func_800686DC(int, int);
void func_80020D50(void);
void func_80021CA4(void);
void func_8003DD64(void);
void func_800141F8(void);

int func_80014454(void) {
    int heap;

    func_800861B0();
    func_8007F80C(0);
    if (func_80014074() == 0) {
        return 1;
    }
    func_80054970();
    func_80086C74(func_80088870(-1));
    func_8003A860();
    func_800686D4();
    D_800C60C8 = 0;
    D_800C60DC = 2;
    D_800C60CC = 2;
    D_800C60D0 = 2;
    D_800C60C4 = 2;
    D_800C60D4 = 2;
    D_800C60E4 = 0;
    D_800C60D8 = 0;
    D_800D302D = 0;
    D_800A4358 = func_8003DCAC(D_800BD494);
    func_80074B8C();
    func_8003A200(5);
    if (D_800C60C0 & 1) {
        func_8006ABF4(D_800BD4A8);
    }
    heap = func_80068F34(10000);
    D_800DDDEC = heap;
    func_8007F708(heap, 10000);
    func_8007F740(2);
    D_800AEA42 = 0;
    func_80076060(D_800BD4BC, 1);
    D_800AEA46 = 100;
    D_800AEA41 = 1;
    func_80086270(0, 0);
    func_80086270(1, 0);
    func_8003DC20();
    func_8003C638();
    D_800AACE0 = 1;
    while (1) {
        func_80088870(2);
        if (D_800AEA42 != 0) {
            func_8007FA74(0);
            func_80088870(0);
            D_800AEA46 = 100;
            break;
        }
    }
    func_80068F9C(D_800DDDEC);
    D_800AEA41 = 0;
    D_800C60CC = 0;
    while (1) {
        switch (D_800C60CC) {
        case 1:
            D_800C60EC = 0;
            if (D_800A48DC == 0) {
                func_800851E4(0, 0xFFFB, 0, 0);
                func_800851E4(1, 0xFFFB, 0, 0);
                func_80068E30();
                func_800686DC(D_800C60F0 = func_80068DA4(0x8000), 0x8000);
            }
            func_80020D50();
            func_80021CA4();
            func_8003DD64();
            D_800C60F0 = 0;
            break;
        case 0:
            D_800C60EC = 1;
            if (D_800A48DC != 0) {
                D_800C60DC = 5;
                D_800C60CC = 1;
                D_800C60C8 = 1;
                D_800C60C4 = 0;
                D_800C60E4 = 0;
                if (D_800C60D0 != 5) {
                    D_800C60D4 = D_800C60D0;
                    D_800C60D0 = 5;
                    D_800C60D8 = 0;
                } else {
                    D_800C60D8 = 1;
                }
            } else {
                func_800141F8();
            }
            break;
        }
    }
}
