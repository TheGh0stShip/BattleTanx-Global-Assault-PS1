typedef struct Position {
    int x;
    int y;
    int z;
} Position;

typedef struct Offset {
    signed char x;
    signed char y;
} Offset;

typedef struct Effect {
    unsigned char fields00[8];
    Position position;
    int created;
    Offset offsets[4];
} Effect;

typedef char Effect_size[(sizeof(Effect) == 0x20) ? 1 : -1];

extern int D_800D2FE0;
extern Effect *func_800237D0(int, int);
extern unsigned int func_80086C84(void);

void func_80034544(Position *position) {
    Effect *effect = func_800237D0(49, 32);
    int i;

    if (effect != 0) {
        effect->position = *position;
        effect->created = D_800D2FE0;
        for (i = 0; i < 4; i++) {
            effect->offsets[i].x = func_80086C84() % 100 - 50;
            effect->offsets[i].y = func_80086C84() % 20 - 10;
        }
    }
}
