typedef signed int s32;
typedef unsigned short u16;

extern u16 D_800B0EEC[];
extern void func_8001B328(s32, s32 *);

void func_8001F094(s32 value, s32 magnitude, s32 angle) {
    s32 pair[2];
    register s32 mask asm("$8");
    register s32 index asm("$9");
    register s32 next_angle asm("$10");
    register u16 sample asm("$9");
    register s32 trig asm("$2");
    register s32 result asm("$3");
    register s32 high asm("$7");

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
    if (mask != 0) {
        asm("sub %0,$0,%0" : "+r"(sample));
    }
    asm("sll %0,%1,1\n\tsra %0,%0,4" : "=r"(trig) : "r"(sample));
    asm volatile("mult %2,%3\n\t"
                 "mflo %0\n\t"
                 "mfhi %1\n\t"
                 "srl %0,%0,12\n\t"
                 "sll %1,%1,20\n\t"
                 "or %0,%0,%1"
                 : "=&r"(result), "=&r"(high) : "r"(trig), "r"(magnitude));
    pair[0] = result;
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
    if (mask != 0) {
        asm("sub %0,$0,%0" : "+r"(sample));
    }
    asm("sll %0,%1,1\n\tsra %0,%0,4" : "=r"(trig) : "r"(sample));
    asm volatile("mult %2,%3\n\t"
                 "mflo %0\n\t"
                 "mfhi %1\n\t"
                 "srl %0,%0,12\n\t"
                 "sll %1,%1,20\n\t"
                 "or %0,%0,%1"
                 : "=&r"(result), "=&r"(high) : "r"(trig), "r"(magnitude));
    pair[1] = result;
    func_8001B328(value, pair);
}
