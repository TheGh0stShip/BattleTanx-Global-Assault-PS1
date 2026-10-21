typedef struct {
    unsigned char size;
    unsigned char pad[3];
    unsigned char *data;
} Block;

typedef struct {
    unsigned short *words;
    unsigned char *entries;
    Block *blocks;
    char pad0C[0x30];
    unsigned char *cur;
    char pad40[6];
    unsigned char state;
    unsigned char index;
    unsigned char remain;
    unsigned char next;
    char pad4A[0x99];
    unsigned char word_count;
    char padE4[5];
    unsigned char entry_count;
    unsigned char block_count;
} Loader;

extern unsigned char *D_800EFC58;

int func_8009F128(Loader *s)
{
    unsigned char *e;
    unsigned char *src;
    Block *b;
    int n;
    int v;
    unsigned char *p;
    unsigned char **dst;

    switch (s->state) {
    case 2:
        s->words[s->index] = s->cur[5] + (s->cur[4] << 8);
        if (++s->index < s->word_count)
            return 0;
        s->index = 0;
        break;
    case 3:
        e = s->entries + s->index * 5;
        e[0] = s->cur[4];
        e[1] = s->cur[5] & 0x7f;
        e[2] = s->cur[6];
        e[3] = s->cur[7];
        v = s->cur[5];
        e[4] = v >> 7;
        if (++s->index < s->entry_count)
            return 0;
        s->index = 0;
        s->remain = 0;
        break;
    case 4:
        b = &s->blocks[s->index];
        if (s->remain == 0) {
            b->size = s->remain = s->cur[4];
            n = 3;
            src = s->cur + 5;
            if (s->index == 0)
                D_800EFC58 = b->data = (unsigned char *)&s->blocks[s->block_count];
            else
                D_800EFC58 = b->data = b[-1].data + ((b[-1].size + 3) & 0x1fc);
        } else {
            src = s->cur + 2;
            n = 6;
        }
        if (n-- != 0) {
            dst = &D_800EFC58;
            do {
                if (s->remain == 0)
                    goto done;
                p = *dst;
                *p = *src++;
                *dst = p + 1;
                s->remain--;
            } while (n-- != 0);
        }
        if (s->remain == 0)
            goto done;
    out:
        return 0;
    done:
        if (++s->index < s->block_count)
            goto more;
        s->next = 6;
        s->state = 0xfe;
        return 0;
    more:
        s->remain = 0;
        goto out;
    }
    return 1;
}
