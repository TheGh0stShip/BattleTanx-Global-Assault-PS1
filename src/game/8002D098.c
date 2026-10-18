typedef struct { char pad[60]; int value; } Target;
typedef struct { int pad[2]; Target *target; int pad2[2]; int value; unsigned int state; int pad3[3]; unsigned short sound; } Trigger;
void func_8001B094(int);

void func_8002D098(Trigger *t, int *done) {
    switch (t->state) {
    case 2:
        func_8001B094(t->sound);
        *done = 1;
        break;
    case 3:
        *done = 1;
        break;
    case 1:
        t->target->value = t->value;
        t->state = 2;
        break;
    }
}
