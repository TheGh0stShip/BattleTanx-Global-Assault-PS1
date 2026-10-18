extern volatile unsigned char *D_800B8FEC;
extern volatile unsigned char *D_800B8FF4;
extern volatile unsigned char *D_800B8FF8;
extern unsigned int *D_800B8FFC;
typedef struct CdMode {
    unsigned char a;
    unsigned char b;
    unsigned char c;
} CdMode;

extern volatile CdMode D_800B9004;

void func_800A090C(void) {
    volatile CdMode *m;

    *D_800B8FEC = 1;
    while (*D_800B8FF8 & 7) {
        *D_800B8FEC = 1;
        *D_800B8FF8 = 7;
        *D_800B8FF4 = 7;
    }
    m = &D_800B9004;
    m->c = 0;
    m->b = m->c;
    m->a = 2;
    *D_800B8FEC = 0;
    *D_800B8FF8 = 0;
    *D_800B8FFC = 0x1325;
}
