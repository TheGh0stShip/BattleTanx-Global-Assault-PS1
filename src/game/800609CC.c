typedef unsigned char u8;
typedef unsigned short u16;

typedef struct MenuEvent {
    u8 pad[8];
    void *data;
} MenuEvent;

extern u8 D_800AACE2;
extern int D_800D3028;
extern void *D_800E4860;
extern u16 D_800E4994;

int func_800609CC(void *object, MenuEvent *event) {
    D_800E4994 = 4;
    D_800D3028 = 0x3F;
    D_800AACE2 = 0x96;
    D_800E4860 = event->data;
    return 0;
}
