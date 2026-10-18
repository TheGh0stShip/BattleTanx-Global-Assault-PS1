typedef unsigned char u8;
typedef void (*Callback)(void);

typedef struct CallbackState {
    u8 pad_00[0x14];
    unsigned int state;
    Callback callbacks[1];
} CallbackState;

extern CallbackState D_800EEE3C;

void func_800919D8(void) {
    if (D_800EEE3C.state != 1) {
        Callback callback = D_800EEE3C.callbacks[D_800EEE3C.state];
        if (callback != 0) {
            callback();
        }
        D_800EEE3C.state = 1;
    }
}
