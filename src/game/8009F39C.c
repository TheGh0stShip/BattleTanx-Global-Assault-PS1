typedef struct PadPort {
    int unk00;
    unsigned char *config;
    char pad08[0xC];
    void *on_start;
    void *on_data;
    char pad1C[4];
    unsigned char *map;
    char pad24[8];
    unsigned char *out;
    char pad30[5];
    unsigned char cmd_len;
    unsigned char cmd;
    char pad37[0xF];
    unsigned char state;
} PadPort;

extern int (*D_800B8C90)(PadPort *);
void func_8009F404(PadPort *p);
int func_8009F420(PadPort *p);

int func_8009F39C(PadPort *p, unsigned char *map)
{
    if (D_800B8C90(p) != 0) {
        return 0;
    }
    p->state = 1;
    p->on_start = func_8009F404;
    p->map = map;
    p->on_data = func_8009F420;
    {
        int result = 1;
        __asm__("" : "+r"(result));
        return result;
    }
}
