typedef struct Entry {
    int value;
    short timer;
} Entry;

extern Entry D_800AAEF4;
extern Entry D_800AAEFC;
extern int *D_800AAF24;
extern int *D_800AAF28;
extern int D_800E4A9C;

void func_80063BF8(int value, unsigned short player, unsigned int kind) {
    Entry *entry;
    int **slot;

    switch (player) {
    case 0:
        entry = &D_800AAEF4;
        slot = &D_800AAF24;
        break;
    case 1:
        entry = &D_800AAEFC;
        slot = &D_800AAF28;
        break;
    default:
        entry = &D_800AAEF4;
        slot = &D_800AAF24;
        break;
    }
    entry->timer = 50;
    entry->value = value;
    if (kind < 2 || kind == 4) {
        *slot = &D_800E4A9C;
    } else {
        *slot = 0;
    }
}
