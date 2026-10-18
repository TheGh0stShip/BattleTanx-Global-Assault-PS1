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
extern int func_80086FC4(int a);
extern void func_80096008(int a);
extern int func_80096340(int a, int b);

int func_8008775C(int name, int arg) {
    int result = 0;

    if (D_800EE588.active != 0) {
        func_800871E0();
    }
    if ((func_80086FC4(name) & 3) == 3) {
        func_80096008(0);
        result = func_80096340(name, arg) == 0;
    }
    return result;
}
