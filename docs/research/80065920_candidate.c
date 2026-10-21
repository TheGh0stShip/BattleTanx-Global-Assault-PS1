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
static __inline__ s32 gte_mfc2_9(void) { s32 value; __asm__ volatile("mfc2 %0,$9" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_10(void) { s32 value; __asm__ volatile("mfc2 %0,$10" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_11(void) { s32 value; __asm__ volatile("mfc2 %0,$11" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_14(void) { s32 value; __asm__ volatile("mfc2 %0,$14" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_25(void) { s32 value; __asm__ volatile("mfc2 %0,$25" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_26(void) { s32 value; __asm__ volatile("mfc2 %0,$26" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_27(void) { s32 value; __asm__ volatile("mfc2 %0,$27" : "=r" (value)); return value; }
static __inline__ s32 gte_mfc2_31(void) { s32 value; __asm__ volatile("mfc2 %0,$31" : "=r" (value)); return value; }
static __inline__ s32 mult_hi(s32 left, s32 right) { s32 value; __asm__ volatile("mult %1,%2\n\tmfhi %0" : "=r" (value) : "r" (left), "r" (right)); return value; }
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
extern M2C_UNK D_800AD9EC;
extern s32 D_800AD9F0;
extern M2C_UNK D_800ADA08;
extern M2C_UNK D_800ADB28;
extern M2C_UNK D_800ADB58;
extern M2C_UNK D_800D3034;
extern M2C_UNK D_800E5358;
extern M2C_UNK D_800E5368;
extern M2C_UNK *D_800E5374;
extern M2C_UNK D_800E5378;
extern M2C_UNK D_800E537C;
extern M2C_UNK D_800E5398;
extern M2C_UNK D_800E53AC;
extern s32 D_800E53B8;
extern M2C_UNK (*D_800E53BC)(M2C_UNK *, M2C_UNK *, s16);
extern M2C_UNK D_800E53C8;
extern s32 D_800E53E8;
extern s32 D_800E53EC;

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
    M2C_UNK (*var_v0_2)(M2C_UNK *, M2C_UNK *, s16);
    M2C_UNK (*var_v0_3)(M2C_UNK *, M2C_UNK *, s16);
    M2C_UNK *var_a0_5;
    M2C_UNK *var_a0_6;
    M2C_UNK *var_a1;
    M2C_UNK *var_a1_2;
    M2C_UNK *var_t9;
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
    s16 var_a2;
    s32 *temp_a0;
    s32 *temp_a0_2;
    s32 *temp_a0_3;
    s32 *temp_a0_4;
    s32 *temp_a0_5;
    s32 *temp_a0_6;
    s32 *temp_s0;
    s32 *temp_s0_2;
    s32 *temp_v0_33;
    s32 *temp_v0_39;
    s32 *var_a0_4;
    s32 *var_a0_7;
    s32 *var_s3;
    s32 *var_v1;
    s32 *var_v1_2;
    s32 *var_v1_3;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t1_4;
    s32 temp_t3;
    s32 temp_t3_3;
    s32 temp_v0;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_14;
    s32 temp_v0_17;
    s32 temp_v0_20;
    s32 temp_v0_23;
    s32 temp_v0_29;
    s32 temp_v0_2;
    s32 temp_v0_30;
    s32 temp_v0_34;
    s32 temp_v0_40;
    s32 temp_v0_5;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1_11;
    s32 temp_v1_14;
    s32 temp_v1_15;
    s32 temp_v1_16;
    s32 temp_v1_17;
    s32 temp_v1_18;
    s32 temp_v1_19;
    s32 temp_v1_20;
    s32 temp_v1_21;
    s32 temp_v1_22;
    s32 temp_v1_27;
    s32 temp_v1_28;
    s32 temp_v1_29;
    s32 temp_v1_2;
    s32 temp_v1_30;
    s32 temp_v1_3;
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 temp_v1_8;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_a2_4;
    s32 var_a2_5;
    s32 var_a2_6;
    s32 var_a2_7;
    s32 var_a2_8;
    s32 var_fp;
    s32 var_fp_2;
    register s32 matrix_count __asm__("$19");
    register s32 var_s5 __asm__("$21");
    s32 var_s5_2;
    s32 var_s7;
    s32 var_s7_2;
    s32 var_t2;
    register s32 var_t2_2 __asm__("$10");
    s32 var_v0;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_7;
    s32 var_v0_8;
    u16 temp_s2;
    u16 temp_s2_2;
    u32 temp_a3_2;
    u8 *var_s0;
    u8 temp_v0_32;
    u8 var_s4;
    u8 var_s4_2;
    u8 var_s4_3;
    u8 var_s4_4;
    void *temp_a3;
    void *temp_t3_2;
    void *temp_t8;
    void *temp_v0_12;
    void *temp_v0_13;
    void *temp_v0_15;
    void *temp_v0_16;
    void *temp_v0_18;
    void *temp_v0_19;
    void *temp_v0_21;
    void *temp_v0_22;
    void *temp_v0_24;
    void *temp_v0_31;
    void *temp_v0_3;
    void *temp_v0_4;
    void *temp_v0_6;
    void *temp_v0_7;
    void *temp_v1;
    void *var_a0;
    void *var_a0_2;
    void *var_a0_3;
    void *var_a1_3;
    void *var_a1_4;
    void *var_s0_2;
    void *var_s0_3;
    void *var_s1;
    void *var_s1_2;
    void *var_s1_3;
    register void *var_t3 __asm__("$11");
    matrix_count = 0;
    __asm__ volatile("" : "+r" (matrix_count));
    stack.spE0 = ((void *)0);
    stack.spE4 = 0;
    stack.spF0 = 0;
    stack.spF8 = ((void *)0);
    stack.spD8 = 0;
    temp_v0 = func_8007F7D8();
    state_or_mask = &D_800AD9EC;
    (*(s32 *)((u8 *)(state_or_mask)+(8))) = temp_v0;
    temp_v0 = func_8006A26C(4);
    D_800E53EC = temp_v0;
    D_800E53E8 = temp_v0;
    D_800E53B8 = -0xA;
    __asm__ volatile("" ::: "memory");
    {
        register M2C_UNK *context __asm__("$7") = &D_800E53C8;
        register s32 identity __asm__("$22") = 0x1000;
        register s32 depth_scale __asm__("$24") = 0xA00;
        __asm__ volatile("" : "+r" (context), "+r" (identity), "+r" (depth_scale));
        (*(s32 *)((u8 *)(context)+(0))) = (s32) (identity & 0xFFFF);
        (*(s32 *)((u8 *)(context)+(4))) = 0;
        (*(s32 *)((u8 *)(context)+(8))) = (s32) (depth_scale & 0xFFFF);
        (*(s32 *)((u8 *)(context)+(0xC))) = 0;
        (*(s16 *)((u8 *)(context)+(0x10))) = identity;
        (*(s32 *)((u8 *)(context)+(0x14))) = 0;
        (*(s32 *)((u8 *)(context)+(0x18))) = 0;
        (*(s32 *)((u8 *)(context)+(0x1C))) = 0;
    }
    (*(s32 *)((u8 *)(&stack.sp38)+(0))) = 0x1000;
    (*(s32 *)((u8 *)(&stack.sp38)+(4))) = 0;
    (*(s32 *)((u8 *)(&stack.sp38)+(8))) = 0x1000;
    (*(s32 *)((u8 *)(&stack.sp38)+(0xC))) = 0;
    (*(s16 *)((u8 *)(&stack.sp38)+(0x10))) = 0x1000;
    (*(s32 *)((u8 *)(&stack.sp38)+(0x14))) = 0;
    (*(s32 *)((u8 *)(&stack.sp38)+(0x18))) = 0;
    (*(s32 *)((u8 *)(&stack.sp38)+(0x1C))) = 0;
    D_800E5374 = &stack.sp38;
    temp_v1 = (arg1 * 0x9C) + &D_800D3034;
    stack.sp20 = (s32) (*(s32 *)((u8 *)(temp_v1)+(0xC))) >> 0xC;
    stack.sp24 = (s32) (*(s32 *)((u8 *)(temp_v1)+(0x10))) >> 0xC;
    stack.sp28 = (s32) (*(s32 *)((u8 *)(temp_v1)+(0x14))) >> 0xC;
    (*(s32 *)((u8 *)(&D_800E5398)+(0))) = (s32) gte_cfc2_0();
    (*(s32 *)((u8 *)(&D_800E5398)+(4))) = (s32) gte_cfc2_1();
    (*(s32 *)((u8 *)(&D_800E5398)+(8))) = (s32) gte_cfc2_2();
    (*(s32 *)((u8 *)(&D_800E5398)+(0xC))) = (s32) gte_cfc2_3();
    (*(s32 *)((u8 *)(&D_800E5398)+(0x10))) = (s32) gte_cfc2_4();
    (*(s32 *)((u8 *)(&D_800E5398)+(0x14))) = (s32) gte_cfc2_5();
    (*(s32 *)((u8 *)(&D_800E5398)+(0x18))) = (s32) gte_cfc2_6();
    (*(s32 *)((u8 *)(&D_800E5398)+(0x1C))) = (s32) gte_cfc2_7();
    (*(s32 *)((u8 *)(&D_800E53AC)+(0))) = (s32) gte_cfc2_5();
    (*(s32 *)((u8 *)(&D_800E53AC)+(4))) = (s32) gte_cfc2_6();
    (*(s32 *)((u8 *)(&D_800E53AC)+(8))) = (s32) gte_cfc2_7();
    var_s5 = matrix_count;
    __asm__ volatile("" : "+r" (var_s5));
    stack.sp98 = func_800924F0();
    stack.sp9A = func_80092500();
    stack.spA0 = func_800924F0();
    stack.spA2 = func_80092500();
    var_s1 = (*(void **)((u8 *)(state_or_mask)+(0)));
    if (var_s1 != (*(s32 *)((u8 *)(state_or_mask)+(4)))) {
        stack.sp110 = &stack.spA8;
        state_or_mask = (M2C_UNK *)0xFFFFFF;
        high_mask = 0xFF000000;
        var_v0 = var_s5 < 0x200;
loop_2:
        if (var_v0 != 0) {
            if ((u8) (*(u8 *)((u8 *)(var_s1)+(7))) < 0xECU) {
                func_80065710(&stack.sp10, var_s1 + 8, &stack.sp20);
            }
            temp_v1_2 = (*(u8 *)((u8 *)(var_s1)+(1))) & 0xF0;
            if (temp_v1_2 != 0x10) {
                var_v0_2 = func_80068940;
                if (temp_v1_2 >= 0x11) {
                    if (temp_v1_2 != 0x20) {
                        var_v0_2 = (M2C_UNK (*)(M2C_UNK *, M2C_UNK *, s16))0x80070000;
                        if (temp_v1_2 != 0x40) {
                            goto block_9;
                        }
                        var_v0_3 = func_80068AE4;
                    } else {
                        var_v0_3 = func_80068888;
                    }
                } else {
block_9:
                    var_v0_3 = var_v0_2;
                }
            } else {
                var_v0_3 = func_800687CC;
            }
            D_800E53BC = var_v0_3;
            if ((*(u8 *)((u8 *)(var_s1)+(2))) == 0) {
                temp_v1_3 = (*(u8 *)((u8 *)(var_s1)+(7))) & 0xFC;
                switch (temp_v1_3) {
                case 0x40:
                case 0x50:
                    temp_v0_2 = var_s5 << 5;
                    var_s5 += 1;
                    temp_v0_3 = temp_v0_2 + D_800E53E8;
                    (*(s32 *)((u8 *)(temp_v0_3)+(0))) = (s32) gte_cfc2_0();
                    (*(s32 *)((u8 *)(temp_v0_3)+(4))) = (s32) gte_cfc2_1();
                    (*(s32 *)((u8 *)(temp_v0_3)+(8))) = (s32) gte_cfc2_2();
                    (*(s32 *)((u8 *)(temp_v0_3)+(0xC))) = (s32) gte_cfc2_3();
                    (*(s32 *)((u8 *)(temp_v0_3)+(0x10))) = (s32) gte_cfc2_4();
                    (*(s32 *)((u8 *)(temp_v0_3)+(0x14))) = (s32) gte_cfc2_5();
                    (*(s32 *)((u8 *)(temp_v0_3)+(0x18))) = (s32) gte_cfc2_6();
                    (*(s32 *)((u8 *)(temp_v0_3)+(0x1C))) = (s32) gte_cfc2_7();
                    temp_v0_4 = temp_v0_3 + 0x14;
                    (*(s32 *)((u8 *)(temp_v0_3)+(0x14))) = (s32) gte_cfc2_5();
                    (*(s32 *)((u8 *)(temp_v0_4)+(4))) = (s32) gte_cfc2_6();
                    (*(s32 *)((u8 *)(temp_v0_4)+(8))) = (s32) gte_cfc2_7();
                    if (var_s5 < 0x1FF) {
block_51:
                        var_a2 = (*(s16 *)((u8 *)(var_s1)+(0x16)));
block_52:
                        D_800E53BC(&stack.sp68, &D_800E53C8, var_a2);
                    case 0xE8:
                    case 0xA4:
                    case 0xB4:
                    case 0xE0:
                        temp_v0_5 = var_s5 << 5;
                        var_s5 += 1;
                        temp_v0_6 = temp_v0_5 + D_800E53E8;
                        (*(s32 *)((u8 *)(temp_v0_6)+(0))) = (s32) gte_cfc2_0();
                        (*(s32 *)((u8 *)(temp_v0_6)+(4))) = (s32) gte_cfc2_1();
                        (*(s32 *)((u8 *)(temp_v0_6)+(8))) = (s32) gte_cfc2_2();
                        (*(s32 *)((u8 *)(temp_v0_6)+(0xC))) = (s32) gte_cfc2_3();
                        (*(s32 *)((u8 *)(temp_v0_6)+(0x10))) = (s32) gte_cfc2_4();
                        (*(s32 *)((u8 *)(temp_v0_6)+(0x14))) = (s32) gte_cfc2_5();
                        (*(s32 *)((u8 *)(temp_v0_6)+(0x18))) = (s32) gte_cfc2_6();
                        (*(s32 *)((u8 *)(temp_v0_6)+(0x1C))) = (s32) gte_cfc2_7();
                        temp_v0_7 = temp_v0_6 + 0x14;
                        (*(s32 *)((u8 *)(temp_v0_6)+(0x14))) = (s32) gte_cfc2_5();
                        (*(s32 *)((u8 *)(temp_v0_7)+(4))) = (s32) gte_cfc2_6();
                        (*(s32 *)((u8 *)(temp_v0_7)+(8))) = (s32) gte_cfc2_7();
                        __asm__ volatile("ctc2 $t4, $0");
                        __asm__ volatile("ctc2 $t5, $1");
                        __asm__ volatile("ctc2 $t4, $2");
                        __asm__ volatile("ctc2 $t5, $3");
                        __asm__ volatile("ctc2 $t6, $4");
                    }
                    goto block_106;
                case 0x10:
                    var_a2 = 0;
                    goto block_52;
                case 0x2C:
                case 0x34:
                case 0x38:
                case 0x3C:
                case 0x30:
                case 0x20:
                case 0x24:
                case 0x28:
                    goto block_51;
                case 0xEC:
                    (*(s32 *)((u8 *)(&D_800E5358)+(0))) = (s32) -(*(s16 *)((u8 *)(var_s1)+(8)));
                    (*(s32 *)((u8 *)(&D_800E5358)+(4))) = (s32) -(*(s16 *)((u8 *)(var_s1)+(0xA)));
                    (*(s32 *)((u8 *)(&D_800E5358)+(8))) = (s32) -(*(s16 *)((u8 *)(var_s1)+(0xC)));
                    (*(s32 *)((u8 *)(&D_800E5368)+(0))) = (s32) (*(s16 *)((u8 *)(var_s1)+(0x10)));
                    (*(s32 *)((u8 *)(&D_800E5368)+(4))) = (s32) (*(s16 *)((u8 *)(var_s1)+(0x12)));
                    (*(s32 *)((u8 *)(&D_800E5368)+(8))) = (s32) (*(s16 *)((u8 *)(var_s1)+(0x14)));
                    __asm__ volatile("mtc2 $s0, $9");
                    __asm__ volatile("mtc2 $t0, $10");
                    __asm__ volatile("mtc2 $t1, $11");
                    __asm__ volatile(".word 0x4AA00428");
                    gte_mfc2_25();
                    gte_mfc2_26();
                    gte_mfc2_27();
                    __asm__ volatile("mtc2 $a1, $30");
                    temp_v0_8 = gte_mfc2_31() & ~1;
                    temp_a2 = (s32) (0x1F - temp_v0_8) >> 1;
                    if ((temp_v0_8 - 0x18) < 0) {
                    }
                    __asm__ volatile("mtc2 $v0, $8");
                    __asm__ volatile("mtc2 $s0, $9");
                    __asm__ volatile("mtc2 $t0, $10");
                    __asm__ volatile("mtc2 $t1, $11");
                    __asm__ volatile(".word 0x4B90003D");
                    (*(s32 *)((u8 *)(&stack.spC8)+(0))) = (s32) ((s32) gte_mfc2_25() >> temp_a2);
                    (*(s32 *)((u8 *)(&stack.spC8)+(4))) = (s32) ((s32) gte_mfc2_26() >> temp_a2);
                    (*(s32 *)((u8 *)(&stack.spC8)+(8))) = (s32) ((s32) gte_mfc2_27() >> temp_a2);
                    __asm__ volatile("ctc2 $t4, $0");
                    __asm__ volatile("ctc2 $t5, $2");
                    __asm__ volatile("ctc2 $t6, $4");
                    __asm__ volatile("lwc2 $11, 0x8($v0)");
                    __asm__ volatile("lwc2 $9, ($v0)");
                    __asm__ volatile("lwc2 $10, 0x4($v0)");
                    __asm__ volatile(".word 0x4B78000C");
                    __asm__ volatile("swc2 $25, ($s6)");
                    __asm__ volatile("swc2 $26, 0x4($s6)");
                    __asm__ volatile("swc2 $27, 0x8($s6)");
                    __asm__ volatile("mtc2 $s0, $9");
                    __asm__ volatile("mtc2 $t0, $10");
                    __asm__ volatile("mtc2 $t1, $11");
                    __asm__ volatile(".word 0x4AA00428");
                    gte_mfc2_25();
                    gte_mfc2_26();
                    gte_mfc2_27();
                    __asm__ volatile("mtc2 $a1, $30");
                    temp_v0_9 = gte_mfc2_31() & ~1;
                    temp_a2_2 = (s32) (0x1F - temp_v0_9) >> 1;
                    if ((temp_v0_9 - 0x18) < 0) {
                    }
                    __asm__ volatile("mtc2 $v0, $8");
                    __asm__ volatile("mtc2 $s0, $9");
                    __asm__ volatile("mtc2 $t0, $10");
                    __asm__ volatile("mtc2 $t1, $11");
                    __asm__ volatile(".word 0x4B90003D");
                    (*(s32 *)((u8 *)(stack.sp110)+(0))) = (s32) ((s32) gte_mfc2_25() >> temp_a2_2);
                    (*(s32 *)((u8 *)(stack.sp110)+(4))) = (s32) ((s32) gte_mfc2_26() >> temp_a2_2);
                    (*(s32 *)((u8 *)(stack.sp110)+(8))) = (s32) ((s32) gte_mfc2_27() >> temp_a2_2);
                    __asm__ volatile("ctc2 $t4, $0");
                    __asm__ volatile("ctc2 $t5, $2");
                    __asm__ volatile("ctc2 $t6, $4");
                    __asm__ volatile("lwc2 $11, 0x8($t9)");
                    __asm__ volatile("lwc2 $9, ($t9)");
                    __asm__ volatile("lwc2 $10, 0x4($t9)");
                    __asm__ volatile(".word 0x4B78000C");
                    __asm__ volatile("swc2 $25, ($v0)");
                    __asm__ volatile("swc2 $26, 0x4($v0)");
                    __asm__ volatile("swc2 $27, 0x8($v0)");
                    (*(s32 *)((u8 *)(&D_800E5378)+(0))) = (s32) (((*(s32 *)((u8 *)(&stack.spB8)+(0))) << 0x10) | ((*(s32 *)((u8 *)(stack.sp110)+(0))) & 0xFFFF));
                    (*(s32 *)((u8 *)(&D_800E5378)+(8))) = (s32) (((*(s32 *)((u8 *)(&stack.spC8)+(4))) << 0x10) | ((*(s32 *)((u8 *)(&stack.spB8)+(4))) & 0xFFFF));
                    (*(s16 *)((u8 *)(&D_800E5378)+(0x10))) = (s16) (*(s32 *)((u8 *)(&stack.spC8)+(8)));
                    (*(s32 *)((u8 *)(&D_800E5378)+(4))) = (s32) (((*(s32 *)((u8 *)(stack.sp110)+(4))) << 0x10) | ((*(s32 *)((u8 *)(&stack.spC8)+(0))) & 0xFFFF));
                    (*(s32 *)((u8 *)(&D_800E5378)+(0xC))) = (s32) (((*(s32 *)((u8 *)(&stack.spB8)+(8))) << 0x10) | ((*(s32 *)((u8 *)(stack.sp110)+(8))) & 0xFFFF));
                    __asm__ volatile("ctc2 $t4, $0");
                    __asm__ volatile("ctc2 $t5, $1");
                    __asm__ volatile("ctc2 $t4, $2");
                    __asm__ volatile("ctc2 $t5, $3");
                    __asm__ volatile("ctc2 $t6, $4");
                    __asm__ volatile("mtc2 $t4, $9");
                    __asm__ volatile("mtc2 $t5, $10");
                    __asm__ volatile("mtc2 $t6, $11");
                    __asm__ volatile(".word 0x4A49E012");
                    (*(s32 *)((u8 *)(&D_800E5378)+(0))) = (s16) gte_mfc2_9();
                    (*(u16 *)((u8 *)(&D_800E5378)+(6))) = (u16) gte_mfc2_10();
                    (*(s32 *)((u8 *)(&D_800E5378)+(0xC))) = (s16) gte_mfc2_11();
                    __asm__ volatile("mtc2 $t4, $9");
                    __asm__ volatile("mtc2 $t5, $10");
                    __asm__ volatile("mtc2 $t6, $11");
                    __asm__ volatile(".word 0x4A49E012");
                    temp_a3 = &D_800E5378 + 2;
                    (*(u16 *)((u8 *)(&D_800E5378)+(2))) = (u16) gte_mfc2_9();
                    (*(s16 *)((u8 *)(temp_a3)+(6))) = (s16) gte_mfc2_10();
                    (*(s16 *)((u8 *)(temp_a3)+(0xC))) = (s16) gte_mfc2_11();
                    __asm__ volatile("mtc2 $t4, $9");
                    __asm__ volatile("mtc2 $t5, $10");
                    __asm__ volatile("mtc2 $t6, $11");
                    __asm__ volatile(".word 0x4A49E012");
                    (*(u16 *)((u8 *)(&D_800E537C)+(0))) = (u16) gte_mfc2_9();
                    (*(u16 *)((u8 *)(&D_800E537C)+(6))) = (u16) gte_mfc2_10();
                    (*(u16 *)((u8 *)(&D_800E537C)+(0xC))) = (u16) gte_mfc2_11();
                    D_800E5374 = &D_800E5378;
                    goto block_105;
                case 0xF4:
                    __asm__ volatile("ctc2 $t4, $0");
                    __asm__ volatile("ctc2 $t5, $1");
                    __asm__ volatile("ctc2 $t4, $2");
                    __asm__ volatile("ctc2 $t5, $3");
                    __asm__ volatile("ctc2 $t6, $4");
                    __asm__ volatile("mtc2 $t4, $9");
                    __asm__ volatile("mtc2 $t5, $10");
                    __asm__ volatile("mtc2 $t6, $11");
                    __asm__ volatile(".word 0x4A49E012");
                    (*(s32 *)((u8 *)(&D_800E5378)+(0))) = (s16) gte_mfc2_9();
                    (*(u16 *)((u8 *)(&D_800E5378)+(6))) = (u16) gte_mfc2_10();
                    (*(s32 *)((u8 *)(&D_800E5378)+(0xC))) = (s16) gte_mfc2_11();
                    __asm__ volatile("mtc2 $t4, $9");
                    __asm__ volatile("mtc2 $t5, $10");
                    __asm__ volatile("mtc2 $t6, $11");
                    __asm__ volatile(".word 0x4A49E012");
                    temp_t8 = &D_800E5378 + 2;
                    (*(u16 *)((u8 *)(&D_800E5378)+(2))) = (u16) gte_mfc2_9();
                    (*(s16 *)((u8 *)(temp_t8)+(6))) = (s16) gte_mfc2_10();
                    (*(s16 *)((u8 *)(temp_t8)+(0xC))) = (s16) gte_mfc2_11();
                    __asm__ volatile("mtc2 $t4, $9");
                    __asm__ volatile("mtc2 $t5, $10");
                    __asm__ volatile("mtc2 $t6, $11");
                    __asm__ volatile(".word 0x4A49E012");
                    (*(u16 *)((u8 *)(&D_800E537C)+(0))) = (u16) gte_mfc2_9();
                    (*(u16 *)((u8 *)(&D_800E537C)+(6))) = (u16) gte_mfc2_10();
                    (*(u16 *)((u8 *)(&D_800E537C)+(0xC))) = (u16) gte_mfc2_11();
                    D_800E5374 = &D_800E5378;
                    goto block_105;
                case 0xF8:
                    temp_v1_4 = (s32) (*(s16 *)((u8 *)(var_s1)+(0xC)));
                    if (temp_v1_4 & 0x11) {
                        (*(s16 *)((u8 *)(var_s1)+(0xC))) = (s32) (temp_v1_4 & ~0x10);
                        var_s3 = func_80068EE8(((*(u8 *)((u8 *)(var_s1)+(0))) - 4) * 4);
                        if (var_s3 != ((void *)0)) {
                            stack.spE0 = var_s1 + 0x10;
                            var_a2_2 = 4;
                            var_v1 = var_s3 + 0x10;
                            if ((s32) (*(u8 *)((u8 *)(var_s1)+(0))) > 4) {
                                var_a0 = var_s1 + 0x20;
                                do {
                                    temp_v0_10 = (*(s32 *)((u8 *)(var_a0)+(-0x10)));
                                    var_a0 += 4;
                                    var_a2_2 += 1;
                                    (*(s32 *)((u8 *)(var_v1)+(-0x10))) = temp_v0_10;
                                    var_v1 += 4;
                                } while (var_a2_2 < (s32) (*(u8 *)((u8 *)(var_s1)+(0))));
                            }
                            temp_v1_5 = (s32) (*(s16 *)((u8 *)(var_s1)+(8)));
                            stack.spD8 = temp_v1_5;
                            if (temp_v1_5 == -1) {
                                *var_s3 = (*var_s3 & high_mask) | ((*(s32 *)((u8 *)(arg0)+(4))) & (u32)state_or_mask);
                                (*(s32 *)((u8 *)(arg0)+(4))) = (s32) (((*(s32 *)((u8 *)(arg0)+(4))) & high_mask) | ((s32) var_s3 & (u32)state_or_mask));
                                goto block_105;
                            }
                            if (temp_v1_5 <= 0) {
                                var_v0_4 = 1;
                                goto block_72;
                            }
                            var_v0_4 = 0xFFF;
                            if (temp_v1_5 >= 0x1000) {
block_72:
                                stack.spD8 = var_v0_4;
                            }
                            if ((s32) (*(s16 *)((u8 *)(var_s1)+(0xC))) & 0x20) {
                                var_s3 = func_80068EE8(0xC);
                                if (var_s3 != ((void *)0)) {
                                    (*(u8 *)((u8 *)(var_s3)+(3))) = 2;
                                    (*(s32 *)((u8 *)(var_s3)+(4))) = (s32) (0xE5000000 | (((*(s16 *)((u8 *)(&stack.spA0)+(2))) & 0x7FF) << 0xB) | ((*(s16 *)((u8 *)(&stack.spA0)+(0))) & 0x7FF));
                                    (*(s32 *)((u8 *)(var_s3)+(8))) = 0;
                                    temp_a0 = (stack.spD8 * 4) + arg0;
                                    *var_s3 = (*var_s3 & high_mask) | (*temp_a0 & (u32)state_or_mask);
                                    *temp_a0 = (*temp_a0 & high_mask) | ((s32)var_s3 & (u32)state_or_mask);
                                    goto block_76;
                                }
                            } else {
block_76:
                                temp_a0_2 = (stack.spD8 * 4) + arg0;
                                *var_s3 = (*var_s3 & high_mask) | (*temp_a0_2 & (u32)state_or_mask);
                                *temp_a0_2 = (*temp_a0_2 & high_mask) | ((s32) var_s3 & (u32)state_or_mask);
                                if ((s32) (*(s16 *)((u8 *)(var_s1)+(0xC))) & 0x40) {
                                    var_s3 = func_80068EE8(0xC);
                                    if (var_s3 != ((void *)0)) {
                                        (*(u8 *)((u8 *)(var_s3)+(3))) = 2;
                                        (*(s32 *)((u8 *)(var_s3)+(4))) = (s32) (0xE5000000 | (((*(s16 *)((u8 *)(&stack.sp98)+(2))) & 0x7FF) << 0xB) | ((*(s16 *)((u8 *)(&stack.sp98)+(0))) & 0x7FF));
                                        (*(s32 *)((u8 *)(var_s3)+(8))) = 0;
                                        temp_a0_3 = (stack.spD8 * 4) + arg0;
                                        *var_s3 = (*var_s3 & high_mask) | (*temp_a0_3 & (u32)state_or_mask);
                                        *temp_a0_3 = (*temp_a0_3 & high_mask) | ((s32)var_s3 & (u32)state_or_mask);
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
                    break;
                }
            } else {
                temp_v1_6 = (*(u8 *)((u8 *)(var_s1)+(7))) & 0xFC;
                switch (temp_v1_6) {
                case 0x50:
                    var_s0 = var_s1 + 0x24;
block_93:
                    temp_v0_11 = var_s5 << 5;
                    var_s5 += 1;
                    temp_v0_12 = temp_v0_11 + D_800E53E8;
                    (*(s32 *)((u8 *)(temp_v0_12)+(0))) = (s32) gte_cfc2_0();
                    (*(s32 *)((u8 *)(temp_v0_12)+(4))) = (s32) gte_cfc2_1();
                    (*(s32 *)((u8 *)(temp_v0_12)+(8))) = (s32) gte_cfc2_2();
                    (*(s32 *)((u8 *)(temp_v0_12)+(0xC))) = (s32) gte_cfc2_3();
                    (*(s32 *)((u8 *)(temp_v0_12)+(0x10))) = (s32) gte_cfc2_4();
                    (*(s32 *)((u8 *)(temp_v0_12)+(0x14))) = (s32) gte_cfc2_5();
                    (*(s32 *)((u8 *)(temp_v0_12)+(0x18))) = (s32) gte_cfc2_6();
                    (*(s32 *)((u8 *)(temp_v0_12)+(0x1C))) = (s32) gte_cfc2_7();
                    temp_v0_13 = temp_v0_12 + 0x14;
                    (*(s32 *)((u8 *)(temp_v0_12)+(0x14))) = (s32) gte_cfc2_5();
                    (*(s32 *)((u8 *)(temp_v0_13)+(4))) = (s32) gte_cfc2_6();
                    (*(s32 *)((u8 *)(temp_v0_13)+(8))) = (s32) gte_cfc2_7();
                    var_s4 = (*(u8 *)((u8 *)(var_s1)+(2)));
loop_94:
                    if (((s32) var_s4 > 0) && (var_s5 < 0x200)) {
                        func_80065710(&stack.sp10, var_s0 + 8, &stack.sp20);
                        temp_v0_14 = var_s5 << 5;
                        var_s5 += 1;
                        temp_v0_15 = temp_v0_14 + D_800E53E8;
                        (*(s32 *)((u8 *)(temp_v0_15)+(0))) = (s32) gte_cfc2_0();
                        (*(s32 *)((u8 *)(temp_v0_15)+(4))) = (s32) gte_cfc2_1();
                        (*(s32 *)((u8 *)(temp_v0_15)+(8))) = (s32) gte_cfc2_2();
                        (*(s32 *)((u8 *)(temp_v0_15)+(0xC))) = (s32) gte_cfc2_3();
                        (*(s32 *)((u8 *)(temp_v0_15)+(0x10))) = (s32) gte_cfc2_4();
                        (*(s32 *)((u8 *)(temp_v0_15)+(0x14))) = (s32) gte_cfc2_5();
                        (*(s32 *)((u8 *)(temp_v0_15)+(0x18))) = (s32) gte_cfc2_6();
                        (*(s32 *)((u8 *)(temp_v0_15)+(0x1C))) = (s32) gte_cfc2_7();
                        temp_v0_16 = temp_v0_15 + 0x14;
                        (*(s32 *)((u8 *)(temp_v0_15)+(0x14))) = (s32) gte_cfc2_5();
                        (*(s32 *)((u8 *)(temp_v0_16)+(4))) = (s32) gte_cfc2_6();
                        (*(s32 *)((u8 *)(temp_v0_16)+(8))) = (s32) gte_cfc2_7();
                        var_s0 += *var_s0 * 4;
                        var_s4 -= 1;
                        goto loop_94;
                    }
                    break;
                case 0x40:
                    var_s0 = var_s1 + 0x20;
                    goto block_93;
                case 0x3C:
                    var_s0_2 = var_s1 + 0x2C;
block_101:
                    D_800E53BC(&stack.sp68, &D_800E53C8, (*(s16 *)((u8 *)(var_s1)+(0x16))));
                    temp_v0_17 = var_s5 << 5;
                    var_s5 += 1;
                    temp_v0_18 = temp_v0_17 + D_800E53E8;
                    (*(s32 *)((u8 *)(temp_v0_18)+(0))) = (s32) gte_cfc2_0();
                    (*(s32 *)((u8 *)(temp_v0_18)+(4))) = (s32) gte_cfc2_1();
                    (*(s32 *)((u8 *)(temp_v0_18)+(8))) = (s32) gte_cfc2_2();
                    (*(s32 *)((u8 *)(temp_v0_18)+(0xC))) = (s32) gte_cfc2_3();
                    (*(s32 *)((u8 *)(temp_v0_18)+(0x10))) = (s32) gte_cfc2_4();
                    (*(s32 *)((u8 *)(temp_v0_18)+(0x14))) = (s32) gte_cfc2_5();
                    (*(s32 *)((u8 *)(temp_v0_18)+(0x18))) = (s32) gte_cfc2_6();
                    (*(s32 *)((u8 *)(temp_v0_18)+(0x1C))) = (s32) gte_cfc2_7();
                    temp_v0_19 = temp_v0_18 + 0x14;
                    (*(s32 *)((u8 *)(temp_v0_18)+(0x14))) = (s32) gte_cfc2_5();
                    (*(s32 *)((u8 *)(temp_v0_19)+(4))) = (s32) gte_cfc2_6();
                    (*(s32 *)((u8 *)(temp_v0_19)+(8))) = (s32) gte_cfc2_7();
                    __asm__ volatile("ctc2 $t4, $0");
                    __asm__ volatile("ctc2 $t5, $1");
                    __asm__ volatile("ctc2 $t4, $2");
                    __asm__ volatile("ctc2 $t5, $3");
                    __asm__ volatile("ctc2 $t6, $4");
                    var_s4_2 = (*(u8 *)((u8 *)(var_s1)+(2)));
                    if ((s32) var_s4_2 > 0) {
                        var_v0_5 = var_s5 < 0x200;
loop_103:
                        if (var_v0_5 != 0) {
                            func_80065710(&stack.sp10, var_s0_2 + 8, &stack.sp20);
                            D_800E53BC(&stack.sp68, &D_800E53C8, (*(s16 *)((u8 *)(var_s0_2)+(0x16))));
                            temp_v0_20 = var_s5 << 5;
                            var_s5 += 1;
                            temp_v0_21 = temp_v0_20 + D_800E53E8;
                            (*(s32 *)((u8 *)(temp_v0_21)+(0))) = (s32) gte_cfc2_0();
                            (*(s32 *)((u8 *)(temp_v0_21)+(4))) = (s32) gte_cfc2_1();
                            (*(s32 *)((u8 *)(temp_v0_21)+(8))) = (s32) gte_cfc2_2();
                            (*(s32 *)((u8 *)(temp_v0_21)+(0xC))) = (s32) gte_cfc2_3();
                            (*(s32 *)((u8 *)(temp_v0_21)+(0x10))) = (s32) gte_cfc2_4();
                            (*(s32 *)((u8 *)(temp_v0_21)+(0x14))) = (s32) gte_cfc2_5();
                            (*(s32 *)((u8 *)(temp_v0_21)+(0x18))) = (s32) gte_cfc2_6();
                            (*(s32 *)((u8 *)(temp_v0_21)+(0x1C))) = (s32) gte_cfc2_7();
                            temp_v0_22 = temp_v0_21 + 0x14;
                            (*(s32 *)((u8 *)(temp_v0_21)+(0x14))) = (s32) gte_cfc2_5();
                            (*(s32 *)((u8 *)(temp_v0_22)+(4))) = (s32) gte_cfc2_6();
                            (*(s32 *)((u8 *)(temp_v0_22)+(8))) = (s32) gte_cfc2_7();
                            var_s0_2 += (*(u8 *)((u8 *)(var_s0_2)+(0))) * 4;
                            __asm__ volatile("ctc2 $t4, $0");
                            __asm__ volatile("ctc2 $t5, $1");
                            __asm__ volatile("ctc2 $t4, $2");
                            __asm__ volatile("ctc2 $t5, $3");
                            __asm__ volatile("ctc2 $t6, $4");
                            var_s4_2 -= 1;
                            var_v0_5 = var_s5 < 0x200;
                            if ((s32) var_s4_2 > 0) {
                                goto loop_103;
                            }
                        }
block_105:
                    }
                    break;
                case 0x2C:
                    var_s0_2 = var_s1 + 0x20;
                    goto block_101;
                case 0x38:
                    var_s0_2 = var_s1 + 0x28;
                    goto block_101;
                case 0x28:
                    var_s0_2 = var_s1 + 0x1C;
                    goto block_101;
                }
block_106:
                var_s1 += (*(u8 *)((u8 *)(var_s1)+(0))) * 4;
                var_v0 = var_s5 < 0x200;
                if (var_s1 == D_800AD9F0) {
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
            stack.sp100 = &stack.sp58;
loop_109:
            if (var_s5_2 < stack.spFC) {
                if ((*(u8 *)((u8 *)(var_s1_2)+(2))) == 0) {
                    if ((u8) (*(u8 *)((u8 *)(var_s1_2)+(7))) < 0xECU) {
                        temp_v0_23 = ((*(u8 *)((u8 *)(var_s1_2)+(3))) + 1) * 4;
                        stack.spE4 = temp_v0_23;
                        var_s3 = func_80068EE8(temp_v0_23);
                        if (var_s3 != ((void *)0)) {
                            temp_s2 = (*(u16 *)((u8 *)(var_s1_2)+(0x14))) & 0x60;
                            stack.spF0 = temp_s2;
                            if ((*(u8 *)((u8 *)(var_s1_2)+(7))) & 4) {
                                temp_v0_24 = (*(void **)((u8 *)(var_s1_2)+(0x1C)));
                                stack.spE0 = var_s3;
                                (*(u16 *)((u8 *)(var_s3)+(0xE))) = (u16) (*(u16 *)((u8 *)(temp_v0_24)+(2)));
                                stack.spF0 = temp_s2 | ((*(u16 *)((u8 *)(temp_v0_24)+(0))) & 0xFF9F);
                                (*(u8 *)((u8 *)(var_s3)+(3))) = (u8) (*(u8 *)((u8 *)(var_s1_2)+(3)));
                                stack.spF8 = (*(void **)((u8 *)(var_s1_2)+(0x1C)));
                                goto block_118;
                            }
                            temp_s0 = var_s3;
                            stack.spE0 = var_s3;
                            var_s3 += 8;
                            stack.spE4 += 8;
                            if (func_80068EE8(8) != ((void *)0)) {
                                (*(u8 *)((u8 *)(var_s3)+(3))) = (u8) (*(u8 *)((u8 *)(var_s1_2)+(3)));
                                (*(u8 *)((u8 *)(temp_s0)+(3))) = 1U;
                                (*(s32 *)((u8 *)(temp_s0)+(4))) = (s32) (temp_s2 | 0xE1000200);
                                temp_t3 = (*(u8 *)((u8 *)(var_s3)+(3))) + (*(u8 *)((u8 *)(temp_s0)+(3))) + 1;
                                if (temp_t3 < 0xB) {
                                    (*(u8 *)((u8 *)(temp_s0)+(3))) = (u8) temp_t3;
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
                        if (temp_v1_7 != 0x10) {
                            var_t2 = 0;
                            if (temp_v1_7 >= 0x11) {
                                if (temp_v1_7 != 0x20) {
                                    var_fp = 2;
                                    if (temp_v1_7 != 0x40) {
                                        goto block_123;
                                    }
                                    goto block_126;
                                }
                                var_fp = 2;
                                goto block_126;
                            }
block_123:
                            var_fp = 1;
                            var_s7 = 2;
                        } else {
                            var_t2 = 2;
                            var_fp = 0;
block_126:
                            var_s7 = 1;
                        }
                        stack.spD8 = 0;
                        stack.sp110 = (M2C_UNK *)3;
                        temp_t3_2 = (((*(u8 *)((u8 *)(var_s1_2)+(1))) & 0xF) << 5) + &D_800ADA08;
                        temp_v1_8 = (*(u8 *)((u8 *)(var_s1_2)+(7))) & ~3;
                        switch (temp_v1_8) {
                        case 0x50:
                            stack.sp110 = (M2C_UNK *)4;
                            (*(void **)((u8 *)(var_s3)+(0xC))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x20)));
                        case 0x40:
                            __asm__ volatile("ctc2 $t4, $0");
                            __asm__ volatile("ctc2 $t5, $1");
                            __asm__ volatile("ctc2 $t4, $2");
                            __asm__ volatile("ctc2 $t5, $3");
                            __asm__ volatile("ctc2 $t6, $4");
                            __asm__ volatile("ctc2 $t4, $5");
                            __asm__ volatile("ctc2 $t5, $6");
                            __asm__ volatile("ctc2 $t6, $7");
                            __asm__ volatile("mtc2 $zero, $0");
                            __asm__ volatile("mtc2 $zero, $1");
                            __asm__ volatile(".word 0x4A180001");
                            __asm__ volatile("swc2 $14, ($v0)");
                            __asm__ volatile("swc2 $19, ($t9)");
                            __asm__ volatile("ctc2 $t4, $0");
                            __asm__ volatile("ctc2 $t5, $1");
                            __asm__ volatile("ctc2 $t4, $2");
                            __asm__ volatile("ctc2 $t5, $3");
                            __asm__ volatile("ctc2 $t6, $4");
                            __asm__ volatile("ctc2 $t4, $5");
                            __asm__ volatile("ctc2 $t5, $6");
                            __asm__ volatile("ctc2 $t6, $7");
                            var_s5_2 = var_s5_2 + 1 + 1;
                            __asm__ volatile("lwc2 $0, ($v0)");
                            __asm__ volatile("lwc2 $1, 0x4($v0)");
                            __asm__ volatile(".word 0x4A180001");
                            __asm__ volatile("swc2 $14, ($v0)");
                            __asm__ volatile("swc2 $19, ($v0)");
block_150:
                            stack.spD8 = (s32) (stack.sp58 + stack.sp5C) >> 1;
                            break;
                        case 0x48:
                        case 0x4C:
                        case 0x58:
                        case 0x5C:
                            (*(void **)((u8 *)(var_s3)+(0x14))) = (void *)0x55555555;
                            break;
                        case 0x34:
                            (*(void **)((u8 *)(var_s3)+(0x10))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x20)));
                            (*(void **)((u8 *)(var_s3)+(0x1C))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x24)));
                            (*(u16 *)((u8 *)(var_s3)+(0x18))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(6)));
                            (*(u16 *)((u8 *)(var_s3)+(0x1A))) = stack.spF0;
                            (*(u16 *)((u8 *)(var_s3)+(0x24))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(8)));
block_135:
                            (*(u16 *)((u8 *)(var_s3)+(0xC))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(4)));
                        case 0x20:
block_136:
                            var_a2_3 = 0;
                            var_a1 = &D_800ADB58;
                            var_a0_2 = temp_t3_2;
                            do {
                                temp_v1_9 = (*(s16 *)((u8 *)(var_a0_2)+(0)));
                                temp_v0_25 = (*(s16 *)((u8 *)(var_s1_2)+(0x18)));
                                stack.sp88[0] = (mult_hi(temp_v1_9, temp_v0_25) << 0x14) | ((u32) (temp_v1_9 * temp_v0_25) >> 0xC);
                                temp_v1_10 = (*(s16 *)((u8 *)(var_a0_2)+(2)));
                                temp_v0_26 = (*(s16 *)((u8 *)(var_s1_2)+(0x1A)));
                                stack.sp8C = (mult_hi(temp_v1_10, temp_v0_26) << 0x14) | ((u32) (temp_v1_10 * temp_v0_26) >> 0xC);
                                stack.sp90 = (s32) (*(s16 *)((u8 *)(var_a0_2)+(4)));
                                (*(u16 *)((u8 *)(var_a1)+(0))) = (u16) (&stack.sp88[0])[var_t2];
                                (*(u16 *)((u8 *)(var_a1)+(2))) = (u16) (&stack.sp88[0])[var_fp];
                                (*(u16 *)((u8 *)(var_a1)+(4))) = (u16) (&stack.sp88[0])[var_s7];
                                var_a1 += 8;
                                var_a2_3 += 1;
                                var_a0_2 += 8;
                            } while (var_a2_3 < 3);
                            __asm__ volatile("ctc2 $t4, $0");
                            __asm__ volatile("ctc2 $t5, $1");
                            __asm__ volatile("ctc2 $t4, $2");
                            __asm__ volatile("ctc2 $t5, $3");
                            __asm__ volatile("ctc2 $t6, $4");
                            __asm__ volatile("ctc2 $t4, $5");
                            __asm__ volatile("ctc2 $t5, $6");
                            __asm__ volatile("ctc2 $t6, $7");
                            var_s5_2 += 1;
                            __asm__ volatile("lwc2 $0, ($t8)");
                            __asm__ volatile("lwc2 $1, 0x4($t8)");
                            __asm__ volatile("lwc2 $2, 0x8($t8)");
                            __asm__ volatile("lwc2 $3, 0xc($t8)");
                            __asm__ volatile("lwc2 $4, 0x10($t8)");
                            __asm__ volatile("lwc2 $5, 0x14($t8)");
                            __asm__ volatile(".word 0x4A280030");
                            __asm__ volatile("swc2 $12, 0x8($s3)");
                            temp_v1_11 = (*(u8 *)((u8 *)(var_s1_2)+(7))) & ~3;
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
                            __asm__ volatile("swc2 $17, ($a3)");
                            __asm__ volatile("swc2 $18, 0x4($a3)");
                            __asm__ volatile("swc2 $19, 0x8($a3)");
                            goto block_150;
                        case 0x30:
                            (*(void **)((u8 *)(var_s3)+(0xC))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x1C)));
                            (*(void **)((u8 *)(var_s3)+(0x14))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x20)));
                            goto block_136;
                        case 0x24:
                            (*(u16 *)((u8 *)(var_s3)+(0x14))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(6)));
                            (*(u16 *)((u8 *)(var_s3)+(0x16))) = stack.spF0;
                            (*(u16 *)((u8 *)(var_s3)+(0x1C))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(8)));
                            goto block_135;
                        case 0x38:
                            (*(void **)((u8 *)(var_s3)+(0xC))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x1C)));
                            (*(void **)((u8 *)(var_s3)+(0x14))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x20)));
                            (*(void **)((u8 *)(var_s3)+(0x1C))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x24)));
                        case 0x28:
block_155:
                            var_a2_4 = 0;
                            var_a1_2 = &D_800ADB58;
                            var_a0_3 = temp_t3_2;
                            do {
                                temp_v1_12 = (*(s16 *)((u8 *)(var_a0_3)+(0)));
                                temp_v0_27 = (*(s16 *)((u8 *)(var_s1_2)+(0x18)));
                                stack.sp88[0] = (mult_hi(temp_v1_12, temp_v0_27) << 0x14) | ((u32) (temp_v1_12 * temp_v0_27) >> 0xC);
                                temp_v1_13 = (*(s16 *)((u8 *)(var_a0_3)+(2)));
                                temp_v0_28 = (*(s16 *)((u8 *)(var_s1_2)+(0x1A)));
                                stack.sp8C = (mult_hi(temp_v1_13, temp_v0_28) << 0x14) | ((u32) (temp_v1_13 * temp_v0_28) >> 0xC);
                                stack.sp90 = (s32) (*(s16 *)((u8 *)(var_a0_3)+(4)));
                                (*(u16 *)((u8 *)(var_a1_2)+(0))) = (u16) (&stack.sp88[0])[var_t2];
                                (*(u16 *)((u8 *)(var_a1_2)+(2))) = (u16) (&stack.sp88[0])[var_fp];
                                (*(u16 *)((u8 *)(var_a1_2)+(4))) = (u16) (&stack.sp88[0])[var_s7];
                                var_a1_2 += 8;
                                var_a2_4 += 1;
                                var_a0_3 += 8;
                            } while (var_a2_4 < 4);
                            __asm__ volatile("ctc2 $t4, $0");
                            __asm__ volatile("ctc2 $t5, $1");
                            __asm__ volatile("ctc2 $t4, $2");
                            __asm__ volatile("ctc2 $t5, $3");
                            __asm__ volatile("ctc2 $t6, $4");
                            __asm__ volatile("ctc2 $t4, $5");
                            __asm__ volatile("ctc2 $t5, $6");
                            __asm__ volatile("ctc2 $t6, $7");
                            var_s5_2 += 1;
                            __asm__ volatile("lwc2 $0, 0x8($t8)");
                            __asm__ volatile("lwc2 $1, 0xc($t8)");
                            __asm__ volatile("lwc2 $2, 0x10($t8)");
                            __asm__ volatile("lwc2 $3, 0x14($t8)");
                            __asm__ volatile("lwc2 $4, 0x18($t8)");
                            __asm__ volatile("lwc2 $5, 0x1c($t8)");
                            __asm__ volatile(".word 0x4A280030");
                            temp_v1_14 = (*(u8 *)((u8 *)(var_s1_2)+(7))) & ~3;
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
                            __asm__ volatile("swc2 $17, 0x4($a3)");
                            __asm__ volatile("swc2 $18, 0x8($a3)");
                            __asm__ volatile("swc2 $19, 0xc($a3)");
                            __asm__ volatile("lwc2 $0, ($s6)");
                            __asm__ volatile("lwc2 $1, 0x4($s6)");
                            __asm__ volatile(".word 0x4A180001");
                            __asm__ volatile("swc2 $14, ($v0)");
                            __asm__ volatile("swc2 $19, ($a3)");
                            stack.spD8 = (s32) (stack.sp58 + stack.sp5C + stack.sp60 + stack.sp64) >> 2;
                            break;
                        case 0x3C:
                            (*(void **)((u8 *)(var_s3)+(0x10))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x20)));
                            (*(void **)((u8 *)(var_s3)+(0x1C))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x24)));
                            (*(void **)((u8 *)(var_s3)+(0x28))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x28)));
                            (*(u16 *)((u8 *)(var_s3)+(0x18))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(6)));
                            (*(u16 *)((u8 *)(var_s3)+(0x24))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(8)));
                            (*(u16 *)((u8 *)(var_s3)+(0x1A))) = stack.spF0;
                            (*(u16 *)((u8 *)(var_s3)+(0x30))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(0xA)));
