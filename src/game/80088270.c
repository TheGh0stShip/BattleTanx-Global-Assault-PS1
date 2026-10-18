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

extern int func_80088324();
extern void func_80087424(void);

int func_80088270(int unused, int arg) {
    int result = 0;
    unsigned int expected;
    unsigned int value;

    if (D_800EE588.b8 != 0) {
        D_800EE588.b9 = 0;
        expected = D_800EE588.checksum;
        if (func_80088324(10, arg, result, &value, 4, func_80087424) != 0) {
            func_80088324(12, arg, 1);
            if (D_800EE588.b9 != 0) {
                result = value == ~expected;
            }
        }
    }
    return result;
}
