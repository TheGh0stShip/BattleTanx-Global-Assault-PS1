void func_8009C6DC(unsigned int *, unsigned short);

void func_8009C52C(unsigned int *mode, int flags)
{
    if (flags & 1) {
        *mode &= ~0x08000000;
    } else {
        *mode |= 0x08000000;
    }
    if (flags & 2) {
        *mode |= 0x02000000;
    } else {
        *mode &= ~0x02000000;
    }
    func_8009C6DC(mode, *(unsigned short *)mode);
}
