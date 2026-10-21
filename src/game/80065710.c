typedef struct {
    int vx;
    int vy;
    int vz;
} LongVector;

static inline void gte_ldlv_3(volatile int *r0, volatile int *r1,
                              volatile int *r2) {
    __asm__ volatile("lwc2 $9, 0(%0)\n\tlwc2 $10, 0(%1)\n\tlwc2 $11, 0(%2)"
                     : : "r"(r0), "r"(r1), "r"(r2));
}

static inline void gte_stlv_3(volatile int *r0, volatile int *r1,
                              volatile int *r2) {
    __asm__ volatile("swc2 $25, 0(%0)\n\tswc2 $26, 0(%1)\n\tswc2 $27, 0(%2)"
                     : : "r"(r0), "r"(r1), "r"(r2) : "memory");
}

static inline void gte_rtir_sf0(void) {
    __asm__ volatile("nop\n\tnop\n\tnop\n\tcop2 0x41E012");
}

static inline void gte_rtir(void) {
    __asm__ volatile("nop\n\tnop\n\tnop\n\tcop2 0x49E012");
}

static inline void gte_SetTransVector(LongVector *r0) {
    __asm__ volatile("lw $12, 0(%0)\n\tlw $13, 4(%0)\n\tlw $14, 8(%0)\n\t"
                     "ctc2 $12, $5\n\tctc2 $13, $6\n\tctc2 $14, $7"
                     : : "r"(r0) : "$12", "$13", "$14");
}

void func_80065710(LongVector *out, LongVector *a, LongVector *b) {
    volatile int high_x;
    volatile int high_y;
    volatile int high_z;
    int low_x;
    int low_y;
    int low_z;

    out->vx = a->vx - b->vx;
    out->vy = a->vy - b->vy;
    out->vz = a->vz - b->vz;
    low_x = out->vx;
    low_y = out->vy;
    low_z = out->vz;

    if (low_x < 0) {
        low_x = -low_x;
        { int h=-(low_x>>15); register int l asm("$3"); __asm__ volatile("andi %0,%1,0x7fff\n\tnegu %0,%0" : "=r"(l) : "r"(low_x)); high_x=h;low_x=l; }
    } else {
        __asm__ volatile("");
        { register int h asm("$8")=low_x>>15; int l=low_x&0x7fff; __asm__("" :: "r"(l)); high_x=h;low_x=l; }
    }
    if (low_y < 0) {
        low_y = -low_y;
        { int h=-(low_y>>15); register int l asm("$3"); __asm__ volatile("andi %0,%1,0x7fff\n\tnegu %0,%0" : "=r"(l) : "r"(low_y)); high_y=h;low_y=l; }
    } else {
        __asm__ volatile("");
        high_y = low_y >> 15;
        low_y = low_y & 0x7FFF;
    }
    { register int z asm("$2") = low_z; register int n asm("$3");
    n=-z;
    if (z < 0) { int h; register int l asm("$3"); low_z=n; h=-(n>>15); __asm__ volatile("andi %0,%1,0x7fff\n\tnegu %0,%0" : "=r"(l) : "r"(n)); high_z=h; low_z=l; }
    else { register int h asm("$8")=z >> 15; int l=z & 0x7FFF; __asm__("" :: "r"(l)); high_z=h; low_z=l; } }

    gte_ldlv_3(&high_x, &high_y, &high_z);
    gte_rtir_sf0();
    gte_stlv_3(&high_x, &high_y, &high_z);
    {
        int *px = &low_x, *py = &low_y, *pz = &low_z;
        __asm__("" : "=r"(px) : "0"(px));
        __asm__("" : "=r"(py) : "0"(py));
        __asm__("" : "=r"(pz) : "0"(pz));
        gte_ldlv_3(px, py, pz);
    }
    gte_rtir();
    high_x <<= 3;
    high_y <<= 3;
    high_z <<= 3;
    gte_stlv_3(&low_x, &low_y, &low_z);

    out->vx = low_x + high_x;
    out->vy = low_y + high_y;
    out->vz = low_z + high_z;
    gte_SetTransVector(out);
}
