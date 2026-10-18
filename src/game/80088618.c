extern unsigned char D_800EE588[];
extern void func_8008DA04(void *destination, void *source);

void func_80088618(unsigned char value, void *source) {
    D_800EE588[0x2F0] = value;
    func_8008DA04(D_800EE588 + 0x2F1, source);
}
