typedef struct { unsigned char b[8]; } Rect8;
extern Rect8 D_800BE7CC;
extern int D_800A48A8;
extern int D_800A48B4;
void func_8007F80C(int);
void func_8007F980(int);
void func_8007FBF8(Rect8 *, int, int, int);
void func_8008B894(void);
void func_8003E9A8(int, int);
void func_8007F9DC(int);

void func_8003A860(void) {
    Rect8 r;

    func_8007F80C(0);
    func_8007F980(0);
    r = D_800BE7CC;
    func_8007FBF8(&r, 0, 0, 0);
    func_8008B894();
    func_8003E9A8(20000, 1024);
    D_800A48A8 = 0;
    D_800A48B4 = 1;
    func_8007F9DC(1);
}
