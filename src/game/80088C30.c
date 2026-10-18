typedef struct Ring {
    char pad00[0x48];
    char *base;
    unsigned int size;
    int wrap;
    int pad54;
    unsigned int start;
    unsigned int end;
} Ring;

extern Ring D_800EEAE8;
extern unsigned int func_80088B00(int, unsigned int);
extern void func_8008A7BC(void *, void *, unsigned int);

void func_80088C30(unsigned int *pos, char **dst, unsigned int *len) {
    unsigned int offset = func_80088B00(D_800EEAE8.wrap, *pos - D_800EEAE8.start);
    unsigned int avail = D_800EEAE8.end - *pos;
    unsigned int n = *len;
    unsigned int first;
    unsigned int second;

    if (avail < n) {
        n = avail;
    }
    first = n;
    second = 0;
    if (D_800EEAE8.size - offset < n) {
        first = D_800EEAE8.size - offset;
        second = n - first;
    }
    func_8008A7BC(*dst, D_800EEAE8.base + offset, first);
    *dst += first;
    if (second != 0) {
        func_8008A7BC(*dst, D_800EEAE8.base, second);
        *dst += second;
    }
    *pos += n;
    *len -= n;
}
