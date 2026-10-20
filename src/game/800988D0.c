unsigned int *func_800988D0(unsigned int *matrix, unsigned int *scale) {
    register unsigned int scale0 asm("$11") = scale[0];
    register unsigned int scale1 asm("$12") = scale[1];
    register unsigned int scale2 asm("$13") = scale[2];
    register unsigned int word asm("$8");
    register unsigned int low asm("$9");
    register unsigned int high asm("$10");
    register unsigned int *target asm("$4") = matrix;

    asm("" : "+r"(scale0), "+r"(scale1), "+r"(scale2), "+r"(target));
    word = target[0];
    asm("" : "+r"(word));
    low = word & 0xFFFF;
    asm("" : "+r"(low));
    low = (unsigned int)(int)(short)low;
    asm volatile("multu %0,%1\n\tmflo %0"
                 : "+r"(low) : "r"(scale0) : "hi", "lo");
    low = (unsigned int)((int)low >> 12);
    low &= 0xFFFF;
    asm("" : "+r"(low));
    high = (unsigned int)((int)word >> 16);
    asm volatile("multu %0,%1\n\tmflo %0"
                 : "+r"(high) : "r"(scale1) : "hi", "lo");
    high = (unsigned int)((int)high >> 12);
    high <<= 16;
    low |= high;
    target[0] = low;
    asm volatile("" : : : "memory");

    word = target[1];
    asm("" : "+r"(word));
    low = word & 0xFFFF;
    asm("" : "+r"(low));
    low = (unsigned int)(int)(short)low;
    asm volatile("multu %0,%1\n\tmflo %0"
                 : "+r"(low) : "r"(scale2) : "hi", "lo");
    low = (unsigned int)((int)low >> 12);
    low &= 0xFFFF;
    asm("" : "+r"(low));
    high = (unsigned int)((int)word >> 16);
    asm volatile("multu %0,%1\n\tmflo %0"
                 : "+r"(high) : "r"(scale0) : "hi", "lo");
    high = (unsigned int)((int)high >> 12);
    high <<= 16;
    low |= high;
    target[1] = low;
    asm volatile("" : : : "memory");

    word = target[2];
    asm("" : "+r"(word));
    low = word & 0xFFFF;
    asm("" : "+r"(low));
    low = (unsigned int)(int)(short)low;
    asm volatile("multu %0,%1\n\tmflo %0"
                 : "+r"(low) : "r"(scale1) : "hi", "lo");
    low = (unsigned int)((int)low >> 12);
    low &= 0xFFFF;
    asm("" : "+r"(low));
    high = (unsigned int)((int)word >> 16);
    asm volatile("multu %0,%1\n\tmflo %0"
                 : "+r"(high) : "r"(scale2) : "hi", "lo");
    high = (unsigned int)((int)high >> 12);
    high <<= 16;
    low |= high;
    target[2] = low;
    asm volatile("" : : : "memory");

    word = target[3];
    asm("" : "+r"(word));
    low = word & 0xFFFF;
    asm("" : "+r"(low));
    low = (unsigned int)(int)(short)low;
    asm volatile("multu %0,%1\n\tmflo %0"
                 : "+r"(low) : "r"(scale0) : "hi", "lo");
    low = (unsigned int)((int)low >> 12);
    low &= 0xFFFF;
    asm("" : "+r"(low));
    high = (unsigned int)((int)word >> 16);
    asm volatile("multu %0,%1\n\tmflo %0"
                 : "+r"(high) : "r"(scale1) : "hi", "lo");
    high = (unsigned int)((int)high >> 12);
    high <<= 16;
    low |= high;
    target[3] = low;
    asm volatile("" : : : "memory");

    word = target[4];
    asm("" : "+r"(word));
    low = word & 0xFFFF;
    asm("" : "+r"(low));
    low = (unsigned int)(int)(short)low;
    asm volatile("multu %0,%1\n\tmflo %0"
                 : "+r"(low) : "r"(scale2) : "hi", "lo");
    low = (unsigned int)((int)low >> 12);
    target[4] = low;
    asm("" : "+r"(target) : : "memory");
    return target;
}
