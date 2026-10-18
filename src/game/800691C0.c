typedef struct {
    short m[3][3];
    short pad;
    int t[3];
} Matrix;

typedef struct {
    int pad;
    unsigned int count32;
    int count8;
    int pad0C[3];
    char data[1];
} ModelHeader;

typedef struct {
    ModelHeader *header;
    char *mesh;
} ModelRef;

typedef struct {
    int kind;
    void *buffer;
    ModelRef *model;
    void *verts;
    unsigned char done;
} Node;

typedef struct {
    char pad[0xC];
    int count;
    char *top;
    char *heap;
    Node *cursor;
    int free;
} Pool;

extern Pool D_800ADD14;
extern int D_800ADD34;
extern int D_800ADD38;
extern int D_800A4CC0;
extern int D_800A4CC4;
extern int D_800A4CC8;
extern int D_800A4CCC;
extern int D_800DE0B0;
extern unsigned int func_8007F7F4(void);
extern void func_8003BD0C(void *params);
extern void func_8008DC5C(int done);
extern void func_8007C0D4(ModelHeader *header, void *buffer, void *view, char *mesh, int a, int b, int c,
                          int *table, int *result, int light, int flag, int depth, int c0, int c1, int c2,
                          int c3);
extern void func_8003E0E4(void *cam, void *params, Matrix *out);
extern void func_8008BF7C(Matrix *m, char *data, void *buffer, void *view, int *result, int light, int flag);

void func_800691C0(void *view, void *cam) {
    Node *node;
    int i;
    int flag;
    int visible;
    Matrix local;

    node = D_800ADD14.cursor;
    for (i = 0; i < D_800ADD14.count; i++, node++) {
        if (func_8007F7F4() <= 10000) {
            continue;
        }
        func_8003BD0C(node->verts);
        func_8008DC5C(node->done);
        if (node->model->mesh == 0) {
            continue;
        }
        if (node->model->header->count32 >= 2 || node->kind == 5 || node->kind == 3) {
            flag = 0;
        } else {
            flag = D_800ADD38;
        }
        func_8007C0D4(node->model->header, node->buffer, view, node->model->mesh + 8, 0, 0, 0, &D_800DE0B0,
                      &visible, D_800ADD34, flag, 2304, D_800A4CC0, D_800A4CC4, D_800A4CC8, D_800A4CCC);
        if (visible) {
            func_8003E0E4(cam, node->verts, &local);
            func_8008BF7C(&local, node->model->header->data, node->buffer, view, &visible, D_800ADD34,
                          D_800ADD38);
        }
    }
}
