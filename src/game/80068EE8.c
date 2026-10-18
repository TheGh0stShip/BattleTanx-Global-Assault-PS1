extern unsigned int func_8007F7D8(void);
extern unsigned int func_8007F7F4(void);
extern void func_8007F7E8(unsigned int value);

void *func_80068EE8(unsigned int size) {
    unsigned int start = func_8007F7D8();

    if (size < func_8007F7F4()) {
        func_8007F7E8(start + size);
        return (void *)start;
    }
    return 0;
}
