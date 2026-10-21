typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned int u32;
typedef unsigned char M2C_UNK;
typedef struct {
    u32 *name;
    u32 fields[3];
} OpcodeClass;
typedef struct {
    u32 opcode;
    u32 *name;
} GteOpcode;
typedef struct {
    union {
        s32 word;
        struct { u8 pad[3]; s8 byte; } parts;
    } a8;
    union {
        s32 word;
        struct { u8 pad[3]; s8 byte; } parts;
    } ac;
    s16 b0;
    s16 b2;
    s16 b4;
    s16 b6;
    s16 b8;
    s16 ba;
    s16 bc;
    s16 be;
} ScreenPrimitive;
typedef union {
    M2C_UNK bytes[0x30];
    struct {
        M2C_UNK header[0x18];
        ScreenPrimitive primitive;
    } layout;
} ScreenBuffer;
extern int func_8007E8E0();
extern int func_8007FA74();
extern int func_8007FE4C();
extern int func_8007FF18();
extern int func_8007FFD8();
extern int func_80088870();
extern int func_8008AFB0();
extern int func_8008BA24();
extern int func_8008BAD8();
extern int func_80091D34();
extern int func_80091D4C();
extern int func_800940C4();
extern u32 func_80094178();
extern GteOpcode D_800B0588[];
extern GteOpcode D_800B0640[];
extern OpcodeClass D_800B07C0[];
extern M2C_UNK D_800B0804;
extern u32 *D_800B080C;
extern u32 *D_800B090C;
extern u32 *D_800B0A14;
extern u32 D_800B0B94[];
extern u32 *D_800B0BC8;
extern M2C_UNK D_800C4784;
extern M2C_UNK D_800C47AC;
extern M2C_UNK D_800C47C0;
extern M2C_UNK D_800C47CC;
extern M2C_UNK D_800C47D8;
extern M2C_UNK D_800C47E8;
extern M2C_UNK D_800C47FC;
extern M2C_UNK D_800C480C;
extern M2C_UNK D_800C4820;
extern M2C_UNK D_800C4824;
extern M2C_UNK D_800C4828;
extern M2C_UNK D_800C4840;
extern M2C_UNK D_800C4858;
extern M2C_UNK D_800C4868;
extern M2C_UNK D_800C487C;
extern M2C_UNK D_800C488C;
extern M2C_UNK D_800C489C;
extern M2C_UNK D_800C48C0;
extern M2C_UNK D_800C48D4;
extern M2C_UNK D_800C48E8;
extern M2C_UNK D_800C4904;
extern M2C_UNK D_800EC100;
extern M2C_UNK D_800EC180;
s32 func_8007AE20(void) {
    void *spC0;
    s32 spC4;
    s32 spC8;
    M2C_UNK sp30[0x60];
    ScreenBuffer sp90;
    M2C_UNK *var_a0;
    M2C_UNK *var_a0_2;
    M2C_UNK *var_a0_3;
    M2C_UNK *var_a0_4;
    M2C_UNK *var_a1;
    M2C_UNK *var_a1_2;
    M2C_UNK *var_a1_3;
    s16 temp_v0;
    s16 temp_v1_7;
    s32 temp_v1_4;
    GteOpcode *var_v1;
    register s32 temp_a2 asm("$6");
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s0_3;
    s32 temp_s0_4;
    s32 temp_s0_5;
    s32 temp_s0_6;
    s32 temp_s0_7;
    s32 temp_s0_8;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_v1_3;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a2;
    s32 var_fp;
    s32 var_fp_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
    register s32 shared_mask_first asm("$16");
    register s32 shared_mask_second asm("$17");
    s32 var_s1;
    register s32 var_s4 asm("$20");
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    u32 **var_s2_2;
    u32 **var_t1;
    u32 **var_v0_2;
    u32 *var_a3;
    u32 *var_s2;
    u32 *var_s3;
    u32 temp_t0;
    u32 temp_v1;
    u32 temp_v1_2;
    u32 var_v0;
    register u32 var_v0_3 asm("$2");
    void *temp_t1;
    void *var_s1_2;
    var_s4 = 0;
    spC8 = 0;
    func_8007E8E0();
    {
        func_80094178();
        __asm__ volatile (
            "srl $2,$2,2\n\t"
            "andi %0,$2,15"
            : "=r" (var_fp)
            :
            : "$2");
    }
    if ((u32) var_fp < 0xDU) {
        var_s2 = (u32 *) D_800B0B94[var_fp];
    } else {
        var_s2 = D_800B0BC8;
    }
    func_8007FA74(0);
    func_80088870(2);
    func_800940C4();
    func_8008BA24(&sp30, 0, 0, 0x200, 0xF0);
    func_8008BAD8(&sp90, 0, 0, 0x200, 0xF0);
    func_8007FF18(&sp30);
    func_8007FFD8(&sp90);
    func_80091D34();
    temp_t1 = *(void **)0x110;
    spC0 = temp_t1;
    var_a0 = &D_800EC180;
    func_8008AFB0(var_a0, &D_800C4784);
    func_80091D4C(0, 0x20, 0x20, 0xFFFFFF, 1, var_a0);
    temp_t1_2 = spC8 + 8;
    spC8 = temp_t1_2;
    spC4 = 0;
    func_8008AFB0(var_a0, &D_800C47AC, var_s2,
                  *(u32 **)((u8 *)temp_t1 + 0x88),
                  **(u32 **)((u8 *)temp_t1 + 0x88));
    var_fp = 0;
    func_80091D4C(0, 0x20, temp_t1_2 + 0x20, 0xFFFFFF, 1, var_a0);
    spC8 = temp_t1_2 + 0x14;
    {
        register u32 *record_pc asm("$3");
        record_pc = *(u32 **)((u8 *)temp_t1 + 0x88);
        var_s3 = record_pc - 0xB;
    }
    do {
        {
            register s32 address_mask asm("$3");
            register s32 masked_address asm("$2");
            __asm__ volatile (
                "lui %0,0xff00\n\t"
                "and %1,%2,%0"
                : "=r" (address_mask), "=r" (masked_address)
                : "r" (var_s3));
            if (masked_address == address_mask) {
                var_s3 = 0;
            }
        }
        temp_t0 = *var_s3;
        {
            register u32 high_bits asm("$2");
            __asm__ volatile ("lui %0,0xa000" : "=r" (high_bits));
            var_s4 |= high_bits;
        }
        __asm__ volatile ("srl %0,%1,26" : "=r" (temp_v1) : "r" (temp_t0));
        temp_a2 = temp_t0 & 0xFFFF;
        switch (temp_v1) {
        case 0x0:
            temp_v1_2 = temp_t0 & 0x3F;
            if (temp_t0 == 0) {
                func_8008AFB0(&D_800EC100, &D_800C47C0, var_s3, D_800B090C);
                __asm__ volatile ("");
            } else {
                switch (temp_v1_2) {
                case 8:
                    var_a1 = &D_800C47CC;
                    temp_s0 = (temp_t0 >> 0x15) & 0x1F;
                    func_8008AFB0(&D_800EC100, var_a1, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) (&D_800B0A14)[temp_s0]);
                    __asm__ volatile ("");
                    var_s4 |= 1 << temp_s0;
                    break;
                case 9:
                    {
                        register u32 **source_slot asm("$2");
                        register M2C_UNK *call_output asm("$4");
                        register M2C_UNK *case_format asm("$5");
                        __asm__ volatile (
                            "srl %0,%1,21\n\t"
                            "andi %0,%0,31"
                            : "=r" (temp_s2) : "r" (temp_t0));
                        source_slot = &(&D_800B0A14)[temp_s2];
                        call_output = &D_800EC100;
                        __asm__ volatile ("" : "+r" (source_slot),
                                              "+r" (call_output));
                        __asm__ volatile ("lui %0,0x800c"
                                          : "=r" (case_format));
                        temp_s0_2 = (temp_t0 >> 0xB) & 0x1F;
                        case_format += 0x47D8;
                        func_8008AFB0(call_output, case_format, var_s3,
                                      (&D_800B080C)[temp_t0 & 0x3F],
                                      (u32) *source_slot,
                                      (&D_800B0A14)[temp_s0_2]);
                        __asm__ volatile ("");
                    }
                    temp_s0_2 = 1 << temp_s0_2;
                    temp_s2 = 1 << temp_s2;
                    temp_s0_2 |= temp_s2;
                    var_s4 |= temp_s0_2;
                    break;
                case 32:
                case 33:
                case 34:
                case 35:
                case 36:
                case 37:
                case 38:
                case 39:
                case 42:
                case 43:
                {
                    register u32 **case32_first_slot asm("$2");
                    register M2C_UNK *case32_output asm("$4");
                    register M2C_UNK *case32_format asm("$5");
                    __asm__ volatile (
                        "srl %0,%1,11\n\t"
                        "andi %0,%0,31"
                        : "=r" (temp_s0_3) : "r" (temp_t0));
                    case32_first_slot = &(&D_800B0A14)[temp_s0_3];
                    __asm__ volatile ("" : "+r" (case32_first_slot));
                    __asm__ volatile (
                        "srl %0,%1,21\n\t"
                        "andi %0,%0,31"
                        : "=r" (var_s1) : "r" (temp_t0));
                    case32_output = &D_800EC100;
                    __asm__ volatile ("" : "+r" (case32_output));
                    __asm__ volatile ("lui %0,0x800c"
                                      : "=r" (case32_format));
                    __asm__ volatile (
                        "srl %0,%1,16\n\t"
                        "andi %0,%0,31"
                        : "=r" (temp_s2) : "r" (temp_t0));
                    case32_format += 0x47E8;
                    func_8008AFB0(case32_output, case32_format, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) *case32_first_slot, (&D_800B0A14)[var_s1], (s32) (&D_800B0A14)[temp_s2]);
                    __asm__ volatile ("");
                    temp_s0_3 = 1 << temp_s0_3;
                    var_s1 = 1 << var_s1;
                    temp_s0_3 |= var_s1;
                    temp_s2 = 1 << temp_s2;
                    temp_s0_3 |= temp_s2;
                    var_s4 |= temp_s0_3;
                    break;
                }
                case 24:
                case 25:
                case 26:
                case 27:
                {
                    register s32 case24_s1 asm("$17");
                    register u32 **case24_first_slot asm("$2");
                    register M2C_UNK *case24_output asm("$4");
                    register M2C_UNK *case24_format asm("$5");
                    __asm__ volatile (
                        "srl %0,%1,21\n\t"
                        "andi %0,%0,31"
                        : "=r" (temp_s0_3) : "r" (temp_t0));
                    case24_first_slot = &(&D_800B0A14)[temp_s0_3];
                    __asm__ volatile ("" : "+r" (case24_first_slot));
                    case24_output = &D_800EC100;
                    __asm__ volatile ("" : "+r" (case24_output));
                    __asm__ volatile ("lui %0,0x800c"
                                      : "=r" (case24_format));
                    __asm__ volatile (
                        "srl %0,%1,16\n\t"
                        "andi %0,%0,31"
                        : "=r" (case24_s1)
                        : "r" (temp_t0));
                    case24_format += 0x47D8;
                    func_8008AFB0(case24_output, case24_format, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) *case24_first_slot, (&D_800B0A14)[case24_s1]);
                    __asm__ volatile ("");
                    temp_s0_3 = 1 << temp_s0_3;
                    case24_s1 = 1 << case24_s1;
                    temp_s0_3 |= case24_s1;
                    var_s4 |= temp_s0_3;
                    break;
                }
                case 16:
                case 17:
                case 18:
                case 19:
                {
                    register M2C_UNK *case16_output asm("$4");
                    register M2C_UNK *case16_format asm("$5");
                    case16_output = &D_800EC100;
                    __asm__ volatile ("" : "+r" (case16_output));
                    __asm__ volatile ("lui %0,0x800c"
                                      : "=r" (case16_format));
                    temp_s0_5 = (temp_t0 >> 0xB) & 0x1F;
                    case16_format += 0x47CC;
                    func_8008AFB0(case16_output, case16_format, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) (&D_800B0A14)[temp_s0_5]);
                    __asm__ volatile ("");
                    var_s4 |= 1 << temp_s0_5;
                    break;
                }
                case 0:
                case 2:
                case 3:
                {
                    register u32 **case0_first_slot asm("$2");
                    register M2C_UNK *case0_output asm("$4");
                    register M2C_UNK *case0_format asm("$5");
                    __asm__ volatile (
                        "srl %0,%1,11\n\t"
                        "andi %0,%0,31"
                        : "=r" (shared_mask_first)
                        : "r" (temp_t0));
                    case0_first_slot = &(&D_800B0A14)[shared_mask_first];
                    __asm__ volatile ("" : "+r" (case0_first_slot));
                    __asm__ volatile (
                        "srl %0,%1,16\n\t"
                        "andi %0,%0,31"
                        : "=r" (shared_mask_second)
                        : "r" (temp_t0));
                    case0_output = &D_800EC100;
                    __asm__ volatile ("" : "+r" (case0_output));
                    __asm__ volatile ("lui %0,0x800c"
                                      : "=r" (case0_format));
                    case0_format += 0x47E8;
                    func_8008AFB0(case0_output, case0_format, var_s3,
                                  (&D_800B080C)[temp_t0 & 0x3F],
                                  (u32) *case0_first_slot,
                                  (&D_800B0A14)[shared_mask_second],
                                  (s32) (&D_800B0A14)[(temp_t0 >> 6) & 0x1F]);
                    goto shared_two_register_mask;
                }
                case 4:
                case 6:
                case 7:
                {
                    register u32 **case4_first_slot asm("$2");
                    register M2C_UNK *case4_output asm("$4");
                    register M2C_UNK *case4_format asm("$5");
                    temp_s0_6 = (temp_t0 >> 0xB) & 0x1F;
                    case4_first_slot = &(&D_800B0A14)[temp_s0_6];
                    __asm__ volatile ("" : "+r" (case4_first_slot));
                    __asm__ volatile (
                        "srl %0,%1,16\n\t"
                        "andi %0,%0,31"
                        : "=r" (var_s1) : "r" (temp_t0));
                    case4_output = &D_800EC100;
                    __asm__ volatile ("" : "+r" (case4_output));
                    __asm__ volatile ("lui %0,0x800c"
                                      : "=r" (case4_format));
                    temp_s2_2 = (temp_t0 >> 0x15) & 0x1F;
                    case4_format += 0x47E8;
                    func_8008AFB0(case4_output, case4_format, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) *case4_first_slot, (&D_800B0A14)[var_s1], (s32) (&D_800B0A14)[temp_s2_2]);
                    __asm__ volatile ("");
                    temp_s0_6 = 1 << temp_s0_6;
                    var_s1 = 1 << var_s1;
                    temp_s0_6 |= var_s1;
                    temp_s2_2 = 1 << temp_s2_2;
                    temp_s0_6 |= temp_s2_2;
                    var_s4 |= temp_s0_6;
                    break;
                }
                default:
                    func_8008AFB0(&D_800EC100, &D_800C47FC, var_s3, (u32 *) temp_t0);
                    break;
                }
            }
            break;
        case 0x1:
            {
                register s32 branch_scratch asm("$2");
                register u32 *branch_target asm("$3");
                register M2C_UNK *branch_output asm("$4");
                register M2C_UNK *branch_format asm("$5");
                u8 *branch_table_base;
                __asm__ volatile (
                    "sll %0,%2,16\n\t"
                    "li $9,16\n\t"
                    "srav %2,%0,$9\n\t"
                    "sll %0,%2,2\n\t"
                    "addiu %0,%0,4\n\t"
                    "addu %1,%0,%3"
                    : "=&r" (branch_scratch), "=&r" (branch_target),
                      "+r" (temp_a2)
                    : "r" (var_s3));
                branch_output = &D_800EC100;
                __asm__ volatile ("" : "+r" (branch_output));
                __asm__ volatile ("lui %0,0x800c"
                                  : "=r" (branch_format));
                temp_s0_7 = (temp_t0 >> 0x15) & 0x1F;
                branch_format += 0x480C;
                branch_table_base = (u8 *)&D_800B0804;
                func_8008AFB0(branch_output, branch_format, var_s3,
                              *(u32 *)(branch_table_base + ((temp_t0 >> 0xE) & 0x7C)),
                              (u32) (&D_800B0A14)[temp_s0_7], branch_target);
                __asm__ volatile ("");
            }
            var_s4 |= 1 << temp_s0_7;
            break;
        case 0xF:
        {
            register M2C_UNK *casef_output asm("$4");
            register M2C_UNK *casef_format asm("$5");
            casef_output = &D_800EC100;
            __asm__ volatile ("" : "+r" (casef_output));
            __asm__ volatile ("lui %0,0x800c"
                              : "=r" (casef_format));
            __asm__ volatile (
                "srl %0,%1,16\n\t"
                "andi %0,%0,31"
                : "=r" (shared_mask_first)
                : "r" (temp_t0));
            casef_format += 0x480C;
            func_8008AFB0(casef_output, casef_format, var_s3,
                          (&D_800B090C)[temp_t0 >> 0x1A],
                          (u32) (&D_800B0A14)[shared_mask_first],
                          (u32 *) temp_a2);
            goto shared_single_register_mask;
        }
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
        case 0x2E:
        {
            register s32 sign_scratch asm("$2");
            register u32 operand_value asm("$2");
            register M2C_UNK *case20_output asm("$4");
            __asm__ volatile (
                "sll %1,%0,16\n\t"
                "li $9,16\n\t"
                "srav %0,%1,$9"
                : "+r" (temp_a2), "=&r" (sign_scratch));
            if (temp_a2 < 0) {
                temp_a2 = -temp_a2;
                var_a1_2 = &D_800C4820;
            } else {
                var_a1_2 = &D_800C4824;
            }
            operand_value = (u32) (&D_800B0A14)[(temp_t0 >> 0x10) & 0x1F];
            __asm__ volatile ("addiu %0,$22,-16128" : "=r" (case20_output));
            func_8008AFB0(case20_output, &D_800C4828, var_s3,
                          (&D_800B090C)[temp_t0 >> 0x1A],
                          operand_value,
                          var_a1_2, temp_a2,
                          (&D_800B0A14)[(temp_t0 >> 21) & 31]);
            shared_mask_first = (temp_t0 >> 21) & 31;
            var_s4 |= 1 << shared_mask_first;
            break;
        }
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        {
            register s32 sign_scratch asm("$2");
            register u32 operand_value asm("$2");
            register u8 *operand_base asm("$3");
            register M2C_UNK *immediate_output asm("$4");
            __asm__ volatile (
                "sll %1,%0,16\n\t"
                "li $9,16\n\t"
                "srav %0,%1,$9"
                : "+r" (temp_a2), "=&r" (sign_scratch));
            if (temp_a2 < 0) {
                temp_a2 = -temp_a2;
                var_a1_2 = &D_800C4820;
            } else {
                var_a1_2 = &D_800C4824;
            }
            operand_base = (u8 *)&D_800B0A14 + 0x80;
            operand_value = *(u32 *)(operand_base + ((temp_t0 >> 14) & 0x7C));
            immediate_output = &D_800EC100;
            func_8008AFB0(immediate_output, &D_800C4828, var_s3,
                          (&D_800B090C)[temp_t0 >> 0x1A],
                          operand_value,
                          var_a1_2, temp_a2,
                          (&D_800B0A14)[(temp_t0 >> 21) & 31]);
            var_s0_4 = (temp_t0 >> 0x15) & 0x1F;
            var_s4 |= 1 << var_s0_4;
            break;
        }
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
        case 0xE:
        {
            register u32 **outer_first_slot asm("$2");
            register M2C_UNK *outer_output asm("$4");
            register M2C_UNK *outer_format asm("$5");
            __asm__ volatile (
                "srl %0,%1,16\n\t"
                "andi %0,%0,31"
                : "=r" (shared_mask_second)
                : "r" (temp_t0));
            outer_first_slot = &(&D_800B0A14)[shared_mask_second];
            __asm__ volatile ("" : "+r" (outer_first_slot));
            outer_output = &D_800EC100;
            __asm__ volatile ("" : "+r" (outer_output));
            __asm__ volatile ("lui %0,0x800c"
                              : "=r" (outer_format));
            __asm__ volatile (
                "srl %0,%1,21\n\t"
                "andi %0,%0,31"
                : "=r" (shared_mask_first)
                : "r" (temp_t0));
            outer_format += 0x4840;
            func_8008AFB0(outer_output, outer_format, var_s3,
                          (&D_800B090C)[temp_t0 >> 0x1A],
                          (u32) *outer_first_slot,
                          (&D_800B0A14)[shared_mask_first], temp_a2);
shared_two_register_mask:
            shared_mask_first = 1 << shared_mask_first;
            shared_mask_second = 1 << shared_mask_second;
            shared_mask_first |= shared_mask_second;
            var_s4 |= shared_mask_first;
            break;
        }
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
        {
            register s32 branch_scratch asm("$2");
            register u32 *branch_target asm("$3");
            register u32 **branch_first_slot asm("$2");
            register M2C_UNK *branch_output asm("$4");
            register M2C_UNK *branch_format asm("$5");
            __asm__ volatile (
                "sll %0,%2,16\n\t"
                "li $9,16\n\t"
                "srav %2,%0,$9\n\t"
                "sll %0,%2,2\n\t"
                "addiu %0,%0,4\n\t"
                "addu %1,%0,%3"
                : "=&r" (branch_scratch), "=&r" (branch_target),
                  "+r" (temp_a2)
                : "r" (var_s3));
            __asm__ volatile (
                "srl %0,%1,21\n\t"
                "andi %0,%0,31"
                : "=r" (shared_mask_first)
                : "r" (temp_t0));
            branch_first_slot = &(&D_800B0A14)[shared_mask_first];
            __asm__ volatile ("" : "+r" (branch_first_slot));
            branch_output = &D_800EC100;
            __asm__ volatile ("" : "+r" (branch_output));
            __asm__ volatile ("lui %0,0x800c"
                              : "=r" (branch_format));
            branch_format += 0x4840;
            func_8008AFB0(branch_output, branch_format, var_s3,
                          (&D_800B090C)[temp_t0 >> 0x1A],
                          (u32) *branch_first_slot,
                          (&D_800B0A14)[(temp_t0 >> 0x10) & 0x1F],
                          branch_target);
            var_s4 |= 1 << shared_mask_first;
            break;
        }
        case 0x2:
        case 0x3:
        {
            register u32 jump_mask asm("$2");
            register u32 jump_bits asm("$6");
            register u32 jump_shifted asm("$4");
            register u32 jump_address asm("$3");
            jump_mask = 0x03FFFFFF;
            jump_bits = temp_t0 & jump_mask;
            jump_shifted = jump_bits << 2;
            jump_mask = (u32) (var_s3 + 1);
            jump_address = 0xF0000000;
            jump_mask &= jump_address;
            __asm__ volatile ("addu %0,%1,%2"
                              : "=r" (jump_address)
                              : "r" (jump_shifted), "r" (jump_mask));
            func_8008AFB0(&D_800EC100, &D_800C4858, var_s3,
                          (&D_800B090C)[temp_t0 >> 0x1A],
                          jump_address);
            break;
        }
