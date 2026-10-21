typedef struct Rect16 {
    short x;
    short y;
    unsigned short width;
    unsigned short height;
} Rect16;

typedef struct DrawState {
    int unused0;
    unsigned short index;
    unsigned short unused6;
    int *images;
    Rect16 *rects;
} DrawState;

extern void func_80056160(int image, short x, short y,
                          int first, int second);
extern void func_80056550(int image, short x, short y,
                          short left, short top, short right, short bottom,
                          int flags, int first, int second);

void func_80056914(DrawState *state, int x, int y, int flags,
                   int first, int second) {
    register DrawState *saved_state asm("$3") = state;
    register int saved_flags asm("$9") = flags;
    register int saved_first asm("$10") = first;
    register int saved_second asm("$11") = second;

    asm("" : "+r"(saved_state), "+r"(saved_flags),
              "+r"(saved_first), "+r"(saved_second));
    if (saved_state->rects == 0) {
        func_80056160(saved_state->images[saved_state->index],
                      (short)x, (short)y, saved_first, saved_second);
    } else {
        Rect16 *rect = &saved_state->rects[saved_state->index];

        func_80056550(*saved_state->images, (short)x, (short)y,
                      rect->x, rect->y,
                      (short)(rect->x + rect->width),
                      (short)(rect->y + rect->height),
                      saved_flags, saved_first, saved_second);
    }
}
