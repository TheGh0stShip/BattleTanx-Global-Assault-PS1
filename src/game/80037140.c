typedef struct { int pad[3]; int height; int pad2[3]; unsigned int state; int start_time; int speed; } Faller;
extern int D_800D2FE0;

void func_80037140(Faller *f) {
    int h;

    switch (f->state) {
    case 1:
        if (D_800D2FE0 - f->start_time > 120) {
            f->state = 2;
        }
        break;
    case 0:
        break;
    case 2:
        f->speed -= 2457;
        h = f->height + f->speed;
        f->height = h;
        if (h < 0) {
            f->height = 0;
            f->state = 3;
        }
        break;
    }
}
