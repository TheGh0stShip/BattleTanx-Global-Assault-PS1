typedef unsigned char u8;

typedef struct StreamState {
    u8 pad_00[2];
    u8 active;
    u8 pad_03[9];
    int identifier;
} StreamState;

extern StreamState D_800EEF0C;
extern void func_80092CD0(void);

int func_80093470(int identifier) {
    int result = 0;
    if (D_800EEF0C.active && D_800EEF0C.identifier == identifier) {
        func_80092CD0();
        result = 1;
    }
    return result;
}
