typedef signed short s16;
typedef signed char s8;

extern unsigned char D_800EEE3C[];

void func_800974F8(void *data);
void func_8009B268(int enabled);

int func_80091A90(int first, int second) {
    s8 data[4];
    register unsigned char *state asm("$2");
    register void *packet asm("$4");
    s16 first_value;
    s16 second_value;

    first_value = first;
    second_value = second;
    asm("addiu $4,$29,0x10" : "=r"(packet));
    state = D_800EEE3C;
    asm("" : "+r"(state));
    *(s16 *)(state + 0x24) = first_value;
    *(s16 *)(state + 0x26) = second_value;
    data[0] = first_value >> 8;
    data[1] = 0;
    data[2] = second_value >> 8;
    data[3] = 0;
    func_800974F8(packet);
    func_8009B268(first_value != 0 || second_value != 0);
    return 1;
}
