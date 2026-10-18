typedef unsigned char u8;

typedef struct MenuState {
    u8 pad[4];
    u8 *data;
} MenuState;

extern MenuState D_800AAC58;
extern void func_8005A7E0(void *object, u8 *event);
extern void func_8005A834(MenuState *state);

int func_8005FAF8(void *object, u8 *event) {
    event[1] = 0x10;
    func_8005A7E0(object, event);
    D_800AAC58.data[0x21] = 0x90;
    func_8005A834(&D_800AAC58);
    return 0;
}
