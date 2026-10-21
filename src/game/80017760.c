typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;
typedef unsigned int u32;

typedef struct CollisionEntry {
    unsigned char pad00[0x10];
    u16 x;
    u16 y;
    s16 z;
    unsigned char pad16[8];
    s16 lower;
    s16 upper;
    s16 radius;
    unsigned char pad24[4];
} CollisionEntry;

extern CollisionEntry D_800C62B0[];
extern u16 D_800C628C;
extern s32 func_800173EC(u32 first, u32 second, void *normal, u16 *depth);

s32 func_80017760(u32 first_arg, u32 second_arg, void *normal, u16 *depth)
{
    register u32 first asm("$4") = first_arg;
    register u32 second asm("$5") = second_arg;
    CollisionEntry *a;
    CollisionEntry *b;
    s32 delta;
    register s32 x_squared asm("$10");
    register s32 y_squared asm("$11");
    register s32 distance asm("$3");
    s32 extent;
    register s32 extent_squared asm("$2");
    register s32 result asm("$2");

    first &= 0xffff;
    a = &D_800C62B0[first];
    asm("" : "+r"(a));
    second &= 0xffff;
    b = &D_800C62B0[second];

    delta = (s16)(a->x - b->x);
    x_squared = delta * delta;
    delta = (s16)(a->y - b->y);
    y_squared = delta * delta;
    extent = a->radius + b->radius;
    distance = x_squared + y_squared;
    extent_squared = extent * extent;
    if ((u32)extent_squared < (u32)distance) {
        return 0;
    }

    if (D_800C628C != 0) {
        register s32 a_z asm("$11");
        register s32 a_edge asm("$3");
        register s32 b_z asm("$10");
        register s32 b_edge asm("$2");
        asm volatile("");
        a_z = a->z;
        a_edge = a->lower;
        b_z = b->z;
        b_edge = b->upper;
        a_edge = a_z + a_edge;
        b_edge = b_z + b_edge;
        if (b_edge < a_edge) {
            result = 0;
            goto mask_result;
        }
        a_edge = a->upper;
        b_edge = b->lower;
        a_edge = a_z + a_edge;
        b_edge = b_z + b_edge;
        {
            register s32 separated asm("$3") = a_edge < b_edge;
            asm volatile("" : "+r"(separated));
            asm volatile(
                ".set noreorder\n\t"
                ".set nomacro\n\t"
                "beq $3,$zero,1f\n\t"
                "nop\n\t"
                "j 2f\n\t"
                "addu $2,$zero,$zero\n"
                "1:\n\t"
                ".set macro\n\t"
                ".set reorder"
                :
                : "r"(separated)
                : "$2");
        }
    }

    result = func_800173EC(first, second, normal, depth);
    asm("" : "+r"(result));
    asm volatile("2:");
mask_result:
    result &= 0xffff;
    return result;
}