block_154:
                            (*(u16 *)((u8 *)(var_s3)+(0xC))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(4)));
                            goto block_155;
                        case 0x2C:
                            (*(u16 *)((u8 *)(var_s3)+(0x14))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(6)));
                            (*(u16 *)((u8 *)(var_s3)+(0x1C))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(8)));
                            (*(u16 *)((u8 *)(var_s3)+(0x16))) = stack.spF0;
                            (*(u16 *)((u8 *)(var_s3)+(0x24))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(0xA)));
                            goto block_154;
                        case 0xE8:
                            (*(void **)((u8 *)(var_s3)+(0xC))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x28)));
                            (*(void **)((u8 *)(var_s3)+(0x14))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x2C)));
                            (*(s8 *)((u8 *)(var_s3)+(7))) = 0x38;
                            (*(void **)((u8 *)(var_s3)+(0x1C))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x30)));
block_173:
                            __asm__ volatile("ctc2 $t4, $0");
                            __asm__ volatile("ctc2 $t5, $1");
                            __asm__ volatile("ctc2 $t4, $2");
                            __asm__ volatile("ctc2 $t5, $3");
                            __asm__ volatile("ctc2 $t6, $4");
                            __asm__ volatile("ctc2 $t4, $5");
                            __asm__ volatile("ctc2 $t5, $6");
                            __asm__ volatile("ctc2 $t6, $7");
                            var_s5_2 += 1;
                            __asm__ volatile("mtc2 $zero, $0");
                            __asm__ volatile("mtc2 $zero, $1");
                            __asm__ volatile(".word 0x4A180001");
                            temp_v1_15 = (*(u8 *)((u8 *)(var_s1_2)+(7))) & ~3;
                            switch (temp_v1_15) {
                            case 0xE0:
                                temp_t0 = gte_mfc2_14();
                                temp_t1 = temp_t0 >> 0x10;
                                (*(void **)((u8 *)(var_s3)+(0xC))) = (void *) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x1C))) + temp_t0) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x1E))) + temp_t1) << 0x10));
                                (*(void **)((u8 *)(var_s3)+(0x10))) = (void *) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x20))) + temp_t0) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x22))) + temp_t1) << 0x10));
                                (*(void **)((u8 *)(var_s3)+(0x14))) = (void *) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x24))) + temp_t0) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x26))) + temp_t1) << 0x10));
                                break;
                            case 0xE8:
                                temp_t0_2 = gte_mfc2_14();
                                temp_t1_2 = temp_t0_2 >> 0x10;
                                (*(void **)((u8 *)(var_s3)+(0x10))) = (void *) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x1C))) + temp_t0_2) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x1E))) + temp_t1_2) << 0x10));
                                (*(u16 *)((u8 *)(var_s3)+(0x18))) = (s32) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x20))) + temp_t0_2) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x22))) + temp_t1_2) << 0x10));
                                (*(s32 *)((u8 *)(var_s3)+(0x20))) = (s32) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x24))) + temp_t0_2) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x26))) + temp_t1_2) << 0x10));
                                break;
                            case 0xA4:
                                temp_t0_3 = gte_mfc2_14();
                                temp_t1_3 = temp_t0_3 >> 0x10;
                                (*(void **)((u8 *)(var_s3)+(0x10))) = (void *) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x20))) + temp_t0_3) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x22))) + temp_t1_3) << 0x10));
                                (*(u16 *)((u8 *)(var_s3)+(0x18))) = (s32) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x24))) + temp_t0_3) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x26))) + temp_t1_3) << 0x10));
                                (*(s32 *)((u8 *)(var_s3)+(0x20))) = (s32) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x28))) + temp_t0_3) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x2A))) + temp_t1_3) << 0x10));
                                break;
                            case 0xB4:
                                temp_t0_4 = gte_mfc2_14();
                                temp_t1_4 = temp_t0_4 >> 0x10;
                                (*(void **)((u8 *)(var_s3)+(0x14))) = (void *) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x20))) + temp_t0_4) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x22))) + temp_t1_4) << 0x10));
                                (*(s32 *)((u8 *)(var_s3)+(0x20))) = (s32) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x24))) + temp_t0_4) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x26))) + temp_t1_4) << 0x10));
                                (*(s32 *)((u8 *)(var_s3)+(0x2C))) = (s32) ((((s16) (*(void **)((u8 *)(var_s1_2)+(0x28))) + temp_t0_4) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x2A))) + temp_t1_4) << 0x10));
                                break;
                            }
                            temp_t0_5 = gte_mfc2_14();
                            __asm__ volatile("swc2 $19, ($v0)");
                            (*(s32 *)((u8 *)(var_s3)+(8))) = (s32) ((((*(s16 *)((u8 *)(var_s1_2)+(0x18))) + temp_t0_5) & 0xFFFF) | (((*(s16 *)((u8 *)(var_s1_2)+(0x1A))) + (temp_t0_5 >> 0x10)) << 0x10));
                            break;
                        case 0xB4:
                            (*(void **)((u8 *)(var_s3)+(0x10))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x28)));
                            (*(void **)((u8 *)(var_s3)+(0x1C))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x2C)));
                            (*(void **)((u8 *)(var_s3)+(0x28))) = (void *) (*(void **)((u8 *)(var_s1_2)+(0x30)));
                            (*(u16 *)((u8 *)(var_s3)+(0x18))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(6)));
                            (*(u16 *)((u8 *)(var_s3)+(0x24))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(8)));
                            (*(s8 *)((u8 *)(var_s3)+(7))) = 0x3C;
                            (*(u16 *)((u8 *)(var_s3)+(0x1A))) = stack.spF0;
                            (*(u16 *)((u8 *)(var_s3)+(0x30))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(0xA)));
