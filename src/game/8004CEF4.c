void func_8004D078(unsigned char *state);

void func_8004CEF4(unsigned char *object) {
    *(int *)(object + 0x144) = 0;
    *(int *)(object + 0x13C) = 0;
    *(short *)(object + 0x148) = 0;
    *(short *)(object + 0x14A) = 0;
    func_8004D078(object + 0x14C);
    *(int *)(object + 0x168) = 0;
    *(int *)(object + 0x16C) = 0;
    *(unsigned int *)(object + 0x180) &= ~0x780U;
}
