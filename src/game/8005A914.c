typedef struct Entry {
    unsigned short active;
    unsigned char reserved[14];
} Entry;

extern Entry D_800E474C[];

void func_80063A68(void);

void func_8005A914(void) {
    unsigned short index = 0;

    do {
        D_800E474C[index].active = 0;
        index++;
    } while (index < 10);
    func_80063A68();
}
