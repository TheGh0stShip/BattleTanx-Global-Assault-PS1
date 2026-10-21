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
    u16 x = *(u16 *)((char *)in + 0);
    u16 y = *(u16 *)((char *)in + 2);
    u16 z = *(u16 *)((char *)in + 4);
    s32 x_shift;
    s32 x_signed;
    s32 x_sign;
    s32 x_value;
    s32 y_shift;
    s32 y_value;
    s32 z_shift;
    s32 z_value;
    s32 x_less_y;

    out->z = 0;
    out->y = 0;
    out->x = 0;
    x_shift = (s32)(x << 16);
    x_signed = x_shift >> 16;
    x_sign = x_shift >> 31;
    x_signed ^= x_sign;
    x_value = x_signed + x_sign;
    y_shift = (s32)(y << 16);
    y_value = ((y_shift >> 16) ^ (y_shift >> 31)) + (y_shift >> 31);
    x_less_y = x_value < y_value;
    z_shift = (s32)(z << 16);
    z_value = ((z_shift >> 16) ^ (z_shift >> 31)) + (z_shift >> 31);
    *(s16 *)((char *)out + ((((x_less_y & (y_value < z_value)) * 2) +
                              ((z_value < x_value) & x_less_y)) * 2)) = 0x1000;
    func_80071360(out, in, x_sign, x_value);
}
