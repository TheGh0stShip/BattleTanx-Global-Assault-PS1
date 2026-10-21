typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int M2C_UNK;
static __inline__ s32 gte_cfc2_0(void) { s32 value; __asm__ volatile("cfc2 %0,$0" : "=r" (value)); return value; }
static __inline__ s32 gte_cfc2_1(void) { s32 value; __asm__ volatile("cfc2 %0,$1" : "=r" (value)); return value; }
static __inline__ s32 gte_cfc2_2(void) { s32 value; __asm__ volatile("cfc2 %0,$2" : "=r" (value)); return value; }
static __inline__ s32 gte_cfc2_3(void) { s32 value; __asm__ volatile("cfc2 %0,$3" : "=r" (value)); return value; }
static __inline__ s32 gte_cfc2_4(void) { s32 value; __asm__ volatile("cfc2 %0,$4" : "=r" (value)); return value; }
static __inline__ s32 gte_cfc2_5(void) { s32 value; __asm__ volatile("cfc2 %0,$5" : "=r" (value)); return value; }
static __inline__ s32 gte_cfc2_6(void) { s32 value; __asm__ volatile("cfc2 %0,$6" : "=r" (value)); return value; }
static __inline__ s32 gte_cfc2_7(void) { s32 value; __asm__ volatile("cfc2 %0,$7" : "=r" (value)); return value; }
static __inline__ s32 gte_cfc2_31(void) { s32 value; __asm__ volatile("cfc2 %0,$31" : "=r" (value)); return value; }
static __inline__ void gte_store_flag(s32 *ptr) {
    register s32 value __asm__("$12");
    __asm__ volatile("cfc2 %0,$31" : "=r" (value));
    __asm__ volatile("nop");
    *ptr = value;
}
static __inline__ s32 gte_mfc2_9(void) { s32 value; __asm__ volatile("mfc2 %0,$9" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_10(void) { s32 value; __asm__ volatile("mfc2 %0,$10" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_11(void) { s32 value; __asm__ volatile("mfc2 %0,$11" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_14(void) { s32 value; __asm__ volatile("mfc2 %0,$14" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_25(void) { s32 value; __asm__ volatile("mfc2 %0,$25" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_26(void) { s32 value; __asm__ volatile("mfc2 %0,$26" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_27(void) { s32 value; __asm__ volatile("mfc2 %0,$27" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_31(void) { s32 value; __asm__ volatile("mfc2 %0,$31" : "=r" (value)); return value; }
static __inline__ s32 mult_hi(s32 left, s32 right) { s32 value; __asm__ volatile("mult %1,%2\n\tmfhi %0" : "=r" (value) : "r" (left), "r" (right)); return value; }
static __inline__ void gte_load_rotation5(const s32 *matrix) {
    register s32 t4 __asm__("$12") = matrix[0];
    register s32 t5 __asm__("$13") = matrix[1];
    __asm__ volatile("ctc2 %0,$0" : : "r" (t4));
    __asm__ volatile("ctc2 %0,$1" : : "r" (t5));
    t4 = matrix[2];
    t5 = matrix[3];
    {
        register s32 t6 __asm__("$14") = matrix[4];
        __asm__ volatile("ctc2 %0,$2" : : "r" (t4));
        __asm__ volatile("ctc2 %0,$3" : : "r" (t5));
        __asm__ volatile("ctc2 %0,$4" : : "r" (t6));
    }
}
static __inline__ void gte_load_diagonal3(const s32 *vector) {
    register s32 t4 __asm__("$12") = vector[0];
    register s32 t5 __asm__("$13") = vector[1];
    register s32 t6 __asm__("$14") = vector[2];
    __asm__ volatile("ctc2 %0,$0" : : "r" (t4));
    __asm__ volatile("ctc2 %0,$2" : : "r" (t5));
    __asm__ volatile("ctc2 %0,$4" : : "r" (t6));
}
static __inline__ void gte_load_transform8(const s32 *matrix) {
    gte_load_rotation5(matrix);
    {
        register s32 t4 __asm__("$12") = matrix[5];
        register s32 t5 __asm__("$13") = matrix[6];
        register s32 t6 __asm__("$14") = matrix[7];
        __asm__ volatile("ctc2 %0,$5" : : "r" (t4));
        __asm__ volatile("ctc2 %0,$6" : : "r" (t5));
        __asm__ volatile("ctc2 %0,$7" : : "r" (t6));
    }
}
static __inline__ void gte_load_transform8_advance(const s32 *matrix) {
    gte_load_rotation5(matrix);
    matrix += 5;
    __asm__ volatile("" : "+r" (matrix));
    {
        register s32 t4 __asm__("$12") = matrix[0];
        register s32 t5 __asm__("$13") = matrix[1];
        register s32 t6 __asm__("$14") = matrix[2];
        __asm__ volatile("ctc2 %0,$5" : : "r" (t4));
        __asm__ volatile("ctc2 %0,$6" : : "r" (t5));
        __asm__ volatile("ctc2 %0,$7" : : "r" (t6));
    }
}
static __inline__ void gte_store_transform8(s32 *matrix) {
    register s32 t4 __asm__("$12");
    register s32 t5 __asm__("$13");
    register s32 t6 __asm__("$14");
    __asm__ volatile("cfc2 %0,$0" : "=r" (t4));
    __asm__ volatile("cfc2 %0,$1" : "=r" (t5));
    matrix[0] = t4;
    matrix[1] = t5;
    __asm__ volatile("cfc2 %0,$2" : "=r" (t4));
    __asm__ volatile("cfc2 %0,$3" : "=r" (t5));
    __asm__ volatile("cfc2 %0,$4" : "=r" (t6));
    matrix[2] = t4;
    matrix[3] = t5;
    matrix[4] = t6;
    __asm__ volatile("cfc2 %0,$5" : "=r" (t4));
    __asm__ volatile("cfc2 %0,$6" : "=r" (t5));
    __asm__ volatile("cfc2 %0,$7" : "=r" (t6));
    matrix[5] = t4;
    matrix[6] = t5;
    matrix[7] = t6;
    __asm__ volatile("" : "+r" (matrix) : : "memory");
    matrix += 5;
    __asm__ volatile("cfc2 %0,$5" : "=r" (t4));
    __asm__ volatile("cfc2 %0,$6" : "=r" (t5));
    __asm__ volatile("cfc2 %0,$7" : "=r" (t6));
    matrix[0] = t4;
    matrix[1] = t5;
    matrix[2] = t6;
}
static __inline__ void gte_load_vector3(const u16 *vector) {
    register u32 t4 __asm__("$12") = vector[0];
    register u32 t5 __asm__("$13") = vector[3];
    register u32 t6 __asm__("$14") = vector[6];
    __asm__ volatile("mtc2 %0,$9" : : "r" (t4));
    __asm__ volatile("mtc2 %0,$10" : : "r" (t5));
    __asm__ volatile("mtc2 %0,$11" : : "r" (t6));
}
extern u16 D_800ADB78;
static __inline__ void gte_normalize3(
    const s32 *input, s32 *output, s32 scale_in_t8, s32 **output_slot) {
    register s32 x __asm__("$16") = input[0];
    register s32 y __asm__("$8") = input[1];
    register s32 z __asm__("$9") = input[2];
    register s32 part_x __asm__("$4");
    register s32 part_y __asm__("$2");
    register s32 part_z __asm__("$6");
    register s32 sum __asm__("$5");
    register s32 leading_raw __asm__("$3");
    register s32 leading __asm__("$2");
    register s32 shift __asm__("$6");
    register s32 table_index __asm__("$2");
    register s32 table_shift __asm__("$4");
    u32 scale;

    __asm__ volatile("mtc2 %0,$9" : : "r" (x));
    __asm__ volatile("mtc2 %0,$10" : : "r" (y));
    __asm__ volatile("mtc2 %0,$11" : : "r" (z));
    __asm__ volatile("nop\n\tnop\n\t.word 0x4AA00428");
    part_x = gte_mfc2_25();
    part_y = gte_mfc2_26();
    part_z = gte_mfc2_27();
    __asm__ volatile("add %0,%0,%1" : "+r" (part_x) : "r" (part_y));
    __asm__ volatile("add %0,%1,%2" : "=r" (sum) : "r" (part_x), "r" (part_z));
    __asm__ volatile("mtc2 %0,$30\n\tnop\n\tnop" : : "r" (sum));
    leading_raw = gte_mfc2_31();
    leading = leading_raw & ~1;
    shift = 31;
    __asm__ volatile("sub %0,%0,%1" : "+r" (shift) : "r" (leading));
    shift >>= 1;
    __asm__ volatile("" : "+r" (shift));
    __asm__ volatile("addi %0,%1,-24" : "=r" (table_shift) : "r" (leading));
    if (table_shift < 0) {
        table_shift = 24;
        __asm__ volatile("sub %0,%0,%1" : "+r" (table_shift) : "r" (leading));
        table_index = sum >> table_shift;
        __asm__ volatile("" : "+r" (table_index));
    } else {
        __asm__ volatile("nop");
        table_index = sum << table_shift;
    }
    table_index -= 64;
    table_index <<= 1;
    __asm__ volatile("" : "+r" (table_index));
    if (scale_in_t8) {
        register u16 *scale_base __asm__("$24");
        __asm__ volatile(
            "lui %0,0x800b\n\taddiu %0,%0,-9352"
            : "=r" (scale_base));
        table_index = table_index + (s32)scale_base;
        scale = *(u16 *)table_index;
    } else {
        register u16 *scale_base __asm__("$25");
        __asm__ volatile(
            "lui %0,0x800b\n\taddiu %0,%0,-9352"
            : "=r" (scale_base));
        table_index = table_index + (s32)scale_base;
        scale = *(u16 *)table_index;
    }
    __asm__ volatile("mtc2 %0,$8" : : "r" (scale));
    __asm__ volatile("mtc2 %0,$9" : : "r" (x));
    __asm__ volatile("mtc2 %0,$10" : : "r" (y));
    __asm__ volatile("mtc2 %0,$11" : : "r" (z));
    __asm__ volatile("nop\n\tnop\n\t.word 0x4B90003D");
    if (scale_in_t8) {
        register s32 *output_base __asm__("$25") = *output_slot;
        register s32 result_x __asm__("$16");
        register s32 result_y __asm__("$8");
        register s32 result_z __asm__("$9");
        __asm__ volatile("" : "+r" (output_base));
        result_x = gte_mfc2_25();
        result_y = gte_mfc2_26();
        __asm__ volatile("srav %0,%0,%1" : "+r" (result_x) : "r" (shift));
        result_z = gte_mfc2_27();
        output_base[0] = result_x;
        __asm__ volatile("srav %0,%0,%1" : "+r" (result_y) : "r" (shift));
        output_base[1] = result_y;
        __asm__ volatile("srav %0,%0,%1" : "+r" (result_z) : "r" (shift));
        output_base[2] = result_z;
    } else {
        register s32 *output_base __asm__("$2") = output;
        register s32 result_x __asm__("$16");
        register s32 result_y __asm__("$8");
        register s32 result_z __asm__("$9");
        __asm__ volatile("" : "+r" (output_base));
        result_x = gte_mfc2_25();
        result_y = gte_mfc2_26();
        __asm__ volatile("srav %0,%0,%1" : "+r" (result_x) : "r" (shift));
        result_z = gte_mfc2_27();
        output_base[0] = result_x;
        __asm__ volatile("srav %0,%0,%1" : "+r" (result_y) : "r" (shift));
        output_base[1] = result_y;
        __asm__ volatile("srav %0,%0,%1" : "+r" (result_z) : "r" (shift));
        output_base[2] = result_z;
    }
}
M2C_UNK func_80065710(M2C_UNK *, void *, s32 *);
s32 func_80068720(void *, void *, s32, M2C_UNK);
M2C_UNK func_800687CC(M2C_UNK *, M2C_UNK *, s16);
M2C_UNK func_80068888(M2C_UNK *, M2C_UNK *, s16);
M2C_UNK func_80068940(M2C_UNK *, M2C_UNK *, s16);
M2C_UNK func_80068AE4(M2C_UNK *, M2C_UNK *, s16);
s32 *func_80068EE8();
s32 func_8006A26C(M2C_UNK);
s32 func_8007F7D8();
s32 func_8008B984();
s16 func_800924F0();
s16 func_80092500();
extern u8 D_800AD9EC;
extern s32 D_800AD9F0;
extern u8 D_800ADA08;
extern u8 D_800ADB28;
extern u8 D_800ADB58;
extern u16 D_800ADB78;
extern u8 D_800D3034;
extern u8 D_800E5358;
extern u8 D_800E5368;
extern M2C_UNK *D_800E5374;
extern u8 D_800E5378;
extern u8 D_800E537C;
extern u8 D_800E5398;
extern u8 D_800E53AC;
extern s32 D_800E53B8;
extern M2C_UNK (*D_800E53BC)(M2C_UNK *, M2C_UNK *, s16);
extern u8 D_800E53C8;
extern s32 D_800E53E8;
extern s32 D_800E53EC;

static __inline__ void save_gte_control_snapshot(u8 *dst) {
    register u8 *snapshot_ptr __asm__("$2") = dst;
    __asm__ volatile(
        "cfc2 $12,$0\n" "cfc2 $13,$1\n"
        "sw $12,0(%0)\n" "sw $13,4(%0)\n"
        "cfc2 $12,$2\n" "cfc2 $13,$3\n" "cfc2 $14,$4\n"
        "sw $12,8(%0)\n" "sw $13,12(%0)\n" "sw $14,16(%0)\n"
        "cfc2 $12,$5\n" "cfc2 $13,$6\n" "cfc2 $14,$7\n"
        "sw $12,20(%0)\n" "sw $13,24(%0)\n" "sw $14,28(%0)\n"
        "addiu %0,%0,20\n"
        "cfc2 $12,$5\n" "cfc2 $13,$6\n" "cfc2 $14,$7\n"
        "sw $12,0(%0)\n" "sw $13,4(%0)\n" "sw $14,8(%0)\n"
        : "+r" (snapshot_ptr) : : "$12", "$13", "$14", "memory");
}

typedef struct {
    M2C_UNK sp10[4];
    s32 sp20;
    s32 sp24;
    s32 sp28;
    u8 pad2C[0xC];
    M2C_UNK sp38[8];
    s32 sp58;
    s32 sp5C;
    s32 sp60;
    s32 sp64;
    M2C_UNK sp68[8];
    s32 sp88[1];
    s32 sp8C;
    s32 sp90;
    u8 pad94[4];
    s16 sp98;
    s16 sp9A;
    u8 pad9C[4];
    s16 spA0;
    s16 spA2;
    u8 padA4[4];
    M2C_UNK spA8[4];
    M2C_UNK spB8[4];
    M2C_UNK spC8[4];
    s32 spD8;
    s32 spDC;
    s32 *spE0;
    s32 spE4;
    s32 spE8;
    u8 padEC[4];
    u16 spF0;
    u8 padF2[6];
    void *spF8;
    s32 spFC;
    s32 *sp100;
    s32 sp104;
    s32 sp108;
    void *sp10C;
    M2C_UNK *sp110;
} Func80065920Frame;

void func_80065920(void * volatile arg0, s32 arg1) {
    Func80065920Frame stack;
    u32 high_mask;
    register M2C_UNK *state_or_mask __asm__("$18");
    register u8 *call_globals __asm__("$23");
    register M2C_UNK (*var_v0_3)(M2C_UNK *, M2C_UNK *, s16) __asm__("$2");
    u8 *var_a0_5;
    u8 *var_a0_6;
    register u8 *var_a1 __asm__("$5");
    register u8 *var_a1_2 __asm__("$5");
    register M2C_UNK *var_t9 __asm__("$25");
    s16 temp_t0;
    s16 temp_t0_2;
    s16 temp_t0_3;
    s16 temp_t0_4;
    s16 temp_t0_5;
    s16 temp_v0_25;
    s16 temp_v0_26;
    s16 temp_v0_27;
    s16 temp_v0_28;
    s16 temp_v0_35;
    s16 temp_v0_36;
    s16 temp_v0_37;
    s16 temp_v0_38;
    s16 temp_v1_10;
    s16 temp_v1_12;
    s16 temp_v1_13;
    s16 temp_v1_23;
    s16 temp_v1_24;
    s16 temp_v1_25;
    s16 temp_v1_26;
    s16 temp_v1_9;
    s32 var_a2;
    s32 *temp_a0;
    s32 *temp_a0_2;
    register s32 *temp_a0_3 __asm__("$4");
    s32 *temp_a0_4;
    s32 *temp_a0_5;
    s32 *temp_a0_6;
    register s32 *temp_s0 __asm__("$16");
    register s32 *temp_s0_2 __asm__("$16");
    register s32 *temp_v0_33 __asm__("$18");
    s32 *temp_v0_39;
    register s32 *var_a0_4 __asm__("$4");
    s32 *var_a0_7;
    register s32 *var_s3 __asm__("$19");
    register s32 *var_v1 __asm__("$3");
    register s32 *var_v1_2 __asm__("$3");
    s32 *var_v1_3;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t1_4;
    s32 temp_t3;
    s32 temp_t3_3;
    register s32 temp_v0 __asm__("$2");
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_14;
    s32 temp_v0_17;
    s32 temp_v0_20;
    register s32 temp_v0_23 __asm__("$2");
    s32 temp_v0_29;
    register s32 temp_v0_2 __asm__("$2");
    register s32 temp_v0_30 __asm__("$2");
    s32 temp_v0_34;
    s32 temp_v0_40;
    register s32 temp_v0_5 __asm__("$2");
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1_11;
    s32 temp_v1_14;
    s32 temp_v1_15;
    s32 temp_v1_16;
    s32 temp_v1_17;
    s32 temp_v1_18;
    s32 temp_v1_19;
    register s32 temp_v1_20 __asm__("$3");
    register u8 *loop_globals __asm__("$3");
    register u8 *matrix_globals __asm__("$25");
    register u16 *index_t0 __asm__("$8");
    register u16 *index_t1 __asm__("$9");
    register u8 *matrix_globals_2 __asm__("$7");
    register M2C_UNK *matrix_call_a0 __asm__("$4");
    s32 temp_v1_21;
    s32 temp_v1_22;
    s32 temp_v1_27;
    s32 temp_v1_28;
    s32 temp_v1_29;
    register s32 temp_v1_2 __asm__("$3");
    s32 temp_v1_30;
    s32 temp_v1_3;
    s32 temp_v1_4;
    register s32 temp_v1_5 __asm__("$3");
    register s32 temp_v1_6 __asm__("$3");
    s32 temp_v1_7;
    register s32 temp_v1_8 __asm__("$3");
    register s32 var_a2_2 __asm__("$6");
    register s32 var_a2_3 __asm__("$6");
    register s32 var_a2_4 __asm__("$6");
    register s32 var_a2_5 __asm__("$6");
    s32 var_a2_6;
    s32 var_a2_7;
    s32 var_a2_8;
    register s32 var_fp __asm__("$30");
    register s32 var_fp_2 __asm__("$30");
    register s32 matrix_count __asm__("$19");
    register s32 allocation_kind __asm__("$4");
    register s32 var_s5 __asm__("$21");
    register s32 var_s5_2 __asm__("$21");
    register s32 var_s7 __asm__("$23");
    register s32 var_s7_2 __asm__("$23");
    register s32 var_t2 __asm__("$10");
    register s32 *second_normalized __asm__("$22");
    register s32 var_t2_2 __asm__("$10");
    register s32 var_v0 __asm__("$2");
    register s32 var_v0_4 __asm__("$2");
    register u8 *packet_coords __asm__("$2");
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    register s32 temp_s2 __asm__("$18");
    register s32 temp_s2_2 __asm__("$18");
    u32 temp_a3_2;
    register u8 *var_s0 __asm__("$16");
    u8 temp_v0_32;
    register s32 var_s4 __asm__("$20");
    register s32 var_s4_2 __asm__("$20");
    register s32 var_s4_3 __asm__("$20");
    register s32 var_s4_4 __asm__("$20");
    register void *temp_a3 __asm__("$7");
    register void *temp_t3_2 __asm__("$11");
    register void *temp_t8 __asm__("$24");
    void *temp_v0_12;
    void *temp_v0_13;
    void *temp_v0_15;
    void *temp_v0_16;
    void *temp_v0_18;
    void *temp_v0_19;
    void *temp_v0_21;
    void *temp_v0_22;
    register void *temp_v0_24 __asm__("$2");
    register void *temp_v0_31 __asm__("$2");
    register void *temp_v0_3 __asm__("$2");
    register void *temp_v0_4 __asm__("$2");
    register void *temp_v0_6 __asm__("$2");
    register void *temp_v0_7 __asm__("$2");
    register void *temp_v1 __asm__("$3");
    void *var_a0;
    void *var_a0_2;
    void *var_a0_3;
    void *var_a1_3;
    void *var_a1_4;
    register void *var_s0_2 __asm__("$16");
    register void *var_s0_3 __asm__("$16");
    register void *var_s1 __asm__("$17");
    register void *var_s1_2 __asm__("$17");
    register void *var_s1_3 __asm__("$17");
    register void *var_t3 __asm__("$11");
    matrix_count = 0;
    __asm__ volatile("" : "+r" (matrix_count));
    stack.spE0 = ((void *)0);
    stack.spE4 = 0;
    stack.spF0 = 0;
    stack.spF8 = ((void *)0);
    stack.spD8 = 0;
    temp_v0 = func_8007F7D8();
    allocation_kind = 4;
    __asm__ volatile("" : "+r" (allocation_kind));
    state_or_mask = &D_800AD9EC;
    (*(s32 *)((u8 *)(state_or_mask)+(8))) = temp_v0;
    temp_v0 = func_8006A26C(allocation_kind);
    {
        register u8 *initialization_globals __asm__("$3");
        register u8 *renderer_globals __asm__("$20");
        __asm__ volatile(
            "lui %0,%%hi(D_800E53EC)\n"
            "lui %1,%%hi(D_800E53E8)\n"
            "sw %2,%%lo(D_800E53EC)(%0)\n"
            "lui %0,%%hi(D_800E53B8)\n"
            "sw %2,%%lo(D_800E53E8)(%1)\n"
            "li %2,-10\n"
            "sw %2,%%lo(D_800E53B8)(%0)\n"
            : "=r" (initialization_globals), "=r" (renderer_globals), "+r" (temp_v0)
            :
            : "memory");
    }
    __asm__ volatile("" ::: "$20", "memory");
    __asm__ volatile("" ::: "memory");
    {
        register M2C_UNK *context __asm__("$7") = &D_800E53C8;
        register s32 identity __asm__("$22") = 0x1000;
        register s32 depth_scale __asm__("$24") = 0xA00;
        __asm__ volatile("" : "+r" (context), "+r" (identity), "+r" (depth_scale));
        __asm__ volatile(
            "move $25,%1\n"
            "addu $12,$0,%1\n"
            "andi $12,$12,0xffff\n"
            "addu $13,$0,%2\n"
            "andi $13,$13,0xffff\n"
            "addu $14,$0,$25\n"
            "sw $12,0(%0)\n"
            "sw $0,4(%0)\n"
            "sw $13,8(%0)\n"
            "sw $0,12(%0)\n"
            "sh $14,16(%0)\n"
            "sw $0,20(%0)\n"
            "sw $0,24(%0)\n"
            "sw $0,28(%0)\n"
            :
            : "r" (context), "r" (identity), "r" (depth_scale)
            : "$12", "$13", "$14", "$25", "memory");
    }
    {
        register M2C_UNK *local_matrix __asm__("$2") = &stack.sp38;
        register s32 local_identity __asm__("$12") = 0x1000;
        register u8 *table_base __asm__("$2");
        __asm__ volatile("" : "+r" (local_matrix), "+r" (local_identity));
        (*(s32 *)((u8 *)(local_matrix)+(0))) = local_identity;
        (*(s32 *)((u8 *)(local_matrix)+(4))) = 0;
        (*(s32 *)((u8 *)(local_matrix)+(8))) = local_identity;
        (*(s32 *)((u8 *)(local_matrix)+(0xC))) = 0;
        (*(s16 *)((u8 *)(local_matrix)+(0x10))) = local_identity;
        (*(s32 *)((u8 *)(local_matrix)+(0x14))) = 0;
        (*(s32 *)((u8 *)(local_matrix)+(0x18))) = 0;
        (*(s32 *)((u8 *)(local_matrix)+(0x1C))) = 0;
        __asm__ volatile("" ::: "$3", "memory");
        D_800E5374 = local_matrix;
        table_base = (u8 *)&D_800D3034;
        __asm__ volatile("" : "+r" (table_base));
        temp_v1 = (void *)(arg1 * 0x9C);
        __asm__ volatile("addu %0,%0,%1" : "+r" (temp_v1) : "r" (table_base));
    }
    stack.sp20 = (s32) (*(s32 *)((u8 *)(temp_v1)+(0xC))) >> 0xC;
    stack.sp24 = (s32) (*(s32 *)((u8 *)(temp_v1)+(0x10))) >> 0xC;
    __asm__ volatile(
        "lw $2,20(%0)\n"
        "nop\n"
        "sra $2,$2,12\n"
        "sw $2,40($sp)\n"
        "lui $7,%%hi(D_800E5398)\n"
        "addiu $7,$7,%%lo(D_800E5398)\n"
        "cfc2 $12,$0\n"
        "cfc2 $13,$1\n"
        "sw $12,0($7)\n"
        "sw $13,4($7)\n"
        "cfc2 $12,$2\n"
        "cfc2 $13,$3\n"
        "cfc2 $14,$4\n"
        "sw $12,8($7)\n"
        "sw $13,12($7)\n"
        "sw $14,16($7)\n"
        "cfc2 $12,$5\n"
        "cfc2 $13,$6\n"
        "cfc2 $14,$7\n"
        "sw $12,20($7)\n"
        "sw $13,24($7)\n"
        "sw $14,28($7)\n"
        "lui $22,%%hi(D_800E53AC)\n"
        "addiu $22,$22,%%lo(D_800E53AC)\n"
        "cfc2 $12,$5\n"
        "cfc2 $13,$6\n"
        "cfc2 $14,$7\n"
        "sw $12,0($22)\n"
        "sw $13,4($22)\n"
        "sw $14,8($22)"
        : : "r" (temp_v1) : "memory");
    stack.sp98 = func_800924F0();
    var_s5 = matrix_count;
    stack.sp9A = func_80092500();
    stack.spA0 = func_800924F0();
    stack.spA2 = func_80092500();
    __asm__ volatile("" ::: "memory");
    var_s1 = (*(void **)((u8 *)(state_or_mask)+(0)));
    if (var_s1 != (*(s32 *)((u8 *)(state_or_mask)+(4)))) {
        temp_t8 = &stack.spA8;
        call_globals = (u8 *)0x800E0000;
        __asm__ volatile("" : "+r" (call_globals));
        stack.sp110 = temp_t8;
        state_or_mask = (M2C_UNK *)0xFFFFFF;
        high_mask = 0xFF000000;
        var_v0 = var_s5 < 0x200;
loop_2:
        if (var_v0 != 0) {
            if ((u8) (*(u8 *)((u8 *)(var_s1)+(7))) < 0xECU) {
                func_80065710(&stack.sp10, var_s1 + 8, &stack.sp20);
            }
            temp_v0 = *(u8 *)((u8 *)(var_s1)+(1));
            temp_v1_2 = temp_v0 & 0xF0;
            if (temp_v1_2 == 0x10) {
                goto dispatch_10;
            }
            if (temp_v1_2 < 0x11) {
                goto dispatch_default;
            }
            if (temp_v1_2 == 0x20) {
                goto dispatch_20;
            }
            if (temp_v1_2 == 0x40) {
                goto dispatch_40;
            }
dispatch_default:
            var_v0_3 = func_80068940;
            goto dispatch_done;
dispatch_20:
            var_v0_3 = func_80068888;
            goto dispatch_done;
dispatch_10:
            var_v0_3 = func_800687CC;
            goto dispatch_done;
dispatch_40:
            var_v0_3 = func_80068AE4;
dispatch_done:
            *(M2C_UNK (**)(M2C_UNK *, M2C_UNK *, s16))
                (call_globals + 0x53BC) = var_v0_3;
            if ((*(u8 *)((u8 *)(var_s1)+(2))) == 0) {
                temp_v1_3 = (*(u8 *)((u8 *)(var_s1)+(7))) & 0xFC;
                if (temp_v1_3 == 0x40) goto opcode_40_50;
                if (temp_v1_3 < 0x41) {
                    if (temp_v1_3 == 0x2C) goto opcode_matrix_call;
                    if (temp_v1_3 < 0x2D) {
                        if (temp_v1_3 == 0x20) goto opcode_matrix_call;
                        if (temp_v1_3 < 0x21) {
                            if (temp_v1_3 == 0x10) goto opcode_zero_call;
                            goto block_106;
                        }
                        if (temp_v1_3 == 0x24) goto opcode_matrix_call;
                        if (temp_v1_3 == 0x28) goto opcode_matrix_call;
                        goto block_106;
                    }
                    if (temp_v1_3 == 0x34) goto opcode_matrix_call;
                    if (temp_v1_3 < 0x35) {
                        if (temp_v1_3 == 0x30) goto opcode_matrix_call;
                        goto block_106;
                    }
                    if (temp_v1_3 == 0x38) goto opcode_matrix_call;
                    if (temp_v1_3 == 0x3C) goto opcode_matrix_call;
                    goto block_106;
                }
                if (temp_v1_3 == 0xE8) goto opcode_e_group;
                if (temp_v1_3 < 0xE9) {
                    if (temp_v1_3 == 0xA4) goto opcode_e_group;
                    if (temp_v1_3 < 0xA5) {
                        if (temp_v1_3 == 0x50) goto opcode_40_50;
                        goto block_106;
                    }
                    if (temp_v1_3 == 0xB4) goto opcode_e_group;
                    if (temp_v1_3 == 0xE0) goto opcode_e_group;
                    goto block_106;
                }
                if (temp_v1_3 == 0xF4) goto opcode_f4;
                if (temp_v1_3 < 0xF5) {
                    if (temp_v1_3 == 0xEC) goto opcode_ec;
                    goto block_106;
                }
                if (temp_v1_3 == 0xF8) goto opcode_f8;
                goto block_106;
opcode_40_50:
                    temp_v0_2 = var_s5 << 5;
                    __asm__ volatile("" : "+r" (temp_v0_2));
                    matrix_globals = (u8 *)0x800E0000;
                    __asm__ volatile("" : "+r" (matrix_globals));
                    var_s5 += 1;
                    temp_v0_3 = temp_v0_2 + *(s32 *)(matrix_globals + 0x53E8);
                    __asm__ volatile("" : "+r" (temp_v0_3));
                    gte_store_transform8(temp_v0_3);
                    if (var_s5 >= 0x1FF) goto block_106;
                    __asm__ volatile("" ::: "memory");
                    matrix_call_a0 = &stack.sp68;
                    goto opcode_matrix_call;
opcode_zero_call:
                {
                    register u8 *call_a1 __asm__("$5");
                    register M2C_UNK (*call_v0)(M2C_UNK *, M2C_UNK *, s16)
                        __asm__("$2");
                    matrix_call_a0 = &stack.sp68;
                    call_a1 = (u8 *)0x800E0000;
                    __asm__ volatile("" : "+r" (call_a1));
                    call_a1 += 0x53C8;
                    __asm__ volatile("" : "+r" (call_a1));
                    call_v0 = *(M2C_UNK (* volatile *)(M2C_UNK *, M2C_UNK *, s16))
                        (call_globals + 0x53BC);
                    __asm__ volatile("" : "+r" (call_v0));
                    var_a2 = 0;
                    goto opcode_call_invoke;
opcode_matrix_call:
                    matrix_call_a0 = &stack.sp68;
                    call_a1 = (u8 *)0x800E0000;
                    __asm__ volatile("" : "+r" (call_a1));
                    var_a2 = (*(s16 *)((u8 *)(var_s1)+(0x16)));
                    call_v0 = *(M2C_UNK (* volatile *)(M2C_UNK *, M2C_UNK *, s16))
                        (call_globals + 0x53BC);
                    __asm__ volatile("" : "+r" (call_v0));
                    call_a1 += 0x53C8;
                    __asm__ volatile("" : "+r" (call_a1));
opcode_call_invoke:
                    call_v0(matrix_call_a0, (M2C_UNK *)call_a1, var_a2);
                }
opcode_e_group:
                    temp_v0_5 = var_s5 << 5;
                    __asm__ volatile("" : "+r" (temp_v0_5));
                    matrix_globals_2 = (u8 *)0x800E0000;
                    __asm__ volatile("" : "+r" (matrix_globals_2));
                    var_s5 += 1;
                    temp_v0_6 = temp_v0_5 + *(s32 *)(matrix_globals_2 + 0x53E8);
                    __asm__ volatile("" : "+r" (temp_v0_6));
                    gte_store_transform8(temp_v0_6);
                    __asm__ volatile("" ::: "memory");
                    {
                        register s32 *rotation_base __asm__("$22") =
                            (s32 *)&D_800E5398;
                        register s32 rotation_t4 __asm__("$12");
                        register s32 rotation_t5 __asm__("$13");
                        __asm__ volatile("" : "+r" (rotation_base));
                        rotation_t4 = rotation_base[0];
                        rotation_t5 = rotation_base[1];
                        __asm__ volatile("ctc2 %0,$0" : : "r" (rotation_t4));
                        __asm__ volatile("ctc2 %0,$1" : : "r" (rotation_t5));
                        rotation_t4 = rotation_base[2];
                        rotation_t5 = rotation_base[3];
                        {
                            register s32 rotation_t6 __asm__("$14") = rotation_base[4];
                            __asm__ volatile("ctc2 %0,$2" : : "r" (rotation_t4));
                            __asm__ volatile("ctc2 %0,$3" : : "r" (rotation_t5));
                            __asm__ volatile("ctc2 %0,$4" : : "r" (rotation_t6));
                        }
                    }
                    goto block_106;
opcode_ec:
                    (*(s32 *)((u8 *)(&D_800E5358)+(0))) = (s32) -(*(s16 *)((u8 *)(var_s1)+(8)));
                    (*(s32 *)((u8 *)(&D_800E5358)+(4))) = (s32) -(*(s16 *)((u8 *)(var_s1)+(0xA)));
                    (*(s32 *)((u8 *)(&D_800E5358)+(8))) = (s32) -(*(s16 *)((u8 *)(var_s1)+(0xC)));
                    __asm__ volatile("lui %0,0x800e" : "=r" (var_v1));
                    (*(s32 *)((u8 *)var_v1 + 0x5368)) =
                        (s32) (*(s16 *)((u8 *)(var_s1)+(0x10)));
                    var_v1 = (s32 *)((u8 *)var_v1 + 0x5368);
                    var_v1[1] = (s32) (*(s16 *)((u8 *)(var_s1)+(0x12)));
                    var_v1[2] = (s32) (*(s16 *)((u8 *)(var_s1)+(0x14)));
                    __asm__ volatile("" ::: "memory");
                    {
                        register u8 *matrix_high __asm__("$24") = (u8 *)0x800E0000;
                        __asm__ volatile("" : "+r" (matrix_high));
                        var_t2 = (s32)(matrix_high + 0x5378);
                        __asm__ volatile("" : "+r" (var_t2));
                    }
                    gte_normalize3(var_v1, (s32 *)&stack.spC8, 0, (s32 **)0);
                    {
                        register s32 *diagonal_base __asm__("$7") =
                            (s32 *)&D_800E5358;
                        register s32 diagonal_t4 __asm__("$12");
                        register s32 diagonal_t5 __asm__("$13");
                        register s32 diagonal_t6 __asm__("$14");
                        __asm__ volatile(
                            "lui %0,0x800e\n\taddiu %0,%0,0x5358"
                            : "=r" (diagonal_base));
                        diagonal_t4 = diagonal_base[0];
                        diagonal_t5 = diagonal_base[1];
                        __asm__ volatile("ctc2 %0,$0" : : "r" (diagonal_t4));
                        diagonal_t6 = diagonal_base[2];
                        __asm__ volatile("ctc2 %0,$2" : : "r" (diagonal_t5));
                        __asm__ volatile("ctc2 %0,$4" : : "r" (diagonal_t6));
                    }
                    __asm__ volatile("lwc2 $11, 0x8($v0)");
                    __asm__ volatile("lwc2 $9, ($v0)");
                    __asm__ volatile("lwc2 $10, 0x4($v0)");
                    __asm__ volatile("nop\n\tnop\n\t.word 0x4B78000C");
                    second_normalized = (s32 *)stack.sp110;
                    __asm__ volatile("" : "+r" (second_normalized));
                    __asm__ volatile("nop");
                    __asm__ volatile("swc2 $25, ($s6)");
                    __asm__ volatile("swc2 $26, 0x4($s6)");
                    __asm__ volatile("swc2 $27, 0x8($s6)");
                    gte_normalize3(
                        second_normalized, second_normalized, 1,
                        (s32 **)&stack.sp110);
                    {
                        register s32 *stack_diagonal __asm__("$3") =
                            (s32 *)&stack.spC8;
                        register s32 diagonal_t4 __asm__("$12");
                        register s32 diagonal_t5 __asm__("$13");
                        register s32 diagonal_t6 __asm__("$14");
                        __asm__ volatile("addiu %0,$sp,200" : "=r" (stack_diagonal));
                        diagonal_t4 = stack_diagonal[0];
                        diagonal_t5 = stack_diagonal[1];
                        __asm__ volatile("ctc2 %0,$0" : : "r" (diagonal_t4));
                        diagonal_t6 = stack_diagonal[2];
                        __asm__ volatile("ctc2 %0,$2" : : "r" (diagonal_t5));
                        __asm__ volatile("ctc2 %0,$4" : : "r" (diagonal_t6));
                    }
                    __asm__ volatile("lwc2 $11, 0x8($t9)");
                    __asm__ volatile("lwc2 $9, ($t9)");
                    __asm__ volatile("lwc2 $10, 0x4($t9)");
                    __asm__ volatile("nop\n\tnop\n\t.word 0x4B78000C");
                    {
                        register s32 *cross_output __asm__("$2") =
                            (s32 *)&stack.spB8;
                        __asm__ volatile("" : "+r" (cross_output));
                    }
                    __asm__ volatile("swc2 $25, ($v0)");
                    __asm__ volatile("swc2 $26, 0x4($v0)");
                    __asm__ volatile("swc2 $27, 0x8($v0)");
                    __asm__ volatile(
                        "lw $11,0($25)\n\t"
                        "lw $12,0($2)\n\t"
                        "lw $13,4($2)\n\t"
                        "lw $14,4($3)\n\t"
                        "lw $15,8($3)\n\t"
                        "andi $11,$11,0xffff\n\t"
                        "sll $12,$12,16\n\t"
                        "andi $13,$13,0xffff\n\t"
                        "sll $14,$14,16\n\t"
                        "or $12,$12,$11\n\t"
                        "or $14,$14,$13\n\t"
                        "sw $12,0($10)\n\t"
                        "sw $14,8($10)\n\t"
                        "sh $15,16($10)\n\t"
                        "lw $12,0($3)\n\t"
                        "lw $13,4($25)\n\t"
                        "lw $14,8($25)\n\t"
                        "lw $15,8($2)\n\t"
                        "sll $13,$13,16\n\t"
                        "andi $12,$12,0xffff\n\t"
                        "or $13,$13,$12\n\t"
                        "sll $15,$15,16\n\t"
                        "andi $14,$14,0xffff\n\t"
                        "or $15,$15,$14\n\t"
                        "sw $13,4($10)\n\t"
                        "sw $15,12($10)"
                        : : : "memory");
                    {
                        register s32 *rotation_base __asm__("$7");
                        register s32 rotation_t4 __asm__("$12");
                        register s32 rotation_t5 __asm__("$13");
                        register s32 rotation_t6 __asm__("$14");
                        __asm__ volatile(
                            "lui %0,0x800e\n\taddiu %0,%0,0x5398"
                            : "=r" (rotation_base));
                        rotation_t4 = rotation_base[0];
                        rotation_t5 = rotation_base[1];
                        __asm__ volatile("ctc2 %0,$0" : : "r" (rotation_t4));
                        __asm__ volatile("ctc2 %0,$1" : : "r" (rotation_t5));
                        rotation_t4 = rotation_base[2];
                        rotation_t5 = rotation_base[3];
                        rotation_t6 = rotation_base[4];
                        __asm__ volatile("ctc2 %0,$2" : : "r" (rotation_t4));
                        __asm__ volatile("ctc2 %0,$3" : : "r" (rotation_t5));
                        __asm__ volatile("ctc2 %0,$4" : : "r" (rotation_t6));
                    }
                    __asm__ volatile(
                        "lui $22,0x800e\n\t"
                        "addiu $22,$22,0x5378\n\t"
                        "lhu $12,0($22)\n\t"
                        "lhu $13,6($22)\n\t"
                        "lhu $14,12($22)\n\t"
                        "mtc2 $12,$9\n\t"
                        "mtc2 $13,$10\n\t"
                        "mtc2 $14,$11\n\t"
                        "nop\n\tnop\n\t.word 0x4A49E012\n\t"
                        "lui $24,0x800e\n\t"
                        "addiu $24,$24,0x5378\n\t"
                        "mfc2 $12,$9\n\t"
                        "mfc2 $13,$10\n\t"
                        "mfc2 $14,$11\n\t"
                        "sh $12,0($24)\n\t"
                        "sh $13,6($24)\n\t"
                        "sh $14,12($24)\n\t"
                        "lui $25,0x800e\n\t"
                        "addiu $25,$25,0x537a\n\t"
                        "lhu $12,0($25)\n\t"
                        "lhu $13,6($25)\n\t"
                        "lhu $14,12($25)\n\t"
                        "mtc2 $12,$9\n\t"
                        "mtc2 $13,$10\n\t"
                        "mtc2 $14,$11\n\t"
                        "nop\n\tnop\n\t.word 0x4A49E012\n\t"
                        "lui $7,0x800e\n\t"
                        "addiu $7,$7,0x537a\n\t"
                        "mfc2 $12,$9\n\t"
                        "mfc2 $13,$10\n\t"
                        "mfc2 $14,$11\n\t"
                        "sh $12,0($7)\n\t"
                        "sh $13,6($7)\n\t"
                        "sh $14,12($7)\n\t"
                        "lui $22,0x800e\n\t"
                        "addiu $22,$22,0x537c\n\t"
                        "lhu $12,0($22)\n\t"
                        "lhu $13,6($22)\n\t"
                        "lhu $14,12($22)\n\t"
                        "mtc2 $12,$9\n\t"
                        "mtc2 $13,$10\n\t"
                        "mtc2 $14,$11\n\t"
                        "nop\n\tnop\n\t.word 0x4A49E012\n\t"
                        "lui $24,0x800e\n\t"
                        "addiu $24,$24,0x537c\n\t"
                        "mfc2 $12,$9\n\t"
                        "mfc2 $13,$10\n\t"
                        "mfc2 $14,$11\n\t"
                        "sh $12,0($24)\n\t"
                        "sh $13,6($24)\n\t"
                        "sh $14,12($24)"
                        : : : "memory");
                    {
                        register u8 *matrix_result __asm__("$25");
                        register u8 *result_global_base __asm__("$2");
                        result_global_base = (u8 *)0x800E0000;
                        __asm__ volatile("" : "+r" (result_global_base));
                        matrix_result = (u8 *)0x800E0000;
                        __asm__ volatile("" : "+r" (matrix_result));
                        matrix_result += 0x5378;
                        __asm__ volatile("" : "+r" (matrix_result));
                        *(u8 **)(result_global_base + 0x5374) = matrix_result;
                    }
                    goto block_105;
opcode_f4:
                    __asm__ volatile(
                        "addiu $2,$17,8\n\t"
                        "lui $7,0x800e\n\taddiu $7,$7,0x5398\n\t"
                        "lw $12,0($7)\n\tlw $13,4($7)\n\t"
                        "ctc2 $12,$0\n\tctc2 $13,$1\n\t"
                        "lw $12,8($7)\n\tlw $13,12($7)\n\tlw $14,16($7)\n\t"
                        "ctc2 $12,$2\n\tctc2 $13,$3\n\tctc2 $14,$4\n\t"
                        "lhu $12,0($2)\n\tlhu $13,6($2)\n\tlhu $14,12($2)\n\t"
                        "mtc2 $12,$9\n\tmtc2 $13,$10\n\tmtc2 $14,$11\n\t"
                        "nop\n\tnop\n\t.word 0x4A49E012\n\t"
                        "lui $22,0x800e\n\taddiu $22,$22,0x5378\n\t"
                        "mfc2 $12,$9\n\tmfc2 $13,$10\n\tmfc2 $14,$11\n\t"
                        "sh $12,0($22)\n\tsh $13,6($22)\n\tsh $14,12($22)\n\t"
                        "addiu $2,$17,10\n\t"
                        "lhu $12,0($2)\n\tlhu $13,6($2)\n\tlhu $14,12($2)\n\t"
                        "mtc2 $12,$9\n\tmtc2 $13,$10\n\tmtc2 $14,$11\n\t"
                        "nop\n\tnop\n\t.word 0x4A49E012\n\t"
                        "lui $24,0x800e\n\taddiu $24,$24,0x537a\n\t"
                        "mfc2 $12,$9\n\tmfc2 $13,$10\n\tmfc2 $14,$11\n\t"
                        "sh $12,0($24)\n\tsh $13,6($24)\n\tsh $14,12($24)\n\t"
                        "addiu $2,$17,12\n\t"
                        "lhu $12,0($2)\n\tlhu $13,6($2)\n\tlhu $14,12($2)\n\t"
                        "mtc2 $12,$9\n\tmtc2 $13,$10\n\tmtc2 $14,$11\n\t"
                        "nop\n\tnop\n\t.word 0x4A49E012\n\t"
                        "lui $25,0x800e\n\taddiu $25,$25,0x537c\n\t"
                        "mfc2 $12,$9\n\tmfc2 $13,$10\n\tmfc2 $14,$11\n\t"
                        "sh $12,0($25)\n\tsh $13,6($25)\n\tsh $14,12($25)"
                        : : : "memory");
                    {
                        register u8 *matrix_result __asm__("$7");
                        register u8 *result_global_base __asm__("$2");
                        result_global_base = (u8 *)0x800E0000;
                        __asm__ volatile("" : "+r" (result_global_base));
                        matrix_result = (u8 *)0x800E0000;
                        __asm__ volatile("" : "+r" (matrix_result));
                        matrix_result += 0x5378;
                        __asm__ volatile("" : "+r" (matrix_result));
                        *(u8 **)(result_global_base + 0x5374) = matrix_result;
                    }
                    goto block_105;
opcode_f8:
                    temp_v1_4 = *(s32 *)((u8 *)var_s1 + 0xC);
                    if (temp_v1_4 & 0x11) {
                        *(s32 *)((u8 *)var_s1 + 0xC) = temp_v1_4 & ~0x10;
                        var_s3 = func_80068EE8(((*(u8 *)((u8 *)(var_s1)+(0))) - 4) * 4);
                        if (var_s3 == ((void *)0)) goto block_338;
                        {
                            second_normalized = (s32 *)((u8 *)var_s1 + 0x10);
                            stack.spE0 = second_normalized;
                            __asm__ volatile("" ::: "memory");
                            {
                                register s32 record_words __asm__("$2") =
                                    *(u8 *)var_s1;
                                __asm__ volatile("" : "+r" (record_words));
                                var_a2_2 = 4;
                                var_v1 = (s32 *)((u8 *)var_s3 + 0x10);
                                if (var_a2_2 < record_words) {
                                    var_a0 = var_s1 + 0x20;
                                    do {
                                        temp_v0_10 = (*(s32 *)((u8 *)(var_a0)+(-0x10)));
                                        var_a0 += 4;
                                        var_a2_2 += 1;
                                        (*(s32 *)((u8 *)(var_v1)+(-0x10))) = temp_v0_10;
                                        var_v1 = (s32 *)((u8 *)var_v1 + 4);
                                        record_words = *(u8 *)var_s1;
                                    } while (var_a2_2 < record_words);
                                }
                            }
                            temp_v1_5 = *(s32 *)((u8 *)var_s1 + 8);
                            stack.spD8 = temp_v1_5;
                            if (temp_v1_5 == -1) {
                                register u8 *context_t8 __asm__("$24") = arg0;
                                __asm__ volatile("" : "+r" (context_t8));
                                *var_s3 = (*var_s3 & high_mask) |
                                    (*(s32 *)(context_t8 + 4) & (u32)state_or_mask);
                                *(s32 *)(context_t8 + 4) =
                                    (*(s32 *)(context_t8 + 4) & high_mask) |
                                    ((s32)var_s3 & (u32)state_or_mask);
                                goto block_105;
                            }
                            __asm__ volatile(
                                ".set\tnoreorder\n\t"
                                "bgtz $3,1f\n\t"
                                "move $16,$0\n\t"
                                "j 2f\n\t"
                                "li $2,1\n"
                                "1:\n\t"
                                "slti $2,$3,0x1000\n\t"
                                "bnez $2,3f\n\t"
                                "li $2,0xfff\n"
                                "2:\n\t"
                                "sw $2,216($sp)\n\t"
                                "3:\n\t"
                                ".set\treorder"
                                : "=r" (var_s0), "=r" (var_v0_4)
                                : "r" (temp_v1_5) : "memory");
                            if ((*(u32 *)((u8 *)(var_s1)+(0xC))) & 0x20) {
                                var_s3 = func_80068EE8(0xC);
                                packet_coords = (u8 *)&stack.spA0;
                                if (var_s3 == ((void *)0)) goto block_338;
                                {
                                    __asm__ volatile(
                                        "lh $13,0($2)\n\t"
                                        "lh $14,2($2)\n\t"
                                        "li $12,2\n\t"
                                        "sb $12,3($16)\n\t"
                                        "lui $12,0xe500\n\t"
                                        "andi $13,$13,0x7ff\n\t"
                                        "andi $14,$14,0x7ff\n\t"
                                        "sll $14,$14,11\n\t"
                                        "or $12,$12,$14\n\t"
                                        "or $12,$12,$13\n\t"
                                        "sw $12,4($16)\n\t"
                                        "sw $0,8($16)"
                                        : : "r" (packet_coords), "r" (var_s0) : "memory");
                                    __asm__ volatile(
                                        "lw $4,216($sp)\n\t"
                                        "nop\n\t"
                                        "sll $4,$4,2\n\t"
                                        "lw $25,320($sp)\n\t"
                                        "lw $3,0($16)\n\t"
                                        "addu $4,$4,$25\n\t"
                                        "lw $2,0($4)\n\t"
                                        "and $3,$3,$30\n\t"
                                        "and $2,$2,$18\n\t"
                                        "or $3,$3,$2\n\t"
                                        "sw $3,0($16)\n\t"
                                        "lw $2,0($4)\n\t"
                                        "and $3,$16,$18\n\t"
                                        "and $2,$2,$30\n\t"
                                        "or $2,$2,$3\n\t"
                                        "sw $2,0($4)"
                                        : : "r" (var_s0), "r" (state_or_mask), "r" (var_fp)
                                        : "$2", "$3", "$4", "$25", "memory");
                                    goto block_76;
                                }
                            } else {
block_76:
                                __asm__ volatile(
                                    "lw $4,216($sp)\n\t"
                                    "lw $7,320($sp)\n\t"
                                    "lw $3,0($19)\n\t"
                                    "sll $4,$4,2\n\t"
                                    "addu $4,$4,$7\n\t"
                                    "lw $2,0($4)\n\t"
                                    "and $3,$3,$30\n\t"
                                    "and $2,$2,$18\n\t"
                                    "or $3,$3,$2\n\t"
                                    "sw $3,0($19)\n\t"
                                    "lw $2,0($4)\n\t"
                                    "and $3,$19,$18\n\t"
                                    "and $2,$2,$30\n\t"
                                    "or $2,$2,$3\n\t"
                                    "sw $2,0($4)"
                                    : : "r" (var_s3), "r" (state_or_mask), "r" (var_fp)
                                    : "$2", "$3", "$4", "$7", "memory");
                                if ((*(u32 *)((u8 *)(var_s1)+(0xC))) & 0x40) {
                                    var_s3 = func_80068EE8(0xC);
                                    packet_coords = (u8 *)&stack.sp98;
                                    if (var_s3 == ((void *)0)) goto block_338;
                                    {
                                        __asm__ volatile(
                                            "lh $13,0($2)\n\t"
                                            "lh $14,2($2)\n\t"
                                            "li $12,2\n\t"
                                            "sb $12,3($16)\n\t"
                                            "lui $12,0xe500\n\t"
                                            "andi $13,$13,0x7ff\n\t"
                                            "andi $14,$14,0x7ff\n\t"
                                            "sll $14,$14,11\n\t"
                                            "or $12,$12,$14\n\t"
                                            "or $12,$12,$13\n\t"
                                            "sw $12,4($16)\n\t"
                                            "sw $0,8($16)\n\t"
                                            "lw $4,216($sp)\n\t"
                                            "nop\n\t"
                                            "sll $4,$4,2\n\t"
                                            "lw $22,320($sp)\n\t"
                                            "lw $3,0($16)\n\t"
                                            "addu $4,$4,$22\n\t"
                                            "lw $2,0($4)\n\t"
                                            "and $3,$3,$30\n\t"
                                            "and $2,$2,$18\n\t"
                                            "or $3,$3,$2\n\t"
                                            "sw $3,0($16)\n\t"
                                            "lw $2,0($4)\n\t"
                                            "and $3,$16,$18\n\t"
                                            "and $2,$2,$30\n\t"
                                            "or $2,$2,$3"
                                            : "=r" (temp_a0_3), "=r" (temp_v0_5)
                                            : "r" (packet_coords), "r" (var_s0),
                                                "r" (state_or_mask), "r" (var_fp)
                                            : "$3", "$12", "$13", "$14", "memory");
                                        *temp_a0_3 = temp_v0_5;
                                        goto block_105;
                                    }
                                } else {
                                    goto block_106;
                                }
                            }
                        }
                    } else {
                        goto block_105;
                    }
                    goto block_106;
            } else {
                temp_v0 = *(u8 *)((u8 *)var_s1 + 7);
                temp_v1_6 = temp_v0 & 0xFC;
                if (temp_v1_6 == 0x3C) {
                    goto case_3c;
                }
                if (temp_v1_6 < 0x3D) {
                    if (temp_v1_6 == 0x2C) {
                        goto case_2c;
                    }
                    if (temp_v1_6 < 0x2D) {
                        if (temp_v1_6 == 0x28) {
                            goto case_28;
                        }
                        goto block_106;
                    }
                    if (temp_v1_6 == 0x38) {
                        goto case_38;
                    }
                    goto block_106;
                }
                if (temp_v1_6 == 0x50) {
                    goto case_50;
                }
                if (temp_v1_6 >= 0x51) {
                    goto block_105;
                }
                if (temp_v1_6 == 0x40) {
                    goto case_40;
                }
                goto block_106;
case_50:
                    var_s0 = var_s1 + 0x24;
                    goto block_93;
case_40:
                    var_s0 = var_s1 + 0x20;
block_93:
                    __asm__ volatile(
                        "sll $2,$21,5\n\t"
                        "lui $24,0x800e\n\t"
                        "lw $3,0x53e8($24)\n\t"
                        "addiu $21,$21,1\n\t"
                        "addu $2,$2,$3\n\t"
                        "cfc2 $12,$0\n\t"
                        "cfc2 $13,$1\n\t"
                        "sw $12,0($2)\n\t"
                        "sw $13,4($2)\n\t"
                        "cfc2 $12,$2\n\t"
                        "cfc2 $13,$3\n\t"
                        "cfc2 $14,$4\n\t"
                        "sw $12,8($2)\n\t"
                        "sw $13,12($2)\n\t"
                        "sw $14,16($2)\n\t"
                        "cfc2 $12,$5\n\t"
                        "cfc2 $13,$6\n\t"
                        "cfc2 $14,$7\n\t"
                        "sw $12,20($2)\n\t"
                        "sw $13,24($2)\n\t"
                        "sw $14,28($2)\n\t"
                        "addiu $2,$2,20\n\t"
                        "cfc2 $12,$5\n\t"
                        "cfc2 $13,$6\n\t"
                        "cfc2 $14,$7\n\t"
                        "sw $12,0($2)\n\t"
                        "sw $13,4($2)\n\t"
                        "sw $14,8($2)"
                        : "+r" (var_s5) : : "$2", "$3", "$12", "$13", "$14", "$24", "memory");
                    var_s4 = (*(u8 *)((u8 *)(var_s1)+(2)));
loop_94:
                    loop_globals = (u8 *)0x800B0000;
                    if ((s32)var_s4 <= 0) {
                        goto block_106;
                    }
                    __asm__ volatile("" ::: "memory");
                    if (var_s5 >= 0x200) {
                        goto block_106;
                    }
                    {
                        func_80065710(&stack.sp10, var_s0 + 8, &stack.sp20);
                        __asm__ volatile(
                            "sll $2,$21,5\n\t"
                            "lui $25,0x800e\n\t"
                            "lw $3,0x53e8($25)\n\t"
                            "addiu $21,$21,1\n\t"
                            "addu $2,$2,$3\n\t"
                            "cfc2 $12,$0\n\t"
                            "cfc2 $13,$1\n\t"
                            "sw $12,0($2)\n\t"
                            "sw $13,4($2)\n\t"
                            "cfc2 $12,$2\n\t"
                            "cfc2 $13,$3\n\t"
                            "cfc2 $14,$4\n\t"
                            "sw $12,8($2)\n\t"
                            "sw $13,12($2)\n\t"
                            "sw $14,16($2)\n\t"
                            "cfc2 $12,$5\n\t"
                            "cfc2 $13,$6\n\t"
                            "cfc2 $14,$7\n\t"
                            "sw $12,20($2)\n\t"
                            "sw $13,24($2)\n\t"
                            "sw $14,28($2)\n\t"
                            "addiu $2,$2,20\n\t"
                            "cfc2 $12,$5\n\t"
                            "cfc2 $13,$6\n\t"
                            "cfc2 $14,$7\n\t"
                            "sw $12,0($2)\n\t"
                            "sw $13,4($2)\n\t"
                            "sw $14,8($2)"
                            : "+r" (var_s5) : : "$2", "$3", "$12", "$13", "$14", "$25", "memory");
                        var_s0 += *var_s0 * 4;
                        __asm__ volatile("" : "+r" (var_s0) : : "memory");
                        var_s4 -= 1;
                        goto loop_94;
                    }
                    goto block_106;
case_3c:
                    var_s0_2 = var_s1 + 0x2C;
                    goto block_101;
case_2c:
                    var_s0_2 = var_s1 + 0x20;
                    goto block_101;
case_38:
                    var_s0_2 = var_s1 + 0x28;
                    goto block_101;
case_28:
                    var_s0_2 = var_s1 + 0x1C;
block_101:
                    __asm__ volatile(
                        ".set\tnoreorder\n\t"
                        "addiu $4,$sp,104\n\t"
                        "lui $5,0x800e\n\t"
                        "lh $6,22($17)\n\t"
                        "lw $2,0x53bc($23)\n\t"
                        "nop\n\t"
                        "jalr $2\n\t"
                        "addiu $5,$5,0x53c8\n\t"
                        ".set\treorder"
                        : : "r" (var_s1), "r" (call_globals)
                        : "$2", "$4", "$5", "$6", "$31", "memory");
                    __asm__ volatile(
                        "sll $2,$21,5\n\t"
                        "lui $7,0x800e\n\t"
                        "lw $3,0x53e8($7)\n\t"
                        "addiu $21,$21,1\n\t"
                        "addu $2,$2,$3\n\t"
                        "cfc2 $12,$0\n\t"
                        "cfc2 $13,$1\n\t"
                        "sw $12,0($2)\n\t"
                        "sw $13,4($2)\n\t"
                        "cfc2 $12,$2\n\t"
                        "cfc2 $13,$3\n\t"
                        "cfc2 $14,$4\n\t"
                        "sw $12,8($2)\n\t"
                        "sw $13,12($2)\n\t"
                        "sw $14,16($2)\n\t"
                        "cfc2 $12,$5\n\t"
                        "cfc2 $13,$6\n\t"
                        "cfc2 $14,$7\n\t"
                        "sw $12,20($2)\n\t"
                        "sw $13,24($2)\n\t"
                        "sw $14,28($2)\n\t"
                        "addiu $2,$2,20\n\t"
                        "cfc2 $12,$5\n\t"
                        "cfc2 $13,$6\n\t"
                        "cfc2 $14,$7\n\t"
                        "sw $12,0($2)\n\t"
                        "sw $13,4($2)\n\t"
                        "sw $14,8($2)\n\t"
                        "lui $22,0x800e\n\t"
                        "addiu $22,$22,0x5398\n\t"
                        "lw $12,0($22)\n\t"
                        "lw $13,4($22)\n\t"
                        "ctc2 $12,$0\n\t"
                        "ctc2 $13,$1\n\t"
                        "lw $12,8($22)\n\t"
                        "lw $13,12($22)\n\t"
                        "lw $14,16($22)\n\t"
                        "ctc2 $12,$2\n\t"
                        "ctc2 $13,$3\n\t"
                        "ctc2 $14,$4"
                        : "+r" (var_s5) :
                        : "$2", "$3", "$7", "$12", "$13", "$14", "$22", "memory");
                    var_s4_2 = (*(u8 *)((u8 *)(var_s1)+(2)));
                    if ((s32) var_s4_2 > 0) {
                        __asm__ volatile("" ::: "memory");
                        var_v0_5 = var_s5 < 0x200;
loop_103:
                        if (var_v0_5 != 0) {
                            func_80065710(&stack.sp10, var_s0_2 + 8, &stack.sp20);
                            __asm__ volatile(
                                ".set\tnoreorder\n\t"
                                "addiu $4,$sp,104\n\t"
                                "lui $5,0x800e\n\t"
                                "lh $6,22($16)\n\t"
                                "lw $2,0x53bc($23)\n\t"
                                "nop\n\t"
                                "jalr $2\n\t"
                                "addiu $5,$5,0x53c8\n\t"
                                ".set\treorder"
                                : : "r" (var_s0_2), "r" (call_globals)
                                : "$2", "$4", "$5", "$6", "$31", "memory");
                            __asm__ volatile(
                                "sll $2,$21,5\n\t"
                                "lui $24,0x800e\n\t"
                                "lw $3,0x53e8($24)\n\t"
                                "addiu $21,$21,1\n\t"
                                "addu $2,$2,$3\n\t"
                                "cfc2 $12,$0\n\t"
                                "cfc2 $13,$1\n\t"
                                "sw $12,0($2)\n\t"
                                "sw $13,4($2)\n\t"
                                "cfc2 $12,$2\n\t"
                                "cfc2 $13,$3\n\t"
                                "cfc2 $14,$4\n\t"
                                "sw $12,8($2)\n\t"
                                "sw $13,12($2)\n\t"
                                "sw $14,16($2)\n\t"
                                "cfc2 $12,$5\n\t"
                                "cfc2 $13,$6\n\t"
                                "cfc2 $14,$7\n\t"
                                "sw $12,20($2)\n\t"
                                "sw $13,24($2)\n\t"
                                "sw $14,28($2)\n\t"
                                "addiu $2,$2,20\n\t"
                                "cfc2 $12,$5\n\t"
                                "cfc2 $13,$6\n\t"
                                "cfc2 $14,$7\n\t"
                                "sw $12,0($2)\n\t"
                                "sw $13,4($2)\n\t"
                                "sw $14,8($2)\n\t"
                                "lbu $2,0($16)\n\t"
                                "nop\n\t"
                                "sll $2,$2,2\n\t"
                                "addu $16,$16,$2\n\t"
                                "lui $25,0x800e\n\t"
                                "addiu $25,$25,0x5398\n\t"
                                "lw $12,0($25)\n\t"
                                "lw $13,4($25)\n\t"
                                "ctc2 $12,$0\n\t"
                                "ctc2 $13,$1\n\t"
                                "lw $12,8($25)\n\t"
                                "lw $13,12($25)\n\t"
                                "lw $14,16($25)\n\t"
                                "ctc2 $12,$2\n\t"
                                "ctc2 $13,$3\n\t"
                                "ctc2 $14,$4"
                                : "+r" (var_s5), "+r" (var_s0_2) :
                                : "$2", "$3", "$12", "$13", "$14", "$24", "$25", "memory");
                            var_s4_2 -= 1;
                            var_v0_5 = var_s5 < 0x200;
                            if ((s32) var_s4_2 > 0) {
                                goto loop_103;
                            }
                        }
block_105:
                    }
                    goto block_106;
block_106:
                loop_globals = (u8 *)0x800B0000;
                __asm__ volatile("" : "+r" (loop_globals));
                __asm__ volatile(
                    "lbu $2,0($17)\n\t"
                    "lw $3,-0x2610($3)\n\t"
                    "sll $2,$2,2\n\t"
                    "addu $17,$17,$2"
                    : "+r" (var_s1), "+r" (loop_globals) : : "$2", "memory");
                var_v0 = var_s5 < 0x200;
                if (var_s1 == loop_globals) {
                    goto block_107;
                }
                goto loop_2;
            }
        } else {
            goto block_107;
        }
    } else {
block_107:
        stack.spFC = var_s5;
        var_s5_2 = 0;
        var_s1_2 = (*(void **)((u8 *)(&D_800AD9EC)+(0)));
        D_800E5374 = &stack.sp38;
        if (var_s1_2 != (*(s32 *)((u8 *)(&D_800AD9EC)+(4)))) {
            var_s4_3 = 0x800E0000;
            __asm__ volatile("" : "+r" (var_s4_3));
            temp_a3 = &stack.sp58;
            stack.sp100 = temp_a3;
            __asm__ volatile("" ::: "memory");
loop_109:
            second_normalized = (s32 *)stack.spFC;
            __asm__ volatile("" : "+r" (second_normalized));
            temp_v0 = var_s5_2 < (s32)second_normalized;
            __asm__ volatile("" : "+r" (temp_v0));
            if (temp_v0 != 0) {
                __asm__ volatile("" ::: "memory");
                temp_t8 = (void *)-4;
                if ((*(u8 *)((u8 *)(var_s1_2)+(2))) == 0) {
                    if ((u8) (*(u8 *)((u8 *)(var_s1_2)+(7))) < 0xECU) {
                        temp_v0_23 = ((*(u8 *)((u8 *)(var_s1_2)+(3))) + 1) * 4;
                        allocation_kind = temp_v0_23;
                        __asm__ volatile("" : "+r" (temp_v0_23), "+r" (allocation_kind));
                        stack.spE4 = temp_v0_23;
                        var_s3 = func_80068EE8(allocation_kind);
                        if (var_s3 != ((void *)0)) {
                            temp_v0 = *(u16 *)((u8 *)var_s1_2 + 0x14);
                            temp_s2 = temp_v0 & 0x60;
                            __asm__ volatile("" : "+r" (temp_s2));
                            temp_v0 = (*(u8 *)((u8 *)(var_s1_2)+(7))) & 4;
                            stack.spF0 = temp_s2;
                            if (temp_v0 != 0) {
                                temp_v0_24 = (*(void **)((u8 *)(var_s1_2)+(0x1C)));
                                temp_v1_8 = *(u16 *)temp_v0_24;
                                temp_v0 = *(u16 *)((u8 *)temp_v0_24 + 2);
                                stack.spE0 = var_s3;
                                temp_v1_8 &= 0xFF9F;
                                *(u16 *)((u8 *)var_s3 + 0xE) = temp_v0;
                                temp_v0 = *(u8 *)((u8 *)var_s1_2 + 3);
                                temp_s2 |= temp_v1_8;
                                stack.spF0 = temp_s2;
                                *(u8 *)((u8 *)var_s3 + 3) = temp_v0;
                                temp_t8 = *(void **)((u8 *)var_s1_2 + 0x1C);
                                stack.spF8 = temp_t8;
                                goto block_118;
                            }
                            temp_s0 = var_s3;
                            __asm__ volatile("" : "+r" (temp_s0));
                            stack.spE0 = var_s3;
                            __asm__ volatile("addiu $19,$19,8" : "+r" (var_s3));
                            __asm__ volatile(
                                "lw $25,228($sp)\n\t"
                                "li $4,8\n\t"
                                "addiu $25,$25,8"
                                : "=r" (matrix_globals), "=r" (allocation_kind));
                            stack.spE4 = (s32)matrix_globals;
                            if (func_80068EE8(allocation_kind) != ((void *)0)) {
                                temp_v1_8 = temp_s2 | 0xE1000200;
                                temp_v0 = *(u8 *)((u8 *)var_s1_2 + 3);
                                *(u8 *)((u8 *)var_s3 + 3) = temp_v0;
                                temp_v0 = 1;
                                *(u8 *)((u8 *)temp_s0 + 3) = temp_v0;
                                *(s32 *)((u8 *)temp_s0 + 4) = temp_v1_8;
                                __asm__ volatile(
                                    "lbu $10,3($16)\n\t"
                                    "lbu $11,3($19)\n\t"
                                    "nop\n\t"
                                    "addu $10,$11,$10\n\t"
                                    "addiu $11,$10,1\n\t"
                                    "slti $10,$11,11"
                                    : "=r" (var_t2), "=r" (temp_t3_2)
                                    : "r" (temp_s0), "r" (var_s3));
                                if (var_t2 != 0) {
                                    (*(u8 *)((u8 *)(temp_s0)+(3))) = (u8)(s32)temp_t3_2;
                                    (*(s32 *)((u8 *)(var_s3)+(0))) = 0;
                                }
block_118:
                                (*(s32 *)((u8 *)(var_s3)+(4))) = (s32) (*(s32 *)((u8 *)(var_s1_2)+(4)));
                                goto block_119;
                            }
                        }
                    } else {
block_119:
                        temp_v1_7 = (*(u8 *)((u8 *)(var_s1_2)+(1))) & 0xF0;
                        if (temp_v1_7 == 0x10) {
                            goto packet_mode_10;
                        }
                        var_t2 = 0;
                        if (temp_v1_7 < 0x11) {
                            goto packet_mode_default;
                        }
                        if (temp_v1_7 == 0x20) {
                            goto packet_mode_20;
                        }
                        var_fp = 2;
                        if (temp_v1_7 == 0x40) {
                            goto packet_mode_40;
                        }
packet_mode_default:
                        var_fp = 1;
                        var_s7 = 2;
                        goto packet_mode_done;
packet_mode_10:
                        var_t2 = 2;
                        var_fp = 0;
                        goto packet_mode_40;
packet_mode_20:
                        var_fp = 2;
packet_mode_40:
                        var_s7 = 1;
packet_mode_done:
                        __asm__ volatile(
                            "li $7,3\n\tlui $2,0x800b\n\taddiu $2,$2,-0x25f8\n\t"
                            "sw $zero,0xd8($sp)\n\tlbu $4,1($17)\n\tli $22,-4\n\t"
                            "sw $7,0x110($sp)\n\tlbu $3,7($17)\n\tandi $4,$4,0xf\n\t"
                            "sll $4,$4,5\n\taddu $11,$4,$2\n\tand $3,$3,$22\n\taddiu $3,$3,-0x10\n"
                            : "=r" (temp_a3), "=r" (temp_v0), "=r" (allocation_kind),
                              "=r" (second_normalized), "=r" (temp_t3_2), "=r" (temp_v1_8)
                            : : "memory"
                        );
                        switch (temp_v1_8) {
                        case 0x40:
                            temp_v0 = *(s32 *)((u8 *)var_s1_2 + 0x20);
                            temp_t8 = (void *)4;
                            stack.sp110 = temp_t8;
                            *(s32 *)((u8 *)var_s3 + 0xC) = temp_v0;
                        case 0x30:
                            packet_coords = (u8 *)*(s32 *)(var_s4_3 + 0x53E8);
                            __asm__ volatile("" : "+r" (packet_coords));
                            temp_v1_8 = var_s5_2 << 5;
                            packet_coords += temp_v1_8;
                            gte_load_transform8_advance((s32 *)packet_coords);
                            var_s5_2 += 1;
                            __asm__ volatile("mtc2 $zero, $0");
                            __asm__ volatile("mtc2 $zero, $1");
                            __asm__ volatile("nop\n\tnop\n\t.word 0x4A180001");
                            packet_coords = (u8 *)var_s3 + 8;
                            __asm__ volatile("" : "+r" (packet_coords));
                            __asm__ volatile("swc2 $14, ($v0)");
                            matrix_globals = (u8 *)stack.sp100;
                            __asm__ volatile("" : "+r" (matrix_globals));
                            __asm__ volatile("nop\n\tswc2 $19, ($t9)");
                            __asm__ volatile("" ::: "memory");
                            temp_v1_8 = var_s5_2 << 5;
                            packet_coords = (u8 *)*(s32 *)(var_s4_3 + 0x53E8);
                            __asm__ volatile("" : "+r" (packet_coords));
                            packet_coords += temp_v1_8;
                            gte_load_transform8_advance((s32 *)packet_coords);
                            var_s5_2 += 1;
                            packet_coords = (u8 *)var_s1_2 + 0x18;
                            __asm__ volatile("" : "+r" (packet_coords));
                            __asm__ volatile("lwc2 $0, ($v0)");
                            __asm__ volatile("lwc2 $1, 0x4($v0)");
                            __asm__ volatile("nop\n\tnop\n\t.word 0x4A180001");
                            temp_a3 = stack.sp110;
                            __asm__ volatile("" : "+r" (temp_a3));
                            packet_coords = (u8 *)var_s3 + ((s32)temp_a3 << 2);
                            __asm__ volatile("" : "+r" (packet_coords));
                            __asm__ volatile("swc2 $14, ($v0)");
                            packet_coords = (u8 *)&stack.sp5C;
                            __asm__ volatile("" : "+r" (packet_coords));
                            __asm__ volatile("swc2 $19, ($v0)");
                            goto block_150;
                        case 0x38:
                        case 0x3C:
                        case 0x48:
                        case 0x4C:
                            (*(void **)((u8 *)(var_s3)+(0x14))) = (void *)0x55555555;
                            break;
                        case 0x24:
                            (*(void **)((u8 *)(var_s3)+(0x10))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x20)));
                            (*(void **)((u8 *)(var_s3)+(0x1C))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x24)));
                            second_normalized = (s32 *)stack.spF8;
                            __asm__ volatile("" : "+r" (second_normalized));
                            temp_v0 = *(u16 *)((u8 *)second_normalized + 6);
                            *(u16 *)((u8 *)var_s3 + 0x18) = temp_v0;
                            temp_t8 = (void *)(u32)stack.spF0;
                            temp_v0 = *(u16 *)((u8 *)second_normalized + 8);
                            *(u16 *)((u8 *)var_s3 + 0x1A) = (u16)(u32)temp_t8;
                            *(u16 *)((u8 *)var_s3 + 0x24) = temp_v0;
                            goto block_135;
                        case 0x20:
                            (*(void **)((u8 *)(var_s3)+(0xC))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x1C)));
                            (*(void **)((u8 *)(var_s3)+(0x14))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x20)));
                            goto block_136;
                        case 0x14:
                            matrix_globals = (u8 *)stack.spF8;
                            __asm__ volatile("" : "+r" (matrix_globals));
                            temp_v0 = *(u16 *)(matrix_globals + 6);
                            *(u16 *)((u8 *)var_s3 + 0x14) = temp_v0;
                            temp_a3 = (void *)(u32)stack.spF0;
                            temp_v0 = *(u16 *)(matrix_globals + 8);
                            *(u16 *)((u8 *)var_s3 + 0x16) = (u16)(u32)temp_a3;
                            *(u16 *)((u8 *)var_s3 + 0x1C) = temp_v0;
block_135:
                            second_normalized = (s32 *)stack.spF8;
                            __asm__ volatile("" : "+r" (second_normalized));
                            temp_v0 = *(u16 *)((u8 *)second_normalized + 4);
                            *(u16 *)((u8 *)var_s3 + 0xC) = temp_v0;
                        case 0x10:
block_136:
                            var_a2_3 = 0;
                            __asm__ volatile(
                                "sll $2,$10,2\n\t"
                                "addiu $3,$sp,136\n\t"
                                "addu $9,$3,$2\n\t"
                                "sll $2,$30,2\n\t"
                                "addu $8,$3,$2\n\t"
                                "sll $2,$23,2\n\t"
                                "addu $16,$3,$2"
                                : "=r" (index_t1), "=r" (index_t0), "=r" (temp_s0)
                                : "r" (var_t2), "r" (var_fp), "r" (var_s7));
                            var_a1 = &D_800ADB58;
                            temp_a0_3 = temp_t3_2;
                            __asm__ volatile(
                                "1:\n\t"
                                "lh $3,0($4)\n\t"
                                "lh $2,24($17)\n\t"
                                "nop\n\t"
                                "mult $3,$2\n\t"
                                "mflo $25\n\t"
                                "mfhi $24\n\t"
                                "sll $24,$24,20\n\t"
                                "srl $25,$25,12\n\t"
                                "addu $2,$24,$zero\n\t"
                                "addu $3,$25,$zero\n\t"
                                "or $2,$2,$3\n\t"
                                "sw $2,136($sp)\n\t"
                                "lh $3,2($4)\n\t"
                                "lh $2,26($17)\n\t"
                                "nop\n\t"
                                "mult $3,$2\n\t"
                                "mflo $22\n\t"
                                "mfhi $7\n\t"
                                "sll $7,$7,20\n\t"
                                "srl $22,$22,12\n\t"
                                "addu $2,$7,$zero\n\t"
                                "addu $3,$22,$zero\n\t"
                                "or $2,$2,$3\n\t"
                                "sw $2,140($sp)\n\t"
                                "lh $2,4($4)\n\t"
                                "nop\n\t"
                                "sw $2,144($sp)\n\t"
                                "lhu $2,0($9)\n\t"
                                "nop\n\t"
                                "sh $2,0($5)\n\t"
                                "lhu $2,0($8)\n\t"
                                "nop\n\t"
                                "sh $2,2($5)\n\t"
                                "lhu $2,0($16)\n\t"
                                "nop\n\t"
                                "sh $2,4($5)\n\t"
                                "addiu $5,$5,8\n\t"
                                "addiu $6,$6,1\n\t"
                                "slti $2,$6,3\n\t"
                                "bnez $2,1b\n\t"
                                "addiu $4,$4,8"
                                : "+r" (temp_a0_3), "+r" (var_a1), "+r" (var_a2_3)
                                : "r" (index_t1), "r" (index_t0), "r" (temp_s0), "r" (var_s1_2)
                                : "$2", "$3", "$7", "$22", "$24", "$25", "memory");
                            packet_coords = (u8 *)*(s32 *)(var_s4_3 + 0x53E8);
                            __asm__ volatile("" : "+r" (packet_coords));
                            temp_v1_8 = var_s5_2 << 5;
                            packet_coords += temp_v1_8;
                            gte_load_transform8_advance((s32 *)packet_coords);
                            var_s5_2 += 1;
                            __asm__ volatile(
                                "lui $24,0x800b\n\taddiu $24,$24,-9384"
                                : "=r" (temp_t8));
                            __asm__ volatile("lwc2 $0, ($t8)");
                            __asm__ volatile("lwc2 $1, 0x4($t8)");
                            __asm__ volatile("lwc2 $2, 0x8($t8)");
                            __asm__ volatile("lwc2 $3, 0xc($t8)");
                            __asm__ volatile("lwc2 $4, 0x10($t8)");
                            __asm__ volatile("lwc2 $5, 0x14($t8)");
                            __asm__ volatile("nop\n\tnop\n\t.word 0x4A280030");
                            __asm__ volatile("swc2 $12, 0x8($s3)");
                            temp_v0 = *(u8 *)((u8 *)var_s1_2 + 7);
                            __asm__ volatile("li $25,-4" : "=r" (matrix_globals));
                            temp_v1_11 = temp_v0 & (s32)matrix_globals;
                            switch (temp_v1_11) {
                            case 0x20:
                                __asm__ volatile("swc2 $13, 0xc($s3)");
                                __asm__ volatile("swc2 $14, 0x10($s3)");
                                break;
                            case 0x30:
                                __asm__ volatile("swc2 $13, 0x10($s3)");
                                __asm__ volatile("swc2 $14, 0x18($s3)");
                                break;
                            case 0x24:
                                __asm__ volatile("swc2 $13, 0x10($s3)");
                                __asm__ volatile("swc2 $14, 0x18($s3)");
                                break;
                            case 0x34:
                                __asm__ volatile("swc2 $13, 0x14($s3)");
                                __asm__ volatile("swc2 $14, 0x20($s3)");
                                break;
                            }
                            temp_a3 = stack.sp100;
                            __asm__ volatile("" : "+r" (temp_a3));
                            __asm__ volatile("nop");
                            __asm__ volatile("swc2 $17, ($a3)");
                            __asm__ volatile("swc2 $18, 0x4($a3)");
                            __asm__ volatile("swc2 $19, 0x8($a3)");
block_150:
                            stack.spD8 = (s32) (stack.sp58 + stack.sp5C) >> 1;
                            break;
                        case 0x28:
                            (*(void **)((u8 *)(var_s3)+(0xC))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x1C)));
                            (*(void **)((u8 *)(var_s3)+(0x14))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x20)));
                            (*(void **)((u8 *)(var_s3)+(0x1C))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x24)));
                            goto block_155;
                        case 0x2C:
                            (*(void **)((u8 *)(var_s3)+(0x10))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x20)));
                            (*(void **)((u8 *)(var_s3)+(0x1C))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x24)));
                            (*(void **)((u8 *)(var_s3)+(0x28))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x28)));
                            second_normalized = (s32 *)stack.spF8;
                            __asm__ volatile("" : "+r" (second_normalized));
                            temp_v0 = *(u16 *)((u8 *)second_normalized + 6);
                            *(u16 *)((u8 *)var_s3 + 0x18) = temp_v0;
                            temp_v0 = *(u16 *)((u8 *)second_normalized + 8);
                            *(u16 *)((u8 *)var_s3 + 0x24) = temp_v0;
                            temp_t8 = (void *)(u32)stack.spF0;
                            temp_v0 = *(u16 *)((u8 *)second_normalized + 0xA);
                            *(u16 *)((u8 *)var_s3 + 0x1A) = (u16)(u32)temp_t8;
                            *(u16 *)((u8 *)var_s3 + 0x30) = temp_v0;
                            goto block_154;
                        case 0x1C:
                            matrix_globals = (u8 *)stack.spF8;
                            __asm__ volatile("" : "+r" (matrix_globals));
                            temp_v0 = *(u16 *)(matrix_globals + 6);
                            *(u16 *)((u8 *)var_s3 + 0x14) = temp_v0;
                            temp_v0 = *(u16 *)(matrix_globals + 8);
                            *(u16 *)((u8 *)var_s3 + 0x1C) = temp_v0;
                            temp_a3 = (void *)(u32)stack.spF0;
                            temp_v0 = *(u16 *)(matrix_globals + 0xA);
                            *(u16 *)((u8 *)var_s3 + 0x16) = (u16)(u32)temp_a3;
                            *(u16 *)((u8 *)var_s3 + 0x24) = temp_v0;
block_154:
                            second_normalized = (s32 *)stack.spF8;
                            __asm__ volatile("" : "+r" (second_normalized));
                            temp_v0 = *(u16 *)((u8 *)second_normalized + 4);
                            *(u16 *)((u8 *)var_s3 + 0xC) = temp_v0;
                        case 0x18:
block_155:
                            var_a2_4 = 0;
                            __asm__ volatile(
                                "sll $2,$10,2\n\t"
                                "addiu $3,$sp,136\n\t"
                                "addu $9,$3,$2\n\t"
                                "sll $2,$30,2\n\t"
                                "addu $8,$3,$2\n\t"
                                "sll $2,$23,2\n\t"
                                "addu $16,$3,$2"
                                : "=r" (index_t1), "=r" (index_t0), "=r" (temp_s0)
                                : "r" (var_t2), "r" (var_fp), "r" (var_s7));
                            var_a1_2 = &D_800ADB58;
                            __asm__ volatile("addu $4,$11,$zero" : "=r" (var_a0_3) : "r" (temp_t3_2));
                            __asm__ volatile(
                                "1:\n\t"
                                "lh $3,0($4)\n\t"
                                "lh $2,24($17)\n\t"
                                "nop\n\t"
                                "mult $3,$2\n\t"
                                "mflo $25\n\t"
                                "mfhi $24\n\t"
                                "sll $24,$24,20\n\t"
                                "srl $25,$25,12\n\t"
                                "addu $2,$24,$zero\n\t"
                                "addu $3,$25,$zero\n\t"
                                "or $2,$2,$3\n\t"
                                "sw $2,136($sp)\n\t"
                                "lh $3,2($4)\n\t"
                                "lh $2,26($17)\n\t"
                                "nop\n\t"
                                "mult $3,$2\n\t"
                                "mflo $22\n\t"
                                "mfhi $7\n\t"
                                "sll $7,$7,20\n\t"
                                "srl $22,$22,12\n\t"
                                "addu $2,$7,$zero\n\t"
                                "addu $3,$22,$zero\n\t"
                                "or $2,$2,$3\n\t"
                                "sw $2,140($sp)\n\t"
                                "lh $2,4($4)\n\t"
                                "nop\n\t"
                                "sw $2,144($sp)\n\t"
                                "lhu $2,0($9)\n\t"
                                "nop\n\t"
                                "sh $2,0($5)\n\t"
                                "lhu $2,0($8)\n\t"
                                "nop\n\t"
                                "sh $2,2($5)\n\t"
                                "lhu $2,0($16)\n\t"
                                "nop\n\t"
                                "sh $2,4($5)\n\t"
                                "addiu $5,$5,8\n\t"
                                "addiu $6,$6,1\n\t"
                                "slti $2,$6,4\n\t"
                                "bnez $2,1b\n\t"
                                "addiu $4,$4,8"
                                : "+r" (var_a0_3), "+r" (var_a1_2), "+r" (var_a2_4)
                                : "r" (index_t1), "r" (index_t0), "r" (temp_s0), "r" (var_s1_2)
                                : "$2", "$3", "$7", "$22", "$24", "$25", "memory");
                            packet_coords = (u8 *)*(s32 *)(var_s4_3 + 0x53E8);
                            __asm__ volatile("" : "+r" (packet_coords));
                            temp_v1_8 = var_s5_2 << 5;
                            packet_coords += temp_v1_8;
                            gte_load_transform8_advance((s32 *)packet_coords);
                            var_s5_2 += 1;
                            __asm__ volatile(
                                "lui $24,0x800b\n\taddiu $24,$24,-9384"
                                : "=r" (temp_t8));
                            __asm__ volatile("lwc2 $0, 0x8($t8)");
                            __asm__ volatile("lwc2 $1, 0xc($t8)");
                            __asm__ volatile("lwc2 $2, 0x10($t8)");
                            __asm__ volatile("lwc2 $3, 0x14($t8)");
                            __asm__ volatile("lwc2 $4, 0x18($t8)");
                            __asm__ volatile("lwc2 $5, 0x1c($t8)");
                            __asm__ volatile("nop\n\tnop\n\t.word 0x4A280030");
                            temp_v0 = *(u8 *)((u8 *)var_s1_2 + 7);
                            __asm__ volatile("li $25,-4" : "=r" (matrix_globals));
                            temp_v1_14 = temp_v0 & (s32)matrix_globals;
                            switch (temp_v1_14) {
                            case 0x28:
                                __asm__ volatile("swc2 $12, 0xc($s3)");
                                __asm__ volatile("swc2 $13, 0x10($s3)");
                                __asm__ volatile("swc2 $14, 0x14($s3)");
                                break;
                            case 0x38:
                            case 0x2C:
                                __asm__ volatile("swc2 $12, 0x10($s3)");
                                __asm__ volatile("swc2 $13, 0x18($s3)");
                                __asm__ volatile("swc2 $14, 0x20($s3)");
                                break;
                            case 0x3C:
                                __asm__ volatile("swc2 $12, 0x14($s3)");
                                __asm__ volatile("swc2 $13, 0x20($s3)");
                                __asm__ volatile("swc2 $14, 0x2c($s3)");
                                break;
                            }
                            temp_a3 = stack.sp100;
                            __asm__ volatile("" : "+r" (temp_a3));
                            __asm__ volatile("nop");
                            __asm__ volatile("swc2 $17, 0x4($a3)");
                            __asm__ volatile("swc2 $18, 0x8($a3)");
                            __asm__ volatile("swc2 $19, 0xc($a3)");
                            __asm__ volatile(
                                "lui $22,0x800b\n\taddiu $22,$22,-9384"
                                : "=r" (second_normalized));
                            __asm__ volatile("lwc2 $0, ($s6)");
                            __asm__ volatile("lwc2 $1, 0x4($s6)");
                            __asm__ volatile("nop\n\tnop\n\t.word 0x4A180001");
                            packet_coords = (u8 *)var_s3 + 8;
                            __asm__ volatile("" : "+r" (packet_coords));
                            __asm__ volatile("swc2 $14, ($v0)");
                            __asm__ volatile("swc2 $19, ($a3)");
                            stack.spD8 = (s32) (stack.sp58 + stack.sp5C + stack.sp60 + stack.sp64) >> 2;
                            break;
                        case 0xD8:
                            temp_v0 = *(s32 *)((u8 *)var_s1_2 + 0x28);
                            *(s32 *)((u8 *)var_s3 + 0xC) = temp_v0;
                            temp_v0 = *(s32 *)((u8 *)var_s1_2 + 0x2C);
                            *(s32 *)((u8 *)var_s3 + 0x14) = temp_v0;
                            temp_v1_8 = *(s32 *)((u8 *)var_s1_2 + 0x30);
                            temp_v0 = 0x38;
                            *(s8 *)((u8 *)var_s3 + 7) = temp_v0;
                            *(s32 *)((u8 *)var_s3 + 0x1C) = temp_v1_8;
                            goto block_173;
                        case 0xA4:
                            (*(void **)((u8 *)(var_s3)+(0x10))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x28)));
                            (*(void **)((u8 *)(var_s3)+(0x1C))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x2C)));
                            (*(void **)((u8 *)(var_s3)+(0x28))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x30)));
                            temp_t8 = stack.spF8;
                            __asm__ volatile("" : "+r" (temp_t8));
                            temp_v0 = *(u16 *)((u8 *)temp_t8 + 6);
                            *(u16 *)((u8 *)var_s3 + 0x18) = temp_v0;
                            temp_v0 = *(u16 *)((u8 *)temp_t8 + 8);
                            *(u16 *)((u8 *)var_s3 + 0x24) = temp_v0;
                            temp_v1_8 = *(u16 *)((u8 *)temp_t8 + 0xA);
                            matrix_globals = (u8 *)(u32)stack.spF0;
                            temp_v0 = 0x3C;
                            *(s8 *)((u8 *)var_s3 + 7) = temp_v0;
                            *(u16 *)((u8 *)var_s3 + 0x1A) = (u16)(u32)matrix_globals;
                            *(u16 *)((u8 *)var_s3 + 0x30) = temp_v1_8;
                            goto block_171;
                        case 0x94:
                            temp_a3 = stack.spF8;
                            __asm__ volatile("" : "+r" (temp_a3));
                            temp_v0 = *(u16 *)((u8 *)temp_a3 + 6);
                            *(u16 *)((u8 *)var_s3 + 0x14) = temp_v0;
                            temp_v0 = *(u16 *)((u8 *)temp_a3 + 8);
                            *(u16 *)((u8 *)var_s3 + 0x1C) = temp_v0;
                            temp_v1_8 = *(u16 *)((u8 *)temp_a3 + 0xA);
                            second_normalized = (s32 *)(u32)stack.spF0;
                            temp_v0 = 0x2C;
                            *(s8 *)((u8 *)var_s3 + 7) = temp_v0;
                            *(u16 *)((u8 *)var_s3 + 0x16) = (u16)(u32)second_normalized;
                            *(u16 *)((u8 *)var_s3 + 0x24) = temp_v1_8;
