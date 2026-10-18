typedef unsigned char u8;

typedef struct TransferState {
    unsigned int flags;
    unsigned int value;
    u8 pad_08[8];
    u8 transfer[1];
} TransferState;

extern TransferState D_800EEC34;
extern void D_8008E860(void);
extern void func_8008EC40(void);
extern void func_800998AC(void *transfer, int first, void (*callback)(void));

void func_8008ED08(int first, unsigned int value) {
    func_8008EC40();
    D_800EEC34.value = value;
    func_800998AC(D_800EEC34.transfer, first, D_8008E860);
}
