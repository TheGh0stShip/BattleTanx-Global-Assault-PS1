typedef struct SysInfo {
    char pad00[0x14];
    unsigned int start;
    unsigned int end;
    unsigned int align;
} SysInfo;

extern SysInfo D_80086058;
extern void func_8008A884(void *, void *, unsigned int);

void func_800864C4(void) {
    SysInfo *base = &D_80086058;
    SysInfo *info;
    unsigned int align = base->align;
    unsigned int mask = -align;
    int *p = (int *)(base->start & mask);
    int *end = (int *)(base->end & mask);
    register int *last asm("$21");
    int *prev;
    int *pair;
    int *q;
    int tmp;
    register int value asm("$22");
    unsigned int n;

    {
        register unsigned int t asm("$2") = (unsigned int)end - align;

        last = (int *)(t & mask);
    }
    if (p < end) {
        info = base;
        __asm__ volatile("" : "=r"(info) : "0"(info));
    top:
        if (*p == 0) {
            goto second;
        }
        if (*p == -1) {
            prev = (int *)(((unsigned int)p - align) & mask);
            pair = (int *)(((unsigned int)prev - align) & mask);
            tmp = *prev;
            value = *pair;
            *pair = tmp;
            *prev = value;
            q = (int *)(info->start & mask);
            while (q < pair) {
                if (*q == value) {
                    n = (unsigned int)last - (unsigned int)q;
                    if (n != 0) {
                        func_8008A884(q, (void *)(((unsigned int)q + align) & mask), n);
                    }
                    *last = 0;
                    p = (int *)(((unsigned int)p - align) & mask);
                } else {
                    q = (int *)(((unsigned int)p + align) & mask);
                }
            }
            n = (unsigned int)last - (unsigned int)p;
            if (n != 0) {
                func_8008A884(p, (void *)(((unsigned int)p + align) & mask), n);
            }
            *last = 0;
        } else {
            p = (int *)(((unsigned int)p + align) & mask);
        }
        if (p < end) {
            goto top;
        }
    }
second:
    for (p = (int *)(D_80086058.start & mask); p < end; p = (int *)(((unsigned int)p + align) & mask)) {
        if (*p == 0) {
            break;
        }
        for (q = (int *)(((unsigned int)p + align) & mask); q < end; q = (int *)(((unsigned int)q + align) & mask)) {
            if (*q == 0) {
                break;
            }
            if (*q == *p) {
                n = (unsigned int)last - (unsigned int)q;
                if (n != 0) {
                    func_8008A884(q, (void *)(((unsigned int)q + align) & mask), n);
                }
                *last = 0;
            }
        }
    }
}
