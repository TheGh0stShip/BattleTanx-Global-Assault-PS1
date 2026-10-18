void func_8008A7BC(void *destination, const void *source, unsigned int size);

extern unsigned char D_800B0CCC[];

void *func_8008040C(void *destination) {
    func_8008A7BC(destination, D_800B0CCC, 0x14);
    return destination;
}
