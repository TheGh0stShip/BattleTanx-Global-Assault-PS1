typedef unsigned char u8;

typedef struct StreamState {
    u8 pad_00[2];
    u8 active;
    u8 pad_03[9];
    int identifier;
} StreamState;

extern StreamState D_800EEF0C;
extern int func_80093470(int identifier);

void func_800934BC(int identifier) {
    if (D_800EEF0C.active && D_800EEF0C.identifier == identifier) {
        func_80093470(identifier);
    }
}
