extern int D_800DDDEC;
void func_80075AEC(void);
void func_80078CF0(void);
void func_800851E4(int, int, int, int);
void func_80068E30(void);
int func_80068DA4(int);
void func_8007F708(int, int);
void func_8007F740(int);
void func_8003A200(int);

void func_800147E0(void) {
    int heap;

    func_80075AEC();
    func_80078CF0();
    func_800851E4(0, 0xFFFB, 800, 400);
    func_800851E4(1, 0xFFFB, 800, 400);
    func_80068E30();
    heap = func_80068DA4(50000);
    D_800DDDEC = heap;
    func_8007F708(heap, 50000);
    func_8007F740(2);
    func_8003A200(5);
}
