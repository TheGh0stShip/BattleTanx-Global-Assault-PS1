typedef struct ByteMapState {
    unsigned char unused0[0x40];
    unsigned char first;
    unsigned char second;
} ByteMapState;

extern ByteMapState D_800EEDF4;
extern unsigned int func_8008FAA4(unsigned int value);

int func_8008FBBC(int unused, unsigned char *data, unsigned int length) {
    register unsigned int saved_length asm("$19") = length;
    register unsigned int index asm("$17") = 0;
    register unsigned int result asm("$6") = 0;
    register unsigned char *saved_data asm("$20") = data;
    register unsigned int value asm("$16");
    register unsigned int first_value asm("$3");
    register unsigned int second_value asm("$4");
    register unsigned int byte_value asm("$2");
    register unsigned char *cursor asm("$2");
    ByteMapState *state;

    asm("" : "+r"(saved_length), "+r"(index), "+r"(saved_data), "+r"(result));
    if (saved_length != 0) {
        state = &D_800EEDF4;
        cursor = saved_data + index;
        do {
            first_value = state->first;
            second_value = state->second;
            value = *cursor;
            asm("" : "+r"(value));
            if (first_value != second_value) {
                byte_value = value & 0xFF;
                if (byte_value == first_value || byte_value == second_value) {
                    result = func_8008FAA4(second_value);
                    first_value = state->second;
                    value -= first_value;
                }
            }
            if (result == 0) {
                result = func_8008FAA4(value & 0xFF);
            }
            index++;
            if (index >= saved_length) {
                break;
            }
            cursor = saved_data + index;
        } while (result == 0);
    }
    return result == 0;
}
