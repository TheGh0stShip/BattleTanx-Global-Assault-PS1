extern int D_800E4864;
extern int D_800E4884;
extern int D_800E4894;
extern int D_800E489C;
extern int D_800E4934;
extern int D_800E495C;
extern int D_800E4974;
extern int D_800E497C;
extern int D_800E4984;
extern int D_800E498C;
extern int D_800E4998;
extern int D_800E49A8;
extern int D_800E49B0;
extern int D_800E4A68;

int *func_800641E4(int kind) {
    switch (kind) {
    case 2:
        return &D_800E497C;
    case 3:
        return &D_800E49A8;
    case 4:
        return &D_800E4884;
    case 5:
    case 15:
        return &D_800E4934;
    case 6:
        return &D_800E489C;
    case 7:
        return &D_800E4894;
    case 8:
        return &D_800E4A68;
    case 9:
        return &D_800E498C;
    case 10:
        return &D_800E4974;
    case 11:
        return &D_800E49B0;
    case 14:
        return &D_800E4864;
    case 12:
        return &D_800E4998;
    case 13:
        return &D_800E4984;
    case 16:
        return &D_800E495C;
    default:
        return 0;
    }
}