block_171:
                            (*(u16 *)((u8 *)(var_s3)+(0xC))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(4)));
                            goto block_173;
                        case 0xA4:
                            (*(u16 *)((u8 *)(var_s3)+(0x14))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(6)));
                            (*(u16 *)((u8 *)(var_s3)+(0x1C))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(8)));
                            (*(s8 *)((u8 *)(var_s3)+(7))) = 0x2C;
                            (*(u16 *)((u8 *)(var_s3)+(0x16))) = stack.spF0;
                            (*(u16 *)((u8 *)(var_s3)+(0x24))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(0xA)));
                            goto block_171;
                        case 0xE0:
                            (*(s8 *)((u8 *)(var_s3)+(7))) = 0x28;
                            goto block_173;
                        case 0x10:
                            var_s5_2 = func_80068720(var_s1_2 + 0x14, var_s1_2 + 0x1C, var_s5_2, 3);
                            break;
                        case 0xF0:
                            D_800E53B8 = (*(s32 *)((u8 *)(var_s1_2)+(8)));
                            break;
                        }
                        if (stack.spD8 != 0) {
                            temp_v1_16 = (s32) (stack.spD8 - func_8008B984()) >> 3;
                            stack.spD8 = temp_v1_16;
                            temp_v1_17 = temp_v1_16 + D_800E53B8;
                            stack.spD8 = temp_v1_17;
                            if (temp_v1_17 < 2) {
                                var_v0_6 = 2;
                                goto block_192;
                            }
                            if (temp_v1_17 >= 0x1000) {
                                var_v0_6 = 0xFFF;
block_192:
                                stack.spD8 = var_v0_6;
                            }
                            stack.spDC = gte_cfc2_31();
                            if (stack.spDC >= 0) {
                                temp_a0_4 = (stack.spD8 * 4) + arg0;
                                *stack.spE0 = (*stack.spE0 & high_mask) | (*temp_a0_4 & (u32)state_or_mask);
                                *temp_a0_4 = (*temp_a0_4 & high_mask) | ((s32) stack.spE0 & (u32)state_or_mask);
                            }
                        }
                        goto block_199;
                    }
                } else {
                    temp_v0_29 = (*(u8 *)((u8 *)(var_s1_2)+(7))) & ~3;
                    switch (temp_v0_29) {
                    case 0x28:
                    case 0x2C:
                    case 0x38:
                    case 0x3C:
                    case 0x40:
                    case 0x50:
                        var_s5_2 = var_s5_2 + 1 + (*(u8 *)((u8 *)(var_s1_2)+(2)));
                        break;
                    }
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
            D_800E5374 = &stack.sp38;
            var_s1_3 = (*(void **)((u8 *)(&D_800AD9EC)+(0)));
            D_800E53B8 = -0xA;
            if (var_s1_3 != (*(s32 *)((u8 *)(&D_800AD9EC)+(4)))) {
                stack.sp104 = (u32)state_or_mask;
loop_203:
                if (var_s5_2 < stack.spFC) {
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
                                } else if (temp_v1_18 != 0xF0) {
                                    var_t9 = &D_800AD9EC;
                                } else {
                                    D_800E53B8 = (*(s32 *)((u8 *)(var_s1_3)+(8)));
                                    goto block_334;
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
                        }
                        goto block_336;
                    }
                    if ((u8) (*(u8 *)((u8 *)(var_s1_3)+(7))) < 0xECU) {
                        temp_v0_30 = ((*(u8 *)((u8 *)(var_s1_3)+(3))) + 1) * 4;
                        stack.spE4 = temp_v0_30;
                        var_s3 = func_80068EE8(temp_v0_30);
                        if (var_s3 != ((void *)0)) {
                            temp_s2_2 = (*(u16 *)((u8 *)(var_s1_3)+(0x14))) & 0x60;
                            stack.spF0 = temp_s2_2;
                            if ((*(u8 *)((u8 *)(var_s1_3)+(7))) & 4) {
                                temp_v0_31 = (*(void **)((u8 *)(var_s1_3)+(0x1C)));
                                stack.spE0 = var_s3;
                                (*(u16 *)((u8 *)(var_s3)+(0xE))) = (u16) (*(u16 *)((u8 *)(temp_v0_31)+(2)));
                                stack.spF0 = temp_s2_2 | ((*(u16 *)((u8 *)(temp_v0_31)+(0))) & 0xFF9F);
                                (*(u8 *)((u8 *)(var_s3)+(3))) = (u8) (*(u8 *)((u8 *)(var_s1_3)+(3)));
                                stack.spF8 = (*(void **)((u8 *)(var_s1_3)+(0x1C)));
                                goto block_244;
                            }
                            temp_s0_2 = var_s3;
                            stack.spE0 = var_s3;
                            var_s3 += 8;
                            stack.spE4 += 8;
                            if (func_80068EE8(8) != ((void *)0)) {
                                (*(u8 *)((u8 *)(var_s3)+(3))) = (u8) (*(u8 *)((u8 *)(var_s1_3)+(3)));
                                (*(u8 *)((u8 *)(temp_s0_2)+(3))) = 1U;
                                (*(s32 *)((u8 *)(temp_s0_2)+(4))) = (s32) (temp_s2_2 | 0xE1000200);
                                temp_t3_3 = (*(u8 *)((u8 *)(var_s3)+(3))) + (*(u8 *)((u8 *)(temp_s0_2)+(3))) + 1;
                                if (temp_t3_3 < 0xB) {
                                    (*(u8 *)((u8 *)(temp_s0_2)+(3))) = (u8) temp_t3_3;
                                    (*(s32 *)((u8 *)(var_s3)+(0))) = 0;
                                }
block_244:
                                (*(s32 *)((u8 *)(var_s3)+(4))) = (s32) (*(s32 *)((u8 *)(var_s1_3)+(4)));
                                goto block_245;
                            }
                        }
                    } else {
block_245:
                        temp_v1_19 = (*(u8 *)((u8 *)(var_s1_3)+(1))) & 0xF0;
                        if (temp_v1_19 != 0x10) {
                            var_t2_2 = 0;
                            if (temp_v1_19 >= 0x11) {
                                if (temp_v1_19 != 0x20) {
                                    var_fp_2 = 2;
                                    if (temp_v1_19 != 0x40) {
                                        goto block_249;
                                    }
                                    goto block_252;
                                }
                                var_fp_2 = 2;
                                goto block_252;
                            }
block_249:
                            var_fp_2 = 1;
                            var_s7_2 = 2;
                        } else {
                            var_t2_2 = 2;
                            var_fp_2 = 0;
block_252:
                            var_s7_2 = 1;
                        }
                        stack.spD8 = 0;
                        stack.sp110 = (M2C_UNK *)3;
                        var_t3 = (((*(u8 *)((u8 *)(var_s1_3)+(1))) & 0xF) * 0x10) + &D_800ADB28;
                        temp_v0_32 = (*(u8 *)((u8 *)(var_s1_3)+(7)));
                        temp_v1_20 = temp_v0_32 & 0xFF & 0xFC;
                        stack.spE8 = temp_v0_32 & 0x10;
                        if (temp_v1_20 != 0x3C) {
                            if (temp_v1_20 < 0x3D) {
                                if (temp_v1_20 != 0x2C) {
                                    if (temp_v1_20 < 0x2D) {
                                        if (temp_v1_20 != 0x28) {
                                            var_t9 = &D_800AD9EC;
                                            goto block_336;
                                        }
                                        var_s0_3 = var_s1_3 + 0x1C;
                                        goto block_294;
                                    }
                                    if (temp_v1_20 != 0x38) {
                                        var_t9 = &D_800AD9EC;
                                        goto block_336;
                                    }
                                    var_s0_3 = var_s1_3 + 0x28;
                                    (*(void **)((u8 *)(var_s3)+(0xC))) = (void *) (*(void **)((u8 *)(var_s1_3)+(0x1C)));
                                    __asm__ volatile("lwc2 $21, 0x1c($s0)");
                                    stack.sp110 = (M2C_UNK *)4;
                                    goto block_294;
                                }
                                (*(u16 *)((u8 *)(var_s3)+(0x14))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(6)));
                                var_s0_3 = var_s1_3 + 0x20;
                                (*(u16 *)((u8 *)(var_s3)+(0x1C))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(8)));
                                stack.sp110 = (M2C_UNK *)4;
                                (*(u16 *)((u8 *)(var_s3)+(0x16))) = stack.spF0;
                                (*(u16 *)((u8 *)(var_s3)+(0x24))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(0xA)));
                                goto block_292;
                            }
                            if (temp_v1_20 != 0x50) {
                                if (temp_v1_20 < 0x51) {
                                    if (temp_v1_20 != 0x40) {
                                        var_t9 = &D_800AD9EC;
                                        goto block_336;
                                    }
                                    goto block_269;
                                }
                                if (temp_v1_20 == 0xFC) {
                                    stack.spD8 = 0;
                                }
                                goto block_335;
                            }
                            stack.sp110 = (M2C_UNK *)4;
                            __asm__ volatile("lwc2 $6, 0x4($s0)");
