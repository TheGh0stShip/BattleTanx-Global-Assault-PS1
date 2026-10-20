typedef struct SoundTransfer {
    int unused0;
    unsigned int flags;
} SoundTransfer;

extern void func_800A19E4(int reason);

void func_800A2DC8(SoundTransfer *transfer) {
    if ((transfer->flags & 1U) != 0) {
        func_800A19E4(0);
    }
}
