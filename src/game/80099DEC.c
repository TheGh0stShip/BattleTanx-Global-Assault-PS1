
typedef struct SioRegs {
    unsigned char data;
    unsigned char pad1[3];
    unsigned short status;
    unsigned short pad6;
    unsigned short mode;
    unsigned short ctrl;
    unsigned short pad12;
    unsigned short baud;
} SioRegs;

extern volatile SioRegs *D_800B76E8;
extern int D_800EF17C;
extern int D_800EF180;
extern int D_800EF184;


int func_80099DEC(unsigned int cmd, unsigned int arg, unsigned int param)
{
    int ret = 0;

    switch (cmd) {
    case 0:
        switch (arg) {
        case 0:
            ret = D_800B76E8->status;
            break;
        case 1:
            ret = D_800B76E8->ctrl;
            break;
        case 2:
            ret = D_800B76E8->mode;
            break;
        case 3:
            ret = (unsigned short)(2073600 / D_800B76E8->baud);
            break;
        case 4:
            ret = D_800B76E8->data;
            break;
        default:
            ret = -1;
            break;
        }
        break;
    case 1:
        switch (arg) {
        case 1:
            D_800B76E8->ctrl = param & 0x1CFF;
            break;
        case 2:
            D_800B76E8->mode = (param & 0xFE) | 2;
            break;
        case 3:
            D_800B76E8->baud = 2073600 / param;
            break;
        case 4:
            D_800B76E8->data = param;
            break;
        default:
            ret = -1;
            break;
        }
        break;
    case 2:
        switch (arg) {
        case 0:
            D_800EF184 = D_800B76E8->ctrl;
            D_800EF17C = D_800B76E8->mode;
            D_800EF180 = D_800B76E8->baud;
            D_800B76E8->ctrl |= 0x40;
            D_800B76E8->ctrl = D_800EF184;
            D_800B76E8->mode = D_800EF17C;
            D_800B76E8->baud = D_800EF180;
            break;
        case 1:
            D_800B76E8->ctrl |= 0x10;
            break;
        }
        ret = -1;
        break;
    default:
        ret = -1;
        break;
    }
    return ret;
}
