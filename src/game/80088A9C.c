struct StreamState {
    unsigned char pad_00[0x48];
    void *current;
    unsigned int aligned_value;
};

extern struct StreamState D_800EEAE8;

void func_80088FB0(void);
void func_80088A80(void);

void func_80088A9C(void *current, unsigned int value) {
    if (D_800EEAE8.current != 0) {
        func_80088FB0();
    }
    D_800EEAE8.current = current;
    D_800EEAE8.aligned_value = value & 0xFFFFF800;
    func_80088A80();
}
