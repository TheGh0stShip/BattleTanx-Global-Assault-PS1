typedef unsigned char u8;

typedef struct TransferState {
    unsigned int flags;
    unsigned int value;
    u8 pad_08[8];
    u8 transfer[1];
} TransferState;

extern volatile TransferState D_800EEC34;
extern void func_800996A4(void *transfer);

void func_8008EC40(void) {
    if (!(D_800EEC34.flags & 0x10)) {
        unsigned int flags = D_800EEC34.flags;
        D_800EEC34.value = 0;
        D_800EEC34.flags = flags | 0x10;
    }
    func_800996A4((void *)D_800EEC34.transfer);
}
