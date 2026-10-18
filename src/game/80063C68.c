typedef struct Entry {
    int value;
    short timer;
} Entry;

extern Entry D_800AAF04;
extern Entry D_800AAF0C;
extern int *D_800AAF2C;
extern int *D_800AAF30;
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

void func_80063C68(int value, unsigned short player, int kind) {
    Entry *entry;
    int **slot;
    int *text;

    switch (player) {
    case 0:
        entry = &D_800AAF04;
        slot = &D_800AAF2C;
        break;
    case 1:
        entry = &D_800AAF0C;
        slot = &D_800AAF30;
        break;
    default:
        entry = &D_800AAF04;
        slot = &D_800AAF2C;
        break;
    }
    entry->timer = 50;
    entry->value = value;
    switch (kind) {
    case 2:
        text = &D_800E497C;
        break;
    case 3:
        text = &D_800E49A8;
        break;
    case 4:
        text = &D_800E4884;
        break;
    case 5:
    case 15:
        text = &D_800E4934;
        break;
    case 6:
        text = &D_800E489C;
        break;
    case 7:
        text = &D_800E4894;
        break;
    case 8:
        text = &D_800E4A68;
        break;
    case 9:
        text = &D_800E498C;
        break;
    case 10:
        text = &D_800E4974;
        break;
    case 11:
        text = &D_800E49B0;
        break;
    case 14:
        text = &D_800E4864;
        break;
    case 12:
        text = &D_800E4998;
        break;
    case 13:
        text = &D_800E4984;
        break;
    case 16:
        text = &D_800E495C;
        break;
    default:
        text = 0;
        break;
    }
    *slot = text;
}
