typedef struct {
    char pad0[8];
    unsigned int mask;
} Group;
extern int func_80052784(Group *, int *, int *);

void func_80052C64(Group *group, int bit) {
    int ids[16];
    int extra[4];
    int count;
    int i;

    group->mask &= ~(1 << bit);
    if (group->mask == 0) {
        count = func_80052784(group, ids, extra);
        for (i = 0; i < count; i++) {
            group->mask |= 1 << ids[i];
        }
    }
}
