void func_80068CA8(unsigned short *matrix, unsigned int *transform) {
    register unsigned short *target asm("$4") = matrix;
    register unsigned int *source asm("$5") = transform;
    register unsigned int t2 asm("$10");
    register unsigned int t3 asm("$11");
    register unsigned int t4 asm("$12");
    register unsigned int t5 asm("$13");
    register unsigned int t6 asm("$14");
    register unsigned int t7 asm("$15");

    asm("" : "+r"(target), "+r"(source));
    t5 = source[0];
    t6 = source[1];
    t7 = source[2];
    asm volatile("" : "+r"(t5), "+r"(t6), "+r"(t7) : : "memory");
    t2 = target[0];
    t3 = target[3];
    t4 = target[6];
    asm("" : "+r"(t2), "+r"(t3), "+r"(t4));
    asm("" : "+r"(t5), "+r"(t6), "+r"(t7));
    asm volatile("ctc2 %0,$0" : : "r"(t5));
    t5 = source[3];
    asm volatile("mtc2 %0,$9" : : "r"(t2));
    t2 = source[4];
    asm volatile("ctc2 %0,$1\n\t"
                 "ctc2 %1,$2\n\t"
                 "mtc2 %2,$10\n\t"
                 "mtc2 %3,$11\n\t"
                 "ctc2 %4,$3\n\t"
                 "ctc2 %5,$4\n\t"
                 "nop\n\tnop\n\tcop2 0x49E012"
                 : : "r"(t6), "r"(t7), "r"(t3), "r"(t4), "r"(t5), "r"(t2)
                 : "memory");

    t2 = target[1];
    t3 = target[4];
    t4 = target[7];
    asm volatile("mfc2 %0,$9\n\t"
                 "mfc2 %1,$10\n\t"
                 "mfc2 %2,$11\n\t"
                 "mtc2 %3,$9\n\t"
                 "mtc2 %4,$10\n\t"
                 "mtc2 %5,$11"
                 : "=r"(t5), "=r"(t6), "=r"(t7)
                 : "r"(t2), "r"(t3), "r"(t4) : "memory");
    t2 = target[2];
    t3 = target[5];
    t4 = target[8];
    asm volatile("cop2 0x49E012" : : : "memory");
    target[0] = t5;
    target[3] = t6;
    target[6] = t7;
    asm volatile("mfc2 %0,$9\n\t"
                 "mfc2 %1,$10\n\t"
                 "mfc2 %2,$11\n\t"
                 "mtc2 %3,$9\n\t"
                 "mtc2 %4,$10\n\t"
                 "mtc2 %5,$11"
                 : "=r"(t5), "=r"(t6), "=r"(t7)
                 : "r"(t2), "r"(t3), "r"(t4) : "memory");
    target[1] = t5;
    target[4] = t6;
    target[7] = t7;
    asm volatile("cop2 0x49E012" : : : "memory");

    t2 = *(unsigned int *)((unsigned char *)target + 0);
    t4 = *(unsigned int *)((unsigned char *)target + 12);
    asm volatile("mfc2 %0,$9\n\t"
                 "mfc2 %1,$10\n\t"
                 "mfc2 %2,$11"
                 : "=r"(t5), "=r"(t6), "=r"(t7));
    target[2] = t5;
    target[5] = t6;
    target[8] = t7;
    asm volatile("" : : "m"(target[2]), "m"(target[5]), "m"(target[8]) : "memory");
    t3 = *(unsigned int *)((unsigned char *)target + 4);
    t5 = *(unsigned int *)((unsigned char *)target + 8);
    t6 = *(unsigned int *)((unsigned char *)target + 16);
    asm volatile("ctc2 %0,$0\n\t"
                 "ctc2 %1,$1\n\t"
                 "ctc2 %2,$3\n\t"
                 "ctc2 %3,$2\n\t"
                 "ctc2 %4,$4"
                 : : "r"(t2), "r"(t3), "r"(t4), "r"(t5), "r"(t6));
}
