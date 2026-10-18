void func_80098D40(int first, int second) {
    asm("ctc2 $4,$29\n\tctc2 $5,$30" : : "r"(first), "r"(second));
}
