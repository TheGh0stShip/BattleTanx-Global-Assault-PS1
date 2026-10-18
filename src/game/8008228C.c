struct ActiveObject {
    unsigned char pad_00[8];
    void *value_08;
};

typedef void (*SlotCallback)(int type, void *value, int enabled);

extern unsigned char D_800EDC9C[];

void func_8008228C(unsigned int index) {
    register unsigned char *base asm("$2") = D_800EDC9C;
    unsigned char *slot;
    struct ActiveObject *object;

    asm("" : "+r"(base));
    index *= 4;
    slot = (unsigned char *)(index + (unsigned int)base);
    object = *(struct ActiveObject **)(slot + 0x1C8);

    if (object != 0) {
        SlotCallback callback = *(SlotCallback *)(slot + 0x0C);

        callback(12, object->value_08, 1);
        if (*(struct ActiveObject **)(slot + 0x1C8) != 0) {
            *(struct ActiveObject **)(slot + 0x1C8) = 0;
        }
    }
}