block_269:
                            __asm__ volatile("ctc2 $t4, $0");
                            __asm__ volatile("ctc2 $t5, $1");
                            __asm__ volatile("ctc2 $t4, $2");
                            __asm__ volatile("ctc2 $t5, $3");
                            __asm__ volatile("ctc2 $t6, $4");
                            __asm__ volatile("ctc2 $t4, $5");
                            __asm__ volatile("ctc2 $t5, $6");
                            __asm__ volatile("ctc2 $t6, $7");
                            var_s5_2 += 1;
                            __asm__ volatile("mtc2 $zero, $0");
                            __asm__ volatile("mtc2 $zero, $1");
                            __asm__ volatile(".word 0x4A180001");
                            __asm__ volatile("swc2 $14, ($v0)");
                            var_s4_3 = (*(u8 *)((u8 *)(var_s1_3)+(2)));
                            if ((s32) var_s4_3 > 0) {
loop_271:
                                if (var_s5_2 < stack.spFC) {
                                    __asm__ volatile("swc2 $19, ($v0)");
                                    __asm__ volatile("ctc2 $t4, $0");
                                    __asm__ volatile("ctc2 $t5, $1");
                                    __asm__ volatile("ctc2 $t4, $2");
                                    __asm__ volatile("ctc2 $t5, $3");
                                    __asm__ volatile("ctc2 $t6, $4");
                                    __asm__ volatile("ctc2 $t4, $5");
                                    __asm__ volatile("ctc2 $t5, $6");
                                    __asm__ volatile("ctc2 $t6, $7");
                                    var_s5_2 += 1;
                                    __asm__ volatile("mtc2 $zero, $0");
                                    __asm__ volatile("mtc2 $zero, $1");
                                    __asm__ volatile(".word 0x4A180001");
                                    temp_v0_33 = func_80068EE8(stack.spE4);
                                    if (temp_v0_33 != ((void *)0)) {
                                        if (stack.spE8 != 0) {
                                            __asm__ volatile("swc2 $6, 0xc($s3)");
                                        }
                                        __asm__ volatile("swc2 $19, ($v0)");
                                        stack.spD8 = (s32) (stack.sp58 + stack.sp5C) >> 1;
                                        temp_v1_21 = (s32) (stack.spD8 - func_8008B984()) >> 3;
                                        stack.spD8 = temp_v1_21;
                                        temp_v1_22 = temp_v1_21 + D_800E53B8;
                                        stack.spD8 = temp_v1_22;
                                        if (temp_v1_22 < 2) {
                                            var_v0_7 = 2;
                                            goto block_279;
                                        }
                                        if (temp_v1_22 >= 0x1000) {
                                            var_v0_7 = 0xFFF;
block_279:
                                            stack.spD8 = var_v0_7;
                                        }
                                        stack.spDC = gte_cfc2_31();
                                        if (stack.spDC >= 0) {
                                            temp_a0_5 = (stack.spD8 * 4) + arg0;
                                            *stack.spE0 = (*stack.spE0 & high_mask) | (*temp_a0_5 & stack.sp104);
                                            *temp_a0_5 = (*temp_a0_5 & high_mask) | ((s32) stack.spE0 & stack.sp104);
                                        }
                                        __asm__ volatile("swc2 $14, ($v0)");
                                        var_a2_5 = ((s32) (temp_v0_33 - stack.spE0) >> 2) - 1;
                                        if (var_a2_5 >= 0) {
                                            var_a0_4 = &temp_v0_33[var_a2_5];
                                            var_v1_2 = &stack.spE0[var_a2_5];
                                            do {
                                                temp_v0_34 = *var_v1_2;
                                                var_v1_2 -= 4;
                                                var_a2_5 -= 1;
                                                *var_a0_4 = temp_v0_34;
                                                var_a0_4 -= 4;
                                            } while (var_a2_5 >= 0);
                                        }
                                        var_s3 = temp_v0_33 + (var_s3 - stack.spE0);
                                        stack.spE0 = temp_v0_33;
                                        stack.sp58 = stack.sp5C;
                                        __asm__ volatile("swc2 $14, ($v0)");
                                        if (stack.spE8 != 0) {
                                            __asm__ volatile("swc2 $6, 0x4($s3)");
                                            __asm__ volatile("lwc2 $6, 0x4($s0)");
                                        }
                                        var_s4_3 -= 1;
                                        if ((s32) var_s4_3 > 0) {
                                            goto loop_271;
                                        }
                                        goto block_335;
                                    }
                                } else {
                                    goto block_334;
                                }
                            } else {
                                goto block_335;
                            }
                        } else {
                            (*(u16 *)((u8 *)(var_s3)+(0x18))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(6)));
                            (*(u16 *)((u8 *)(var_s3)+(0x24))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(8)));
                            (*(u16 *)((u8 *)(var_s3)+(0x30))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(0xA)));
                            var_s0_3 = var_s1_3 + 0x2C;
                            (*(u16 *)((u8 *)(var_s3)+(0x1A))) = stack.spF0;
                            (*(s32 *)((u8 *)(var_s3)+(0x10))) = (s32) (*(s32 *)((u8 *)(var_s1_3)+(0x20)));
                            __asm__ volatile("lwc2 $21, 0x1c($s0)");
                            stack.sp110 = (M2C_UNK *)5;
