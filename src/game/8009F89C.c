extern int D_800B8D0C;
extern int D_800B8D10;
extern signed char D_800B6B31[];
extern char D_800EFCB8[];
extern void func_8009F74C(int fd, char *buf, int n);

void func_8009F89C(c)
signed char c;
{
    switch (c) {
    case '\n':
        func_8009F89C('\r');
        D_800B8D0C = 0;
        break;
    case '\t':
        do {
            func_8009F89C(' ');
        } while (D_800B8D0C & 7);
        return;
    default:
        if (D_800B6B31[(unsigned char)c] & 0x97) {
            D_800B8D0C++;
        }
        break;
    }
    if (D_800B8D10 >= 32) {
        func_8009F74C(1, D_800EFCB8, D_800B8D10);
        D_800B8D10 = 0;
    }
    {
        int *n = &D_800B8D10;
        int i = *n;
        D_800EFCB8[i] = c;
        *n = i + 1;
    }
}
