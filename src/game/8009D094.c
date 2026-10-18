int func_8009D094(void) {
    register int result asm("$2");
    register int returned asm("$3");

    asm("break 262\n\tbeqz $2,1f\n\taddu $2,$3,$0\n\taddiu $2,$0,-1\n1:"
        : "=r"(result), "=r"(returned));
    return result;
}
