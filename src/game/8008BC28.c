typedef struct ScratchChannel {
    unsigned char unused0[10];
    short mode;
    unsigned char unusedC[8];
} ScratchChannel;

void func_8008BC28(unsigned int mode) {
    register ScratchChannel *channels asm("$9") = (ScratchChannel *)0x1F800300;
    register unsigned int bits asm("$4") = mode;
    register int value asm("$3");

    asm("" : "+r"(channels), "+r"(bits));
    value = channels[0].mode;
    asm("" : "+r"(value), "+r"(bits));
    bits &= 3U;
    value &= 0xFF9F;
    bits <<= 5;
    value = bits | value;
    channels[0].mode = (short)value;
    value = channels[1].mode;
    value &= 0xFF9F;
    value = bits | value;
    channels[1].mode = (short)value;
    value = channels[2].mode;
    value &= 0xFF9F;
    value = bits | value;
    channels[2].mode = (short)value;
}
