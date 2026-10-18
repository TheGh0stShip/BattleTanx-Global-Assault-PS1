typedef struct TypeInfo {
    int pad[3];
    int value;
    int pad2[5];
} TypeInfo;

typedef struct Item {
    short id;
    char pad2[2];
    short kind;
    char pad6;
    unsigned char type;
    struct Item *link;
    char padC[0x18];
    int value;
} Item;

extern TypeInfo D_800ADF64[];

void func_8006F224(Item *item, Item *other) {
    if (item->kind == 73) {
        if (other != 0) {
            if (item->id != other->id) {
                return;
            }
            if (item->link != other) {
                return;
            }
        }
        if (item != 0) {
            item->value = D_800ADF64[item->type].value;
        }
    }
}
