extern int D_800DDFF8[];
extern void func_8008D058(unsigned int red, unsigned int green, unsigned int blue);

void func_8003BC68(unsigned int color) {
    unsigned int red = color & 0xFF;
    unsigned int green = (color >> 8) & 0xFF;
    unsigned int blue = (color >> 16) & 0xFF;

    D_800DDFF8[1] = red << 16;
    D_800DDFF8[2] = green << 16;
    D_800DDFF8[3] = blue << 16;
    func_8008D058(red, green, blue);
}
