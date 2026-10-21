typedef signed int s32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct Record Record;

typedef struct Owner {
    u8 unused00[0xC];
    Record *records;
    u8 unused10[0x36];
    u8 status;
} Owner;

struct Record {
    u8 unused00[0xC];
    s32 active;
    Owner *owner;
    u8 unused14[0x32];
    u8 status;
    u8 unused47[0x9F];
    u16 enabled;
    u8 unusedE8[8];
};

s32 func_800A3954(Record *record) {
    s32 var_a1;
    s32 result;
    u8 temp_status;
    u8 owner_status;
    Record *var_record;

    result = 1;
    if (record->enabled != 0) {
        if (record->active != 0) {
            result = 1;
            if (record->status == 0xFF) {
                var_a1 = 0;
                var_record = record->owner->records;
loop:
                temp_status = var_record->status;
                if (temp_status == 0xFF ||
                    (result = 1, temp_status == 0)) {
                    var_a1++;
                    var_record++;
                    if (var_a1 >= 4) {
                        return 0;
                    }
                    goto loop;
                }
                return result;
            }
            return result;
        }
        owner_status = record->owner->status;
        if (owner_status != 0xFF ||
            (result = 0, record->status != owner_status)) {
            result = 1;
        }
        return result;
    }
    return result;
}
