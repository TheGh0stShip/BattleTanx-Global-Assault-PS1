extern unsigned char D_800EE588[];
extern void func_8008DA04(unsigned char *destination, const unsigned char *source);

int func_80086E6C(unsigned char *destination) {
    destination[0] = 0x42;
    destination[1] = D_800EE588[752];
    func_8008DA04(destination + 2, D_800EE588 + 753);
    return 12;
}
