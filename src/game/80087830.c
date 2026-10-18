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
extern int func_80087460(int port);
extern int func_80086FC4(int port);
extern void func_80086F0C(char *path, char *name);
extern int func_80095DB4(int port, char *name, DirEntry *entries, int *count, int first, int max);
extern int func_800952D0(int port, char *path, int mode);
extern int func_80087380(void);
extern void func_800877E4(int port, char *name, int size, int header);

int func_80087830(int port, char *name) {
    int result = 0;
    char path[24];
    DirEntry entry;
    int count;
    int n;

    if (D_800EE588.active != 0) {
        func_800871E0();
    }
    if (D_800EE588.open != 0) {
        func_80087460(D_800EE588.port);
    }
    if ((func_80086FC4(port) & 3) == 3) {
        func_80086F0C(path, name);
        if (func_80095DB4(port, path, &entry, &count, 0, 1) == 0) {
            n = count;
            if (n == 1 && func_800952D0(port, path, 1) == 0) {
                func_800877E4(port, name, entry.size, func_80087380());
                result = D_800EE588.port;
                D_800EE588.readonly = n;
            }
        }
    }
    return result;
}
