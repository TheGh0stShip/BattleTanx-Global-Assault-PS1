int func_8001EE10(int x1, int y1, int x2, int y2) {
    int y = y1 - y2;
    int x;
    int result;
    int large;

    if (y < 0) {
        y = -y;
    }
    x = x1 - x2;
    if (x < 0) {
        x = -x;
    }
    __asm__ volatile ("");
    result = x;
    __asm__ volatile ("" : "+r"(x));
    large = y;
    if (x < y) {
        y = x;
    }
    result += large;
    return result - y / 2;
}
