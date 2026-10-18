typedef unsigned char u8;
typedef unsigned short u16;

typedef struct MenuEvent {
    u8 pad[8];
    u8 *data;
} MenuEvent;

extern u16 D_800E4994;
extern u16 D_800E4A90;

int func_80061398(void *object, MenuEvent *event) {
    event->data[7] = 0;
    D_800E4994 = 0;
    D_800E4A90 = 0;
    return 1;
}
