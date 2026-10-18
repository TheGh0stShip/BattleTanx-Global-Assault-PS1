typedef struct {
    int pending;
    unsigned int position;
    int pad8;
    int ready;
    int enabled;
} Channel;
typedef struct {
    int handle;
    int pad4;
    unsigned short wide;
    unsigned short step;
} ChannelRate;
typedef struct {
    Channel channels[4];
    ChannelRate rates[4];
} ChannelBank;
extern ChannelBank D_800EDF08;
extern unsigned short func_800914AC(int handle);

unsigned int func_80083A5C(unsigned int index) {
    unsigned int pos = 0;

    if (index >= 4) {
        goto done;
    }
    pos = D_800EDF08.channels[index].position;
    if (index >= 2) {
        goto done;
    }
    if (D_800EDF08.channels[index].pending == 0) {
        pos += func_800914AC(D_800EDF08.rates[index].handle);
    }
    if (D_800EDF08.rates[index].wide != 0) {
        goto done;
    }
mask:
    pos &= 0xFFFF;
done:
    return pos;
}
