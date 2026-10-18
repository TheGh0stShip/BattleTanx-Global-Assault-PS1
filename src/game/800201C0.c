extern void func_8001F330(int value, void *buffer);
extern void *func_8001F6D4(void *buffer);
extern void func_8001F8D8(void *value, void *buffer);

void func_800201C0(void) {
    unsigned char buffer[24];
    void *value;

    func_8001F330(16, buffer);
    value = func_8001F6D4(buffer);
    func_8001F8D8(value, buffer);
}
