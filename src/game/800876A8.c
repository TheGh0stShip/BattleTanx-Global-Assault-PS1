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

extern void func_800871E0(void);
extern int func_80086FC4(unsigned int port);
extern void func_80096008(int a);
extern int func_800964FC(unsigned int port);

int func_800876A8(unsigned int port) {
    int result = 0;
    int slot;
    int rc;

    if (D_800EE588.active != 0) {
        func_800871E0();
    }
    if (func_80086FC4(port) & 1) {
        func_80096008(0);
        rc = func_800964FC(port);
        slot = ((port >> 2) & 4) | (port & 3);
        if (rc == 0) {
            D_800EE588.slot_state[slot] = 3;
            result = 1;
        } else {
            D_800EE588.slot_state[slot] = 1;
        }
    }
    return result;
}
