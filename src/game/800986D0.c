typedef struct Matrix3x3 {
    short value[9];
} Matrix3x3;

extern unsigned int D_800B90F8[];

Matrix3x3 *func_800986D0(int angle, Matrix3x3 *matrix) {
    register int angle_value asm("$15") = angle;
    register Matrix3x3 *target asm("$5") = matrix;
    register Matrix3x3 *result asm("$2") = matrix;
    register int cosine asm("$8");
    register int sine asm("$9");
    register int first0 asm("$10");
    register int first1 asm("$11");
    register int first2 asm("$12");
    register int second0 asm("$13");
    register int second1 asm("$14");
    register int second2 asm("$15");
    register unsigned int product0 asm("$24");
    register unsigned int product1 asm("$25");
    register unsigned int packed asm("$25");
    register unsigned int offset asm("$24");

    asm("" : "+r"(angle_value), "+r"(target), "+r"(result));
    packed = angle_value & 0xFFF;
    if (angle_value < 0) {
        register int low asm("$14");
        angle_value = -angle_value;
        asm volatile(".set\tnoreorder\n\t"
                     "bgez %0,1f\n\t"
                     "andi %0,%0,0xFFF\n"
                     "1:\n\t"
                     ".set\treorder"
                     : "+r"(angle_value));
        offset = angle_value << 2;
        asm volatile("lui %0,%%hi(D_800B90F8)\n\t"
                     "addu %0,%0,%1\n\t"
                     "lw %0,%%lo(D_800B90F8)(%0)"
                     : "=r"(packed) : "r"(offset) : "memory");
        low = (int)(short)packed;
        sine = -low;
        asm("" : "+r"(sine));
        cosine = (int)packed >> 16;
    } else {
        register int low asm("$24");
        offset = packed << 2;
        asm volatile("lui %0,%%hi(D_800B90F8)\n\t"
                     "addu %0,%0,%1\n\t"
                     "lw %0,%%lo(D_800B90F8)(%0)"
                     : "=r"(packed) : "r"(offset) : "memory");
        low = packed << 16;
        asm("" : "+r"(low));
        sine = low >> 16;
        cosine = (int)packed >> 16;
    }

    first0 = target->value[0];
    second0 = target->value[3];
    asm volatile("multu %0,%1" : : "r"(cosine), "r"(first0) : "hi", "lo");
    first1 = target->value[1];
    asm("" : "+r"(first1));
    second1 = target->value[4];
    asm volatile("mflo %0" : "=r"(product0) : : "lo");
    first2 = target->value[2];
    asm("" : "+r"(first2));
    second2 = target->value[5];

    asm volatile("multu %0,%1" : : "r"(sine), "r"(second0) : "hi", "lo");
    asm volatile("nop\n\tnop");
    asm volatile("mflo %0" : "=r"(product1) : : "lo");
    product1 = product0 - product1;
    product0 = (unsigned int)((int)product1 >> 12);

    asm volatile("multu %0,%1" : : "r"(cosine), "r"(first1) : "hi", "lo");
    target->value[0] = (short)product0;
    asm volatile("nop");
    asm volatile("mflo %0" : "=r"(product0) : : "lo");
    asm volatile("nop\n\tnop");
    asm volatile("multu %0,%1" : : "r"(sine), "r"(second1) : "hi", "lo");
    asm volatile("nop\n\tnop");
    asm volatile("mflo %0" : "=r"(product1) : : "lo");
    product1 = product0 - product1;
    product0 = (unsigned int)((int)product1 >> 12);

    asm volatile("multu %0,%1" : : "r"(cosine), "r"(first2) : "hi", "lo");
    target->value[1] = (short)product0;
    asm volatile("nop");
    asm volatile("mflo %0" : "=r"(product0) : : "lo");
    asm volatile("nop\n\tnop");
    asm volatile("multu %0,%1" : : "r"(sine), "r"(second2) : "hi", "lo");
    asm volatile("nop\n\tnop");
    asm volatile("mflo %0" : "=r"(product1) : : "lo");
    product1 = product0 - product1;
    product0 = (unsigned int)((int)product1 >> 12);

    asm volatile("multu %0,%1" : : "r"(sine), "r"(first0) : "hi", "lo");
    target->value[2] = (short)product0;
    asm volatile("nop");
    asm volatile("mflo %0" : "=r"(product0) : : "lo");
    asm volatile("nop\n\tnop");
    asm volatile("multu %0,%1" : : "r"(cosine), "r"(second0) : "hi", "lo");
    asm volatile("nop\n\tnop");
    asm volatile("mflo %0" : "=r"(product1) : : "lo");
    product1 = product0 + product1;
    product0 = (unsigned int)((int)product1 >> 12);

    asm volatile("multu %0,%1" : : "r"(sine), "r"(first1) : "hi", "lo");
    target->value[3] = (short)product0;
    asm volatile("nop");
    asm volatile("mflo %0" : "=r"(product0) : : "lo");
    asm volatile("nop\n\tnop");
    asm volatile("multu %0,%1" : : "r"(cosine), "r"(second1) : "hi", "lo");
    asm volatile("nop\n\tnop");
    asm volatile("mflo %0" : "=r"(product1) : : "lo");
    product1 = product0 + product1;
    product0 = (unsigned int)((int)product1 >> 12);

    asm volatile("multu %0,%1" : : "r"(sine), "r"(first2) : "hi", "lo");
    target->value[4] = (short)product0;
    asm volatile("nop");
    asm volatile("mflo %0" : "=r"(product0) : : "lo");
    asm volatile("nop\n\tnop");
    asm volatile("multu %0,%1" : : "r"(cosine), "r"(second2) : "hi", "lo");
    asm volatile("nop\n\tnop");
    asm volatile("mflo %0" : "=r"(product1) : : "lo");
    product1 = product0 + product1;
    product0 = (unsigned int)((int)product1 >> 12);
    *(volatile short *)&target->value[5] = (short)product0;
    return result;
}
