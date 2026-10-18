typedef struct {
    short x;
    short y;
    short value;
    short pad;
    int extra[2];
} Entry800903A4;
extern Entry800903A4 *D_800B76F0;

void func_80090CE0(int index, int x, int y) {
    struct {
        int count;
        volatile int value;
    } d;

    x &= 0x7FFF;
    y &= 0x7FFF;
    D_800B76F0[index].x = x;
    D_800B76F0[index].y = y;
    d.value = 1;
    d.count = 0;
    while (*(volatile int *)&d.count < 2) {
        d.value = d.value * 13;
        (*(volatile int *)&d.count)++;
    }
}
