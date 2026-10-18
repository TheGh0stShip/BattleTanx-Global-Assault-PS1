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

extern Entry D_800A8FB8[];
extern int D_800EAD64;
extern int D_800EADD0;
extern unsigned short D_800A60D8;
extern unsigned char D_800AED48;
extern unsigned char D_800AED49;
extern unsigned char D_800AED4A;
extern unsigned char D_800AED4B;
extern unsigned char D_800AED4C;
extern unsigned char D_800AED4F;
extern unsigned char D_800AED50;
extern unsigned char D_800AED51;
extern unsigned char D_800AED52;
extern unsigned char D_800AED53;
extern unsigned char D_800AED54;
extern unsigned char D_800AED55;
extern unsigned char D_800AED56;
extern unsigned char D_800AED57;
extern unsigned char D_800AED58;
extern unsigned char D_800AED59;
extern int D_800AE830;
extern int D_800AE850;
extern int D_800AE860;
extern int D_800AE86C;
extern int D_800AE878;
extern int D_800AE884;
extern int D_800AE8B8;
extern int D_800AE8C4;
extern int D_800AE8D0;
extern int D_800AE8DC;
extern int D_800AE8E8;
extern int D_800AE8F4;
extern int D_800AE900;
extern int D_800AE910;
extern int D_800AE91C;
extern int D_800AE92C;
extern int D_800AE940;
extern int func_8007AC04(int *);

static inline void append_item(int *item) {
    unsigned char enabled;
    Entry *entry;

    entry = D_800A8FB8;
    enabled = func_8007AC04(item) & 1;
    while (entry->kind != 1) {
        entry++;
    }
    entry->kind = 24;
    entry->flag = 16;
    entry->value = item;
    if (enabled) {
        entry->style = &D_800EAD64;
    } else {
        entry->style = &D_800EADD0;
    }
    entry->state = 4;
}

void func_8005BFCC(void) {
    Entry *entry;

    for (entry = D_800A8FB8; entry->kind != 1; entry++) {
        entry->kind = 1;
        entry->flag = 3;
        entry->value = 0;
        entry->style = 0;
    }
    if (D_800A60D8 != 0) {
        append_item(&D_800AE830);
    }
    if (D_800AED48 != 0) {
        append_item(&D_800AE850);
    }
    if (D_800AED49 != 0) {
        append_item(&D_800AE860);
    }
    if (D_800AED4A != 0) {
        append_item(&D_800AE86C);
    }
    if (D_800AED4B != 0) {
        append_item(&D_800AE878);
    }
    if (D_800AED4C != 0) {
        append_item(&D_800AE884);
    }
    if (D_800AED4F != 0) {
        append_item(&D_800AE8B8);
    }
    if (D_800AED50 != 0) {
        append_item(&D_800AE8C4);
    }
    if (D_800AED51 != 0) {
        append_item(&D_800AE8D0);
    }
    if (D_800AED52 != 0) {
        append_item(&D_800AE8DC);
    }
    if (D_800AED53 != 0) {
        append_item(&D_800AE8E8);
    }
    if (D_800AED54 != 0) {
        append_item(&D_800AE8F4);
    }
    if (D_800AED55 != 0) {
        append_item(&D_800AE900);
    }
    if (D_800AED56 != 0) {
        append_item(&D_800AE910);
    }
    if (D_800AED57 != 0) {
        append_item(&D_800AE91C);
    }
    if (D_800AED58 != 0) {
        append_item(&D_800AE92C);
    }
    if (D_800AED59 != 0) {
        append_item(&D_800AE940);
    }
}