block_171:
                            temp_t8 = stack.spF8;
                            __asm__ volatile("" : "+r" (temp_t8));
                            temp_v0 = *(u16 *)((u8 *)temp_t8 + 4);
                            *(u16 *)((u8 *)var_s3 + 0xC) = temp_v0;
                            goto block_173;
                        case 0xD0:
                            (*(s8 *)((u8 *)(var_s3)+(7))) = 0x28;
block_173:
                            packet_coords = (u8 *)*(s32 *)(var_s4_3 + 0x53E8);
                            __asm__ volatile("" : "+r" (packet_coords));
                            temp_v1_8 = var_s5_2 << 5;
                            packet_coords += temp_v1_8;
                            gte_load_transform8_advance((s32 *)packet_coords);
                            var_s5_2 += 1;
                            __asm__ volatile("mtc2 $zero, $0");
                            __asm__ volatile("mtc2 $zero, $1");
                            __asm__ volatile("nop\n\tnop\n\t.word 0x4A180001");
                            __asm__ volatile(
                                "lbu $2,7($17)\n\tli $25,-4\n\tand $3,$2,$25\n\t"
                                "li $2,0xb4\n\t.word 0x1062006b\n\tslti $2,$3,0xb5\n\t"
                                ".word 0x10400005\n\tli $2,0xa4\n\t.word 0x10620048\n\taddiu $2,$sp,0xd8\n\t"
                                ".word 0x08019d7a\n\tnop\n1:\n\tli $2,0xe0\n\t.word 0x10620005\n\tli $2,0xe8\n\t"
                                ".word 0x10620022\n\taddiu $2,$sp,0xd8\n\t.word 0x08019d7a\n\tnop\n"
                                "2:\n\tlh $10,0x1c($17)\n\tlh $11,0x1e($17)\n\tlh $12,0x20($17)\n\tlh $13,0x22($17)\n\tlh $14,0x24($17)\n\tlh $15,0x26($17)\n\t"
                                "mfc2 $8,$14\n\tnop\n\tsra $9,$8,16\n\tsll $8,$8,16\n\tsra $8,$8,16\n\t"
                                "add $10,$10,$8\n\tadd $12,$12,$8\n\tadd $14,$14,$8\n\tadd $11,$11,$9\n\tadd $13,$13,$9\n\tadd $15,$15,$9\n\t"
                                "sll $11,$11,16\n\tsll $13,$13,16\n\tsll $15,$15,16\n\tandi $10,$10,0xffff\n\tandi $12,$12,0xffff\n\tandi $14,$14,0xffff\n\t"
                                "or $10,$10,$11\n\tor $12,$12,$13\n\tor $14,$14,$15\n\tsw $10,0xc($19)\n\tsw $12,0x10($19)\n\tsw $14,0x14($19)\n\t.word 0x08019d7a\n\taddiu $2,$sp,0xd8\n"
                                "6:\n\tlh $10,0x1c($17)\n\tlh $11,0x1e($17)\n\tlh $12,0x20($17)\n\tlh $13,0x22($17)\n\tlh $14,0x24($17)\n\tlh $15,0x26($17)\n\t"
                                "mfc2 $8,$14\n\tnop\n\tsra $9,$8,16\n\tsll $8,$8,16\n\tsra $8,$8,16\n\t"
                                "add $10,$10,$8\n\tadd $12,$12,$8\n\tadd $14,$14,$8\n\tadd $11,$11,$9\n\tadd $13,$13,$9\n\tadd $15,$15,$9\n\t"
                                "sll $11,$11,16\n\tsll $13,$13,16\n\tsll $15,$15,16\n\tandi $10,$10,0xffff\n\tandi $12,$12,0xffff\n\tandi $14,$14,0xffff\n\t"
                                "or $10,$10,$11\n\tor $12,$12,$13\n\tor $14,$14,$15\n\tsw $10,0x10($19)\n\tsw $12,0x18($19)\n\tsw $14,0x20($19)\n\t.word 0x08019d7a\n\taddiu $2,$sp,0xd8\n"
                                "3:\n\tlh $10,0x20($17)\n\tlh $11,0x22($17)\n\tlh $12,0x24($17)\n\tlh $13,0x26($17)\n\tlh $14,0x28($17)\n\tlh $15,0x2a($17)\n\t"
                                "mfc2 $8,$14\n\tnop\n\tsra $9,$8,16\n\tsll $8,$8,16\n\tsra $8,$8,16\n\t"
                                "add $10,$10,$8\n\tadd $12,$12,$8\n\tadd $14,$14,$8\n\tadd $11,$11,$9\n\tadd $13,$13,$9\n\tadd $15,$15,$9\n\t"
                                "sll $11,$11,16\n\tsll $13,$13,16\n\tsll $15,$15,16\n\tandi $10,$10,0xffff\n\tandi $12,$12,0xffff\n\tandi $14,$14,0xffff\n\t"
                                "or $10,$10,$11\n\tor $12,$12,$13\n\tor $14,$14,$15\n\tsw $10,0x10($19)\n\tsw $12,0x18($19)\n\tsw $14,0x20($19)\n\t.word 0x08019d7a\n\taddiu $2,$sp,0xd8\n"
                                "4:\n\tlh $10,0x20($17)\n\tlh $11,0x22($17)\n\tlh $12,0x24($17)\n\tlh $13,0x26($17)\n\tlh $14,0x28($17)\n\tlh $15,0x2a($17)\n\t"
                                "mfc2 $8,$14\n\tnop\n\tsra $9,$8,16\n\tsll $8,$8,16\n\tsra $8,$8,16\n\t"
                                "add $10,$10,$8\n\tadd $12,$12,$8\n\tadd $14,$14,$8\n\tadd $11,$11,$9\n\tadd $13,$13,$9\n\tadd $15,$15,$9\n\t"
                                "sll $11,$11,16\n\tsll $13,$13,16\n\tsll $15,$15,16\n\tandi $10,$10,0xffff\n\tandi $12,$12,0xffff\n\tandi $14,$14,0xffff\n\t"
                                "or $10,$10,$11\n\tor $12,$12,$13\n\tor $14,$14,$15\n\tsw $10,0x14($19)\n\tsw $12,0x20($19)\n\tsw $14,0x2c($19)\n\taddiu $2,$sp,0xd8\n"
                                "5:\n\tlh $12,0x18($17)\n\tlh $13,0x1a($17)\n\tmfc2 $8,$14\n\tnop\n\tsra $9,$8,16\n\tsll $8,$8,16\n\tsra $8,$8,16\n\t"
                                "add $12,$12,$8\n\tadd $13,$13,$9\n\tsll $13,$13,16\n\tandi $12,$12,0xffff\n\tor $12,$12,$13\n\tswc2 $19,0($2)\n\tsw $12,8($19)\n"
                            );
                            break;
                        case 0x00:
                            var_s5_2 = ((s32 (*)(void *, void *, s32))func_80068720)(
                                var_s1_2 + 0x14, var_s1_2 + 0x1C, var_s5_2);
                            break;
                        case 0xE0:
                            D_800E53B8 = (*(s32 *)((u8 *)(var_s1_2)+(8)));
                            break;
                        case 0xDC:
                        case 0xE4:
                        case 0xE8:
                        case 0xEC:
                        default:
                            break;
                        }
                        __asm__ volatile(
                            "lw $2,0xd8($sp)\n\tnop\n\t.word 0x10400043\n\tlui $3,0x800b\n\t"
                            ".word 0x0c022e61\n\tnop\n\tlw $3,0xd8($sp)\n\tnop\n\tsubu $3,$3,$2\n\t"
                            "lui $2,0x800e\n\tlw $2,0x53b8($2)\n\tsra $3,$3,3\n\tsw $3,0xd8($sp)\n\taddu $3,$3,$2\n\t"
                            "slti $2,$3,2\n\t.word 0x10400003\n\tsw $3,0xd8($sp)\n\t.word 0x08019daa\n\tli $2,2\n\t"
                            "slti $2,$3,0x1000\n\t.word 0x14400004\n\taddiu $2,$sp,0xdc\n\tli $2,0xfff\n\t"
                            "sw $2,0xd8($sp)\n\taddiu $2,$sp,0xdc\n\tcfc2 $12,$31\n\tnop\n\tsw $12,0($2)\n\t"
                            "lw $2,0xdc($sp)\n\tnop\n\t.word 0x04400027\n\tlui $3,0x800b\n\t"
                            "lui $5,0xff\n\tori $5,$5,0xffff\n\tlui $6,0xff00\n\tlw $4,0xd8($sp)\n\tlw $7,0x140($sp)\n\tlw $22,0xe0($sp)\n\t"
                            "sll $4,$4,2\n\taddu $4,$4,$7\n\tlw $3,0($22)\n\tlw $2,0($4)\n\tand $3,$3,$6\n\tand $2,$2,$5\n\tor $3,$3,$2\n\tsw $3,0($22)\n\t"
                            "lw $2,0($4)\n\tand $5,$22,$5\n\tand $2,$2,$6\n\tor $2,$2,$5\n"
                            : "=r" (temp_v0), "=r" (temp_a0_3)
                        );
                        *temp_a0_3 = temp_v0;
                        goto block_199;
                    }
                } else {
                    __asm__ volatile(
                        "lbu $2,7($17)\n\tnop\n\tand $2,$2,$24\n\taddiu $3,$2,-0x28\n\t"
                        "sltiu $2,$3,0x29\n\t.word 0x1040000b\n\tlui $2,0x800c\n\taddiu $2,$2,0x2b8\n\t"
                        "sll $3,$3,2\n\taddu $3,$3,$2\n\tlw $2,0($3)\n\tnop\n\tjr $2\n\tnop\n\t"
                        "lbu $3,2($17)\n\taddiu $2,$21,1\n\taddu $21,$2,$3\n"
                        : : "r" (temp_t8)
                    );
block_199:
                    var_s1_2 += (*(u8 *)((u8 *)(var_s1_2)+(0))) * 4;
                    if (var_s1_2 == D_800AD9F0) {
                        goto block_200;
                    }
                    goto loop_109;
                }
            } else {
block_200:
                var_s5_2 = 0;
                goto block_201;
            }
        } else {
block_201:
            __asm__ volatile(
                "lui $4,0x800b\n\tlui $3,0x800e\n\taddiu $2,$sp,0x38\n\t"
                "addiu $5,$4,-0x2614\n\tsw $2,0x5374($3)\n\tlui $3,0x800e\n\t"
                "lw $17,-0x2614($4)\n\tlw $4,4($5)\n\tli $2,-10\n"
                : "=r" (matrix_call_a0), "=r" (loop_globals), "=r" (temp_v0),
                  "=r" (var_a1), "=r" (var_s1_3)
                : : "memory"
            );
            *(s32 *)(loop_globals + 0x53B8) = temp_v0;
            if (var_s1_3 != matrix_call_a0) {
                matrix_globals = (u8 *)0x00FFFFFF;
                __asm__ volatile("" : "+r" (matrix_globals));
                stack.sp104 = (u32)matrix_globals;
loop_203:
                temp_a3 = (void *)stack.spFC;
                __asm__ volatile("" : "+r" (temp_a3));
                temp_v0 = var_s5_2 < (s32)temp_a3;
                __asm__ volatile("" : "+r" (temp_v0));
                __asm__ volatile(".word 0x1040031e\n\tnop" : : "r" (temp_v0));
                {
                    if ((*(u8 *)((u8 *)(var_s1_3)+(2))) == 0) {
                        temp_v1_18 = (*(u8 *)((u8 *)(var_s1_3)+(7))) & 0xFC;
                        if (temp_v1_18 != 0x40) {
                            if (temp_v1_18 < 0x41) {
                                if (temp_v1_18 != 0x2C) {
                                    if (temp_v1_18 < 0x2D) {
                                        if (temp_v1_18 != 0x20) {
                                            if (temp_v1_18 < 0x21) {
                                                if (temp_v1_18 != 0x10) {
                                                    var_t9 = &D_800AD9EC;
                                                } else {
                                                    goto block_235;
                                                }
                                            } else if ((temp_v1_18 != 0x24) && (temp_v1_18 != 0x28)) {
                                                var_t9 = &D_800AD9EC;
                                            } else {
                                                goto block_235;
                                            }
                                        } else {
                                            goto block_235;
                                        }
                                    } else if (temp_v1_18 != 0x34) {
                                        if (temp_v1_18 < 0x35) {
                                            if (temp_v1_18 != 0x30) {
                                                var_t9 = &D_800AD9EC;
                                            } else {
                                                goto block_235;
                                            }
                                        } else if ((temp_v1_18 != 0x38) && (temp_v1_18 != 0x3C)) {
                                            var_t9 = &D_800AD9EC;
                                        } else {
                                            goto block_235;
                                        }
                                    } else {
                                        goto block_235;
                                    }
                                } else {
                                    goto block_235;
                                }
                            } else if (temp_v1_18 != 0xE8) {
                                if (temp_v1_18 < 0xE9) {
                                    if (temp_v1_18 != 0xA4) {
                                        if (temp_v1_18 < 0xA5) {
                                            if (temp_v1_18 != 0x50) {
                                                var_t9 = &D_800AD9EC;
                                            } else {
                                                goto block_234;
                                            }
                                        } else if ((temp_v1_18 != 0xB4) && (temp_v1_18 != 0xE0)) {
                                            var_t9 = &D_800AD9EC;
                                        } else {
                                            goto block_235;
                                        }
                                    } else {
                                        goto block_235;
                                    }
                                } else {
                                    if (temp_v1_18 == 0xF0) {
                                        goto block_233_f0;
                                    }
                                    var_t9 = &D_800AD9EC;
                                }
                            } else {
                                goto block_235;
                            }
                        } else {
block_234:
                            var_s5_2 += 1;
block_235:
                            var_s5_2 += 1;
                            goto block_334;
block_233_f0:
                            D_800E53B8 = (*(s32 *)((u8 *)(var_s1_3)+(8)));
                            goto block_334;
                        }
                        goto block_336;
                    }
                    if ((u8) (*(u8 *)((u8 *)(var_s1_3)+(7))) < 0xECU) {
                        temp_v0_30 = ((*(u8 *)((u8 *)(var_s1_3)+(3))) + 1) * 4;
                        allocation_kind = temp_v0_30;
                        __asm__ volatile("" : "+r" (temp_v0_30), "+r" (allocation_kind));
                        stack.spE4 = temp_v0_30;
                        var_s3 = func_80068EE8(allocation_kind);
                        __asm__ volatile("" : "+r" (var_s3));
                        if (var_s3 != ((void *)0)) {
                            __asm__ volatile(
                                "lhu $2,0x14($17)\n\tnop\n\tandi $18,$2,0x60\n\t"
                                "lbu $2,7($17)\n\tnop\n\tandi $2,$2,4\n"
                                : "=r" (temp_v0), "=r" (temp_s2_2) : : "memory"
                            );
                            stack.spF0 = temp_s2_2;
                            if (temp_v0 != 0) {
                                __asm__ volatile(
                                    "lw $2,0x1c($17)\n\tnop\n\tlhu $3,0($2)\n\tlhu $2,2($2)\n\t"
                                    "sw $19,0xe0($sp)\n\tandi $3,$3,0xff9f\n\tsh $2,0xe($19)\n\t"
                                    "lbu $2,3($17)\n\tor $18,$18,$3\n\tsh $18,0xf0($sp)\n\t"
                                    "sb $2,3($19)\n\tlw $22,0x1c($17)\n"
                                    : "=r" (temp_v0_31), "+r" (temp_s2_2),
                                      "=r" (second_normalized), "=r" (temp_v1_20)
                                    : : "memory"
                                );
                                stack.spF8 = second_normalized;
                                goto block_244;
                            }
                            temp_s0_2 = var_s3;
                            __asm__ volatile("" : "+r" (temp_s0_2));
                            stack.spE0 = var_s3;
                            var_s3 = (s32 *)((u8 *)var_s3 + 8);
                            __asm__ volatile("" : "+r" (var_s3));
                            __asm__ volatile(
                                "lw $24,0xe4($sp)\n\tli $4,8\n\taddiu $24,$24,8\n"
                                : "=r" (temp_t8), "=r" (allocation_kind)
                            );
                            stack.spE4 = (s32)temp_t8;
                            temp_v0 = (s32)func_80068EE8(allocation_kind);
                            __asm__ volatile(
                                ".word 0x104002b4\n\tlui $3,0xe100\n"
                                : : "r" (temp_v0) : "memory"
                            );
                            {
                                __asm__ volatile(
                                    "ori $3,$3,0x200\n\t"
                                    "lbu $2,3($17)\n\tor $3,$18,$3\n\tsb $2,3($19)\n\t"
                                    "li $2,1\n\tsb $2,3($16)\n\tsw $3,4($16)\n\t"
                                    "lbu $10,3($16)\n\tlbu $11,3($19)\n\tnop\n\t"
                                    "addu $10,$11,$10\n\taddiu $11,$10,1\n\t"
                                    "slti $10,$11,11\n\tbeqz $10,1f\n\tnop\n\t"
                                    "sb $11,3($16)\n\tsw $zero,0($19)\n\t"
                                    "1:\n"
                                    : : : "memory"
                                );
block_244:
                                (*(s32 *)((u8 *)(var_s3)+(4))) = (s32) (*(s32 *)((u8 *)(var_s1_3)+(4)));
                                goto block_245;
                            }
                        }
                    } else {
block_245:
                        __asm__ volatile(
                            ".set noreorder\n\tlbu $2,1($17)\n\tnop\n\tandi $3,$2,0xf0\n\tli $2,0x10\n\t"
                            ".word 0x1062000b\n\tslti $2,$3,0x11\n\t"
                            ".word 0x14400006\n\tmove $10,$zero\n\tli $2,0x20\n\t"
                            ".word 0x10620009\n\tli $2,0x40\n\t.word 0x10620008\n\tli $30,2\n\t"
                            "2:\n\tli $30,1\n\t.word 0x08019e9a\n\tli $23,2\n\t"
                            "4:\n\tli $10,2\n\t.word 0x08019e99\n\tmove $30,$zero\n\t"
                            "3:\n\tli $30,2\n\t5:\n\tli $23,1\n\t"
                            "6:\n\tli $25,3\n\tlui $2,0x800b\n\tsw $zero,0xd8($sp)\n\t"
                            "lbu $3,1($17)\n\taddiu $2,$2,-0x24d8\n\tsw $25,0x110($sp)\n\t"
                            "andi $3,$3,0xf\n\tsll $3,$3,4\n\taddu $11,$3,$2\n\t"
                            "lbu $2,7($17)\n\tnop\n\tandi $3,$2,0xff\n\tandi $2,$2,0x10\n\t"
                            "andi $3,$3,0xfc\n\tsw $2,0xe8($sp)\n"
                            : "=r" (var_t2_2), "=r" (var_fp_2), "=r" (var_s7_2),
                              "=r" (var_t9), "=r" (var_t3), "=r" (temp_v0),
                              "=r" (temp_v1_20)
                            : : "memory"
                        );
                        if (temp_v1_20 != 0x3C) {
                            if (temp_v1_20 < 0x3D) {
                                if (temp_v1_20 != 0x2C) {
                                    if (temp_v1_20 < 0x2D) {
                                        if (temp_v1_20 != 0x28) {
                                            var_t9 = &D_800AD9EC;
                                            goto block_336;
                                        }
                                        goto block_293_28;
                                    }
                                    if (temp_v1_20 != 0x38) {
                                        var_t9 = &D_800AD9EC;
                                        goto block_336;
                                    }
                                    goto block_293_38;
                                }
                                goto block_293_2c;
                            }
                            if (temp_v1_20 != 0x50) {
                                if (temp_v1_20 < 0x51) {
                                    if (temp_v1_20 != 0x40) {
                                        var_t9 = &D_800AD9EC;
                                        goto block_336;
                                    }
                                    goto block_269_40;
                                }
                                if (temp_v1_20 == 0xFC) {
                                    stack.spD8 = 0;
                                }
                                goto block_335;
                            }
                            __asm__ volatile("addiu %0,$17,0x24" : "=r" (var_s0_3));
                            temp_a3 = (void *)4;
                            stack.sp110 = (M2C_UNK *)temp_a3;
                            __asm__ volatile("lwc2 $6, 0x4($s0)");
                            goto block_269;
block_269_40:
                            __asm__ volatile("addiu %0,$17,0x20" : "=r" (var_s0_3));
block_269:
                            second_normalized = (s32 *)0x800E0000;
                            __asm__ volatile("" : "+r" (second_normalized));
                            gte_load_transform8_advance((s32 *)(
                                *(s32 *)((u8 *)second_normalized + 0x53E8) + (var_s5_2 << 5)));
                            var_s5_2 += 1;
                            __asm__ volatile("mtc2 $zero, $0");
                            __asm__ volatile("mtc2 $zero, $1");
                            __asm__ volatile("nop\n\tnop\n\t.word 0x4A180001");
                            temp_v0_30 = (s32)((u8 *)var_s3 + 8);
                            __asm__ volatile("swc2 $14, ($v0)" : : "r" (temp_v0_30));
                            var_s4_3 = (*(u8 *)((u8 *)(var_s1_3)+(2)));
                            if ((s32) var_s4_3 > 0) {
                                __asm__ volatile("lui %0,0xff00" : "=r" (var_s7_2));
loop_271:
                                temp_t8 = (void *)stack.spFC;
                                __asm__ volatile("" : "+r" (temp_t8));
                                temp_v0_30 = var_s5_2 < (s32)temp_t8;
                                __asm__ volatile("" : "+r" (temp_v0_30));
                                if (temp_v0_30) {
                                    temp_v0_30 = (s32)&stack.sp58;
                                    __asm__ volatile("swc2 $19, ($v0)" : : "r" (temp_v0_30));
                            temp_v1_20 = var_s5_2 << 5;
                            __asm__ volatile("" : "+r" (temp_v1_20));
                            var_t9 = (M2C_UNK *)0x800E0000;
                            __asm__ volatile("" : "+r" (var_t9));
                            gte_load_transform8_advance((s32 *)(
                                *(s32 *)((u8 *)var_t9 + 0x53E8) + temp_v1_20));
                                    var_s5_2 += 1;
                                    __asm__ volatile("mtc2 $zero, $0");
                                    __asm__ volatile("mtc2 $zero, $1");
                                    __asm__ volatile("nop\n\tnop\n\t.word 0x4A180001");
                                    __asm__ volatile(
                                        "lbu $2,0($16)\n\tlw $4,0xe4($sp)\n\t"
                                        "sll $2,$2,2\n\t.word 0x0c01a3ba\n\taddu $16,$16,$2\n\t"
                                        "move $18,$2\n"
                                        : "=r" (temp_v0_30), "=r" (temp_s2_2) : : "memory"
                                    );
                                    temp_v0_33 = (s32 *)temp_s2_2;
                                    if (temp_v0_33 != ((void *)0)) {
                                        __asm__ volatile(
                                            "lw $7,0xe8($sp)\n\tnop\n\t"
                                            "beqz $7,1f\n\taddiu $2,$sp,0x5c\n\t"
                                            "swc2 $6,0xc($19)\n\taddiu $2,$sp,0x5c\n"
                                            "1:\n\tswc2 $19,0($2)"
                                            : : : "memory"
                                        );
                                        stack.spD8 = (s32) (stack.sp58 + stack.sp5C) >> 1;
                                        func_8008B984();
                                        __asm__ volatile(
                                            "lw $3,0xd8($sp)\n\tnop\n\t"
                                            "subu $3,$3,$2\n\tlui $2,0x800e\n\t"
                                            "lw $2,0x53b8($2)\n\tsra $3,$3,3\n\t"
                                            "sw $3,0xd8($sp)\n\taddu $3,$3,$2"
                                            : "=r" (temp_v1_20) : : "memory"
                                        );
                                        __asm__ volatile(
                                            "slti $2,$3,2\n\t.word 0x10400003\n\tsw $3,0xd8($sp)\n\t"
                                            ".word 0x08019f3b\n\tli $2,2\n\t"
                                            "slti $2,$3,0x1000\n\t.word 0x14400004\n\taddiu $2,$sp,0xdc\n\t"
                                            "li $2,0xfff\n\tsw $2,0xd8($sp)\n\taddiu $2,$sp,0xdc\n\t"
                                            "cfc2 $12,$31\n\tnop\n\tsw $12,0($2)\n"
                                            : "+r" (temp_v1_20), "=r" (temp_v0) : : "memory"
                                        );
                                        __asm__ volatile(
                                            "lw $2,0xdc($sp)\n\tnop\n\t.word 0x04400012\n\tnop\n\t"
                                            "lw $4,0xd8($sp)\n\tlw $22,0x140($sp)\n\t"
                                            "lw $24,0xe0($sp)\n\tlw $25,0x104($sp)\n\t"
                                            "sll $4,$4,2\n\taddu $4,$4,$22\n\t"
                                            "lw $2,0($24)\n\tlw $3,0($4)\n\t"
                                            "and $2,$2,$23\n\tand $3,$3,$25\n\t"
                                            "or $2,$2,$3\n\tsw $2,0($24)\n\t"
                                            "lw $2,0($4)\n\tand $3,$24,$25\n\t"
                                            "and $2,$2,$23\n\tor $2,$2,$3\n\tsw $2,0($4)\n"
                                            : : : "memory"
                                        );
                                        temp_a3 = stack.sp110;
                                        __asm__ volatile("" : "+r" (temp_a3));
                                        temp_v0_30 = (s32)var_s3 + ((s32)temp_a3 << 2);
                                        __asm__ volatile("swc2 $14, ($v0)" : : "r" (temp_v0_30));
                                        __asm__ volatile(
                                            "lw $22,0xe0($sp)\n\tnop\n\t"
                                            "subu $2,$18,$22\n\tsra $2,$2,2\n\t"
                                            "addiu $6,$2,-1"
                                            : "=r" (second_normalized),
                                              "=r" (temp_v0_30), "=r" (var_a2_5)
                                            : : "memory"
                                        );
                                        __asm__ volatile(
                                            ".word 0x04c00009\n\tsll $2,$6,2\n\t"
                                            "addu $4,$2,$18\n\taddu $3,$2,$22\n"
                                            "1:\n\tlw $2,0($3)\n\taddiu $3,$3,-4\n\t"
                                            "addiu $6,$6,-1\n\tsw $2,0($4)\n\t"
                                            ".word 0x04c1fffb\n\taddiu $4,$4,-4"
                                            : : : "memory"
                                        );
                                        __asm__ volatile(
                                            "lw $24,0xe0($sp)\n\tnop\n\t"
                                            "subu $2,$19,$24\n\taddu $19,$18,$2\n\t"
                                            "lw $2,0x5c($sp)\n\tsw $18,0xe0($sp)\n\t"
                                            "sw $2,0x58($sp)\n\taddiu $2,$19,8\n\t"
                                            "swc2 $14,0($2)"
                                            : "+r" (var_s3), "=r" (temp_v0_30),
                                              "=r" (temp_t8)
                                            : "r" (temp_v0_33) : "memory"
                                        );
                                        var_t9 = (M2C_UNK *)stack.spE8;
                                        __asm__ volatile("" : "+r" (var_t9));
                                        if (var_t9 != 0) {
                                            __asm__ volatile("swc2 $6, 0x4($s3)");
                                            __asm__ volatile("lwc2 $6, 0x4($s0)");
                                        }
                                        var_s4_3 -= 1;
                                        if ((s32) var_s4_3 <= 0) {
                                            goto block_335;
                                        }
                                        goto loop_271;
                                    }
                                } else {
                                    goto block_334;
                                }
                            } else {
                                goto block_335;
                            }
                        } else {
                            temp_a3 = stack.spF8;
                            __asm__ volatile("" : "+r" (temp_a3));
                            (*(u16 *)((u8 *)(var_s3)+(0x18))) = (u16) (*(u16 *)((u8 *)(temp_a3)+(6)));
                            (*(u16 *)((u8 *)(var_s3)+(0x24))) = (u16) (*(u16 *)((u8 *)(temp_a3)+(8)));
                            (*(u16 *)((u8 *)(var_s3)+(0x30))) = (u16) (*(u16 *)((u8 *)(temp_a3)+(0xA)));
                            temp_v0_30 = (*(s32 *)((u8 *)(var_s1_3)+(0x20)));
                            second_normalized = (s32 *)(u32)stack.spF0;
                            __asm__ volatile("" : "+r" (temp_v0_30), "+r" (second_normalized));
                            __asm__ volatile("addiu %0,$17,0x2c" : "=r" (var_s0_3));
                            (*(u16 *)((u8 *)(var_s3)+(0x1A))) = (u16)(u32)second_normalized;
                            (*(s32 *)((u8 *)(var_s3)+(0x10))) = temp_v0_30;
                            __asm__ volatile("lwc2 $21, 0x1c($s0)");
                            temp_t8 = (void *)5;
                            stack.sp110 = (M2C_UNK *)temp_t8;
                            goto block_292;
block_293_38:
                            temp_v0_30 = (*(s32 *)((u8 *)(var_s1_3)+(0x1C)));
                            __asm__ volatile("" : "+r" (temp_v0_30));
                            __asm__ volatile("addiu %0,$17,0x28" : "=r" (var_s0_3));
                            (*(s32 *)((u8 *)(var_s3)+(0xC))) = temp_v0_30;
                            __asm__ volatile("lwc2 $21, 0x1c($s0)");
                            var_t9 = (M2C_UNK *)4;
                            stack.sp110 = var_t9;
                            goto block_294;
block_293_2c:
                            __asm__ volatile(
                                "lw $7,0xf8($sp)\n\tnop\n\tlhu $2,6($7)\n\tnop\n\t"
                                "sh $2,0x14($19)\n\tlhu $2,8($7)\n\taddiu $16,$17,0x20\n\t"
                                "sh $2,0x1c($19)\n\tlhu $2,0xa($7)\n\tlhu $24,0xf0($sp)\n\t"
                                "li $22,4\n\tsw $22,0x110($sp)\n\t"
                                "sh $24,0x16($19)\n\tsh $2,0x24($19)\n"
                                : "=r" (temp_a3), "=r" (temp_v0),
                                  "=r" (var_s0_3), "=r" (second_normalized)
                                : : "memory"
                            );
block_292:
                            var_t9 = (M2C_UNK *)stack.spF8;
                            __asm__ volatile("" : "+r" (var_t9));
                            (*(u16 *)((u8 *)(var_s3)+(0xC))) = (u16) (*(u16 *)((u8 *)(var_t9)+(4)));
                            goto block_294;
block_293_28:
                            __asm__ volatile("addiu %0,$17,0x1c" : "=r" (var_s0_3));
block_294:
                            temp_a3 = (void *)0x800E0000;
                            __asm__ volatile("" : "+r" (temp_a3));
                            gte_load_transform8_advance((s32 *)(
                                *(s32 *)((u8 *)temp_a3 + 0x53E8) + (var_s5_2 << 5)));
                            var_s5_2 += 1;
                            __asm__ volatile("lwc2 $20, 0x4($s0)");
                            __asm__ volatile(
                                "move $6,$zero\n\tsll $2,$10,2\n\t"
                                "addiu $3,$sp,0x88\n\taddu $9,$3,$2\n\t"
                                "sll $2,$30,2\n\taddu $8,$3,$2\n\t"
                                "sll $2,$23,2\n\taddu $18,$3,$2\n\t"
                                "lui $2,0x800b\n\taddiu $4,$2,-0x24a8\n\t"
                                "move $5,$11"
                                : : : "memory"
                            );
                            __asm__ volatile(
                                "1:\n\tlh $3,0($5)\n\tlh $2,0x18($17)\n\tnop\n\t"
                                "mult $3,$2\n\tmflo $24\n\tmfhi $22\n\t"
                                "sll $22,$22,20\n\tsrl $24,$24,12\n\t"
                                "move $2,$22\n\tmove $3,$24\n\tor $2,$2,$3\n\t"
                                "sw $2,0x88($sp)\n\tlh $3,2($5)\n\t"
                                "lh $2,0x1a($17)\n\tnop\n\tmult $3,$2\n\t"
                                "mflo $7\n\tmfhi $25\n\tsll $25,$25,20\n\t"
                                "srl $7,$7,12\n\tmove $2,$25\n\tmove $3,$7\n\t"
                                "or $2,$2,$3\n\tsw $2,0x8c($sp)"
                                : : : "memory"
                            );
                            __asm__ volatile(
                                "lh $2,4($5)\n\tnop\n\tsw $2,0x90($sp)\n\t"
                                "lhu $2,0($9)\n\tnop\n\tsh $2,0($4)\n\t"
                                "lhu $2,0($8)\n\tnop\n\tsh $2,2($4)\n\t"
                                "lhu $2,0($18)\n\tnop\n\tsh $2,4($4)\n\t"
                                "addiu $4,$4,8\n\taddiu $6,$6,1\n\t"
                                "slti $2,$6,2\n\t.word 0x1440ffd8\n\taddiu $5,$5,8"
                                : : : "memory"
                            );
                            __asm__ volatile(
                                "lui $22,0x800b\n\taddiu $22,$22,-0x24a8"
                                : "=r" (second_normalized)
                            );
                            __asm__ volatile("lwc2 $0, ($s6)");
                            __asm__ volatile("lwc2 $1, 0x4($s6)");
                            __asm__ volatile("lwc2 $2, 0x8($s6)");
                            __asm__ volatile("lwc2 $3, 0xc($s6)");
                            __asm__ volatile("nop\n\tnop\n\t.word 0x4A280030");
                            temp_t8 = stack.sp110;
                            __asm__ volatile("" : "+r" (temp_t8));
                            temp_v0_30 = (s32)var_s3 + ((s32)temp_t8 << 2);
                            __asm__ volatile("" : "+r" (temp_v0_30));
                            __asm__ volatile("swc2 $12, 0x8($s3)");
                            __asm__ volatile("swc2 $13, ($v0)" : : "r" (temp_v0_30));
                            var_s4_4 = (*(u8 *)((u8 *)(var_s1_3)+(2)));
                            if ((s32) var_s4_4 > 0) {
loop_297:
                                var_t9 = (M2C_UNK *)stack.spFC;
                                __asm__ volatile("" : "+r" (var_t9));
                                temp_v0_30 = var_s5_2 < (s32)var_t9;
                                __asm__ volatile("" : "+r" (temp_v0_30));
                                if (temp_v0_30) {
                                    temp_v0_30 = (s32)&stack.sp58;
                                    __asm__ volatile("swc2 $17, ($v0)\n\tswc2 $18, 0x4($v0)" : : "r" (temp_v0_30));
                            temp_v1_20 = var_s5_2 << 5;
                            __asm__ volatile("" : "+r" (temp_v1_20));
                            temp_a3 = (void *)0x800E0000;
                            __asm__ volatile("" : "+r" (temp_a3));
                            gte_load_transform8_advance((s32 *)(
                                *(s32 *)((u8 *)temp_a3 + 0x53E8) + temp_v1_20));
                                    var_s5_2 += 1;
                                    __asm__ volatile(
                                        "move $6,$zero\n\tsll $2,$10,2\n\t"
                                        "addiu $3,$sp,0x88\n\taddu $9,$3,$2\n\t"
                                        "sll $2,$30,2\n\taddu $8,$3,$2\n\t"
                                        "sll $2,$23,2\n\taddu $18,$3,$2\n\t"
                                        "lui $4,0x800b\n\taddiu $4,$4,-0x24a8\n\t"
                                        "move $5,$11"
                                        : : : "memory"
                                    );
                                    __asm__ volatile(
                                        "1:\n\tlh $3,0($5)\n\tlh $2,0x18($16)\n\tnop\n\t"
                                        "mult $3,$2\n\tmflo $24\n\tmfhi $22\n\t"
                                        "sll $22,$22,20\n\tsrl $24,$24,12\n\t"
                                        "move $2,$22\n\tmove $3,$24\n\tor $2,$2,$3\n\t"
                                        "sw $2,0x88($sp)\n\tlh $3,2($5)\n\t"
                                        "lh $2,0x1a($16)\n\tnop\n\tmult $3,$2\n\t"
                                        "mflo $7\n\tmfhi $25\n\tsll $25,$25,20\n\t"
                                        "srl $7,$7,12\n\tmove $2,$25\n\tmove $3,$7\n\t"
                                        "or $2,$2,$3\n\tsw $2,0x8c($sp)"
                                        : : : "memory"
                                    );
                                    __asm__ volatile(
                                        "lh $2,4($5)\n\tnop\n\tsw $2,0x90($sp)\n\t"
                                        "lhu $2,0($9)\n\tnop\n\tsh $2,0($4)\n\t"
                                        "lhu $2,0($8)\n\tnop\n\tsh $2,2($4)\n\t"
                                        "lhu $2,0($18)\n\tnop\n\tsh $2,4($4)\n\t"
                                        "addiu $4,$4,8\n\taddiu $6,$6,1\n\t"
                                        "slti $2,$6,2\n\t.word 0x1440ffd8\n\taddiu $5,$5,8"
                                        : : : "memory"
                                    );
                                    __asm__ volatile(
                                        "lui $22,0x800b\n\taddiu $22,$22,-0x24a8"
                                        : "=r" (second_normalized)
                                    );
                                    __asm__ volatile("lwc2 $0, ($s6)");
                                    __asm__ volatile("lwc2 $1, 0x4($s6)");
                                    __asm__ volatile("lwc2 $2, 0x8($s6)");
                                    __asm__ volatile("lwc2 $3, 0xc($s6)");
                                    __asm__ volatile("nop\n\tnop\n\t.word 0x4A280030");
                                    __asm__ volatile(
                                        "lbu $2,0($16)\n\tlw $4,0xe4($sp)\n\t"
                                        "sw $10,0x108($sp)\n\tsw $11,0x10c($sp)\n\t"
                                        "sll $2,$2,2\n\t.word 0x0c01a3ba\n\taddu $16,$16,$2\n\t"
                                        "move $18,$2\n\tlw $10,0x108($sp)\n\tlw $11,0x10c($sp)\n"
                                        : "=r" (temp_v0_30), "=r" (temp_s2_2),
                                          "+r" (var_t2_2), "+r" (var_t3)
                                        : : "memory"
                                    );
                                    temp_v0_39 = (s32 *)temp_s2_2;
                                    if (temp_v0_39 != ((void *)0)) {
                                        temp_v1_27 = (*(u8 *)((u8 *)(var_s1_3)+(7))) & 0xFC;
                                        switch (temp_v1_27) {
                                        case 0x28:
                                            __asm__ volatile("swc2 $12, 0x10($s3)");
                                            __asm__ volatile("swc2 $13, 0x14($s3)");
                                            break;
                                        case 0x38:
                                            __asm__ volatile("swc2 $20, 0x14($s3)");
                                            __asm__ volatile("swc2 $21, 0x1c($s3)");
                                        case 0x2C:
                                            __asm__ volatile("swc2 $12, 0x18($s3)");
                                            __asm__ volatile("swc2 $13, 0x20($s3)");
                                            break;
                                        case 0x3C:
                                            __asm__ volatile("swc2 $12, 0x20($s3)");
                                            __asm__ volatile("swc2 $13, 0x2c($s3)");
                                            __asm__ volatile("swc2 $20, 0x1c($s3)");
                                            __asm__ volatile("swc2 $21, 0x28($s3)");
                                            break;
                                        }
                                        temp_v0_30 = (s32)&stack.sp58;
                                        __asm__ volatile("swc2 $17, 0x8($v0)" : : "r" (temp_v0_30));
                                        __asm__ volatile("swc2 $18, 0xc($v0)" : : "r" (temp_v0_30));
                                        __asm__ volatile(
                                            "lw $2,0x58($sp)\n\tlw $3,0x5c($sp)\n\t"
                                            "lw $4,0x64($sp)\n\taddu $2,$2,$3\n\t"
                                            "lw $3,0x60($sp)\n\tsw $10,0x108($sp)\n\t"
                                            "sw $11,0x10c($sp)\n\taddu $2,$2,$3\n\t"
                                            "addu $2,$2,$4\n\tsra $2,$2,2\n\t"
                                            ".word 0x0c022e61\n\tsw $2,0xd8($sp)\n\t"
                                            "lw $3,0xd8($sp)\n\tlw $10,0x108($sp)\n\t"
                                            "lw $11,0x10c($sp)\n\tsubu $3,$3,$2\n\t"
                                            "lui $2,0x800e\n\tlw $2,0x53b8($2)\n\t"
                                            "sra $3,$3,3\n\tsw $3,0xd8($sp)\n\t"
                                            "addu $3,$3,$2\n"
                                            : "=r" (temp_v0), "=r" (temp_v1_29),
                                              "+r" (var_t2_2), "+r" (var_t3)
                                            : : "memory"
                                        );
                                        temp_v1_20 = temp_v1_29;
                                        __asm__ volatile(
                                            "slti $2,$3,2\n\t.word 0x10400003\n\tsw $3,0xd8($sp)\n\t"
                                            ".word 0x0801a0b3\n\tli $2,2\n\t"
                                            "slti $2,$3,0x1000\n\t.word 0x14400004\n\taddiu $2,$sp,0xdc\n\t"
                                            "li $2,0xfff\n\tsw $2,0xd8($sp)\n\taddiu $2,$sp,0xdc\n\t"
                                            "cfc2 $12,$31\n\tnop\n\tsw $12,0($2)\n"
                                            : "+r" (temp_v1_20), "=r" (temp_v0) : : "memory"
                                        );
                                        __asm__ volatile(
                                            "lw $2,0xdc($sp)\n\tnop\n\t.word 0x04400012\n\tlui $5,0xff00\n\t"
                                            "lw $4,0xd8($sp)\n\tlw $24,0x140($sp)\n\t"
                                            "lw $25,0xe0($sp)\n\tlw $7,0x104($sp)\n\t"
                                            "sll $4,$4,2\n\taddu $4,$4,$24\n\t"
                                            "lw $2,0($25)\n\tlw $3,0($4)\n\t"
                                            "and $2,$2,$5\n\tand $3,$3,$7\n\t"
                                            "or $2,$2,$3\n\tsw $2,0($25)\n\t"
                                            "lw $2,0($4)\n\tand $3,$25,$7\n\t"
                                            "and $2,$2,$5\n\tor $2,$2,$3\n\tsw $2,0($4)\n"
                                            : : : "memory"
                                        );
                                        __asm__ volatile(
                                            "lw $22,0xe0($sp)\n\tnop\n\tsubu $2,$18,$22\n\t"
                                            "sra $2,$2,2\n\taddiu $6,$2,-1\n\t"
                                            ".word 0x04c00009\n\tsll $2,$6,2\n\t"
                                            "addu $4,$2,$18\n\taddu $3,$2,$22\n\t"
                                            "lw $2,0($3)\n\taddiu $3,$3,-4\n\t"
                                            "addiu $6,$6,-1\n\tsw $2,0($4)\n\t"
                                            ".word 0x04c1fffb\n\taddiu $4,$4,-4\n\t"
                                            "lw $24,0xe0($sp)\n\tlw $3,0x64($sp)\n\t"
                                            "subu $2,$19,$24\n\taddu $19,$18,$2\n\t"
                                            "lw $2,0x60($sp)\n\tsw $18,0xe0($sp)\n\t"
                                            "sw $3,0x5c($sp)\n\tsw $2,0x58($sp)"
                                            : "+r" (var_s3) : : "memory"
                                        );
                                        __asm__ volatile("swc2 $12, 0x8($s3)");
                                        __asm__ volatile("swc2 $20, 0x4($s3)");
                                        __asm__ volatile("lwc2 $20, 0x4($s0)");
                                        temp_v1_30 = (*(u8 *)((u8 *)(var_s1_3)+(7))) & 0xFC;
                                        if (temp_v1_30 == 0x38) goto block_330_38;
                                        if (temp_v1_30 < 0x39) {
                                            if (temp_v1_30 == 0x28) goto block_330_28;
                                            if (temp_v1_30 == 0x2C) goto block_331;
                                            goto block_330_done;
                                        }
                                        if (temp_v1_30 == 0x3C) goto block_330_3c;
                                        goto block_330_done;
block_330_28:
                                        __asm__ volatile("swc2 $13, 0xc($s3)");
                                        goto block_330_done;
block_330_38:
                                        __asm__ volatile("swc2 $21, 0xc($s3)");
                                        __asm__ volatile("lwc2 $21, 0x1c($s0)");
block_331:
                                        __asm__ volatile("swc2 $13, 0x10($s3)");
                                        goto block_330_done;
block_330_3c:
                                        __asm__ volatile("swc2 $13, 0x14($s3)");
                                        __asm__ volatile("swc2 $21, 0x10($s3)");
                                        __asm__ volatile("lwc2 $21, 0x1c($s0)");
block_330_done:
                                        var_s4_4 -= 1;
                                        if ((s32) var_s4_4 <= 0) {
                                            goto block_334;
                                        }
                                        goto loop_297;
                                    }
                                } else {
block_334:
                                    goto block_335;
                                }
                            } else {
block_335:
                                var_t9 = &D_800AD9EC;
block_336:
                                var_s1_3 += (*(u8 *)((u8 *)(var_s1_3)+(0))) * 4;
                                if (var_s1_3 == (*(s32 *)((u8 *)(var_t9)+(4)))) {
                                    goto block_337;
                                }
                                goto loop_203;
                            }
                        }
                    }
                }
            } else {
block_337:
                temp_a3 = (void *)&D_800E5398;
                __asm__ volatile("" : "+r" (temp_a3));
                __asm__ volatile(
                    "lw $12,0($7)\n\tlw $13,4($7)\n\tctc2 $12,$0\n\tctc2 $13,$1\n\t"
                    "lw $12,8($7)\n\tlw $13,12($7)\n\tlw $14,16($7)\n\t"
                    "ctc2 $12,$2\n\tctc2 $13,$3\n\tctc2 $14,$4\n"
                    : "+r" (temp_a3) : : "memory"
                );
                second_normalized = (s32 *)&D_800E53AC;
                __asm__ volatile("" : "+r" (second_normalized));
                __asm__ volatile(
                    "lw $12,0($22)\n\tlw $13,4($22)\n\tlw $14,8($22)\n\t"
                    "ctc2 $12,$5\n\tctc2 $13,$6\n\tctc2 $14,$7\n"
                    : : "r" (second_normalized) : "memory"
                );
            }
block_338:
            ;
        }
    }
}
