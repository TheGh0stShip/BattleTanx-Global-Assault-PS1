typedef void (*Callback)(void);

typedef struct CallbackState {
    Callback fields[6];
} CallbackState;

extern CallbackState *D_800B6B00;

void func_80094450(void) {
    D_800B6B00->fields[1]();
}
