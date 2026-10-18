typedef signed short s16;

void func_800150A4(s16 *input) {
    register int first asm("$5") = input[0];
    register int second asm("$3") = input[1];
    register int third asm("$2") = input[2];

    asm("mtc2 $5,$9\n\tmtc2 $3,$10\n\tmtc2 $2,$11"
        : : "r"(first), "r"(second), "r"(third));
}
