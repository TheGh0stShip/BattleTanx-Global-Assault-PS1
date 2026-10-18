static inline void gte_ldlzc(int value) {
    __asm__ volatile("mtc2 %0, $30\n\tnop\n\tnop" : : "r"(value));
}

static inline void gte_stlzc(int *result) {
    __asm__ volatile("swc2 $31, 0(%0)" : : "r"(result) : "memory");
}

int func_8001EE5C(int *values) {
    int first;
    int second;
    int minimum = 32;
    int result;

    gte_ldlzc(values[0]);
    gte_stlzc(&first);
    if (first < minimum)
        minimum = first;
    gte_ldlzc(values[1]);
    gte_stlzc(&second);
    if (second < minimum)
        minimum = second;
    result = 18 - minimum;
    if (result > 0)
        return result;
    return 0;
}
