typedef unsigned char u8;
typedef signed int s32;

s32 func_8009F420(u8 *object) {
    register s32 index asm("$8");
    register s32 record_offset asm("$10");
    register s32 disabled asm("$11");

    if (object[0xe9] != 0) {
        index = 0;
        disabled = 0xff;
        asm("addu %0,$zero,$zero" : "=r"(record_offset));
        do {
            register u8 *values asm("$5") = *(u8 **)(object + 0x20);
            register s32 matches asm("$7") = 0;
            register s32 scan asm("$3") = 5;
            do {
                if (*values++ == index) {
                    matches++;
                }
                scan--;
            } while (scan >= 0);
            asm volatile("");
            {
                register s32 threshold asm("$9") =
                    *(record_offset + *(u8 **)(object + 4) + 2);
                register u8 *output asm("$6");
                register s32 slot asm("$3") = 0;
                values = *(u8 **)(object + 0x20);
                if (threshold == 0) {
                    threshold = 1;
                }
                asm("" : : "r"(threshold));
                output = object;
                do {
                    if (*values++ == index) {
                        if (matches < threshold) {
                            asm volatile("");
                            output[0x5d] = disabled;
                            matches--;
                        } else {
                            output[0x5d] = index;
                        }
                    }
                    slot++;
                    output++;
                } while (slot < 6);
            }
            {
                register s32 count asm("$2") = object[0xe9];
                asm("" : "+r"(count));
                index++;
                record_offset += 5;
                if (index >= count) {
                    break;
                }
            }
        } while (1);
    }
    object[0x46] = 0xfe;
    return 0;
}
