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
extern int func_80086FC4(int port);
extern void func_80096008(int a);
extern int func_80095DB4(int port, char *name, DirEntry *entries, int *count, int first, int max);
extern unsigned int func_80086EC8(void);
extern char D_800C6078[];

unsigned int func_80087268(int port) {
    unsigned int result = 0;
    int count;
    unsigned int total;
    unsigned int avail;
    unsigned int used;
    int i;

    if (D_800EE588.active != 0) {
        func_800871E0();
    }
    if ((func_80086FC4(port) & 3) == 3) {
        func_80096008(0);
        if (func_80095DB4(port, D_800C6078, D_800EE588.entries, &count, 0, 15) == 0) {
            total = 0;
            for (i = 0; i < count; i++) {
                total += (D_800EE588.entries[i].size + 0x1FFF) & ~0x1FFF;
            }
            if (total < 0x1E000) {
                avail = 0x1E000 - total;
                used = func_80086EC8();
                if (used < avail) {
                    result = avail - used;
                }
            }
        }
    }
    return result;
}
