typedef unsigned char u8;

typedef void (*Callback)(unsigned int, unsigned int, unsigned int, unsigned int);

typedef struct CallbackState {
    unsigned int first;
    u8 pad_04[0x28];
    unsigned int pending;
    Callback callback;
    unsigned int second;
    unsigned int third;
} CallbackState;

extern CallbackState D_800EEDF4;

void func_8008F4B4(unsigned int fourth) {
    Callback callback = D_800EEDF4.callback;
    unsigned int second = D_800EEDF4.second;
    unsigned int third = D_800EEDF4.third;
    D_800EEDF4.pending = 0;
    D_800EEDF4.callback = 0;
    D_800EEDF4.second = 0;
    D_800EEDF4.third = 0;
    if (callback != 0) {
        callback(D_800EEDF4.first, second, third, fourth);
    }
}
