extern volatile unsigned char *D_800B8FEC;
extern volatile unsigned char *D_800B8FF0;
extern volatile unsigned char *D_800B8FF4;
extern volatile unsigned char *D_800B8FF8;

int func_800A0884(unsigned char *vol) {
    *D_800B8FEC = 2;
    *D_800B8FF4 = vol[0];
    *D_800B8FF8 = vol[1];
    *D_800B8FEC = 3;
    *D_800B8FF0 = vol[2];
    *D_800B8FF4 = vol[3];
    *D_800B8FF8 = 0x20;
    return 0;
}
