typedef struct {
    unsigned short flags;
    char pad2;
    signed char children[6];
    char pad9[3];
    void *owner;
} Slot;
extern Slot D_800E474C[];

void func_8005AAEC(unsigned short index) {
    unsigned short i;

    for (i = 0; i < 6; i++) {
        if (D_800E474C[index].children[i] > 0) {
            func_8005AAEC(D_800E474C[index].children[i]);
            D_800E474C[index].children[i] = -1;
        }
    }
    D_800E474C[index].flags = 0;
}
