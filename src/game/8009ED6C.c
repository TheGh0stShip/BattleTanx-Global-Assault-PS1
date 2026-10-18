typedef struct DeviceState {
    unsigned char reserved[4];
    unsigned short status;
} DeviceState;

extern volatile DeviceState *D_800B8CD8;

void func_8009ED6C(void) {
    register volatile DeviceState **globals asm("$3") =
        (volatile DeviceState **)0x800C0000;
    register volatile DeviceState *device asm("$3");

    asm("" : "+r"(globals));
    device = globals[-7370];
    asm("" : "+r"(device));
    asm("nop");
    while ((device->status & 2) == 0) {
    }
}
