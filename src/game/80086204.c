extern unsigned char D_800EE488[];
extern void func_8008AA48(void *destination, int value, int count);

void func_80086204(void) {
    func_8008AA48(D_800EE488, 0, 0x88);
    *(int *)D_800EE488 = -1;
}
