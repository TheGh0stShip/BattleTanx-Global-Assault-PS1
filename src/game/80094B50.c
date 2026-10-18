typedef struct Stream {
    unsigned char pad0[0x10];
    struct Stream *self;
    unsigned char pad14[0x30 - 0x14];
    unsigned char *pending;
    unsigned int flags;
    unsigned char busy;
    unsigned char pad39[0x49 - 0x39];
    unsigned char state;
} Stream;
extern Stream *(*D_800B8C88)(void);

int func_80094B50(void)
{
    Stream *s = D_800B8C88();

    if ((s->flags & 0xFFFF0000) != 0 || (s != s->self && s->busy != 0) || *s->pending != 0) {
        switch (s->state) {
        case 3:
            return 1;
        case 2:
            return 1;
        case 6:
            return 4;
        }
    }
    return s->state;
}
