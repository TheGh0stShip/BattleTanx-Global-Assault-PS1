extern volatile unsigned char *D_800B8FEC;
extern volatile unsigned char *func_800B8FF8;
extern volatile unsigned int *D_800B8FFC;
extern volatile unsigned int *D_800B9020;
extern volatile unsigned int *D_800B9024;
extern volatile unsigned int *D_800B9028;
extern volatile unsigned int *D_800B902C;
extern volatile unsigned int *D_800B9030;

int func_800A0E64(unsigned int address, unsigned int length) {
    *D_800B8FEC = 0;
    *func_800B8FF8 = 0x80;
    *D_800B9020 = 0x20943;
    *D_800B8FFC = 0x1323;
    *D_800B9024 |= 0x8000;
    *D_800B9028 = address;
    *D_800B902C = length | 0x10000;
    while ((*D_800B8FEC & 0x40) == 0) {
    }
    *D_800B9030 = 0x11000000;
    if ((*D_800B9030 & 0x01000000) != 0) {
        while ((*D_800B9030 & 0x01000000) != 0) {
        }
    }
    *D_800B8FFC = 0x1325;
    return 0;
}
