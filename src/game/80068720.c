typedef struct {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

typedef struct {
    short x, y, z;
} SVec;

extern Matrix *D_800E53E8;

int func_80068720(SVec *a, SVec *b, int index) {
    Matrix *m;
    int v[6];

    m = &D_800E53E8[index];
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tctc2 $12, $0\n\tctc2 $13, $1\n\t"
                     "lw $12, 8(%0)\n\tlw $13, 12(%0)\n\tlw $14, 16(%0)\n\tctc2 $12, $2\n\tctc2 $13, $3\n\tctc2 $14, $4"
                     : : "r"(m) : "$12", "$13", "$14");
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tlw $14, 8(%0)\n\tctc2 $12, $5\n\tctc2 $13, $6\n\tctc2 $14, $7"
                     : : "r"(m->t) : "$12", "$13", "$14");
    v[0] = a->x;
    v[1] = a->y;
    v[2] = a->z;
    v[3] = b->x;
    v[4] = b->y;
    v[5] = b->z;
    return index + 1;
}
