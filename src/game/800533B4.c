typedef struct {
    unsigned short age;
    unsigned char priority;
    unsigned char sound;
} Voice;
extern Voice D_800E465C[];
extern int func_800901C4(int);
extern void func_800907C4(int, int);

unsigned char func_800533B4(unsigned char priority) {
    int i;
    int mask;
    int status;
    unsigned short best;
    unsigned char lowest;

    for (i = 0; i < 24; i++) {
        mask = 1 << i;
        status = func_800901C4(mask);
        if (status == 1) {
            D_800E465C[i].age++;
        } else if (status == 3) {
            if (D_800E465C[i].age != 0) {
                D_800E465C[i].age = 0;
                D_800E465C[i].priority = priority;
                func_800907C4(0, mask);
                return i;
            }
            D_800E465C[i].age = 1;
        } else if (status == 2) {
            D_800E465C[i].age = 0;
            D_800E465C[i].priority = priority;
            return i;
        } else {
            D_800E465C[i].age = 0;
            D_800E465C[i].priority = priority;
            return i;
        }
    }
    best = 0;
    for (i = 0; i < 24; i++) {
        if (D_800E465C[best].priority > D_800E465C[i].priority) {
            best = i;
        }
    }
    lowest = D_800E465C[best].priority;
    if (priority < lowest) {
        return 100;
    }
    {
        unsigned short oldest = best;

        for (i = best; i < 24; i++) {
            if (D_800E465C[i].priority == lowest && D_800E465C[i].age > D_800E465C[oldest].age) {
                oldest = i;
            }
        }
        func_800907C4(0, 1 << oldest);
        return oldest;
    }
}
