typedef signed int s32;
typedef unsigned int u32;

extern volatile s32 *D_800B59E0;
extern volatile s32 *D_800B59E8;

s32 func_800940C4(void) {
    volatile s32 sp0;
    s32 temp_v0;
    register volatile s32 **status_slot asm("$4");
    register volatile s32 *status asm("$4");

    asm("lui %0,0x800B" : "=r"(status_slot));
    status = *(volatile s32 **)((char *) status_slot + 0x59E8);
    if (!(*status & 0x01000000)) {
        return 0;
    }
    if (((u32) (*status & 0x700) >> 8) != 4) {
        return -1;
    }
    *status &= 0xFEFFFFFF;
    {
        register volatile s32 *read_status asm("$2");
        register volatile s32 *read_data asm("$3");

        asm("lui %0,0x800B\n\t"
            "lw %0,0x59E8(%0)\n\t"
            "lui %1,0x800B\n\t"
            "lw %1,0x59E0(%1)"
            : "=r"(read_status), "=r"(read_data));
        sp0 = *read_status;
        temp_v0 = *read_data;
    }
    sp0 = temp_v0;
    if (((u32) sp0 & 0xFFFFFF) == 0xFFFFFF) {
        return 0;
    }
    return sp0;
}
