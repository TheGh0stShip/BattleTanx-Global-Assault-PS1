typedef struct {
    char pad000[0xC];
    int value;
} Object;

extern int D_800D2FE8;
extern char *D_800A5B24;

void func_80051340(Object *, int, int, int);

void func_800514E0(Object *object) {
    int action;

    switch (D_800D2FE8) {
    case 1:
    case 2:
    case 3:
    case 11:
        action = 2;
        break;
    case 4:
    case 10:
        action = 7;
        if (*(int *)(D_800A5B24 + 0xE078) == object->value) {
            action = 1;
        }
        break;
    case 9:
        return;
    case 12:
    case 13:
    case 14:
        action = 1;
        break;
    default:
        action = 1;
        break;
    }

    func_80051340(object, action, 0, 0);
}
