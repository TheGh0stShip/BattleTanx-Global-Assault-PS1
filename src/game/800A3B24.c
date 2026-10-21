typedef struct {
    char pad0[12];
    char *buf;
    char pad10[38];
    unsigned char mode;
} Stream;

extern int D_800B8CB4;
extern int D_800B8CC4;
extern int D_800B8CB0;
extern void (*D_800B8CA4)(void);
extern void (*D_800B8CA0)(void);
extern int D_800BD45C;
extern void (*D_800B8C8C)(char *);
extern void func_8009EAA8(Stream *, int);

void func_800A3B24(Stream *s)
{
    if (D_800B8CB4 == D_800B8CC4 && D_800B8CB0 != 0) {
        D_800B8CA4();
        D_800B8CA0();
    }
    if (D_800BD45C != 0) {
        D_800B8C8C(s->buf);
        D_800B8C8C(s->buf + 240);
    }
    if (s->mode == 0) {
        func_8009EAA8(s, 66);
    } else {
        func_8009EAA8(s, s->mode);
    }
}
