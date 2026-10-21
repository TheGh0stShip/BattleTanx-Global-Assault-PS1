typedef struct DirEntry {
    char name[20];
    int attr;
    int size;
    struct DirEntry *next;
    int head;
    char system[4];
} DirEntry;

typedef struct CardInfo {
    char pad00[4];
    unsigned char busy;
    char pad05;
    unsigned char pending;
    unsigned char dirty;
    unsigned char header;
    char pad09[0x27];
    int handle;
    char pad34[0xB8];
    char buffer[0x200];
    unsigned int file_size;
} CardInfo;

extern CardInfo D_800EE588;
extern void func_800871E0(void);
extern void func_80087460(int);
extern int func_80086FC4(int);
extern void func_80086F0C(char *, char *);
extern void func_80096008(int);
extern int func_80096138(int, char *, int);
extern int func_80095DB4(int, char *, DirEntry *, int *, int, int);
extern int func_80096340(int, char *);
extern int func_800952D0(int, char *, int);
extern int func_80086EC8(void);
extern int func_80095684(void *, int, int);
extern void func_80086CAC(int, int *, int *);
extern void func_800877E4(int, char *, int, int);

int func_80087950(int chan, char *name) {
    char path[24];
    DirEntry entry;
    int count;
    int event;
    int code;
    int result = 0;
    unsigned int blocks;
    int size;
    int r;
    int len;
    int n;

    if (D_800EE588.busy != 0) {
        func_800871E0();
    }
    if (D_800EE588.pending != 0) {
        func_80087460(D_800EE588.handle);
    }
    if ((func_80086FC4(chan) & 3) != 3) {
        goto done;
    }
        func_80086F0C(path, name);
        blocks = D_800EE588.file_size >> 13;
        func_80096008(0);
        r = func_80096138(chan, path, blocks);
        if (r == 6) {
            size = 0;
            r = func_80095DB4(chan, path, &entry, &count, 0, 1);
            if (r == 0) {
                if (count == 1) {
                    size = entry.size;
                }
                if (size != blocks << 13) {
                    r = func_80096340(chan, path);
                    if (r == 0) {
                        r = func_80096138(chan, path, blocks);
                    }
                    if (r == 6) {
                        r = 7;
                    }
                }
            }
        }
        if (r != 0 && r != 6) {
            goto done;
        }
        if (func_800952D0(chan, path, 2) != 0) {
            goto done;
        }
        len = func_80086EC8();
        n = len;
        if (D_800EE588.header != 0) {
            n = len - 4;
        }
        if (func_80095684(D_800EE588.buffer, 0, n)) {
            func_80086CAC(0x60, &event, &code);
            if (event == 6 && code == 0) {
                func_800877E4(chan, name, blocks << 13, len);
                result = D_800EE588.handle;
                D_800EE588.dirty = 0;
            }
        }
done:
    return result;
}