block_188:
            break;
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            __asm__ volatile ("srl %0,%1,21"
                              : "=r" (var_v0_3)
                              : "r" (temp_t0));
            temp_v1_3 = var_v0_3 & 0x1F;
            if (temp_v1_3 == 2) {
                goto gte_class_2;
            }
            if (temp_v1_3 < 3) {
                if (temp_v1_3 != 0) {
                    temp_v1_3 = temp_t0;
                    __asm__ volatile ("" : "+r" (temp_v1_3));
                    var_v0_3 = (u32) temp_v1_3 >> 0x19;
                    goto block_52;
                }
                goto gte_class_0;
            }
            if (temp_v1_3 == 4) {
                goto gte_class_4;
            }
            var_a0_2 = &D_800EC100;
            if (temp_v1_3 != 6) {
                temp_v1_3 = temp_t0;
                goto gte_default_shift;
            }
            goto gte_class_6;
gte_class_2:
            var_a0_2 = &D_800EC100;
            func_8008AFB0(var_a0_2, &D_800C4868, var_s3,
                          D_800B07C0[0].fields[1],
                          (temp_t0 >> 0x1A) & 3,
                          (&D_800B0A14)[(temp_t0 >> 11) & 31],
                          (&D_800B0A14)[0x40 + ((temp_t0 >> 16) & 0x1F)]);
            shared_mask_first = (temp_t0 >> 11) & 31;
