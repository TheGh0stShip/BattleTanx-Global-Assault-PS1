struct LookupItem {
    unsigned int key;
};

struct LookupRange {
    unsigned char pad_00[8];
    unsigned int start;
    unsigned int end;
    unsigned int stride;
};

extern struct LookupRange D_80086058;

struct LookupItem *func_80086694(unsigned int key) {
    unsigned int stride = D_80086058.stride;
    unsigned int mask = -stride;
    unsigned int cursor = D_80086058.start & mask;
    struct LookupItem *result = 0;
    unsigned int end = D_80086058.end & mask;

    while (cursor < end && result == 0) {
        struct LookupItem *item = *(struct LookupItem **)cursor;

        if (item->key == key) {
            result = item;
        }
        cursor = (cursor + stride) & mask;
    }
    return result;
}
