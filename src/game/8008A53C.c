typedef unsigned char u8;

typedef struct Matrix {
    u8 pad_00[0x14];
    int x;
    int y;
    int z;
} Matrix;

extern void func_8008A65C(Matrix *matrix, int *input, int *output);
extern void func_80098A10(Matrix *matrix, Matrix *other);

void func_8008A53C(Matrix *matrix, Matrix *other) {
    int transformed[3];

    func_8008A65C(matrix, &other->x, transformed);
    matrix->x += transformed[0];
    matrix->y += transformed[1];
    matrix->z += transformed[2];
    func_80098A10(matrix, other);
}
