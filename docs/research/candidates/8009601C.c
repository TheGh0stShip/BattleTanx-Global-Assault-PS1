typedef signed int s32;

typedef struct EventState {
    volatile s32 first;
    volatile s32 second;
    volatile s32 ready;
} EventState;

extern EventState D_800EF094;
extern volatile s32 D_800EF0DC;
extern volatile s32 D_800EF0E0;

s32 func_8009601C(s32 wait, s32 *first, s32 *second) {
    s32 result;

    if ((D_800EF094.first != 0) || (result = -1, D_800EF094.ready != 0)) {
        if (wait == 0) {
            if (D_800EF094.ready == 0) {
                do {
                } while (D_800EF094.ready == 0);
            }
            if (second != 0) {
                *second = D_800EF0E0;
            }
            if (first != 0) {
                *first = D_800EF0DC;
            }
            D_800EF094.ready = 0;
            return 1;
        }
        if (D_800EF094.ready == 0) {
            if (second != 0) {
                *second = D_800EF094.second;
            }
            result = 0;
            if (first != 0) {
                *first = D_800EF094.first;
                return 0;
            }
            return result;
        }
        if (second != 0) {
            *second = D_800EF0E0;
        }
        if (first != 0) {
            *first = D_800EF0DC;
        }
        D_800EF094.ready = 0;
        result = 1;
        return result;
    }
    return result;
}
