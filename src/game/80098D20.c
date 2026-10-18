void func_80098D20(int first, int second) {
    asm("sll $4,$4,16\n\tsll $5,$5,16\n\tctc2 $4,$24\n\tctc2 $5,$25"
        : : "r"(first), "r"(second));
}
