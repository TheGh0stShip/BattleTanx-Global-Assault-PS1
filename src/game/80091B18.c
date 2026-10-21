extern int func_80091A90(int, int);
extern void func_80088870(int);

typedef struct {
    int w0;
    int rate;
} Cfg80091B18;
extern Cfg80091B18 D_80086058;

int func_80091B18(int ms, short x0, short y0, short x1, short y1) {
    unsigned int steps;
    short dx;
    short dy;
    short x;
    short y;
    int ok;

    steps = ms * D_80086058.rate;
    steps /= 1000;
    if (steps == 0) {
        steps = 1;
    }
    x = x0;
    y = y0;
    dx = (x1 - x0) / (int)steps;
    dy = (y1 - y0) / (int)steps;
    do {
        x += dx;
        y += dy;
        ok = func_80091A90(x, y);
        func_80088870(0);
        steps--;
        if (ok == 0) {
            break;
        }
    } while (steps != 0);
    if ((x != x1 || y != y1) && func_80091A90(x1, y1) == 0) {
        ok = 0;
    }
    return ok;
}
