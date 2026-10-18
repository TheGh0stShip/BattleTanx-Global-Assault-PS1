extern int D_800C60DC;
extern unsigned char D_800ABA38[];
extern short D_800ABA54[2];
extern short D_800ABA58;
extern unsigned char D_800ABA5A;

void func_80054CA0(void);
void func_8006AFC0(int enabled);
void func_8005AC50(unsigned char *state);

int func_80063EE8(void) {
    D_800C60DC = 5;
    D_800ABA5A = 0;
    func_80054CA0();
    func_8006AFC0(1);
    D_800ABA54[0] = 0;
    D_800ABA54[1] = 0;
    D_800ABA58 = 0;
    func_8005AC50(D_800ABA38);
    return 3;
}
