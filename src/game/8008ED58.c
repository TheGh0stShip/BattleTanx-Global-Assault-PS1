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
extern void func_8009991C(void *transfer, int first, int second, int third, void (*callback)(void));

void func_8008ED58(int first, int second, int third, unsigned int value) {
    func_8008EC40();
    D_800EEC34.value = value;
    func_8009991C(D_800EEC34.transfer, first, second, third, D_8008E860);
}
