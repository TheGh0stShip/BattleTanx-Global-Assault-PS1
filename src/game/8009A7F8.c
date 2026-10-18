extern int D_800B770C;
extern unsigned short D_800B7708;
extern int D_800B7718;
extern int func_8009A578();
extern void func_8009A2FC(unsigned char *, unsigned int);

unsigned int func_8009A7F8(unsigned char *addr, unsigned int size) {
    if (D_800B770C == 0) {
        func_8009A578(2, D_800B7708 << D_800B7718);
        func_8009A578(1);
        func_8009A578(3, addr, size);
    } else {
        func_8009A2FC(addr, size);
    }
    return size;
}
