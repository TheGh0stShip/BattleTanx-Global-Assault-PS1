typedef signed int s32;
typedef unsigned short u16;

extern u16 D_800B0EEC[];
extern void func_8001B4B8(s32, s32, s32, s32 *, s32);

void func_8001F170(s32 unused0, s32 unused1, s32 unused2, s32 angle, s32 value) {
    s32 pair[2];
    register s32 saved_value asm("$3") = value;
    register s32 mask asm("$8");
    register s32 index asm("$9");
    register s32 next_angle asm("$10");
    register u16 sample asm("$9");
    register s32 *pair_argument asm("$7");

    asm volatile("" : "+r"(saved_value) : : "memory");
    mask = angle & 0x4000;
    index = angle & 0x3FFF;
    asm volatile("beqz %1,1f\n\t"
                 "nop\n\t"
                 "addiu %1,$0,0x3FFF\n\t"
                 "sub %0,%1,%0\n"
                 "1:" : "+r"(index), "+r"(mask));
    asm volatile("andi %0,%0,0x3FFE\n\t"
                 "lui $1,%%hi(D_800B0EEC)\n\t"
                 "addu $1,$1,%0\n\t"
                 "lhu %0,%%lo(D_800B0EEC)($1)" : "+r"(sample));
    mask = angle & 0x8000;
    if (mask) {
        asm("sub %0,$0,%0" : "+r"(sample));
    }
    asm volatile("sll $2,%0,1\n\t"
                 "sra $2,$2,4\n\t"
                 "sw $2,24($29)" : : "r"(sample) : "$2", "memory");
    next_angle = angle + 0x4000;
    mask = next_angle & 0x4000;
    index = next_angle & 0x3FFF;
    asm volatile("beqz %1,1f\n\t"
                 "nop\n\t"
                 "addiu %1,$0,0x3FFF\n\t"
                 "sub %0,%1,%0\n"
                 "1:" : "+r"(index), "+r"(mask));
    asm volatile("andi %0,%0,0x3FFE\n\t"
                 "lui $1,%%hi(D_800B0EEC)\n\t"
                 "addu $1,$1,%0\n\t"
                 "lhu %0,%%lo(D_800B0EEC)($1)" : "+r"(sample));
    mask = next_angle & 0x8000;
    if (mask) {
        asm("sub %0,$0,%0" : "+r"(sample));
    }
    asm volatile("sll $2,%0,1\n\t"
                 "sra $2,$2,4" : : "r"(sample) : "$2");
    pair_argument = pair;
    asm("" : "+r"(pair_argument));
    asm volatile("sw $2,28($29)" : : : "memory");
    func_8001B4B8(unused0, unused1, unused2, pair_argument, saved_value);
}
