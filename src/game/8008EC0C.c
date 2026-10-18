typedef unsigned char u8;

typedef struct TransferState {
    unsigned int flags;
    u8 pad_04[12];
    u8 transfer[1];
} TransferState;

extern TransferState D_800EEC34;
extern void func_800996A4(void *transfer);

void func_8008EC0C(void) {
    if (D_800EEC34.flags & 0x10) {
        func_800996A4(D_800EEC34.transfer);
    }
}
