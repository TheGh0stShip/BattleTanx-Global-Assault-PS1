typedef signed int s32;
typedef unsigned short u16;

typedef struct DeviceState {
    char pad0[4];
    u16 status;
    char pad6[4];
    u16 control;
} DeviceState;

extern s32 *D_800B8CD4;
extern DeviceState *D_800B8CD8;
extern s32 func_800A3A44(void);

s32 func_8009ECDC(void) {
    s32 result;

    *D_800B8CD4 = -0x81;
    if (D_800B8CD8->status & 0x80) {
        do {
            result = 0;
            if (func_800A3A44() != 0) {
                return result;
            }
        } while (D_800B8CD8->status & 0x80);
    }
    D_800B8CD8->control |= 0x10;
    return 1;
}
