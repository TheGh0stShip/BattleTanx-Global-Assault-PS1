typedef struct SVec3 {
    short x;
    short y;
    short z;
} SVec3;
typedef struct ViewPreset {
    SVec3 single_a;
    SVec3 split_a;
    SVec3 single_b;
    SVec3 split_b;
} ViewPreset;
typedef struct Vehicle {
    char pad00[0x9C];
    int type;
} Vehicle;
typedef struct ViewOwner {
    unsigned short id;
    char pad02[2];
    short kind;
    char pad06[2];
    Vehicle *vehicle;
} ViewOwner;
typedef struct View {
    short fov;
    char pad02[0x14 - 2];
    short rot_z;
    short rot_y;
    short rot_x;
    char pad1A[2];
    SVec3 color;
    char pad22[2];
    short scale_x;
    short scale_y;
    char pad28[0x48 - 0x28];
    ViewOwner *owner;
    unsigned short owner_id;
    char pad4E[0x90 - 0x4E];
    SVec3 angle;
    SVec3 offset;
} View;
extern ViewPreset *D_800AEDD4[];
extern ViewPreset D_800AEE10;
extern ViewPreset D_800AEE28;
extern ViewPreset D_800AEE40;
extern ViewPreset D_800BD4E0;
extern SVec3 D_800BD4D8;
extern unsigned char D_800D2FEC;

static inline void copy_svec(SVec3 *dst, SVec3 *src) {
    short x = src->x;
    short y = src->y;
    short z = src->z;

    dst->x = x;
    dst->y = y;
    dst->z = z;
}

void func_800149B8(View *view, ViewOwner *owner, ViewPreset *preset) {
    ViewPreset p;

    view->scale_x = 4096;
    view->scale_y = 4096;
    view->owner = owner;
    view->owner_id = owner->id;
    if (preset != 0) {
        p = *preset;
    } else {
        switch (owner->kind) {
        case 6:
            p = D_800AEE40;
            break;
        case 3:
            p = D_800AEE28;
            break;
        case 12:
            p = D_800AEE10;
            break;
        case 4:
            if (owner->vehicle != 0) {
                p = *D_800AEDD4[owner->vehicle->type];
                break;
            }
        default:
            p = D_800BD4E0;
            break;
        }
    }
    if (D_800D2FEC >= 2) {
        view->angle = p.split_a;
        view->offset = p.split_b;
    } else {
        view->angle = p.single_a;
        view->offset = p.single_b;
    }
    view->fov = (view->angle.z << 16) / 36000;
    view->rot_z = 0;
    view->rot_x = view->angle.x << 2;
    view->rot_y = view->angle.y << 2;
    copy_svec(&view->color, &D_800BD4D8);
}
