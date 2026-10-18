typedef struct Record {
    unsigned int reserved[2];
    unsigned int key;
} Record;

typedef struct RecordBlock {
    Record *records;
    int size;
} RecordBlock;

Record *func_8009825C(RecordBlock *block, unsigned int key) {
    register int size asm("$6") = block->size;
    register Record *result asm("$3") = 0;

    if (size < 0) {
        Record *record = block->records;
        register unsigned int length asm("$2") = size & 0x7FFFFFFF;
        register unsigned char *end asm("$6");

        end = (unsigned char *)record + length;

    loop:
        if ((unsigned char *)record >= end) {
            goto done;
        }
        if (record->key == key) {
            result = record;
        }
        record++;
        if (result == 0) {
            goto loop;
        }
    }
done:
    return result;
}
