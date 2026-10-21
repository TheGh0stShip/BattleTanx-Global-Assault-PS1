typedef struct MatrixState {
    unsigned int values[5];
} MatrixState;

extern int func_8008AD60(int angle, MatrixState *source);
extern int func_8008ACC0(int angle);
extern void func_80068CA8(MatrixState *destination, MatrixState *source);

void func_80068888(MatrixState *destination, MatrixState *source, int angle_arg) {
    register MatrixState *saved_destination asm("$17") = destination;
    register MatrixState *saved_source asm("$18") = source;
    register int angle asm("$16") = (short)angle_arg;
    register unsigned int t4 asm("$12");
    register unsigned int t5 asm("$13");
    register unsigned int t6 asm("$14");
    register unsigned int t7 asm("$15");

    asm("" : "+r"(saved_destination), "+r"(saved_source),
              "+r"(angle));
    if (angle != 0) {
        angle = func_8008AD60(angle, saved_source);
        t4 = func_8008ACC0((short)angle_arg) & 0xFFFF;
        t5 = angle & 0xFFFF;
        t6 = 0x1000;
        t7 = (-angle) & 0xFFFF;
        asm("" : "+r"(t4), "+r"(t5), "+r"(t6), "+r"(t7));
        saved_destination->values[0] = t4;
        saved_destination->values[1] = t5;
        saved_destination->values[2] = t6;
        saved_destination->values[3] = t7;
        saved_destination->values[4] = t4;
        func_80068CA8(saved_destination, saved_source);
    } else {
        asm volatile("lw $12,0(%0)\n\t"
                     "lw $13,4(%0)\n\t"
                     "ctc2 $12,$0\n\t"
                     "ctc2 $13,$1\n\t"
                     "lw $12,8(%0)\n\t"
                     "lw $13,12(%0)\n\t"
                     "lw $14,16(%0)\n\t"
                     "ctc2 $12,$2\n\t"
                     "ctc2 $13,$3\n\t"
                     "ctc2 $14,$4"
                     : : "r"(saved_source)
                     : "$12", "$13", "$14", "memory");
    }
}
