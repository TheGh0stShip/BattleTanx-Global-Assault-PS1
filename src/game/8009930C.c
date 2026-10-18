extern void func_800A2A64(void *transfer);
extern void func_8008AA48(void *destination, int value, unsigned int size);

void func_8009930C(void *transfer) {
    func_800A2A64(transfer);
    func_8008AA48(transfer, 0, 0x88);
}
