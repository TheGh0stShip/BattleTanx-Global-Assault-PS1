struct CallbackContext {
    unsigned char pad_00[8];
    void (*callback)(void *owner, void *value, int type, void *context);
    unsigned char pad_0C[0x14];
    void *owner;
};

extern unsigned char D_800C4C18[];
extern struct CallbackContext *D_800B0C58;

void func_8007FADC(unsigned char *state, void *value);

void func_8007FC88(void *value, void *context) {
    register void *callback_value asm("$5");

    func_8007FADC(D_800C4C18, value);
    callback_value = value;
    asm("" : "+r"(callback_value));
    D_800B0C58->callback(D_800B0C58->owner, callback_value, 8, context);
}
