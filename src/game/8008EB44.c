typedef unsigned char u8;

typedef struct TransferState {
    unsigned int flags;
    u8 pad_04[12];
    u8 transfer[1];
} TransferState;

extern volatile TransferState D_800EEC34;
extern void func_800996A4(void *transfer);
extern void func_8009930C(void *transfer);

void func_8008EB44(void) {
    if (D_800EEC34.flags & 1) {
        D_800EEC34.flags &= ~1U;
        func_800996A4((void *)D_800EEC34.transfer);
        func_8009930C((void *)D_800EEC34.transfer);
    }
}
