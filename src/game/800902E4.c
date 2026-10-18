extern volatile unsigned short D_800B7708;
extern int D_800B7718;
int func_8009A8C0(int, unsigned int);

int func_800902E4(unsigned int addr)
{
    if (addr - 0x1010 > 0x7EFE8) {
        return 0;
    }
    D_800B7708 = func_8009A8C0(-1, addr);
    return D_800B7708 << D_800B7718;
}
