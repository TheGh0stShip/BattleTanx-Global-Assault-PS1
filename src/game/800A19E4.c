typedef struct SoundTransfer {
    int handle;
    volatile unsigned int flags;
    int active;
    unsigned char unusedC[36];
    unsigned char mode;
    unsigned char unused31[3];
    int value34;
    unsigned char unused38[4];
    int value3C;
    unsigned char unused40[8];
    void (*callback)(struct SoundTransfer *, unsigned char, int, int, int);
} SoundTransfer;

typedef struct SoundGlobals {
    unsigned char unused0[0x108];
    SoundTransfer *active;
} SoundGlobals;

extern SoundGlobals D_800EFD0C;
extern void func_8008FF1C(int event, int handle);
extern void func_8008F9A4(void);

void func_800A19E4(int reason) {
    register int saved_reason asm("$20") = reason;
    register SoundTransfer *transfer asm("$16");
    register int value3C asm("$19");
    register void (*callback)(SoundTransfer *, unsigned char, int, int, int)
        asm("$17");
    register int value34 asm("$18");
    register SoundTransfer *active_arg asm("$4");

    asm("" : "+r"(saved_reason));
    active_arg = D_800EFD0C.active;
    if (active_arg != 0) {
        register unsigned int active_flags asm("$2");
        register unsigned int new_flags asm("$3");
        int clear_mask;

        transfer = active_arg;
        D_800EFD0C.active = 0;
        value3C = transfer->value3C;
        asm volatile("" : : : "memory");
        active_flags = transfer->flags;
        asm volatile("" : : : "memory");
        new_flags = transfer->flags;
        asm volatile("" : : : "memory");
        callback = transfer->callback;
        asm volatile("" : : : "memory");
        value34 = transfer->value34;
        asm volatile("" : : "r"(value3C), "r"(active_flags),
                     "r"(new_flags), "r"(callback), "r"(value34)
                     : "memory");
        clear_mask = -0x404;
        transfer->active = 0;
        asm volatile("" : : : "memory");
        transfer->value3C = 0;
        asm volatile("" : "+r"(active_flags), "+r"(new_flags)
                     : "r"(clear_mask) : "memory");
        new_flags &= clear_mask;
        active_flags &= 1U;
        transfer->flags = new_flags;
        if (saved_reason == 0 && active_flags != 0) {
            func_8008FF1C(0xD, transfer->handle);
            func_8008F9A4();
        }
        if (callback != 0) {
            transfer->callback = 0;
            callback(transfer, transfer->mode, value3C, value34,
                     saved_reason);
        }
    }
}
