typedef struct Entry {
    unsigned char kind;
    char pad1[7];
    int *value;
    char pad2[0x1C];
    int *style;
    char pad3[0x14];
} Entry;

extern signed char D_800E4800;
extern unsigned char D_800E4804;
extern unsigned char D_800E4808;
extern unsigned char D_800E480C;
extern unsigned char D_800E4810;
extern unsigned char D_800E4814;
extern unsigned char D_800E4818;
extern unsigned char D_800E481C;
extern unsigned char D_800E4820;
extern unsigned char D_800E4850;
extern short D_800A60D8;
extern unsigned char D_800AED48;
extern unsigned char D_800AED49;
extern unsigned char D_800AED4A;
extern unsigned char D_800AED4B;
extern unsigned char D_800AED4C;
extern unsigned char D_800AED4F;
extern unsigned char D_800AED50;
extern unsigned char D_800AED51;
extern unsigned char D_800AED52;
extern Entry D_800A8FB8[];
extern int D_800EAD30;
extern int D_800EAD64;
extern int D_800EADD0;
extern int func_8007AC04(int *);

void func_8005CA14(void) {
    Entry *entry;

    D_800A60D8 = D_800E4800;
    D_800AED48 = D_800E4804;
    D_800AED49 = D_800E4808;
    D_800AED4A = D_800E480C;
    D_800AED4B = D_800E4810;
    D_800AED4C = D_800E4814;
    D_800AED4F = D_800E4818;
    D_800AED50 = D_800E481C;
    D_800AED51 = D_800E4820;
    D_800AED52 = D_800E4850;
    for (entry = D_800A8FB8; entry->kind != 1; entry++) {
        if (entry->value == &D_800EAD30) {
            break;
        }
        if (func_8007AC04(entry->value) & 1) {
            entry->style = &D_800EAD64;
        } else {
            entry->style = &D_800EADD0;
        }
    }
}
