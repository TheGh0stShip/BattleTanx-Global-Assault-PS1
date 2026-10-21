extern int D_800B903C[];
extern int func_80094AAC(int c);

int func_800A1134(unsigned char *s, int fold)
{
    int sum;
    unsigned int i;
    int c;

    sum = 0;
    i = 0;
    while ((c = *s) != 0) {
        if (fold) {
            c = (unsigned char)func_80094AAC(c);
        } else {
            c = (unsigned char)c;
        }
        sum += c * D_800B903C[i];
        if (++i >= 31) {
            i = 0;
        }
        s++;
    }
    return sum;
}
