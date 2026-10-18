typedef struct {
    short x;
    short y;
    short z;
    short pad;
} SVector;
typedef struct {
    unsigned char kind;
    char pad1;
    short current;
    int target;
    short count;
} MoveA;
typedef struct {
    unsigned char kind;
    char pad1;
    short current;
    int a;
    int b;
    short c;
    short d;
    short e;
    unsigned char f;
} MoveB;
typedef struct {
    unsigned char kind;
    char pad1;
    short current;
    int a;
    int pad8;
    int b;
    SVector point;
    unsigned char c;
    char pad19;
    short d;
} MoveC;
typedef struct {
    unsigned char kind;
    char pad1;
    short current;
    int a;
    int b;
} MoveD;
typedef struct {
    unsigned char kind;
    char pad1;
    short current;
    void *next;
    unsigned short id;
} MoveFree;
typedef union {
    unsigned char kind;
    MoveFree free;
    MoveA a;
    MoveB b;
    MoveC c;
    MoveD d;
} Movement;
typedef struct {
    char pad0[0xE008];
    Movement *free_moves;
} MoveSystem;
extern MoveSystem *D_800A5B24;
extern void func_80049360(SVector *);

unsigned short func_8004A694(Movement **out, unsigned int kind) {
    MoveSystem *sys = D_800A5B24;
    Movement *move = sys->free_moves;
    unsigned short id;

    if (move == 0) {
        if (out != 0) {
            *out = 0;
        }
        return 0;
    }
    id = move->free.id;
    sys->free_moves = move->free.next;
    move->kind = kind;
    switch (kind) {
    case 2:
        move->b.current = 0;
        move->b.a = 0;
        move->b.b = 0;
        move->b.c = 0;
        move->b.d = 0;
        move->b.e = 0;
        move->b.f = 0;
        break;
    case 3:
        move->c.current = 0;
        move->c.b = 0;
        move->c.a = 0;
        func_80049360(&move->c.point);
        move->c.c = 0;
        move->c.d = 0;
        break;
    case 4:
        move->d.kind = kind;
        move->d.current = 0;
        move->d.a = 0;
        move->d.b = 0;
        break;
    }
    if (out != 0) {
        *out = move;
    }
    return id;
}
