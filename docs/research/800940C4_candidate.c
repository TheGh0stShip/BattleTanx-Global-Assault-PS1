typedef signed int s32;
typedef unsigned int u32;

extern volatile s32 *D_800B59E0;
extern volatile s32 *D_800B59E8;
extern volatile s32 *D_800B59E8_reload asm("D_800B59E8");

s32 func_800940C4(void) {
    volatile s32 sp0;
    s32 temp_v0;

    if (!(*D_800B59E8 & 0x01000000)) {
        return 0;
    }
    if (((u32) (*D_800B59E8 & 0x700) >> 8) != 4) {
        return -1;
    }
    *D_800B59E8 &= 0xFEFFFFFF;
    sp0 = *D_800B59E8_reload;
    temp_v0 = *D_800B59E0;
    sp0 = temp_v0;
    if (((u32) sp0 & 0xFFFFFF) == 0xFFFFFF) {
        return 0;
    }
    return sp0;
}
