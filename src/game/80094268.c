int func_80094268(int first, int second) {
    register int argument1 asm("$5") = first;
    register int argument2 asm("$6") = second;
    register int error asm("$2");
    register int result asm("$3");

    asm("break 259\n\tbeqz $2,1f\n\taddu $2,$3,$0\n\taddiu $2,$0,-1\n1:"
        : "=r"(error), "=r"(result) : "r"(argument1), "r"(argument2));
    return error;
}
