typedef signed short s16;
typedef unsigned short u16;
typedef signed int s32;

typedef struct Vec3s {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern void func_80071360(Vec3s *out, const Vec3s *in, s32 sign, s32 magnitude);

void func_800717F8(const Vec3s *in, Vec3s *out) {
    register const Vec3s *src asm("$9") = in;
    register s32 x_shift asm("$6");
    register s32 y_shift asm("$3");
    register s32 z_shift asm("$5");
    register s32 x_signed asm("$7");
    register s32 x_sign asm("$6");
    register s32 x_value asm("$8");
    register s32 y_value asm("$2");
    register s32 z_value asm("$3");
    register s32 x_less_y asm("$8");
    register s16 *axis asm("$2");
    register Vec3s *dst asm("$4");
    register s32 unit asm("$3");

    asm("" : "+r"(src));
    asm("addu %0,%1,$zero" : "=r"(dst) : "r"(out));
    x_shift = *(u16 *)((char *)src + 0);
    y_shift = *(u16 *)((char *)src + 2);
    z_shift = *(u16 *)((char *)src + 4);
    dst->z = 0;
    dst->y = 0;
    dst->x = 0;
    x_shift <<= 16;
    x_signed = x_shift >> 16;
    x_sign = x_shift >> 31;
    x_signed ^= x_sign;
    x_value = x_signed + x_sign;
    y_shift <<= 16;
    y_value = ((y_shift >> 16) ^ (y_shift >> 31)) + (y_shift >> 31);
    x_less_y = x_value < y_value;
    z_shift <<= 16;
    z_value = ((z_shift >> 16) ^ (z_shift >> 31)) + (z_shift >> 31);
    asm volatile(
        "slt $2,$2,$3\n\t"
        "addu $7,$7,$6\n\t"
        "slt $3,$3,$7\n\t"
        "and $2,$8,$2\n\t"
        "sll $2,$2,1\n\t"
        "and $3,$3,$8\n\t"
        "addu $2,$2,$3\n\t"
        "sll $2,$2,1\n\t"
        "addu $2,$2,$4"
        : "=r"(axis), "+r"(x_signed)
        : "r"(y_value), "r"(z_value), "r"(x_less_y), "r"(x_sign), "r"(dst));
    unit = 0x1000;
    asm("" : "+r"(unit));
    *axis = unit;
    func_80071360(dst, src, x_sign, x_signed);
}
