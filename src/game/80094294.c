int func_80094294(int value) {
    register int argument1 asm("$5") = value;
    register int argument2 asm("$6") = 0;
    register int error asm("$2");
    register int result asm("$3");

    asm("break 258\n\tbeqz $2,1f\n\taddu $2,$3,$0\n\taddiu $2,$0,-1\n1:"
        : "=r"(error), "=r"(result) : "r"(argument1), "r"(argument2));
    return error;
}
