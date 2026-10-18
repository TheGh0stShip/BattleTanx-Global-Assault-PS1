typedef int (*Handler)(int, int, int *);
typedef struct {
    int current;
    int current_arg;
    unsigned int count;
    Handler handlers[10];
} HandlerTable;
extern HandlerTable D_800EDC9C;

int func_80082110(Handler handler) {
    HandlerTable *t = &D_800EDC9C;
    unsigned int index = t->count;
    int arg;

    if (index < 10) {
        t->handlers[index] = handler;
        t->count++;
        arg = 0;
        if (handler(0, index, &arg) != 0 && D_800EDC9C.current == -1) {
            D_800EDC9C.current = index;
            t->current_arg = arg;
        }
    }
    return 0;
}
