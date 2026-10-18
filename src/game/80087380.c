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
extern int func_80095494(unsigned char *buf, int a, int len);
extern void func_80086CAC(int timeout, int *result, int *status);
extern int func_80086E38(unsigned char b);

int func_80087380(void) {
    int result = 0;
    unsigned char *buf;
    int event;
    int status;

    func_80096008(result);
    buf = D_800EE588.buf;
    if (func_80095494(buf, result, 128) != 0) {
        func_80086CAC(24, &event, &status);
        if (event == 5 && status == 0) {
            result = func_80086E38(buf[2]);
            if (D_800EE588.b8 != 0) {
                result += 4;
            }
        }
    }
    return result;
}
