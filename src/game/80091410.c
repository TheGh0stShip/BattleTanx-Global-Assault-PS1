typedef struct ChannelState {
    unsigned char unused0[4];
    unsigned short flags;
    unsigned char unused6[2];
    volatile short value;
    unsigned char unusedA[6];
} ChannelState;

extern ChannelState *D_800B5940;

int func_80091410(int channel, short value, unsigned int options) {
    int index;
    unsigned short flags;
    register int result asm("$2");
    register ChannelState *state asm("$3");

    index = channel & 0xFFFF;
    flags = 0x48;
    if (index >= 3) {
        result = 0;
        goto done;
    }
    state = (ChannelState *)((index << 4) + (unsigned int)D_800B5940);
    asm("" : "+r"(state));
    state->flags = 0;
    state->value = value;
    if ((unsigned int)index < 2U) {
        result = options & 0x10;
        if (result != 0) {
            flags = 0x49;
        }
        result = options & 1;
        if (result == 0) {
            flags |= 0x100;
        }
        result = options & 0x1000;
    } else {
        result = 2;
        if (index != result) {
            result = options & 0x1000;
        } else {
            result = options & 1;
            if (result == 0) {
                flags = 0x248;
            }
            result = options & 0x1000;
        }
    }
    asm volatile(".set\tnoreorder\n\t"
                 "beqz %0,1f\n\t"
                 "addiu %0,$0,1\n\t"
                 "ori %1,%1,0x10\n"
                 "1:\n\t"
                 ".set\treorder"
                 : "+r"(result), "+r"(flags));
    {
        register ChannelState *base asm("$4");
        register ChannelState *target asm("$3");
        asm volatile("lui %0,%%hi(D_800B5940)\n\t"
                     "lw %0,%%lo(D_800B5940)(%0)"
                     : "=r"(base));
        target = (ChannelState *)((index << 4) + (unsigned int)base);
        asm("" : "+r"(base), "+r"(target));
        *(volatile unsigned short *)&target->flags = flags;
    }
done:
    asm volatile("" : "+r"(result));
    return result;
}
