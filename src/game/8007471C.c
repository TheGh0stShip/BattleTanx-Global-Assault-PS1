typedef struct { short m[3][3]; int t[3]; } MATRIX;
typedef struct { short axis, mode, speed, amp, phase, offset; } Wobble;
typedef struct { short duration; short hold; Wobble w[5]; } WobbleDef;
typedef struct { int pad0, pad4; short *ref; unsigned short id; short pad; int index; MATRIX *mat; int time; } Obj;
extern WobbleDef *D_800AE280[];
extern int D_800DE30C;
extern int func_8008AD60(int);
extern void func_8008A510(MATRIX *, int, int, int);

static inline void reset_matrix(Obj *o)
{
    __asm__ volatile("li $8, 4096\n\tsw $8, 0(%0)\n\tsw $0, 4(%0)\n\tsw $8, 8(%0)\n\tsw $0, 12(%0)\n\tsw $8, 16(%0)\n\tsw $0, 20(%0)\n\tsw $0, 24(%0)\n\tsw $0, 28(%0)" : : "r"(o->mat) : "$8", "memory");
}

static inline void shear_matrix(MATRIX *m, int axis, int d)
{
    short xy = m->m[0][1], xz = m->m[0][2], yx = m->m[1][0];
    short yz = m->m[1][2], zx = m->m[2][0], zy = m->m[2][1];

    switch (axis) {
    case 0: xy += d; break;
    case 1: yz += d; break;
    case 2: zx += d; break;
    case 3: xz += d; break;
    case 4: yx += d; break;
    case 5: zy += d; break;
    }
    m->m[0][1] = xy; m->m[0][2] = xz; m->m[1][0] = yx;
    m->m[1][2] = yz; m->m[2][0] = zx; m->m[2][1] = zy;
}

void func_8007471C(Obj *arg0, int *done)
{
    Obj *obj = arg0;
    WobbleDef *def = D_800AE280[obj->index];
    int amp, i, d;

    if (obj->ref == 0 || *obj->ref != obj->id) {
        obj->time = def->duration << 12;
    }
    if (obj->time < def->duration << 12) {
        amp = 0;
        reset_matrix(obj);
        for (i = 0; i < 5; i++) {
            short off;
            if (def->w[i].mode == 2) {
                int a = def->w[i].amp;
                int len = def->duration << 12;
                int t = obj->time << 1;
                int over = t - len;
                amp = a * (over >= 0 ? len - over : t) / len;
            } else if (def->w[i].mode == 1) {
                amp = def->w[i].amp * obj->time / (def->duration << 12);
            } else if (def->w[i].mode == 0) {
                amp = def->w[i].amp;
            }
            {
                int tm = obj->time;
                off = def->w[i].offset;
                d = (off + func_8008AD60(def->w[i].phase + tm * def->w[i].speed / 4096)) * (short)amp / 4096;
            }
            switch (def->w[i].axis) {
            case 0: shear_matrix(obj->mat, 0, d); break;
            case 1: shear_matrix(obj->mat, 1, d); break;
            case 2: shear_matrix(obj->mat, 2, d); break;
            case 3: shear_matrix(obj->mat, 3, d); break;
            case 4: shear_matrix(obj->mat, 4, d); break;
            case 5: shear_matrix(obj->mat, 5, d); break;
            case 6: func_8008A510(obj->mat, d, 0x1000, 0x1000); break;
            case 7: func_8008A510(obj->mat, 0x1000, d, 0x1000); break;
            case 8: func_8008A510(obj->mat, 0x1000, 0x1000, d); break;
            }
        }
        obj->time += D_800DE30C;
        *done = 0;
    } else {
        if (def->hold) {
            reset_matrix(obj);
        }
        *done = 1;
    }
}
