typedef struct SpuVoice {
    unsigned short vol_l;
    unsigned short vol_r;
    unsigned short pitch;
    unsigned short addr;
    unsigned short adsr1;
    unsigned short adsr2;
    unsigned short volx;
    unsigned short loop;
} SpuVoice;

typedef struct SpuRegs {
    SpuVoice voice[24];
    volatile unsigned short main_vol_l;
    volatile unsigned short main_vol_r;
    unsigned short rev_vol_l;
    unsigned short rev_vol_r;
    unsigned short key_on_l;
    unsigned short key_on_r;
    unsigned short key_off_l;
    unsigned short key_off_r;
    volatile unsigned short pitch_mod_l;
    volatile unsigned short pitch_mod_r;
    volatile unsigned short noise_l;
    volatile unsigned short noise_r;
    unsigned short reverb_l;
    unsigned short reverb_r;
    unsigned short status_l;
    unsigned short status_r;
    unsigned short pad1a0;
    unsigned short rev_addr;
    unsigned short irq_addr;
    unsigned short trans_addr;
    unsigned short data;
    volatile unsigned short control;
    unsigned short trans_ctrl;
    volatile unsigned short status;
    volatile unsigned short cd_vol_l;
    volatile unsigned short cd_vol_r;
    volatile unsigned short ext_vol_l;
    volatile unsigned short ext_vol_r;
} SpuRegs;

extern SpuRegs *D_800B76F0;
extern volatile int *D_800B7700;
extern unsigned short D_800B7708;
extern int D_800B770C;
extern int D_800B7710;
extern int D_800B7714;
extern int D_800B7718;
extern int D_800B771C;
extern int D_800B7720;
extern volatile int D_800B7724;
extern volatile int D_800B7728;
extern volatile int D_800B772C;
extern unsigned char D_800B7730[];
extern short D_800EF188[];
extern char D_800C5530[];
extern char D_800C5540[];
extern void func_8009AA0C(void);
extern void func_800943B0(char *, char *);
extern void func_8009A2FC(unsigned char *, int);

int func_8009A07C(int mode) {
    unsigned int count;
    int i;

    *D_800B7700 |= 0xB0000;
    D_800B770C = 0;
    D_800B7710 = 0;
    D_800B7708 = 0;
    D_800B76F0->main_vol_l = 0;
    D_800B76F0->main_vol_r = 0;
    D_800B76F0->control = 0;
    func_8009AA0C();
    D_800B76F0->main_vol_l = 0;
    D_800B76F0->main_vol_r = 0;
    count = 0;
    while (D_800B76F0->status & 0x7FF) {
        if (++count > 0xF00) {
            func_800943B0(D_800C5530, D_800C5540);
            break;
        }
    }
    D_800B7714 = 2;
    D_800B7718 = 3;
    D_800B771C = 8;
    D_800B7720 = 7;
    D_800B76F0->trans_ctrl = 4;
    D_800B76F0->rev_vol_l = 0;
    D_800B76F0->rev_vol_r = 0;
    D_800B76F0->key_off_l = 0xFFFF;
    D_800B76F0->key_off_r = 0xFFFF;
    D_800B76F0->reverb_l = 0;
    D_800B76F0->reverb_r = 0;
    {
        short *p;
        for (i = 0, p = D_800EF188; i < 10; i++) {
            *p++ = 0;
        }
    }
    if (mode == 0) {
        D_800B7708 = 0x200;
        D_800B76F0->pitch_mod_l = 0;
        D_800B76F0->pitch_mod_r = 0;
        D_800B76F0->noise_l = 0;
        D_800B76F0->noise_r = 0;
        D_800B76F0->cd_vol_l = 0;
        D_800B76F0->cd_vol_r = 0;
        D_800B76F0->ext_vol_l = 0;
        D_800B76F0->ext_vol_r = 0;
        func_8009A2FC(D_800B7730, 16);
        {
            SpuVoice *v = D_800B76F0->voice;
            for (i = 0; i < 24; i++) {
                v->vol_l = 0;
                v->vol_r = 0;
                v->pitch = 0x3FFF;
                v->addr = 0x200;
                v->adsr1 = 0;
                v->adsr2 = 0;
                v++;
            }
        }
        D_800B76F0->key_on_l = 0xFFFF;
        D_800B76F0->key_on_r = 0xFF;
        func_8009AA0C();
        func_8009AA0C();
        func_8009AA0C();
        func_8009AA0C();
        D_800B76F0->key_off_l = 0xFFFF;
        D_800B76F0->key_off_r = 0xFF;
        func_8009AA0C();
        func_8009AA0C();
        func_8009AA0C();
        func_8009AA0C();
    }
    {
        int r;
        r = 0;
        D_800B7724 = 1;
        D_800B76F0->control = 0xC000;
        D_800B7728 = 0;
        D_800B772C = 0;
        __asm__("" : "=r"(r) : "0"(r));
        return r;
    }
}
