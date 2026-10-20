typedef struct GteMatrix {
    unsigned int word[5];
} GteMatrix;

GteMatrix *func_8008D0A8(GteMatrix *matrix, unsigned char *source, GteMatrix *destination) {
    register GteMatrix *rotation asm("$4") = matrix;
    register unsigned char *input asm("$5") = source;
    register GteMatrix *output asm("$6") = destination;
    register unsigned int t0 asm("$8");
    register unsigned int t1 asm("$9");
    register unsigned int t2 asm("$10");
    register unsigned int t3 asm("$11");
    register unsigned int t4 asm("$12");
    register unsigned int t5 asm("$13");
    register unsigned int t6 asm("$14");
    register unsigned int t7 asm("$15");
    register unsigned int t8 asm("$24");

    asm("" : "+r"(rotation), "+r"(input), "+r"(output));
    t0 = rotation->word[0];
    t1 = rotation->word[1];
    t2 = rotation->word[2];
    t3 = rotation->word[3];
    t4 = rotation->word[4];
    asm("" : "+r"(t0), "+r"(t1), "+r"(t2), "+r"(t3), "+r"(t4));
    asm volatile("ctc2 %0,$0\n\t"
                 "ctc2 %1,$1\n\t"
                 "ctc2 %2,$2\n\t"
                 "ctc2 %3,$3\n\t"
                 "ctc2 %4,$4"
                 : : "r"(t0), "r"(t1), "r"(t2), "r"(t3), "r"(t4));

    t0 = *(unsigned short *)(input + 0);
    t1 = *(unsigned int *)(input + 4);
    t2 = *(unsigned int *)(input + 12);
    asm volatile("lui $1,0xFFFF\n\tand %0,%0,$1"
                 : "+r"(t1) : : "$1");
    t0 |= t1;
    asm volatile("mtc2 %0,$0\n\tmtc2 %1,$1\n\tnop\n\tcop2 0x486012"
                 : : "r"(t0), "r"(t2) : "memory");

    t0 = *(unsigned short *)(input + 2);
    t1 = *(unsigned int *)(input + 8);
    t2 = *(short *)(input + 14);
    t1 <<= 16;
    t0 |= t1;
    asm volatile("mfc2 %0,$9\n\tmfc2 %1,$10\n\tmfc2 %2,$11\n\t"
                 "mtc2 %3,$0\n\tmtc2 %4,$1\n\tnop\n\tcop2 0x486012"
                 : "=r"(t3), "=r"(t4), "=r"(t5)
                 : "r"(t0), "r"(t2) : "memory");

    t0 = *(unsigned short *)(input + 4);
    t1 = *(unsigned int *)(input + 8);
    t2 = *(unsigned int *)(input + 16);
    asm volatile("lui $1,0xFFFF\n\tand %0,%0,$1"
                 : "+r"(t1) : : "$1");
    t0 |= t1;
    asm volatile("mfc2 %0,$9\n\tmfc2 %1,$10\n\tmfc2 %2,$11\n\t"
                 "mtc2 %3,$0\n\tmtc2 %4,$1\n\tnop\n\tcop2 0x486012"
                 : "=r"(t6), "=r"(t7), "=r"(t8)
                 : "r"(t0), "r"(t2) : "memory");

    t3 &= 0xFFFF;
    t6 <<= 16;
    t6 |= t3;
    *(volatile unsigned int *)&output->word[0] = t6;
    asm volatile("" : "+r"(t5), "+r"(t8)
                 : "m"(output->word[0]) : "memory");
    t5 &= 0xFFFF;
    t8 <<= 16;
    t8 |= t5;
    *(volatile unsigned int *)&output->word[3] = t8;
    asm volatile("mfc2 %0,$9\n\tmfc2 %1,$10" : "=r"(t0), "=r"(t1));
    t0 &= 0xFFFF;
    t4 <<= 16;
    t0 |= t4;
    *(volatile unsigned int *)&output->word[1] = t0;
    asm volatile("" : "+r"(t7), "+r"(t1)
                 : "m"(output->word[1]) : "memory");
    t7 &= 0xFFFF;
    t1 <<= 16;
    t1 |= t7;
    *(volatile unsigned int *)&output->word[2] = t1;
    asm volatile("swc2 $11,16(%0)" : : "r"(output) : "memory");
    {
        register GteMatrix *return_value asm("$2") = output;
        asm volatile("" : "+r"(return_value));
        return return_value;
    }
}
