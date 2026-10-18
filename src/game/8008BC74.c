typedef unsigned short u16;
typedef unsigned int u32;

typedef struct PackedRecord {
    u16 word_00;
    u16 word_02;
    u16 word_04;
    u16 pad_06[6];
    u16 field_12;
} PackedRecord;

void func_8008BC74(PackedRecord *record, u32 shift, u32 value,
                   u32 small_value, u32 high_value, u32 source,
                   u32 field_12) {
    register u32 field_value asm("$10") = field_12;
    register u32 source_value asm("$9") = source;
    register u32 high_bits asm("$8") = high_value;
    register u32 packed asm("$11");
    register u32 part asm("$12");

    asm volatile("" : "+r"(field_value), "+r"(source_value), "+r"(high_bits));
    record->field_12 = field_value;
    asm volatile("" : : : "memory");
    packed = (shift << 2) & 0xFC;
    packed >>= source_value;
    part = value << 8;
    packed |= part;
    record->word_00 = packed;
    asm volatile("" : : : "memory");
    packed = (shift >> 6) & 0xF;
    asm volatile("" : : "r"(shift));
    part = (value >> 4) & 0x10;
    asm volatile("" : : "r"(value));
    packed |= part;
    part = source_value << 7;
    packed |= part;
    record->word_02 = packed;
    asm volatile("" : : : "memory");
    packed = (small_value >> 4) & 0x3F;
    asm volatile("" : : "r"(small_value));
    part = high_bits << 6;
    packed |= part;
    record->word_04 = packed;
}
