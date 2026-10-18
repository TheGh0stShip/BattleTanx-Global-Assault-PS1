typedef struct TimedValue {
    unsigned char pad_00[0x20];
    int value;
    unsigned char pad_24[4];
    int ticks;
} TimedValue;

void func_80037048(TimedValue *state, int *finished) {
    state->value += (int)0xFFB50000;
    state->ticks--;
    if (state->ticks <= 0 || state->value <= 0) {
        *finished = 1;
    }
}
