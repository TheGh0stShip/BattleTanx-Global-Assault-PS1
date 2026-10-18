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

extern void func_80096008(int a);

void func_80087134(int status) {
    CardCallback done;
    CardCallback error;
    int length;

    D_800EE588.active = 0;
    func_80096008(0);
    done = D_800EE588.done;
    if (done != 0) {
        length = status ? D_800EE588.wD4 : 0;
        D_800EE588.done = 0;
        done(D_800EE588.w0, D_800EE588.wC4, length, status);
    }
    error = D_800EE588.error;
    if (error != 0) {
        length = status ? D_800EE588.wD4 : 0;
        D_800EE588.error = 0;
        error(D_800EE588.w0, D_800EE588.wC4, length, status);
    }
}
