typedef void (*CardCallback)(int, int, int, int);
typedef struct {
    char name[20];
    unsigned char selected;
    char pad15[3];
    int size;
    char pad1c[12];
} DirEntry;
typedef struct {
    int w0;
    volatile unsigned char active;
    volatile unsigned char busy;
    volatile unsigned char open;
    volatile unsigned char readonly;
    volatile unsigned char b8;
    volatile unsigned char b9;
    char pad_a[2];
    int slot_state[8];
    char pad2c[4];
    int port;
    char pad34[8];
    unsigned char buf[0x80];
    int wBC;
    int wC0;
    int wC4;
    char padC8[0xC];
    int wD4;
    char padD8[0xC];
    CardCallback done;
    CardCallback error;
    char padEC[0x210];
    unsigned int checksum;
    DirEntry entries[15];
    int count;
    int loaded;
} CardState;
extern CardState D_800EE588;

extern void func_80094198(void);
extern void func_80096E6C(unsigned int a, int b);
extern void func_80094168(void);
extern void func_80086CAC(int a, int *b, int *c);
extern void func_80087134(int a);

void func_800871E0(void) {
    CardState *s = &D_800EE588;
    int a;
    int b;

    if (s->active != 0) {
        s->busy = 1;
        func_80094198();
        func_80096E6C(0xF4000001, 0x8000);
        func_80094168();
        func_80086CAC(0xA4, &a, &b);
        if (s->active != 0) {
            func_80087134(0);
        }
        s->active = 0;
        s->busy = 0;
    }
}
