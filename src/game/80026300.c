typedef unsigned short u16;

typedef struct EntrySource {
    unsigned char pad_00[0x1C];
    int first_index;
} EntrySource;

typedef struct EntryContext {
    EntrySource *source;
    unsigned char pad_04[0x10];
    unsigned char *entries;
} EntryContext;

void *func_80026300(EntryContext *context, u16 index) {
    register EntrySource *source asm("$3") = context->source;

    asm("" : "+r"(source));
    if (index == 0xFFFF) {
        return 0;
    }
    return context->entries + (source->first_index + index) * 12;
}
