typedef unsigned char u8;
typedef short s16;

typedef struct Primitive {
    s16 first;
    s16 second;
    s16 third;
    s16 fourth;
    s16 zero_08;
    s16 zero_0A;
    s16 zero_0C;
    s16 zero_0E;
    u8 zero_10;
    u8 zero_11;
    u8 zero_12;
    u8 zero_13;
} Primitive;

Primitive *func_8008BAD8(
    Primitive *primitive,
    int first,
    int second,
    int third,
    int fourth
) {
    primitive->first = first;
    primitive->second = second;
    primitive->third = third;
    primitive->fourth = fourth;
    primitive->zero_08 = 0;
    primitive->zero_0A = 0;
    primitive->zero_0C = 0;
    primitive->zero_0E = 0;
    primitive->zero_11 = 0;
    primitive->zero_10 = 0;
    primitive->zero_13 = 0;
    primitive->zero_12 = 0;
    return primitive;
}
