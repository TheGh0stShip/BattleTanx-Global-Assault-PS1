typedef unsigned short u16;

typedef struct MenuRecord {
    void *first;
    void *second;
    int third;
    int fourth;
} MenuRecord;

extern MenuRecord D_800E4D4C[];

void func_80063D8C(void *first, void *second, u16 index) {
    D_800E4D4C[index].first = first;
    D_800E4D4C[index].second = second;
    D_800E4D4C[index].third = -1;
    D_800E4D4C[index].fourth = -1;
}
