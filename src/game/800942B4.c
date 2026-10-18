int func_800942B4(int first, int second, int third) {
    register int error asm("$2");
    register int result asm("$3");

    asm("addu $7,$6,$0\n\taddu $6,$5,$0\n\taddu $5,$4,$0\n\tbreak 263\n\t"
        "beqz $2,1f\n\taddu $2,$3,$0\n\taddiu $2,$0,-1\n1:"
        : "=r"(error), "=r"(result) : "r"(first), "r"(second), "r"(third));
    return error;
}
