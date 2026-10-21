typedef unsigned int u32;
typedef unsigned char u8;

void *func_8008AA48(void *destination, int value, u32 size) {
    register u8 *cursor asm("$4") = destination;
    register u32 byte asm("$5") = value;
    register u32 remaining asm("$6") = size;
    register u32 count asm("$8");
    register u32 four asm("$9");
    register void *result asm("$2") = destination;

    if (cursor != 0 && remaining != 0) {
        count = 7;
        if (remaining > count) {
            count = (u32)cursor & 3;
            if (count != 0) {
                four = 4;
                count = four - count;
                remaining -= count;
                do {
                    *cursor = (u8)byte;
                    count--;
                    asm("addi %0,%0,1" : "+r"(cursor));
                } while (count != 0);
            }
            byte &= 0xFF;
            count = byte << 8;
            byte = count | byte;
            count = byte << 16;
            byte = count | byte;
            count = remaining >> 2;
            remaining &= 3;
            do {
                *(u32 *)cursor = byte;
                count--;
                asm("addi %0,%0,4" : "+r"(cursor));
            } while (count != 0);
            if (remaining == 0) {
                return result;
            }
        }
        do {
            *cursor = (u8)byte;
            remaining--;
            asm("addi %0,%0,1" : "+r"(cursor));
        } while (remaining != 0);
    }
    return result;
}
