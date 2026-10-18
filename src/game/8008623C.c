typedef struct Record {
    unsigned int state;
    unsigned char padding[136];
} Record;

extern Record D_800EE028[];

int func_8008623C(int index) {
    return (unsigned int)(D_800EE028[index].state - 4) < 2;
}
