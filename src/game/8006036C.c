extern unsigned char D_800AACD6;
extern unsigned char D_800AACD7;
extern unsigned char D_800AACD8;

void func_8005A648(void);
void func_8003DFC8(void);
void func_8003DF4C(void);

int func_8006036C(void) {
    D_800AACD6 = 0;
    D_800AACD7 = 0;
    D_800AACD8 = 0;
    func_8005A648();
    func_8003DFC8();
    func_8003DF4C();
    return 1;
}
