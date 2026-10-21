typedef struct SpuVolume {
    short left;
    short right;
} SpuVolume;

typedef struct SpuVoiceAttr {
    unsigned long voice;
    unsigned long mask;
    SpuVolume volume;
    SpuVolume volmode;
    SpuVolume volumex;
    unsigned short pitch;
    unsigned short note;
    unsigned short sample_note;
    short envx;
    unsigned long addr;
    unsigned long loop_addr;
    long a_mode;
    long s_mode;
    long r_mode;
    unsigned short ar;
    unsigned short dr;
    unsigned short sr;
    unsigned short rr;
    unsigned short sl;
    unsigned short adsr1;
    unsigned short adsr2;
} SpuVoiceAttr;

extern volatile unsigned short *D_800B76F0;
extern unsigned short D_800B778C[];
extern unsigned short func_8009AEE4(int, int, int, int);
extern void func_8009A8C0(int, unsigned long);

void func_80090E10(SpuVoiceAttr *attr) {
    volatile int count;
    volatile int value;
    int all;
    unsigned long mask;
    int voice;
    int pos;
    unsigned short volmode;
    unsigned short vol;
    unsigned short center;
    unsigned short note;
    unsigned int rate;
    int mode;
    int adsr;
    volatile unsigned short *p;
    unsigned short *centers;

    voice = 0;
    mask = attr->mask;
    all = mask == 0;
    centers = D_800B778C;
    for (; voice < 24; voice++, centers++) {
        if ((attr->voice & (1 << voice)) == 0) {
            continue;
        }
        pos = voice * 8;
        if (all || (mask & 0x10)) {
            D_800B76F0[pos + 2] = attr->pitch;
        }
        if (all || (mask & 0x40)) {
            *centers = attr->sample_note;
        }
        if (all || (mask & 0x20)) {
            center = *centers;
            note = attr->note;
            D_800B76F0[pos + 2] = func_8009AEE4(center >> 8, center & 0xFF, note >> 8, note & 0xFF);
        }
        if (all || (mask & 0x1)) {
            volmode = 0;
            vol = attr->volume.left & 0x7FFF;
            if (all || (mask & 0x4)) {
                switch (attr->volmode.left) {
                case 1:
                    volmode = 0x8000;
                    break;
                case 2:
                    volmode = 0x9000;
                    break;
                case 3:
                    volmode = 0xA000;
                    break;
                case 4:
                    volmode = 0xB000;
                    break;
                case 5:
                    volmode = 0xC000;
                    break;
                case 6:
                    volmode = 0xD000;
                    break;
                case 7:
                    volmode = 0xE000;
                    break;
                }
            }
            if (volmode != 0) {
                if (attr->volume.left >= 0x80) {
                    vol = 0x7F;
                } else if (attr->volume.left < 0) {
                    vol = 0;
                }
            }
            D_800B76F0[pos] = vol | volmode;
        }
        if (all || (mask & 0x2)) {
            volmode = 0;
            vol = attr->volume.right & 0x7FFF;
            if (all || (mask & 0x8)) {
                switch (attr->volmode.right) {
                case 1:
                    volmode = 0x8000;
                    break;
                case 2:
                    volmode = 0x9000;
                    break;
                case 3:
                    volmode = 0xA000;
                    break;
                case 4:
                    volmode = 0xB000;
                    break;
                case 5:
                    volmode = 0xC000;
                    break;
                case 6:
                    volmode = 0xD000;
                    break;
                case 7:
                    volmode = 0xE000;
                    break;
                }
            }
            if (volmode != 0) {
                if (attr->volume.right >= 0x80) {
                    vol = 0x7F;
                } else if (attr->volume.right < 0) {
                    vol = 0;
                }
            }
            D_800B76F0[pos + 1] = vol | volmode;
        }
        if (all || (mask & 0x80)) {
            func_8009A8C0(pos | 3, attr->addr);
        }
        if (all || (mask & 0x10000)) {
            func_8009A8C0(pos | 7, attr->loop_addr);
        }
        if (all || (mask & 0x20000)) {
            D_800B76F0[pos + 4] = attr->adsr1;
        }
        if (all || (mask & 0x40000)) {
            D_800B76F0[pos + 5] = attr->adsr2;
        }
        if (all || (mask & 0x800)) {
            rate = attr->ar;
            if (rate >= 0x80) {
                rate = 0x7F;
            }
            mode = 0;
            if (all || (mask & 0x100)) {
                if (attr->a_mode == 5) {
                    mode = 0x80;
                }
            }
            p = (volatile unsigned short *)(pos * 2);
            p = (volatile unsigned short *)((int)p + (int)D_800B76F0);
            adsr = p[4];
            adsr &= 0xFF;
            adsr |= (rate | mode) << 8;
            p[4] = adsr;
        }
        if (all || (mask & 0x1000)) {
            rate = attr->dr;
            if (rate >= 0x10) {
                rate = 0xF;
            }
            D_800B76F0[pos + 4] = (D_800B76F0[pos + 4] & 0xFF0F) | (rate << 4);
        }
        if (all || (mask & 0x2000)) {
            rate = attr->sr;
            if (rate >= 0x80) {
                rate = 0x7F;
            }
            mode = 0x100;
            if (all || (mask & 0x200)) {
                switch (attr->s_mode) {
                case 1:
                    mode = 0;
                    break;
                case 5:
                    mode = 0x200;
                    break;
                case 7:
                    mode = 0x300;
                    break;
                }
            }
            p = (volatile unsigned short *)(pos * 2);
            p = (volatile unsigned short *)((int)p + (int)D_800B76F0);
            adsr = p[5];
            adsr &= 0x3F;
            adsr |= (rate | mode) << 6;
            p[5] = adsr;
        }
        if (all || (mask & 0x4000)) {
            rate = attr->rr;
            if (rate >= 0x20) {
                rate = 0x1F;
            }
            mode = 0;
            if (all || (mask & 0x400)) {
                switch (attr->r_mode) {
                case 3:
                    break;
                case 7:
                    mode = 0x20;
                    break;
                }
            }
            D_800B76F0[pos + 5] = (D_800B76F0[pos + 5] & 0xFFC0) | (rate | mode);
        }
        if (all || (mask & 0x8000)) {
            rate = attr->sl;
            if (rate >= 0x10) {
                rate = 0xF;
            }
            D_800B76F0[pos + 4] = (D_800B76F0[pos + 4] & ~0xF) | rate;
        }
    }
    value = 1;
    count = 0;
    while (count < 2) {
        value = value * 13;
        count = count + 1;
    }
}
