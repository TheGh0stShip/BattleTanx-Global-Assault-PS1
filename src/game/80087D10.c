typedef struct State {
    unsigned char padding[764];
    unsigned int checksum;
} State;

extern State D_800EE588;

void func_80087D10(const unsigned char *data, unsigned int count) {
    unsigned int index = 0;

    if (count != 0) {
        do {
            D_800EE588.checksum += data[index];
            index++;
        } while (index < count);
    }
}
