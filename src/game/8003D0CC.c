typedef unsigned int u32;

typedef struct PaletteRecord {
    unsigned char fields00[8];
    u32 mode;
    unsigned char fields0C[8];
    u32 clut_count;
    u32 *clut;
    u32 clut_size;
    unsigned char fields20[8];
} PaletteRecord;

typedef char PaletteRecord_size[(sizeof(PaletteRecord) == 40) ? 1 : -1];

extern PaletteRecord *func_80068F34(u32);

static inline void read_record(u32 **cursor, PaletteRecord *record) {
    u32 *words = *cursor;

    record->mode = *words++;
    switch (record->mode) {
    case 0:
        {
            register u32 bytes asm("$3") = *words++;
            register u32 elements asm("$2");

            record->clut = words;
            record->clut_count = bytes;
            asm("" : "+r"(bytes) : : "memory");
            elements = bytes;
            asm("" : "+r"(elements), "+r"(bytes));
            bytes <<= 5;
            words += elements << 3;
            record->clut_size = bytes;
        }
        break;
    case 1:
        {
            register u32 bytes asm("$3") = *words++;
            register u32 elements asm("$2");

            record->clut = words;
            record->clut_count = bytes;
            asm("" : "+r"(bytes) : : "memory");
            elements = bytes;
            asm("" : "+r"(elements), "+r"(bytes));
            bytes <<= 9;
            words += elements << 7;
            record->clut_size = bytes;
        }
        break;
    case 2:
        record->clut_count = 0;
        record->clut_size = 0;
        break;
    }
    *cursor = words;
}

PaletteRecord *func_8003D0CC(u32 *data) {
    u32 *cursor = data;
    u32 count;
    u32 i;
    PaletteRecord *records;

    cursor++;
    count = *cursor++;
    records = func_80068F34(count * 40);
    for (i = 0; i < count; i++)
        read_record(&cursor, &records[i]);
    return records;
}
