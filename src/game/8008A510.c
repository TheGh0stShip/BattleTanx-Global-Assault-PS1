extern void func_800988D0(void *matrix, int *scale);

void func_8008A510(void *matrix, int x, int y, int z) {
    int scale[3];
    scale[0] = x;
    scale[1] = y;
    scale[2] = z;
    func_800988D0(matrix, scale);
}
