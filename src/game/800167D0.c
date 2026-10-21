typedef signed int s32;
typedef unsigned short u16;

extern u16 D_800B0EEC[];

static inline s32 fixed_mul(s32 a, s32 b) {
    s32 r, hi;
    asm("mult %2,%3\n\tmflo %0\n\tmfhi %1\n\tsrl %0,%0,12\n\t"
        "sll %1,%1,20\n\tor %0,%0,%1"
        : "=&r"(r), "=&r"(hi) : "r"(a), "r"(b));
    return r;
}

void func_800167D0(s32 *in, s32 angle_arg, s32 *out) {
    s32 *src = in;

    register s32 angle asm("$4") = angle_arg;
    s32 *dst = out;
    register s32 mask asm("$8");
    register s32 index asm("$9");
    register s32 next asm("$10");
    register s32 s asm("$5");
    register s32 c asm("$4");
    s32 neg_s;
    s32 x, y, b, b2;

    switch ((u16)angle) {
    case 0:
        dst[0] = src[0];
        dst[1] = src[1];
        return;
    case 0x4000:
        dst[0] = -src[1];
        dst[1] = src[0];
        return;
    case 0x8000:
        dst[0] = -src[0];
        dst[1] = -src[1];
        return;
    case 0xC000:
        dst[0] = src[1];
        dst[1] = -src[0];
        return;
    }

    asm("andi %1,%2,0x4000\n\tandi %0,%2,0x3FFF\n\tbeqz %1,1f\n\tnop\n\t"
        "addiu %1,$0,0x3FFF\n\tsub %0,%1,%0\n1:"
        : "=r"(index), "=r"(mask) : "r"(angle));
    index = *(u16 *)((char *)D_800B0EEC + (index & 0x3FFE));
    asm("andi %1,%2,0x8000\n\tbeqz %1,1f\n\tnop\n\tsub %0,$0,%0\n1:"
        : "+r"(index), "=r"(mask) : "r"(angle));
    asm("sll %0,%1,1\n\tsra %0,%0,4" : "=r"(s) : "r"(index));

    next = angle + 0x4000;
    asm("andi %1,%2,0x4000\n\tandi %0,%2,0x3FFF\n\tbeqz %1,1f\n\tnop\n\t"
        "addiu %1,$0,0x3FFF\n\tsub %0,%1,%0\n1:"
        : "=r"(index), "=r"(mask) : "r"(next));
    index = *(u16 *)((char *)D_800B0EEC + (index & 0x3FFE));
    asm("andi %1,%2,0x8000\n\tbeqz %1,1f\n\tnop\n\tsub %0,$0,%0\n1:"
        : "+r"(index), "=r"(mask) : "r"(next));
    c = (index << 1) >> 4;
    asm("" : "=r"(c) : "0"(c));

    neg_s = -s;
    asm("" : "=r"(b) : "0"(src[1]));
    x = fixed_mul(src[0], c);
    y = fixed_mul(b, neg_s);
    dst[0] = x + y;
    asm("" : "=r"(b2) : "0"(src[1]));
    x = fixed_mul(src[0], s);
    y = fixed_mul(b2, c);
    dst[1] = x + y;
}
