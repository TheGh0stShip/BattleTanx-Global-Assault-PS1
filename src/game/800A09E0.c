typedef struct SpuRegs {
    char pad0[0x180];
    unsigned short main_vol_l;
    unsigned short main_vol_r;
    char pad184[0x26];
    unsigned short control;
    char pad1ac[4];
    unsigned short cd_vol_l;
    unsigned short cd_vol_r;
    char pad1b4[4];
    unsigned short cur_main_vol_l;
    unsigned short cur_main_vol_r;
} SpuRegs;

typedef struct CdAtv {
    unsigned char val0;
    unsigned char val1;
    unsigned char val2;
    unsigned char val3;
} CdAtv;

extern SpuRegs *D_800B9000;
extern volatile unsigned char *D_800B8FEC;
extern volatile unsigned char *D_800B8FF0;
extern volatile unsigned char *D_800B8FF4;
extern volatile unsigned char *D_800B8FF8;

static inline int cd_mix(CdAtv *vol) {
    *D_800B8FEC = 2;
    *D_800B8FF4 = vol->val0;
    *D_800B8FF8 = vol->val1;
    *D_800B8FEC = 3;
    *D_800B8FF0 = vol->val2;
    *D_800B8FF4 = vol->val3;
    *D_800B8FF8 = 0x20;
    return 0;
}

int func_800A09E0(void) {
    CdAtv atv;

    if (D_800B9000->cur_main_vol_l == 0 && D_800B9000->cur_main_vol_r == 0) {
        D_800B9000->main_vol_l = 0x3FFF;
        D_800B9000->main_vol_r = 0x3FFF;
    }
    D_800B9000->cd_vol_l = 0x3FFF;
    D_800B9000->cd_vol_r = 0x3FFF;
    D_800B9000->control = 0xC001;
    atv.val2 = 0x80;
    atv.val0 = 0x80;
    atv.val3 = 0;
    atv.val1 = 0;
    return cd_mix(&atv);
}
