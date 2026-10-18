typedef unsigned char u8;

typedef struct MenuObject {
    u8 header[4];
    u8 data[0x9600];
} MenuObject;

extern u8 D_800AACD5;
extern u8 D_800AACF8;
extern MenuObject *D_800DE0C8;
extern void func_8007FC88(void *state, void *object);

void func_8005FBD4(int selection) {
    u8 index = selection;

    if (D_800AACD5 != index) {
        D_800AACD5 = selection;
        func_8007FC88(&D_800AACF8, D_800DE0C8[index].data);
    }
}
