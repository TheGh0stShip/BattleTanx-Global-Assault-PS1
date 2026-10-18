typedef struct {
    char pad0[0xC];
    void *owner;
} Slot;
extern Slot D_800E474C[];
extern void func_8005992C(unsigned short);

void func_8005AC50(void *owner) {
    unsigned short i;

    for (i = 0; i < 10; i++) {
        if (D_800E474C[i].owner == owner) {
            func_8005992C(i);
        }
    }
}
