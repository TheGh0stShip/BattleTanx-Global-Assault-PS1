typedef unsigned short u16;
typedef unsigned int u32;

u16 func_80049E4C(u32 mask) {
    u16 index = 0;

    while ((mask & 1) == 0) {
        mask >>= 1;
        index++;
    }
    return index;
}
