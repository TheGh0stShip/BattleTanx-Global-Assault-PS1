typedef struct Pair {
    char pad[0x30];
    int current;
    int pending;
} Pair;

extern int D_800C6074;
extern Pair D_80086058;
int func_800854EC(int *, int, int, int);

int *func_800855D0(void) {
    if (D_800C6074 == 0) {
        Pair *pair = &D_80086058;

        if (func_800854EC(&D_800C6074, pair->current, pair->pending, 0)) {
            pair->current = pair->pending;
        }
    }
    return &D_800C6074;
}
