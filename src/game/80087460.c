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
extern int func_80088324();
extern void func_80087424(void);
extern void func_80095450(void);

int func_80087460(int port) {
    int result = 0;
    unsigned int value;

    if (D_800EE588.active != 0) {
        func_800871E0();
    }
    if (D_800EE588.open != 0 && port == D_800EE588.port) {
        result = 1;
        if (D_800EE588.b8 != 0 && D_800EE588.readonly == 0) {
            D_800EE588.b9 = 0;
            value = ~D_800EE588.checksum;
            result = func_80088324(11, port, 0, &value, 4, func_80087424);
            if (result != 0) {
                func_80088324(12, port, 1);
                result = D_800EE588.b9 == 1;
            }
        }
        func_80095450();
        D_800EE588.open = 0;
        D_800EE588.wC0 = 0;
        D_800EE588.wBC = 0;
    }
    return result;
}
