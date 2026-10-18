typedef unsigned char u8;

typedef struct Matrix {
    u8 pad_00[0x14];
    int x;
    int y;
    int z;
} Matrix;

extern void func_8008A65C(Matrix *matrix, int *input, int *output);
extern void func_80098B20(Matrix *matrix, Matrix *other);

void func_8008A5B4(Matrix *matrix, Matrix *other) {
    func_8008A65C(matrix, &other->x, &other->x);
    other->x += matrix->x;
    other->y += matrix->y;
    other->z += matrix->z;
    func_80098B20(matrix, other);
}
