typedef unsigned short u16;

typedef struct Entry {
    short value;
    unsigned char pad[14];
} Entry;

extern Entry D_800E474C[];

void func_8005A888(void) {
    u16 index;

    for (index = 0; index < 10; index++) {
        D_800E474C[index].value = 0;
    }
}
