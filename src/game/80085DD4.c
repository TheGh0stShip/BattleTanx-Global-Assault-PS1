unsigned char *func_80085B68(unsigned char *cursor, void **start_out,
                             unsigned char **owner_out);
void func_800853DC(unsigned char *owner, unsigned char *first,
                   unsigned char *second, int rebucket);
int func_800852BC(unsigned int value);
void func_80085300(unsigned char *owner, unsigned char *entry,
                   unsigned int amount, unsigned int bucket);

void func_80085DD4(unsigned char *cursor) {
    unsigned char *start;
    unsigned char *owner;
    register unsigned char *block asm("$16");
    register unsigned int size asm("$17");
    register unsigned int extent asm("$3");
    register unsigned char *next asm("$6");
    register unsigned char *current_owner asm("$4");
    register unsigned char *limit asm("$2");
    unsigned char *previous;

    if (cursor == 0) {
        return;
    }

    block = func_80085B68(cursor, (void **)&start, &owner);
    size = *(unsigned int *)(block + 4);
    *(unsigned int *)(block + 4) = size | 1;
    current_owner = owner;
    asm("" : "+r"(current_owner));
    extent = size + 12;
    asm("" : "+r"(extent));
    limit = *(unsigned char **)current_owner;
    asm("" : "+r"(limit));
    next = block + extent;
    asm("" : "+r"(next));
    if (next < limit &&
        (*(unsigned int *)(next + 4) & 1) != 0) {
        func_800853DC(current_owner, block, next, 0);
        {
            register unsigned int raw_size asm("$3") =
                *(unsigned int *)(block + 4);
            register unsigned int mask asm("$2") = ~1U;

            asm("" : "+r"(raw_size));
            asm("" : "+r"(mask));
            size = raw_size & mask;
        }
    }

    previous = *(unsigned char **)block;
    if (previous != 0 && (*(unsigned int *)(previous + 4) & 1) != 0) {
        func_800853DC(owner, previous, block, 1);
        return;
    }

    func_80085300(owner, block, size, func_800852BC(size));
}
