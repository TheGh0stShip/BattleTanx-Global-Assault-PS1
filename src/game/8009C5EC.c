extern volatile int *D_800B8BA0;
extern volatile int *D_800B8B74;
extern volatile int *D_800B8B80;
extern char D_800B8A5C[];
extern char D_800B8AE0[];
extern char D_800C5A88[];
extern void func_8009C6DC(char *, int);
extern void func_800943B0(char *, ...);

void func_8009C5EC(int mode)
{
    int dummy;

    switch (mode) {
    case 0:
        *D_800B8BA0 = 0x80000000;
        *D_800B8B74 = 0;
        *D_800B8B80 = 0;
        *D_800B8BA0 = 0x60000000;
        func_8009C6DC(D_800B8A5C, 32);
        func_8009C6DC(D_800B8AE0, 32);
        break;
    case 1:
        *D_800B8BA0 = 0x80000000;
        *D_800B8B74 = 0;
        *D_800B8B80 = 0;
        dummy = *D_800B8B80;
        *D_800B8BA0 = 0x60000000;
        break;
    default:
        func_800943B0(D_800C5A88, mode);
        break;
    }
}
