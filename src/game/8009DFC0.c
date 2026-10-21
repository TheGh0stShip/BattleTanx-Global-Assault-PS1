typedef struct {
    char pad00[4];
    unsigned char *table;
    char pad08[0x20];
    unsigned char *buf;
    char pad2C[8];
    unsigned char count;
    char pad35[0x22];
    unsigned char out[6];
    unsigned char map[0x89];
    unsigned short active;
    unsigned char type;
    unsigned char entry_count;
} Pad;

extern int D_800B8CBC;
extern void func_8008AC90(void *, int);

void func_8009DFC0(Pad *s)
{
    int i;
    int j;
    int n;
    int mask;
    int ok;
    int cost;
    unsigned char *m;
    unsigned char *b;
    unsigned char t;

    func_8008AC90(s->out, 6);
    if (s->active != 0 && s->buf != 0) {
        n = 6;
        if (s->count < 7) {
            __asm__("" : : : "memory");
            n = s->count;
        }
        if (s->entry_count != 0) {
            i = 0;
            do {
                ok = 0;
                mask = 1;
                if (s->table[i * 5 + 2] != 0)
                    mask = 0xff;
                m = s->map;
                b = s->buf;
                j = 0;
                if (n != 0) {
                    do {
                        if (*m == i && (*b & mask)) {
                            ok = 1;
                            goto found;
                        }
                        m++;
                        j++;
                        b++;
                    } while (j < n);
                }
            found:
                if (ok) {
                    cost = D_800B8CBC + s->table[i * 5 + 3];
                    if (cost < 61) {
                        D_800B8CBC = cost;
                    } else {
                        ok = 0;
                    }
                }
                if (ok) {
                    m = s->map;
                    b = s->out;
                    j = 0;
                    if (n != 0) {
                        do {
                            if (*m++ == i)
                                *b = 1;
                            j++;
                            b++;
                        } while (j < n);
                    }
                }
                i++;
            } while (i < s->entry_count);
        }
        return;
    }
    t = s->type;
    if ((unsigned)(t - 4) < 2 || t == 7) {
        if (s->active == 0 && s->count >= 2) {
            if ((s->buf[0] & 0xc0) != 0x40)
                return;
            if (!(s->buf[1] & 1))
                return;
            if (D_800B8CBC + 10 >= 61)
                return;
            s->out[0] = s->out[1] = 1;
            D_800B8CBC += 10;
            return;
        }
    }
    __asm__("" : : : "memory");
    if (s->type == 3) {
        s->out[0] = 1;
        return;
    }
    if (s->active == 0) {
        for (j = 0; j < 6; j++)
            s->out[j] = 1;
    }
}
