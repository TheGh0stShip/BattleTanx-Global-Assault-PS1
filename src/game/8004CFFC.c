typedef struct Vector {
    int x;
    int y;
    int z;
} Vector;

typedef struct PathTank {
    unsigned char pad000[8];
    Vector position;
    unsigned char pad014[0x13C - 0x14];
    Vector goal;
} PathTank;

typedef char Vector_size[(sizeof(Vector) == 0xC) ? 1 : -1];
typedef char PathTank_size[(sizeof(PathTank) == 0x148) ? 1 : -1];

extern int func_800494FC(Vector *, Vector *, Vector *);
extern int func_800495D8(Vector *, Vector *);

int func_8004CFFC(PathTank *tank, Vector *target_arg) {
    register Vector *target asm("$18") = target_arg;
    int reached = 0;
    register Vector *position asm("$16");
    Vector *goal;

    asm("" : "=r"(target) : "0"(target));

    do {
    } while (0);
    goal = &tank->goal;
    do {
        if (target == 0)
            break;
        position = &tank->position;
        if (func_800494FC(position, goal, target) != 1)
            break;
        if (func_800495D8(position, target) > 0x1E000)
            goto done;
    } while (0);
    reached = 1;
done:
    return reached;
}
