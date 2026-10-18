int func_800852BC(unsigned int value);
void func_80085300(unsigned char *owner, unsigned char *entry,
                   unsigned int amount, unsigned int bucket);
void func_8008532C(unsigned int *owner, unsigned int *entry,
                   unsigned int amount, unsigned int bucket);

void func_800853DC(unsigned char *owner, unsigned char *first,
                   unsigned char *second, int rebucket) {
    register unsigned char *saved_owner asm("$21") = owner;
    register unsigned char *saved_first asm("$20") = first;
    register unsigned char *saved_second asm("$19") = second;
    register unsigned int first_size asm("$17");
    register unsigned int second_size asm("$16");
    register unsigned int combined_size asm("$18");
    register unsigned int mask asm("$4") = ~1U;
    register unsigned int second_extent asm("$3");
    register unsigned char *after asm("$3");
    register unsigned char *limit asm("$2");

    asm("" : "+r"(saved_owner));
    asm("" : "+r"(saved_first));
    asm("" : "+r"(saved_second));
    asm("" : "+r"(mask));
    asm volatile(
        "lw $2, 4(%2)\n\t"
        "lw $3, 4(%3)\n\t"
        "and %0, $2, %4\n\t"
        "and %1, $3, %4"
        : "=r"(first_size), "=r"(second_size)
        : "r"(saved_first), "r"(saved_second), "r"(mask)
        : "$2", "$3");
    second_extent = second_size + 12;
    combined_size = first_size + second_extent;
    *(unsigned int *)(saved_first + 4) = combined_size | 1;
    limit = *(unsigned char **)saved_owner;
    after = saved_second + second_extent;
    if (after < limit) {
        *(unsigned char **)after = saved_first;
    }

    if (rebucket) {
        unsigned int first_bucket;
        unsigned int combined_bucket;

        first_bucket = func_800852BC(first_size);
        combined_bucket = func_800852BC(combined_size);
        if (first_bucket != combined_bucket) {
            func_8008532C((unsigned int *)saved_owner,
                          (unsigned int *)saved_first,
                          first_size, first_bucket);
            func_80085300(saved_owner, saved_first,
                          combined_size, combined_bucket);
        } else {
            register unsigned int delta asm("$3") = combined_size - first_size;

            *(unsigned int *)(saved_owner + 4) += delta;
        }
    } else {
        unsigned int second_bucket = func_800852BC(second_size);

        func_8008532C((unsigned int *)saved_owner,
                      (unsigned int *)saved_second,
                      second_size, second_bucket);
    }
}