shared_single_register_mask:
            shared_mask_first = 1 << shared_mask_first;
            var_s4 |= shared_mask_first;
            break;
gte_class_6:
            func_8008AFB0(var_a0_2, &D_800C4868, var_s3,
                          D_800B07C0[1].fields[1],
                          (temp_t0 >> 0x1A) & 3,
                          (&D_800B0A14)[(temp_t0 >> 16) & 31],
                          (&D_800B0A14)[0x40 + ((temp_t0 >> 11) & 0x1F)]);
            shared_mask_first = (temp_t0 >> 16) & 31;
            var_s4 |= 1 << shared_mask_first;
            break;
gte_class_0:
            __asm__ volatile ("");
            func_8008AFB0(&D_800EC100, &D_800C4868, var_s3,
                          D_800B07C0[0].name,
                          (temp_t0 >> 0x1A) & 3,
                          (&D_800B0A14)[(temp_t0 >> 16) & 31],
                          (&D_800B0A14)[0x20 + ((temp_t0 >> 11) & 0x1F)]);
            shared_mask_first = (temp_t0 >> 16) & 31;
            var_s4 |= 1 << shared_mask_first;
            break;
gte_class_4:
            func_8008AFB0(&D_800EC100, &D_800C4868, var_s3,
                          D_800B07C0[1].name,
                          (temp_t0 >> 0x1A) & 3,
                          (&D_800B0A14)[(temp_t0 >> 16) & 31],
                          (&D_800B0A14)[0x20 + ((temp_t0 >> 11) & 0x1F)]);
            shared_mask_first = (temp_t0 >> 16) & 31;
            var_s4 |= 1 << shared_mask_first;
            break;
            if (temp_v1_3 != 2) {
                if (temp_v1_3 < 3) {
                    if (temp_v1_3 != 0) {
                        var_v0_3 = temp_t0 >> 0x19;
                        goto block_52;
                    }
                    var_s0_4 = (temp_t0 >> 0x10) & 0x1F;
                    func_8008AFB0(&D_800EC100, &D_800C4868, var_s3,
                                  D_800B07C0[0].name,
                                  (temp_t0 >> 0x1A) & 3,
                                  (&D_800B0A14)[var_s0_4],
                                  (&D_800B0A14)[0x20 + ((temp_t0 >> 11) & 0x1F)]);
                    var_s4 |= 1 << var_s0_4;
                    break;
                }
                if (temp_v1_3 != 4) {
                    var_a0_2 = &D_800EC100;
                    if (temp_v1_3 != 6) {
gte_default_shift:
                        __asm__ volatile ("srl %0,%1,25"
                                          : "=r" (var_v0_3)
                                          : "r" (temp_v1_3));
block_52:
                        var_a2 = 0x16;
                        if (var_v0_3 & 1) {
                            {
                                register u32 first_opcode asm("$4");
                                __asm__ volatile ("andi %0,$3,0xffff"
                                                  : "=r" (first_opcode));
                                var_v1 = &D_800B0588[var_a2];
loop_index:
                                {
                                    register u32 first_loaded asm("$2");
                                    first_loaded = var_v1->opcode;
                                    if (first_opcode != first_loaded) {
                                    var_a2--;
                                    var_v1--;
                                    if (var_a2 >= 0) {
                                        goto loop_index;
                                    }
                                    }
                                }
                            }
                            temp_v1_4 = temp_t0 & 0xFFFF;
                            if (var_a2 < 0) {
                                var_a2 = 0;
                            }
                            if (temp_v1_4 != 0x107F) {
                                __asm__ volatile ("");
                                if (temp_v1_4 < 0x1080) {
                                    if (temp_v1_4 != 0xE7F) {
                                        if (temp_v1_4 < 0xE80) {
                                            if (temp_v1_4 != 0xBF) {
                                                if (temp_v1_4 < 0xC0) {
                                                    var_a0_3 = &D_800EC100;
                                                    if (temp_v1_4 != 0x7F) {
                                                    var_a2 = 0x2F;
                                                    goto late_search_setup;
                                                    }
                                                    var_a0_3 = &D_800EC100;
                                                    goto block_95;
                                                }
                                                var_a0_3 = &D_800EC100;
                                                if (temp_v1_4 == 0xDFF) {
                                                    goto block_95;
                                                }
                                                if (temp_v1_4 == 0xE3F) {
                                                    var_v0_3 = temp_t0 >> 0x1A;
                                                    goto block_97;
                                                }
                                                var_a2 = 0x2F;
                                                goto late_search_setup;
                                            }
                                            goto block_95;
                                        }
                                        var_a0_3 = &D_800EC100;
                                        if (temp_v1_4 == 0xFBF) {
                                            goto block_95;
                                        }
                                        if (temp_v1_4 < 0xFC0) {
                                            if ((temp_v1_4 == 0xEBF) || (temp_v1_4 == 0xF7F)) {
                                                var_v0_3 = temp_t0 >> 0x1A;
                                                goto block_97;
                                            }
                                            var_a2 = 0x2F;
                                            goto late_search_setup;
                                        }
                                        var_a0_3 = &D_800EC100;
                                        if (temp_v1_4 == 0xFFF) {
                                            goto block_95;
                                        }
                                        if (temp_v1_4 == 0x103F) {
                                                var_v0_3 = temp_t0 >> 0x1A;
                                                goto block_97;
                                        }
                                        var_a2 = 0x2F;
                                        goto late_search_setup;
                                    }
                                    goto block_95;
                                    goto block_188;
                                }
                                var_a0_3 = &D_800EC100;
                                if (temp_v1_4 != 0x11FF) {
                                    if (temp_v1_4 < 0x1200) {
                                        if (temp_v1_4 == 0x113F) {
                                            var_v0_3 = temp_t0 >> 0x1A;
                                            goto block_97;
                                        }
                                        if (temp_v1_4 < 0x1140) {
                                            if ((temp_v1_4 == 0x10BF) || (temp_v1_4 == 0x10FF)) {
                                                var_v0_3 = temp_t0 >> 0x1A;
                                                goto block_97;
                                            }
                                            var_a2 = 0x2F;
                                            goto late_search_setup;
                                        }
                                        var_a0_3 = &D_800EC100;
                                        if (temp_v1_4 == 0x117F) {
                                            goto block_95;
                                        }
                                        if (temp_v1_4 == 0x11BF) {
                                                var_v0_3 = temp_t0 >> 0x1A;
                                                goto block_97;
                                        }
                                        var_a2 = 0x2F;
                                        goto late_search_setup;
                                    }
                                    if (temp_v1_4 != 0x143F) {
                                        if (temp_v1_4 < 0x1440) {
                                            if (temp_v1_4 == 0x13BF) {
                                                goto block_183;
                                            }
                                            var_v0_3 = 0x13FF;
                                            __asm__ volatile ("");
                                            var_a0_4 = &D_800EC100;
                                            if (temp_v1_4 == var_v0_3) {
                                                goto block_185;
                                            }
                                            var_a2 = 0x2F;
                                            goto late_search_setup;
                                        } else {
                                            if (temp_v1_4 == 0x147F) {
                                                goto block_184;
                                            }
                                            var_v0_3 = 0x14BF;
                                            __asm__ volatile ("");
                                            var_a0_4 = &D_800EC100;
                                            if (temp_v1_4 == var_v0_3) {
                                                goto block_185_high;
                                            }
                                            var_a2 = 0x2F;
                                            goto late_search_setup;
                                                    {
                                                    register GteOpcode *late_base asm("$2");
                                                    register GteOpcode *late_ptr asm("$3");
                                                    register u32 late_opcode asm("$4");
                                                    u32 loaded_opcode;
                                                    __asm__ volatile ("" : "=r" (late_base), "=r" (late_ptr));
                                                    __asm__ volatile ("" : "+r" (var_a2));
                                                    if (var_a2 == 0x2F) {
                                                        goto late_search_setup;
                                                    }
                                                    var_a0_3 = &D_800EC100;
                                                    {
                                                        register GteOpcode *outer_base asm("$3");
                                                        register s32 outer_mode asm("$2");
                                                        register M2C_UNK *outer_output asm("$4");
                                                        register M2C_UNK *outer_format asm("$5");
block_95:
                                                        outer_output = &D_800EC100;
                                                        __asm__ volatile ("" : "+r" (outer_output));
block_96:
                                                        outer_mode = temp_t0 >> 0x1A;
block_97:
                                                        outer_mode &= 3;
                                                        __asm__ volatile ("lui %0,0x800c" : "=r" (outer_format));
                                                        outer_base = D_800B0588;
                                                        outer_format += 0x487C;
                                                        func_8008AFB0(outer_output, outer_format, var_s3,
                                                                      D_800B07C0[temp_t0 >> 0x1C].name,
                                                                      outer_mode,
                                                                      outer_base[var_a2].name);
                                                    }
                                                    goto block_188;
late_search_setup:
                                                    __asm__ volatile (
                                                        "lui $2,0x1ff\n\t"
                                                        "ori $2,$2,0xffff\n\t"
                                                        "and %0,$8,$2"
                                                        : "=r" (late_opcode)
                                                        :
                                                        : "$2");
                                                    __asm__ volatile (
                                                        "lui %0,0x800b\n\t"
                                                        "addiu %0,%0,1600\n\t"
                                                        "addiu %1,%0,376"
                                                        : "=r" (late_base), "=r" (late_ptr));
loop_99:
                                                    __asm__ volatile ("" : "+r" (late_ptr));
                                                    loaded_opcode = late_ptr->opcode;
                                                    if (late_opcode != loaded_opcode) {
                                                        var_a2 -= 1;
                                                        late_ptr -= 1;
                                                        if (var_a2 >= 0) {
                                                            goto loop_99;
                                                        }
                                                    }
                                                    if (var_a2 < 0) {
                                                        var_a2 = 0;
                                                    }
                                                    temp_v1_5 = temp_t0 & 0x01FFFFFF;
                                                    }
                                                    switch (temp_v1_5) {
                                                    case 0x486012:
                                                    case 0x48E012:
                                                    case 0x496012:
                                                    case 0x49E012:
                                                    case 0x41E012:
                                                    case 0x480012:
                                                    case 0x488012:
                                                    case 0x490012:
                                                    case 0x498012:
                                                    case 0x482012:
                                                    case 0x48A012:
                                                    case 0x492012:
                                                    case 0x49A012:
                                                    case 0x4A6412:
                                                    case 0x4A6012:
                                                    case 0x4AE012:
                                                    case 0x4B6012:
                                                    case 0x4BE012:
                                                    case 0x4A0012:
                                                    case 0x4A8012:
                                                    case 0x4B0012:
                                                    case 0x4B8012:
                                                    case 0x4A2012:
                                                    case 0x4AA012:
                                                    case 0x4B2012:
                                                    case 0x4BA012:
                                                    case 0x4DA412:
                                                    case 0x4C6012:
                                                    case 0x4CE012:
                                                    case 0x4D6012:
                                                    case 0x4DE012:
                                                    case 0x4C0012:
                                                    case 0x4C8012:
                                                    case 0x4D0012:
                                                    case 0x4D8012:
                                                    case 0x4C2012:
                                                    case 0x4CA012:
                                                    case 0x4D2012:
                                                    case 0x4DA012:
                                                    case 0xA80428:
                                                    case 0xA00428:
                                                    case 0x78000C:
                                                    case 0x70000C:
                                                    case 0x98003D:
                                                    case 0x90003D:
                                                    case 0xA8003E:
                                                    case 0xA0003E:
                                                        func_8008AFB0(&D_800EC100, &D_800C487C, var_s3,
                                                                      D_800B07C0[temp_t0 >> 0x1C].name,
                                                                      (temp_t0 >> 0x1A) & 3,
                                                                      D_800B0640[var_a2].name);
                                                        break;
                                                    default:
                                                        func_8008AFB0(&D_800EC100, &D_800C488C, var_s3,
                                                                      D_800B07C0[temp_t0 >> 0x1C].name,
                                                                      (temp_t0 >> 0x1A) & 3,
                                                                      temp_t0 & 0x01FFFFFF);
                                                        break;
                                                    }
                                                    goto block_188;
                                        }
                                    } else {
                                        goto block_184;
block_183:
                                        func_8008AFB0(&D_800EC100, &D_800C489C, var_s3, D_800B07C0[temp_t0 >> 0x1C].name, (temp_t0 >> 0x1A) & 3, D_800B0588[var_a2].name, (temp_t0 >> 0x18) & 1, (temp_t0 >> 0x16) & 3, (temp_t0 >> 0x14) & 3, (temp_t0 >> 0x12) & 3, (temp_t0 >> 0x11) & 1);
                                        goto block_188;
                                    }
                                } else {
                                    var_a0_3 = &D_800EC100;
                                    goto block_95;
block_184:
                                    var_a0_4 = &D_800EC100;
block_185_high:
                                    __asm__ volatile ("");
block_185:
                                    func_8008AFB0(var_a0_4, &D_800C48C0, var_s3, D_800B07C0[temp_t0 >> 0x1C].name, (temp_t0 >> 0x1A) & 3, D_800B0588[var_a2].name, (temp_t0 >> 0x18) & 1);
                                    break;
                                }
                            } else {
                                goto block_95;
                            }
                        } else {
                            func_8008AFB0(&D_800EC100, &D_800C48D4, var_s3,
                                          D_800B07C0[temp_t0 >> 0x1C].name,
                                          (temp_t0 >> 0x1A) & 3);
                            break;
                        }
                    } else {
                        var_s0_4 = (temp_t0 >> 0x10) & 0x1F;
                        func_8008AFB0(&D_800EC100, &D_800C4868, var_s3,
                                      D_800B07C0[1].fields[1],
                                      (temp_t0 >> 0x1A) & 3,
                                      (&D_800B0A14)[var_s0_4],
                                      (&D_800B0A14)[0x40 + ((temp_t0 >> 16) & 0x1F)]);
                        var_s4 |= 1 << var_s0_4;
                        break;
                    }
                } else {
                    var_s0_4 = (temp_t0 >> 0x10) & 0x1F;
                    func_8008AFB0(&D_800EC100, &D_800C4868, var_s3,
                                  D_800B07C0[1].name,
                                  (temp_t0 >> 0x1A) & 3,
                                  (&D_800B0A14)[var_s0_4],
                                  (&D_800B0A14)[0x20 + ((temp_t0 >> 11) & 0x1F)]);
                    var_s4 |= 1 << var_s0_4;
                    break;
                }
            } else {
                var_s0_4 = (temp_t0 >> 0xB) & 0x1F;
                func_8008AFB0(&D_800EC100, &D_800C4868, var_s3,
                              D_800B07C0[0].fields[1],
                              (temp_t0 >> 0x1A) & 3,
                              (&D_800B0A14)[var_s0_4],
                              (&D_800B0A14)[0x40 + ((temp_t0 >> 16) & 0x1F)]);
                var_s4 |= 1 << var_s0_4;
                break;
            }
            break;
        default:
            func_8008AFB0(&D_800EC100, &D_800C48E8, var_s3);
            break;
        }
        if (var_s3 == *(u32 **)((u8 *)spC0 + 0x88)) {
            register ScreenPrimitive *primitive asm("$4");
            register s32 primitive_size asm("$5");
            register s32 primitive_color asm("$6");
            __asm__ volatile (
                "lui %2,0xff\n\t"
                "ori %2,%2,0xffff\n\t"
                "addiu %0,$sp,168\n\t"
                "sll $3,%3,3\n\t"
                "addiu $2,$3,32\n\t"
                "li %1,512\n\t"
                "lw $9,200($sp)\n\t"
                "addiu $3,$3,40\n\t"
                "sh $0,176($sp)\n\t"
                "sh %1,180($sp)\n\t"
                "sh $0,184($sp)\n\t"
                "sh %1,188($sp)\n\t"
                "addu $2,$9,$2\n\t"
                "addu $3,$9,$3\n\t"
                "sh $2,178($sp)\n\t"
                "sh $2,182($sp)\n\t"
                "li $2,128\n\t"
                "sw $2,172($sp)\n\t"
                "li $2,5\n\t"
                "sh $3,186($sp)\n\t"
                "sh $3,190($sp)\n\t"
                "sb $2,171($sp)"
                : "=r" (primitive), "=r" (primitive_size),
                  "=r" (primitive_color)
                : "r" (var_fp)
                : "$2", "$3", "memory");
            sp90.layout.primitive.ac.parts.byte = 0x28;
            sp90.layout.primitive.a8.word |= primitive_color;
            func_8007FE4C(&primitive->a8.word, primitive_size, primitive_color);
        }
        {
            register s32 line_zero asm("$4");
            register s32 line_base asm("$5");
            register s32 line_y asm("$6");
            line_zero = 0;
            __asm__ volatile ("" : "+r" (line_zero));
            line_base = 0x20;
            line_y = var_fp * 8;
            line_y += line_base;
            line_y = spC8 + line_y;
            func_80091D4C(line_zero, line_base, line_y, 0xFFFFFF, 1, &D_800EC100);
        }
        var_s3 += 1;
        var_fp += 1;
    } while (++spC4 < 0x14);
    {
        register s32 final_index asm("$30");
        register s32 final_one asm("$21");
        register u32 **final_names asm("$18");
        register void *final_record asm("$17");
        register s32 final_y asm("$16");
        register M2C_UNK *final_output asm("$19");
        register void *final_address asm("$2");
        register M2C_UNK *final_call_output asm("$4");
        register M2C_UNK *final_format asm("$5");

        var_s4 &= ~1;
        final_index = 0;
        final_one = 1;
        __asm__ volatile ("lui %0,0x800f" : "=r" (final_address));
        final_output = (M2C_UNK *)final_address - 0x3F00;
        __asm__ volatile ("lui %0,0x800b" : "=r" (final_address));
        final_names = (u32 **)((u8 *)final_address + 0xA14);
        final_record = spC0;
        final_y = 0x20;
        do {
            if (var_s4 & (final_one << final_index)) {
                final_call_output = final_output;
                __asm__ volatile ("lui %0,0x800c"
                                  : "=r" (final_format));
                final_format += 0x4904;
                func_8008AFB0(final_call_output, final_format, *final_names,
                              *(void **)((u8 *)final_record + 8));
                func_80091D4C(0, 0x16A, spC8 + final_y, 0xFFFFFF,
                              final_one, final_output);
                final_y += 8;
            }
            final_names += 1;
            final_index += 1;
            final_record += 4;
        } while (final_index < 0x20);
    }
    return 0;
}
