typedef struct {
    int x;
    int y;
    int z;
} Vector;

typedef struct {
    char pad000[0x10];
    Vector target;
    int nearer_target;
} MoveState;

typedef struct {
    char pad000[8];
    Vector position;
    char pad014[0x80];
    Vector *reference;
    char pad098[0xEC];
    MoveState move;
} Tank;

int func_800495D8(Vector *, Vector *);

int func_800509F4(Tank *tank) {
    Vector point;
    Vector *reference;
    MoveState *move;
    int first_distance;
    int second_distance;
    int nearer_target;
    int difference;
    int result;

    result = 0;
    reference = tank->reference;
    if (reference != 0) {
        point.x = reference->x;
        point.z = reference->y;
        move = &tank->move;
        first_distance = func_800495D8(&point, &tank->position);
        second_distance = func_800495D8(&point, &move->target);
        nearer_target = first_distance < second_distance;
        if (nearer_target != move->nearer_target) {
            move->nearer_target = nearer_target;
            result = 1;
        } else {
            if (nearer_target) {
                difference = second_distance - first_distance;
            } else {
                difference = first_distance - second_distance;
            }
            if (difference <= 0x64000) {
                result = 1;
            }
        }
    }
    return result;
}
