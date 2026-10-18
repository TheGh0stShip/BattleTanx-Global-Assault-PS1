typedef struct Entry {
    unsigned short flags;
    unsigned char reserved[10];
    void *value;
} Entry;

extern Entry D_800E474C[];

void func_8005A7E0(void *value) {
    unsigned short index = 0;

    do {
        Entry *entry = &D_800E474C[index];

        index++;
        if (entry->value == value) {
            entry->flags &= ~2;
            return;
        }
    } while (index < 10);
}
