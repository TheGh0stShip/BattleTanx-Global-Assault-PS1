typedef unsigned char u8;

typedef struct Matrix {
    u8 pad_00[0x14];
    int x;
    int y;
    int z;
} Matrix;

void func_8008A62C(Matrix *matrix, int x, int y, int z) {
    matrix->x = x;
    matrix->y = y;
    matrix->z = z;
}
