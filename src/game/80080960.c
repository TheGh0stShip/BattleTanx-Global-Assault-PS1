typedef unsigned int u32;

extern short D_800B0C64;
extern short D_800B0C66;

static __inline__ u32 pack_x(int x)
{
    return (x & 0x3FF) | 0xE4000000;
}

u32 func_80080960(int x, int y)
{
    register int temporary asm("$2");
    register int signed_value asm("$6");
    register u32 packed_y asm("$3");

    asm("sll %0,%2,16\n\tsra %1,%0,16"
        : "=r"(temporary), "=r"(signed_value) : "r"(x));
    temporary = 0;
    if (signed_value >= 0) {
        temporary = D_800B0C64 - 1;
        temporary = temporary < signed_value;
        asm("lui %0,%%hi(D_800B0C64)\n\tlhu %0,%%lo(D_800B0C64)(%0)"
            : "=r"(signed_value) : "r"(temporary));
        if (temporary == 0) {
            temporary = x;
        } else {
            temporary = signed_value - 1;
        }
    }
    x = temporary;

    asm("sll %0,%2,16\n\tsra %1,%0,16"
        : "=r"(temporary), "=r"(signed_value) : "r"(y));
    if (signed_value < 0) {
        goto negative_y;
    }
    temporary = D_800B0C66 - 1;
    temporary = temporary < signed_value;
    asm("lui %0,%%hi(D_800B0C66)\n\tlhu %0,%%lo(D_800B0C66)(%0)"
        : "=r"(signed_value) : "r"(temporary));
    if (temporary == 0) {
        goto pack_y;
    }
    y = signed_value - 1;
    goto pack_y;
negative_y:
    y = 0;
pack_y:
    packed_y = (y & 0x3FF) << 10;
    return packed_y | pack_x(x);
}
