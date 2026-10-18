void func_8009AA0C(void) {
    struct {
        int count;
        volatile int value;
    } d;

    d.value = 13;
    d.count = 0;
    while (*(volatile int *)&d.count < 60) {
        d.value = d.value * 13;
        (*(volatile int *)&d.count)++;
    }
}
