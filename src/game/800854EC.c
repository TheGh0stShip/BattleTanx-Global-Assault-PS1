void func_8008AA48(void *destination, int value, int size);
int func_800852BC(unsigned int value);

int func_800854EC(unsigned char **handle, unsigned char *start,
                  unsigned char *end, int unused) {
    register unsigned char **saved_handle asm("$21");
    register unsigned char *arena asm("$18");
    register int result asm("$20");
    register unsigned int available asm("$19");
    register unsigned char *block asm("$17");
    register unsigned int block_size asm("$16");
    register void *volatile *global_pointer asm("$28");
    int bucket;

    register unsigned int too_small asm("$2");
    register unsigned int temporary asm("$2");
    register unsigned int mask asm("$2");
    register unsigned char *arena_end asm("$2");
    register unsigned char *wipe_start asm("$4");
    register unsigned char **slot asm("$2");

    saved_handle = handle;
    asm("" : "+r"(saved_handle));
    arena = start;
    asm("" : "+r"(arena));
    result = 0;
    asm("" : "+r"(result));
    available = end - arena;
    asm("" : "+r"(available));
    too_small = available < 0x88;
    asm("" : "+r"(too_small));
    if (too_small) {
        goto done;
    }

    block = arena + 0x88;
    asm("" : "+r"(block));
    temporary = end - block;
    asm("" : "+r"(temporary));
    block_size = temporary - 12;
    asm("" : "+r"(block_size));
    mask = ~3U;
    asm("" : "+r"(mask));
    block_size &= mask;
    asm("" : "+r"(block_size));
    wipe_start = arena + 8;
    asm("" : "+r"(wipe_start));
    temporary = block_size + 12;
    asm("" : "+r"(temporary));
    arena_end = block + temporary;
    asm("" : "+r"(arena_end));
    *(unsigned char **)arena = arena_end;
    *(unsigned int *)(arena + 4) = block_size;
    func_8008AA48(wipe_start, result, 0x80);
    bucket = func_800852BC(block_size);
    slot = (unsigned char **)(arena + bucket * 4);
    asm("" : "+r"(slot));
    slot[2] = block;

    too_small = available < 0x98;
    if (too_small) {
        goto done;
    }

    {
        register void *head asm("$3");
        register unsigned int tagged_size asm("$2");

        asm volatile(
            "lw %0, 0($28)\n\t"
            "ori %1, %2, 1"
            : "=r"(head), "=r"(tagged_size)
            : "r"(block_size));
        *(unsigned char **)(block + 8) = arena;
        *(unsigned int *)(arena + 0x88) = 0;
        *(unsigned int *)(block + 4) = tagged_size;
        *(unsigned int *)(block + 12) = 0;
        if (head == 0) {
        global_pointer[0] = arena;
        }
    }
    result = 1;
    if (saved_handle != (unsigned char **)-1) {
        *saved_handle = arena;
    }
done:
    return result;
}
