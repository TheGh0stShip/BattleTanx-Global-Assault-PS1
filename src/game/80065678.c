extern unsigned char D_800D2FED;
extern unsigned char D_800AC860;
extern unsigned char D_800AD040;
extern unsigned char D_800AD640;
extern int D_800ABA84;
extern void func_80054A30(int);

int func_80065678(void) {
    switch (D_800D2FED) {
    case 2:
        D_800AC860 = 6;
        break;
    case 3:
        D_800AD640 = 6;
        break;
    case 4:
        D_800AD040 = 6;
        break;
    }
    D_800ABA84 = 1;
    func_80054A30(13);
    return 1;
}
