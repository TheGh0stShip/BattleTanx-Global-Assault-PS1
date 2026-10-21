typedef struct {
    short left;
    short right;
} SpuVolume80090414;

typedef struct {
    SpuVolume80090414 volume;
    int reverb;
    int mix;
} SpuExtAttr80090414;

typedef struct {
    unsigned int mask;
    SpuVolume80090414 mvol;
    SpuVolume80090414 mvolmode;
    SpuVolume80090414 mvolx;
    SpuExtAttr80090414 cd;
    SpuExtAttr80090414 ext;
} SpuCommonAttr80090414;

typedef struct {
    char pad0[0x180];
    unsigned short main_vol_l;
    unsigned short main_vol_r;
    char pad184[0x26];
    unsigned short spucnt;
    char pad1AC[4];
    unsigned short cd_vol_l;
    unsigned short cd_vol_r;
    unsigned short ex_vol_l;
    unsigned short ex_vol_r;
} SpuRegs80090414;

extern SpuRegs80090414 *D_800B76F0;

void func_80090414(SpuCommonAttr80090414 *attr) {
    int mask;
    int all;
    int vol_l;
    int vol_r;
    int mode;
    short sv;
    int uv;

    vol_l = 0;
    __asm__("" : "=r"(vol_l) : "0"(vol_l));
    mask = attr->mask;
    all = mask == 0;
    vol_r = 0;
    if (all || (mask & 1)) {
        if (all || (mask & 4)) {
            switch (attr->mvolmode.left) {
            case 1:
                mode = 0x8000;
                break;
            case 2:
                mode = 0x9000;
                break;
            case 3:
                mode = 0xA000;
                break;
            case 4:
                mode = 0xB000;
                break;
            case 5:
                mode = 0xC000;
                break;
            case 6:
                mode = 0xD000;
                break;
            case 7:
                mode = 0xE000;
                break;
            case 0:
                vol_l = (unsigned short)attr->mvol.left;
                mode = 0;
                break;
            default:
                vol_l = (unsigned short)attr->mvol.left;
                mode = 0;
                break;
            }
        } else {
            vol_l = (unsigned short)attr->mvol.left;
            mode = 0;
        }
        if (mode != 0) {
            uv = (unsigned short)attr->mvol.left;
            sv = attr->mvol.left;
            if (sv >= 0x80) {
                vol_l = 0x7F;
            } else if (sv >= 0) {
                vol_l = uv;
            } else {
                vol_l = 0;
            }
        }
        D_800B76F0->main_vol_l = (vol_l & 0x7FFF) | mode;
    }
    if (all || (mask & 2)) {
        if (all || (mask & 8)) {
            switch (attr->mvolmode.right) {
            case 1:
                mode = 0x8000;
                break;
            case 2:
                mode = 0x9000;
                break;
            case 3:
                mode = 0xA000;
                break;
            case 4:
                mode = 0xB000;
                break;
            case 5:
                mode = 0xC000;
                break;
            case 6:
                mode = 0xD000;
                break;
            case 7:
                mode = 0xE000;
                break;
            case 0:
                vol_r = (unsigned short)attr->mvol.right;
                mode = 0;
                break;
            default:
                vol_r = (unsigned short)attr->mvol.right;
                mode = 0;
                break;
            }
        } else {
            vol_r = (unsigned short)attr->mvol.right;
            mode = 0;
        }
        if (mode != 0) {
            uv = (unsigned short)attr->mvol.right;
            sv = attr->mvol.right;
            if (sv >= 0x80) {
                vol_r = 0x7F;
            } else if (sv >= 0) {
                vol_r = uv;
            } else {
                vol_r = 0;
            }
        }
        D_800B76F0->main_vol_r = (vol_r & 0x7FFF) | mode;
    }
    if (all || (mask & 0x40)) {
        D_800B76F0->cd_vol_l = attr->cd.volume.left;
    }
    if (all || (mask & 0x80)) {
        D_800B76F0->cd_vol_r = attr->cd.volume.right;
    }
    if (all || (mask & 0x400)) {
        D_800B76F0->ex_vol_l = attr->ext.volume.left;
    }
    if (all || (mask & 0x800)) {
        D_800B76F0->ex_vol_r = attr->ext.volume.right;
    }
    if (all || (mask & 0x100)) {
        if (attr->cd.reverb == 0) {
            D_800B76F0->spucnt &= ~4;
        } else {
            D_800B76F0->spucnt |= 4;
        }
    }
    if (all || (mask & 0x200)) {
        if (attr->cd.mix == 0) {
            D_800B76F0->spucnt &= ~1;
        } else {
            D_800B76F0->spucnt |= 1;
        }
    }
    if (all || (mask & 0x1000)) {
        if (attr->ext.reverb == 0) {
            D_800B76F0->spucnt &= ~8;
        } else {
            D_800B76F0->spucnt |= 8;
        }
    }
    if (all || (mask & 0x2000)) {
        if (attr->ext.mix == 0) {
            D_800B76F0->spucnt &= ~2;
        } else {
            D_800B76F0->spucnt |= 2;
        }
    }
    __asm__ volatile("");
}
