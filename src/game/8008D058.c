void func_8008D058(int first, int second, int third) {
    asm("sll $4,$4,4\n\tsll $5,$5,4\n\tsll $6,$6,4\n\t"
        "ctc2 $4,$13\n\tctc2 $5,$14\n\tctc2 $6,$15"
        : : "r"(first), "r"(second), "r"(third));
}
