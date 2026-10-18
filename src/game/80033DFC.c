typedef struct { int x, y, z; } Vector;
typedef struct { int pad; unsigned int mode; char pad2; unsigned char limit; char pad3[42]; unsigned char counts[8]; } Rules;
typedef struct { char pad[16]; int base; } Header;
typedef struct { Header *header; } Ctx;
typedef struct { unsigned char pad; unsigned char team; unsigned short body; int offset; } Def;
typedef struct { char pad[58]; short slot; } Unit;
typedef struct { int pad[2]; int link; Vector pos; unsigned char count; char pad2[3]; Unit *unit; } Spawn;
extern Rules D_800D2FE4;
extern unsigned int D_800D2FE8;
extern char *D_800D3258;
Spawn *func_800237D0(int, int);
Unit *func_800263F0(int, Ctx *, Vector *, int);
int func_80026300(Ctx *, int);
void func_800334F8(Spawn *, int, int);

static inline int mode_allows_spawn(void) {
    switch (D_800D2FE8) {
    case 1:
    case 3:
    case 11:
        return 1;
    }
    return 0;
}

void func_80033DFC(Def *def, Ctx *ctx, Vector *pos, unsigned short id) {
    Rules *rules;
    Spawn *s;
    int count;

    if (mode_allows_spawn()) {
        rules = &D_800D2FE4;
        count = rules->counts[def->team];
        if (count < rules->limit) {
            s = func_800237D0(21, 32);
            if (s != 0) {
                s->pos = *pos;
                s->count = count;
                s->unit = func_800263F0(ctx->header->base + def->offset, ctx, pos, id);
                s->unit->slot = (unsigned int)((char *)s - D_800D3258) >> 6;
                if (rules->mode == 1 || rules->mode == 11) {
                    func_800334F8(s, func_80026300(ctx, def->body), 0);
                } else {
                    s->link = 0;
                }
            }
        }
    }
}
