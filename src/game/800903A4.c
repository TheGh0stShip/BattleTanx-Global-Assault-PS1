typedef struct {
    short x;
    short y;
    short value;
    short pad;
    int extra[2];
} Entry800903A4;
extern Entry800903A4 *D_800B76F0;

void func_800903A4(int index, short value) {
    struct {
        int count;
        volatile int value;
    } d;

    D_800B76F0[index].value = value;
    d.value = 1;
    d.count = 0;
    while (*(volatile int *)&d.count < 2) {
        d.value = d.value * 13;
        (*(volatile int *)&d.count)++;
    }
}
