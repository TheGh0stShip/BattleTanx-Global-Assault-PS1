typedef signed int s32;

typedef struct Record {
    char pad_00[8];
    void *owner;
    char pad_0C[4];
    s32 field_10;
    s32 field_14;
    s32 field_18;
    char pad_1C[4];
    s32 descriptor;
} Record;

typedef struct Owner {
    char pad_00[0xAC];
    Record *record;
} Owner;

extern s32 D_800D2FE0;
extern Record *func_8002380C(s32 pool, s32 size);

Record *func_8006C2D4(Owner *owner) {
    register Record *record asm("$4");
    register s32 *descriptor_ptr asm("$2");
    register s32 descriptor asm("$3");
    Record *result;

    record = func_8002380C(6, 0x28);
    if (record == 0)
        goto failed;
    descriptor_ptr = &D_800D2FE0;
    descriptor = *descriptor_ptr;
    result = record;
    record->owner = owner;
    owner->record = record;
    record->field_10 = 0;
    record->field_14 = 0;
    record->field_18 = 0;
    record->descriptor = descriptor;
    goto done;
failed:
    asm volatile("" : : : "$4");
    result = 0;
done:
    return result;
}
