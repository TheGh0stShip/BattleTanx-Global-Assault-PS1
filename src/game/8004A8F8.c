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
typedef union {
    unsigned char kind;
    MoveA a;
    MoveB b;
    MoveC c;
    MoveD d;
} Movement;
extern void func_80049360(SVector *);

void func_8004A8F8(Movement *move, unsigned int kind) {
    switch (kind) {
    case 0:
        break;
    case 1:
        move->a.kind = 1;
        move->a.current = 0;
        move->a.target = 0;
        move->a.count = 0;
        break;
    case 2:
        move->b.kind = 2;
        move->b.current = 0;
        move->b.a = 0;
        move->b.b = 0;
        move->b.c = 0;
        move->b.d = 0;
        move->b.e = 0;
        move->b.f = 0;
        break;
    case 3:
        move->c.kind = 3;
        move->c.current = 0;
        move->c.b = 0;
        move->c.a = 0;
        func_80049360(&move->c.point);
        move->c.c = 0;
        move->c.d = 0;
        break;
    case 4:
        move->d.kind = 4;
        move->d.current = 0;
        move->d.a = 0;
        move->d.b = 0;
        break;
    }
}
