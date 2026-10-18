void func_8003BD50(unsigned char *object, unsigned int color) {
    register unsigned int component asm("$2");

    component = color & 0xFF;
    asm("" : "+r"(component));
    component <<= 4;
    *(short *)(object + 0x10) = component;

    component = color >> 8;
    asm("" : "+r"(component));
    component &= 0xFF;
    asm("" : "+r"(component));
    component <<= 4;
    *(short *)(object + 0x12) = component;

    component = color >> 16;
    asm("" : "+r"(component));
    component &= 0xFF;
    asm("" : "+r"(component));
    component <<= 4;
    *(short *)(object + 0x14) = component;
    *(unsigned int *)(object + 0x30) = color;
}
