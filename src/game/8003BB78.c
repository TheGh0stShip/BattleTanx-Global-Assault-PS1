typedef struct { short m[3][3]; int t[3]; } Matrix;
typedef struct { char pad[8]; short dir[4]; short color[3]; char pad2[60 - 22]; } Light;
typedef struct { char pad[0x30]; Light *lights; unsigned int count; short dirs[3][3]; } LightState;
extern LightState D_800DDFF8;
extern void func_8008D078(Matrix *);

void func_8003BB78(Light *lights, unsigned int count)
{
    Matrix m;
    unsigned int i;
    Light *l;

    D_800DDFF8.lights = lights;
    D_800DDFF8.count = count;
    l = lights;
    for (i = 0; i < 3; i++, l++) {
        if (i < count) {
            m.m[0][i] = l->color[0];
            m.m[1][i] = l->color[1];
            m.m[2][i] = l->color[2];
            D_800DDFF8.dirs[i][0] = l->dir[0];
            D_800DDFF8.dirs[i][1] = l->dir[1];
            D_800DDFF8.dirs[i][2] = l->dir[2];
        } else {
            m.m[0][i] = 0;
            m.m[1][i] = 0;
            m.m[2][i] = 0;
            D_800DDFF8.dirs[i][0] = 0;
            D_800DDFF8.dirs[i][1] = 0;
            D_800DDFF8.dirs[i][2] = 0;
        }
    }
    func_8008D078(&m);
}
