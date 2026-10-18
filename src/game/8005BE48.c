typedef struct Entry {
    unsigned char kind;
    unsigned char flag;
    char pad1[6];
    int *value;
    char pad2[0x14];
    unsigned char state;
    char pad3[7];
    int *style;
    char pad4[0x14];
} Entry;

typedef struct Page {
    char pad[0x61];
    unsigned char flag;
    char pad2[6];
    int text;
} Page;

typedef struct List {
    char pad[0x3A1];
    unsigned char state;
    char pad2[6];
    int *current;
} List;

extern unsigned short D_800E4994;
extern int D_800A8B18;
extern List D_800A8B24;
extern int *D_800EADAC;
extern int D_800AE840;
extern int D_800AE898;
extern int D_800AE8A8;
extern Entry D_800A8FB8[];
extern int D_800EAD64;
extern int D_800EADD0;
extern int *func_8007A498(void *, int);
extern void func_800203E0(void);
extern int func_8007AC04(int *);

int func_8005BE48(int key, Page *page) {
    int *item;
    Entry *entry;

    if (D_800E4994 == 0) {
        item = func_8007A498(&D_800A8B18, key);
        if (item == 0) {
            page->text = *D_800EADAC;
            page->flag = 1;
            return 0;
        }
        D_800A8B24.current = item;
        if (item == &D_800AE840) {
            D_800A8B24.state = 2;
            func_800203E0();
        }
        if (item != &D_800AE898 && item != &D_800AE8A8) {
            for (entry = D_800A8FB8; entry->kind != 1; entry++) {
                if (entry->value == item) {
                    if (func_8007AC04(item) & 1) {
                        entry->style = &D_800EAD64;
                    } else {
                        entry->style = &D_800EADD0;
                    }
                    break;
                }
            }
            if (entry->kind == 1) {
                entry->kind = 24;
                entry->flag = 16;
                entry->value = item;
                entry->state = 4;
                if (func_8007AC04(item) & 1) {
                    entry->style = &D_800EAD64;
                } else {
                    entry->style = &D_800EADD0;
                }
            }
        }
    }
    return 0;
}
