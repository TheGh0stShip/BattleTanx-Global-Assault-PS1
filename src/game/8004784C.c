static inline int fixed_mul(int a, int b) {
    int low;
    int high;

    __asm__ volatile("mult\t%2, %3\n\tmflo %0\n\tmfhi %1\n\tsrl %0, %0, 12\n\tsll %1, %1, 20\n\tor %0, %0, %1"
                     : "=&r"(low), "=&r"(high) : "r"(a), "r"(b));
    return low;
}
unsigned int func_80086C84(void);
int func_8004784C(unsigned char chance, unsigned char spread, int dist, int range, int *out) {
    int scaled;
    int falloff;
    unsigned char odds;
    int scale;
    int jitter;

    odds = chance;
    if (dist < fixed_mul(3686, range)) {
        falloff = 0;
    } else {
        scaled = fixed_mul(3686, dist - range);
        falloff = fixed_mul(409, (scaled << 12) / range);
        odds = chance + fixed_mul(falloff, 100 - chance);
    }
    if ((unsigned char)(func_80086C84() % 100) >= odds) {
        return 1;
    }
    jitter = fixed_mul(func_80086C84() % 819 + 3686, scale = (short)spread * 30);
    *out = fixed_mul(4096 - (falloff >> 1), jitter);
    return 0;
}
