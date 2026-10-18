struct DispatchContext {
    unsigned char pad_00[7];
    unsigned char value_07;
};

struct DispatchObject {
    unsigned char pad_000[8];
    void *value_008;
    unsigned char pad_00C[4];
    void *value_010;
    unsigned char pad_014[0x18];
    unsigned short value_02C;
    unsigned char pad_02E[0x72];
    int value_0A0;
    unsigned char pad_0A4[0x174];
    unsigned int flags_218;
};

void *func_8006B1AC(void *arg0, void *arg1, unsigned int arg2, int arg3, int arg4);
void func_80052A24(struct DispatchContext *context, void *value);
void func_8006C2D4(struct DispatchContext *context);

void func_80052BE8(struct DispatchContext *context, struct DispatchObject *object) {
    if (object->flags_218 & 2) {
        unsigned int type = object->value_02C;
        int mode = 2;
        void *value;

        if (object->value_0A0 == 0) {
            mode = 1;
        }
        value = func_8006B1AC(
            object->value_008,
            object->value_010,
            type,
            mode,
            context->value_07
        );

        func_80052A24(context, value);
    } else {
        func_8006C2D4(context);
    }
}