block_292:
                            (*(u16 *)((u8 *)(var_s3)+(0xC))) = (u16) (*(u16 *)((u8 *)(stack.spF8)+(4)));
block_294:
                            __asm__ volatile("ctc2 $t4, $0");
                            __asm__ volatile("ctc2 $t5, $1");
                            __asm__ volatile("ctc2 $t4, $2");
                            __asm__ volatile("ctc2 $t5, $3");
                            __asm__ volatile("ctc2 $t6, $4");
                            __asm__ volatile("ctc2 $t4, $5");
                            __asm__ volatile("ctc2 $t5, $6");
                            __asm__ volatile("ctc2 $t6, $7");
                            var_s5_2 += 1;
                            __asm__ volatile("lwc2 $20, 0x4($s0)");
                            var_a2_6 = 0;
                            var_a0_5 = &D_800ADB58;
                            var_a1_3 = var_t3;
                            do {
                                temp_v1_23 = (*(s16 *)((u8 *)(var_a1_3)+(0)));
                                temp_v0_35 = (*(s16 *)((u8 *)(var_s1_3)+(0x18)));
                                stack.sp88[0] = (mult_hi(temp_v1_23, temp_v0_35) << 0x14) | ((u32) (temp_v1_23 * temp_v0_35) >> 0xC);
                                temp_v1_24 = (*(s16 *)((u8 *)(var_a1_3)+(2)));
                                temp_v0_36 = (*(s16 *)((u8 *)(var_s1_3)+(0x1A)));
                                stack.sp8C = (mult_hi(temp_v1_24, temp_v0_36) << 0x14) | ((u32) (temp_v1_24 * temp_v0_36) >> 0xC);
                                stack.sp90 = (s32) (*(s16 *)((u8 *)(var_a1_3)+(4)));
                                (*(u16 *)((u8 *)(var_a0_5)+(0))) = (u16) (&stack.sp88[0])[var_t2_2];
                                (*(u16 *)((u8 *)(var_a0_5)+(2))) = (u16) (&stack.sp88[0])[var_fp_2];
                                (*(u16 *)((u8 *)(var_a0_5)+(4))) = (u16) (&stack.sp88[0])[var_s7_2];
                                var_a0_5 += 8;
                                var_a2_6 += 1;
                                var_a1_3 += 8;
                            } while (var_a2_6 < 2);
                            __asm__ volatile("lwc2 $0, ($s6)");
                            __asm__ volatile("lwc2 $1, 0x4($s6)");
                            __asm__ volatile("lwc2 $2, 0x8($s6)");
                            __asm__ volatile("lwc2 $3, 0xc($s6)");
                            __asm__ volatile(".word 0x4A280030");
                            __asm__ volatile("swc2 $12, 0x8($s3)");
                            __asm__ volatile("swc2 $13, ($v0)");
                            var_s4_4 = (*(u8 *)((u8 *)(var_s1_3)+(2)));
                            if ((s32) var_s4_4 > 0) {
loop_297:
                                if (var_s5_2 < stack.spFC) {
                                    __asm__ volatile("swc2 $17, ($v0)");
                                    __asm__ volatile("swc2 $18, 0x4($v0)");
                                    __asm__ volatile("ctc2 $t4, $0");
                                    __asm__ volatile("ctc2 $t5, $1");
                                    __asm__ volatile("ctc2 $t4, $2");
                                    __asm__ volatile("ctc2 $t5, $3");
                                    __asm__ volatile("ctc2 $t6, $4");
                                    __asm__ volatile("ctc2 $t4, $5");
                                    __asm__ volatile("ctc2 $t5, $6");
                                    __asm__ volatile("ctc2 $t6, $7");
                                    var_s5_2 += 1;
                                    var_a2_7 = 0;
                                    var_a0_6 = &D_800ADB58;
                                    var_a1_4 = var_t3;
                                    do {
                                        temp_v1_25 = (*(s16 *)((u8 *)(var_a1_4)+(0)));
                                        temp_v0_37 = (*(s16 *)((u8 *)(var_s0_3)+(0x18)));
                                        stack.sp88[0] = (mult_hi(temp_v1_25, temp_v0_37) << 0x14) | ((u32) (temp_v1_25 * temp_v0_37) >> 0xC);
                                        temp_v1_26 = (*(s16 *)((u8 *)(var_a1_4)+(2)));
                                        temp_v0_38 = (*(s16 *)((u8 *)(var_s0_3)+(0x1A)));
                                        temp_a3_2 = (u32) (temp_v1_26 * temp_v0_38) >> 0xC;
                                        stack.sp8C = (mult_hi(temp_v1_26, temp_v0_38) << 0x14) | temp_a3_2;
                                        stack.sp90 = (s32) (*(s16 *)((u8 *)(var_a1_4)+(4)));
                                        (*(u16 *)((u8 *)(var_a0_6)+(0))) = (u16) (&stack.sp88[0])[var_t2_2];
                                        (*(u16 *)((u8 *)(var_a0_6)+(2))) = (u16) (&stack.sp88[0])[var_fp_2];
                                        (*(u16 *)((u8 *)(var_a0_6)+(4))) = (u16) (&stack.sp88[0])[var_s7_2];
                                        var_a0_6 += 8;
                                        var_a2_7 += 1;
                                        var_a1_4 += 8;
                                    } while (var_a2_7 < 2);
                                    __asm__ volatile("lwc2 $0, ($s6)");
                                    __asm__ volatile("lwc2 $1, 0x4($s6)");
                                    __asm__ volatile("lwc2 $2, 0x8($s6)");
                                    __asm__ volatile("lwc2 $3, 0xc($s6)");
                                    __asm__ volatile(".word 0x4A280030");
                                    stack.sp108 = var_t2_2;
                                    stack.sp10C = var_t3;
                                    var_s0_3 += (*(u8 *)((u8 *)(var_s0_3)+(0))) * 4;
                                    temp_v0_39 = func_80068EE8(stack.spE4, var_a1_4, var_a2_7, temp_a3_2);
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
                                        __asm__ volatile("swc2 $17, 0x8($v0)");
                                        __asm__ volatile("swc2 $18, 0xc($v0)");
                                        stack.sp108 = var_t2_2;
                                        stack.sp10C = var_t3;
                                        stack.spD8 = (s32) (stack.sp58 + stack.sp5C + stack.sp60 + stack.sp64) >> 2;
                                        temp_v1_28 = (s32) (stack.spD8 - func_8008B984(stack.sp64)) >> 3;
                                        stack.spD8 = temp_v1_28;
                                        temp_v1_29 = temp_v1_28 + D_800E53B8;
                                        stack.spD8 = temp_v1_29;
                                        if (temp_v1_29 < 2) {
                                            var_v0_8 = 2;
                                            goto block_316;
                                        }
                                        if (temp_v1_29 >= 0x1000) {
                                            var_v0_8 = 0xFFF;
block_316:
                                            stack.spD8 = var_v0_8;
                                        }
                                        stack.spDC = gte_cfc2_31();
                                        if (stack.spDC >= 0) {
                                            temp_a0_6 = (stack.spD8 * 4) + arg0;
                                            *stack.spE0 = (*stack.spE0 & high_mask) | (*temp_a0_6 & stack.sp104);
                                            *temp_a0_6 = (*temp_a0_6 & high_mask) | ((s32) stack.spE0 & stack.sp104);
                                        }
                                        var_a2_8 = ((s32) (temp_v0_39 - stack.spE0) >> 2) - 1;
                                        if (var_a2_8 >= 0) {
                                            var_a0_7 = &temp_v0_39[var_a2_8];
                                            var_v1_3 = &stack.spE0[var_a2_8];
                                            do {
                                                temp_v0_40 = *var_v1_3;
                                                var_v1_3 -= 4;
                                                var_a2_8 -= 1;
                                                *var_a0_7 = temp_v0_40;
                                                var_a0_7 -= 4;
                                            } while (var_a2_8 >= 0);
                                        }
                                        var_s3 = temp_v0_39 + (var_s3 - stack.spE0);
                                        stack.spE0 = temp_v0_39;
                                        stack.sp5C = stack.sp64;
                                        stack.sp58 = stack.sp60;
                                        __asm__ volatile("swc2 $12, 0x8($s3)");
                                        __asm__ volatile("swc2 $20, 0x4($s3)");
                                        __asm__ volatile("lwc2 $20, 0x4($s0)");
                                        temp_v1_30 = (*(u8 *)((u8 *)(var_s1_3)+(7))) & 0xFC;
                                        if (temp_v1_30 != 0x38) {
                                            if (temp_v1_30 < 0x39) {
                                                if (temp_v1_30 != 0x28) {
                                                    if (temp_v1_30 != 0x2C) {
                                                        var_s4_4 -= 1;
                                                    } else {
                                                        goto block_331;
                                                    }
                                                } else {
                                                    __asm__ volatile("swc2 $13, 0xc($s3)");
                                                    var_s4_4 -= 1;
                                                }
                                            } else if (temp_v1_30 != 0x3C) {
                                                var_s4_4 -= 1;
                                            } else {
                                                __asm__ volatile("swc2 $13, 0x14($s3)");
                                                __asm__ volatile("swc2 $21, 0x10($s3)");
                                                __asm__ volatile("lwc2 $21, 0x1c($s0)");
                                                var_s4_4 -= 1;
                                            }
                                        } else {
                                            __asm__ volatile("swc2 $21, 0xc($s3)");
                                            __asm__ volatile("lwc2 $21, 0x1c($s0)");
block_331:
                                            __asm__ volatile("swc2 $13, 0x10($s3)");
                                            var_s4_4 -= 1;
                                        }
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
                } else {
                    goto block_337;
                }
            } else {
block_337:
                __asm__ volatile("ctc2 $t4, $0");
                __asm__ volatile("ctc2 $t5, $1");
                __asm__ volatile("ctc2 $t4, $2");
                __asm__ volatile("ctc2 $t5, $3");
                __asm__ volatile("ctc2 $t6, $4");
                __asm__ volatile("ctc2 $t4, $5");
                __asm__ volatile("ctc2 $t5, $6");
                __asm__ volatile("ctc2 $t6, $7");
            }
        }
    }
}
