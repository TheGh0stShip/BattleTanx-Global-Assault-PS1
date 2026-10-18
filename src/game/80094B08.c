extern unsigned char D_800EEFF8[];

void func_8009DA78(void *first, void *last);

void func_80094B08(void) {
    func_8009DA78(D_800EEFF8, D_800EEFF8 + 0x22);
}
