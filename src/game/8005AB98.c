typedef struct {
    unsigned short flags;
    char pad2;
    signed char children[6];
    char pad9[3];
    void *owner;
} Slot;
extern void func_80057E40(void *);
extern Slot D_800E474C[];

void func_8005AB98(unsigned short index) {
    unsigned short i;

    for (i = 0; i < 6; i++) {
        if (D_800E474C[index].children[i] > 0) {
            func_8005AB98(D_800E474C[index].children[i]);
        }
    }
    if (D_800E474C[index].flags & 1) {
        func_80057E40(D_800E474C[index].owner);
    }
}
