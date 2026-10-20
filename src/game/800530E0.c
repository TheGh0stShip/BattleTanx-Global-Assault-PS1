typedef struct Counters {
    unsigned char fields00[0x0C];
    int counter0C;
    int field10;
    int counter14;
    int total;
} Counters;

typedef struct Subject {
    unsigned char fields00[0x0C];
    Counters *counters;
    unsigned char fields10[0x70 - 0x10];
    int local_total;
} Subject;

typedef char Counters_size[(sizeof(Counters) == 0x1C) ? 1 : -1];
typedef char Subject_size[(sizeof(Subject) == 0x74) ? 1 : -1];

extern int func_80022814(void);

void func_800530E0(Subject *subject, int amount, int flag) {
    int before;
    int after;
    int bonus;

    if (func_80022814()) {
        if (flag == 0)
            subject->local_total += amount;
        before = subject->counters->total / 10000;
        subject->counters->total += amount;
        after = subject->counters->total / 10000;
        if (after != before) {
            bonus = (after - before) * 10;
            subject->counters->counter0C += bonus;
            subject->counters->counter14 += bonus;
        }
    } else {
        subject->local_total += amount;
    }
}
