typedef struct { unsigned short size; unsigned short pad; unsigned int cells[1]; } Grid;
extern Grid *D_800DDDF0;

void func_8003BADC(int x, int z) {
    unsigned int *cell = 0;
    Grid *g;

    x = -x + 256;
    z = z + 256;
    g = D_800DDDF0;
    switch (g->size) {
    case 64:
        cell = &((unsigned int (*)[64])g->cells)[((z >> 9) + 128) & 0xFF][((x >> 9) + 32) & 0x3F];
        break;
    case 128:
        cell = &((unsigned int (*)[128])g->cells)[((z >> 9) + 64) & 0x7F][((x >> 9) + 64) & 0x7F];
        break;
    }
    *cell &= 0xFFFF8000;
}
