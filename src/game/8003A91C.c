typedef struct { unsigned addr : 24; unsigned len : 8; } Tag;
typedef struct { char pad[0xCC]; int ot; char pad2[0x128 - 0xD0]; } Buf;
extern Buf D_800DDB9C[];
extern int D_800A48B0;
extern Tag *func_8007F7D8(void);
extern void func_80080440(Tag *, int *);
extern Tag *func_8003A9F4(void);
extern void func_8007F7E8(Tag *);

static inline Buf *current_buf(void)
{
    return &D_800DDB9C[D_800A48B0];
}

void func_8003A91C(void)
{
    Tag *p;

    p = func_8007F7D8();
    func_80080440(p, &current_buf()->ot);
    p->addr = func_8003A9F4()->addr;
    func_8003A9F4()->addr = (unsigned int)p;
    func_8007F7E8(p + 16);
}
