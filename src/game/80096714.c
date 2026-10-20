typedef struct PackedText {
    int word;
    signed char byte4;
    signed char byte5;
} __attribute__((packed)) PackedText;

extern PackedText D_800C54B4;
extern int D_800EF070;
extern int D_800EF074;
extern int D_800EF078;
extern int D_800EF07C;
extern int D_800EF080;
extern int D_800EF084;
extern int D_800EF088;
extern int D_800EF08C;

void func_80096714(int value, PackedText *output) {
    register int number asm("$6") = value;
    register PackedText *out asm("$7") = output;
    register PackedText *source asm("$5") = &D_800C54B4;
    register int quotient asm("$2");
    register int tens asm("$3");

    asm("" : "+r"(number), "+r"(out), "+r"(source));
    {
        register int word asm("$2") = source->word;
        register int byte4 asm("$3") = source->byte4;
        register int byte5 asm("$4") = source->byte5;
        out->word = word;
        out->byte4 = byte4;
        out->byte5 = byte5;
        asm volatile("" : : : "memory");
    }
    quotient = number;
    if (number < 0) {
        quotient = number + 15;
    }
    quotient >>= 4;
    tens = quotient + '0';
    quotient <<= 4;
    quotient = number - quotient;
    quotient += '0';
    ((unsigned char *)out)[2] = tens;
    ((unsigned char *)out)[3] = quotient;
}

int func_80096770(void) {
    register int one asm("$2") = 1;
    asm volatile("lui $1,%%hi(D_800EF070)\n\t"
                 "sw %0,%%lo(D_800EF070)($1)"
                 : : "r"(one) : "$1", "memory");
    return 0;
}

int func_80096784(void) {
    register int one asm("$2") = 1;
    asm volatile("lui $1,%%hi(D_800EF074)\n\t"
                 "sw %0,%%lo(D_800EF074)($1)"
                 : : "r"(one) : "$1", "memory");
    return 0;
}

int func_80096798(void) {
    register int one asm("$2") = 1;
    asm volatile("lui $1,%%hi(D_800EF078)\n\t"
                 "sw %0,%%lo(D_800EF078)($1)"
                 : : "r"(one) : "$1", "memory");
    return 0;
}

int func_800967AC(void) {
    register int one asm("$2") = 1;
    asm volatile("lui $1,%%hi(D_800EF07C)\n\t"
                 "sw %0,%%lo(D_800EF07C)($1)"
                 : : "r"(one) : "$1", "memory");
    return 0;
}

int func_800967C0(void) {
    register int one asm("$2") = 1;
    asm volatile("lui $1,%%hi(D_800EF080)\n\t"
                 "sw %0,%%lo(D_800EF080)($1)"
                 : : "r"(one) : "$1", "memory");
    return 0;
}

int func_800967D4(void) {
    register int one asm("$2") = 1;
    asm volatile("lui $1,%%hi(D_800EF084)\n\t"
                 "sw %0,%%lo(D_800EF084)($1)"
                 : : "r"(one) : "$1", "memory");
    return 0;
}

int func_800967E8(void) {
    register int one asm("$2") = 1;
    asm volatile("lui $1,%%hi(D_800EF088)\n\t"
                 "sw %0,%%lo(D_800EF088)($1)"
                 : : "r"(one) : "$1", "memory");
    return 0;
}

int func_800967FC(void) {
    register int one asm("$2") = 1;
    asm volatile("lui $1,%%hi(D_800EF08C)\n\t"
                 "sw %0,%%lo(D_800EF08C)($1)"
                 : : "r"(one) : "$1", "memory");
    return 0;
}
