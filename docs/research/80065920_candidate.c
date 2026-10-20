M2C_UNK func_80065710(M2C_UNK *, void *, s32 *);    /* extern */
s32 func_80068720(void *, void *, s32, M2C_UNK);    /* extern */
M2C_UNK func_800687CC(M2C_UNK *, M2C_UNK *, s16);   /* extern */
M2C_UNK func_80068888(M2C_UNK *, M2C_UNK *, s16);   /* extern */
M2C_UNK func_80068940(M2C_UNK *, M2C_UNK *, s16);   /* extern */
M2C_UNK func_80068AE4(M2C_UNK *, M2C_UNK *, s16);   /* extern */
s32 *func_80068EE8(s32, void *, s32, u32);          /* extern */
s32 func_8006A26C(M2C_UNK);                         /* extern */
s32 func_8007F7D8();                                /* extern */
s32 func_8008B984(s32);                             /* extern */
s16 func_800924F0();                                /* extern */
s16 func_80092500();                                /* extern */
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

void func_80065920(void *arg0, s32 arg1) {
    M2C_UNK *sp110;
    void *sp10C;
    s32 sp108;
    s32 sp104;
    s32 *sp100;
    s32 spFC;
    void *spF8;
    u16 spF0;
    s32 spE8;
    s32 spE4;
    s32 *spE0;
    s32 spDC;
    s32 spD8;
    M2C_UNK spC8;
    M2C_UNK spB8;
    M2C_UNK spA8;
    s16 spA2;
    s16 spA0;
    s16 sp9A;
    s16 sp98;
    s32 sp90;
    s32 sp8C;
    M2C_UNK sp68;
    s32 sp5C;
    s32 sp58;
    M2C_UNK sp38;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    M2C_UNK sp10;
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
    s32 var_s5;
    s32 var_s5_2;
    s32 var_s7;
    s32 var_s7_2;
    s32 var_t2;
    s32 var_t2_2;
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
    void *var_t3;

    var_s3 = NULL;
    spE0 = NULL;
    spE4 = 0;
    spF0 = 0;
    spF8 = NULL;
    spD8 = 0;
    M2C_FIELD(&D_800AD9EC, s32 *, 8) = func_8007F7D8();
    temp_v0 = func_8006A26C(4);
    D_800E53EC = temp_v0;
    D_800E53E8 = temp_v0;
    D_800E53B8 = -0xA;
    M2C_FIELD(&D_800E53C8, s32 *, 0) = (s32) (0x1000 & 0xFFFF);
    M2C_FIELD(&D_800E53C8, s32 *, 4) = 0;
    M2C_FIELD(&D_800E53C8, s32 *, 8) = (s32) (0xA00 & 0xFFFF);
    M2C_FIELD(&D_800E53C8, s32 *, 0xC) = 0;
    M2C_FIELD(&D_800E53C8, s16 *, 0x10) = 0x1000;
    M2C_FIELD(&D_800E53C8, s32 *, 0x14) = 0;
    M2C_FIELD(&D_800E53C8, s32 *, 0x18) = 0;
    M2C_FIELD(&D_800E53C8, s32 *, 0x1C) = 0;
    M2C_FIELD(&sp38, s32 *, 0) = 0x1000;
    M2C_FIELD(&sp38, s32 *, 4) = 0;
    M2C_FIELD(&sp38, s32 *, 8) = 0x1000;
    M2C_FIELD(&sp38, s32 *, 0xC) = 0;
    M2C_FIELD(&sp38, s16 *, 0x10) = 0x1000;
    M2C_FIELD(&sp38, s32 *, 0x14) = 0;
    M2C_FIELD(&sp38, s32 *, 0x18) = 0;
    M2C_FIELD(&sp38, s32 *, 0x1C) = 0;
    D_800E5374 = &sp38;
    temp_v1 = (arg1 * 0x9C) + &D_800D3034;
    sp20 = (s32) M2C_FIELD(temp_v1, s32 *, 0xC) >> 0xC;
    sp24 = (s32) M2C_FIELD(temp_v1, s32 *, 0x10) >> 0xC;
    sp28 = (s32) M2C_FIELD(temp_v1, s32 *, 0x14) >> 0xC;
    M2C_FIELD(&D_800E5398, s32 *, 0) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $0 */);
    M2C_FIELD(&D_800E5398, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $1 */);
    M2C_FIELD(&D_800E5398, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $2 */);
    M2C_FIELD(&D_800E5398, s32 *, 0xC) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $3 */);
    M2C_FIELD(&D_800E5398, s32 *, 0x10) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $4 */);
    M2C_FIELD(&D_800E5398, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
    M2C_FIELD(&D_800E5398, s32 *, 0x18) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
    M2C_FIELD(&D_800E5398, s32 *, 0x1C) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
    M2C_FIELD(&D_800E53AC, s32 *, 0) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
    M2C_FIELD(&D_800E53AC, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
    M2C_FIELD(&D_800E53AC, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
    var_s5 = 0;
    sp98 = func_800924F0();
    sp9A = func_80092500();
    spA0 = func_800924F0();
    spA2 = func_80092500();
    var_s1 = M2C_FIELD(&D_800AD9EC, void **, 0);
    if (var_s1 != M2C_FIELD(&D_800AD9EC, s32 *, 4)) {
        sp110 = &spA8;
        var_v0 = 0 < 0x200;
loop_2:
        if (var_v0 != 0) {
            if ((u8) M2C_FIELD(var_s1, u8 *, 7) < 0xECU) {
                func_80065710(&sp10, var_s1 + 8, &sp20);
            }
            temp_v1_2 = M2C_FIELD(var_s1, u8 *, 1) & 0xF0;
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
            if (M2C_FIELD(var_s1, u8 *, 2) == 0) {
                temp_v1_3 = M2C_FIELD(var_s1, u8 *, 7) & 0xFC;
                switch (temp_v1_3) {                /* switch 1; irregular */
                case 0x40:                          /* switch 1 */
                case 0x50:                          /* switch 1 */
                    temp_v0_2 = var_s5 << 5;
                    var_s5 += 1;
                    temp_v0_3 = temp_v0_2 + D_800E53E8;
                    M2C_FIELD(temp_v0_3, s32 *, 0) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $0 */);
                    M2C_FIELD(temp_v0_3, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $1 */);
                    M2C_FIELD(temp_v0_3, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $2 */);
                    M2C_FIELD(temp_v0_3, s32 *, 0xC) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $3 */);
                    M2C_FIELD(temp_v0_3, s32 *, 0x10) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $4 */);
                    M2C_FIELD(temp_v0_3, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                    M2C_FIELD(temp_v0_3, s32 *, 0x18) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                    M2C_FIELD(temp_v0_3, s32 *, 0x1C) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                    temp_v0_4 = temp_v0_3 + 0x14;
                    M2C_FIELD(temp_v0_3, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                    M2C_FIELD(temp_v0_4, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                    M2C_FIELD(temp_v0_4, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                    if (var_s5 < 0x1FF) {
block_51:
                        var_a2 = M2C_FIELD(var_s1, s16 *, 0x16);
block_52:
                        D_800E53BC(&sp68, &D_800E53C8, var_a2);
                    case 0xE8:                      /* switch 1 */
                    case 0xA4:                      /* switch 1 */
                    case 0xB4:                      /* switch 1 */
                    case 0xE0:                      /* switch 1 */
                        temp_v0_5 = var_s5 << 5;
                        var_s5 += 1;
                        temp_v0_6 = temp_v0_5 + D_800E53E8;
                        M2C_FIELD(temp_v0_6, s32 *, 0) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $0 */);
                        M2C_FIELD(temp_v0_6, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $1 */);
                        M2C_FIELD(temp_v0_6, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $2 */);
                        M2C_FIELD(temp_v0_6, s32 *, 0xC) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $3 */);
                        M2C_FIELD(temp_v0_6, s32 *, 0x10) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $4 */);
                        M2C_FIELD(temp_v0_6, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                        M2C_FIELD(temp_v0_6, s32 *, 0x18) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                        M2C_FIELD(temp_v0_6, s32 *, 0x1C) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                        temp_v0_7 = temp_v0_6 + 0x14;
                        M2C_FIELD(temp_v0_6, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                        M2C_FIELD(temp_v0_7, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                        M2C_FIELD(temp_v0_7, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                        M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                        M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                        M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                        M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                        M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                    }
                    goto block_106;
                case 0x10:                          /* switch 1 */
                    var_a2 = 0;
                    goto block_52;
                case 0x2C:                          /* switch 1 */
                case 0x34:                          /* switch 1 */
                case 0x38:                          /* switch 1 */
                case 0x3C:                          /* switch 1 */
                case 0x30:                          /* switch 1 */
                case 0x20:                          /* switch 1 */
                case 0x24:                          /* switch 1 */
                case 0x28:                          /* switch 1 */
                    goto block_51;
                case 0xEC:                          /* switch 1 */
                    M2C_FIELD(&D_800E5358, s32 *, 0) = (s32) -M2C_FIELD(var_s1, s16 *, 8);
                    M2C_FIELD(&D_800E5358, s32 *, 4) = (s32) -M2C_FIELD(var_s1, s16 *, 0xA);
                    M2C_FIELD(&D_800E5358, s32 *, 8) = (s32) -M2C_FIELD(var_s1, s16 *, 0xC);
                    M2C_FIELD(&D_800E5368, s32 *, 0) = (s32) M2C_FIELD(var_s1, s16 *, 0x10);
                    M2C_FIELD(&D_800E5368, s32 *, 4) = (s32) M2C_FIELD(var_s1, s16 *, 0x12);
                    M2C_FIELD(&D_800E5368, s32 *, 8) = (s32) M2C_FIELD(var_s1, s16 *, 0x14);
                    M2C_ERROR(/* unknown instruction: mtc2 $s0, $9 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t0, $10 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t1, $11 */);
                    M2C_ERROR(/* unknown instruction: sqr 0x0 */);
                    M2C_ERROR(/* unknown instruction: mfc2 $a0, $25 */);
                    M2C_ERROR(/* unknown instruction: mfc2 $v0, $26 */);
                    M2C_ERROR(/* unknown instruction: mfc2 $a2, $27 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $a1, $30 */);
                    temp_v0_8 = M2C_ERROR(/* unknown instruction: mfc2 $v1, $31 */) & ~1;
                    temp_a2 = (s32) (0x1F - temp_v0_8) >> 1;
                    if ((temp_v0_8 - 0x18) < 0) {

                    }
                    M2C_ERROR(/* unknown instruction: mtc2 $v0, $8 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $s0, $9 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t0, $10 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t1, $11 */);
                    M2C_ERROR(/* unknown instruction: gpf 0x0 */);
                    M2C_FIELD(&spC8, s32 *, 0) = (s32) ((s32) M2C_ERROR(/* unknown instruction: mfc2 $s0, $25 */) >> temp_a2);
                    M2C_FIELD(&spC8, s32 *, 4) = (s32) ((s32) M2C_ERROR(/* unknown instruction: mfc2 $t0, $26 */) >> temp_a2);
                    M2C_FIELD(&spC8, s32 *, 8) = (s32) ((s32) M2C_ERROR(/* unknown instruction: mfc2 $t1, $27 */) >> temp_a2);
                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $2 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                    M2C_ERROR(/* unknown instruction: lwc2 $11, 0x8($v0) */);
                    M2C_ERROR(/* unknown instruction: lwc2 $9, ($v0) */);
                    M2C_ERROR(/* unknown instruction: lwc2 $10, 0x4($v0) */);
                    M2C_ERROR(/* unknown instruction: op 0x1 */);
                    M2C_ERROR(/* unknown instruction: swc2 $25, ($s6) */);
                    M2C_ERROR(/* unknown instruction: swc2 $26, 0x4($s6) */);
                    M2C_ERROR(/* unknown instruction: swc2 $27, 0x8($s6) */);
                    M2C_ERROR(/* unknown instruction: mtc2 $s0, $9 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t0, $10 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t1, $11 */);
                    M2C_ERROR(/* unknown instruction: sqr 0x0 */);
                    M2C_ERROR(/* unknown instruction: mfc2 $a0, $25 */);
                    M2C_ERROR(/* unknown instruction: mfc2 $v0, $26 */);
                    M2C_ERROR(/* unknown instruction: mfc2 $a2, $27 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $a1, $30 */);
                    temp_v0_9 = M2C_ERROR(/* unknown instruction: mfc2 $v1, $31 */) & ~1;
                    temp_a2_2 = (s32) (0x1F - temp_v0_9) >> 1;
                    if ((temp_v0_9 - 0x18) < 0) {

                    }
                    M2C_ERROR(/* unknown instruction: mtc2 $v0, $8 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $s0, $9 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t0, $10 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t1, $11 */);
                    M2C_ERROR(/* unknown instruction: gpf 0x0 */);
                    M2C_FIELD(sp110, s32 *, 0) = (s32) ((s32) M2C_ERROR(/* unknown instruction: mfc2 $s0, $25 */) >> temp_a2_2);
                    M2C_FIELD(sp110, s32 *, 4) = (s32) ((s32) M2C_ERROR(/* unknown instruction: mfc2 $t0, $26 */) >> temp_a2_2);
                    M2C_FIELD(sp110, s32 *, 8) = (s32) ((s32) M2C_ERROR(/* unknown instruction: mfc2 $t1, $27 */) >> temp_a2_2);
                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $2 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                    M2C_ERROR(/* unknown instruction: lwc2 $11, 0x8($t9) */);
                    M2C_ERROR(/* unknown instruction: lwc2 $9, ($t9) */);
                    M2C_ERROR(/* unknown instruction: lwc2 $10, 0x4($t9) */);
                    M2C_ERROR(/* unknown instruction: op 0x1 */);
                    M2C_ERROR(/* unknown instruction: swc2 $25, ($v0) */);
                    M2C_ERROR(/* unknown instruction: swc2 $26, 0x4($v0) */);
                    M2C_ERROR(/* unknown instruction: swc2 $27, 0x8($v0) */);
                    M2C_FIELD(&D_800E5378, s32 *, 0) = (s32) ((M2C_FIELD(&spB8, s32 *, 0) << 0x10) | (M2C_FIELD(sp110, s32 *, 0) & 0xFFFF));
                    M2C_FIELD(&D_800E5378, s32 *, 8) = (s32) ((M2C_FIELD(&spC8, s32 *, 4) << 0x10) | (M2C_FIELD(&spB8, s32 *, 4) & 0xFFFF));
                    M2C_FIELD(&D_800E5378, s16 *, 0x10) = (s16) M2C_FIELD(&spC8, s32 *, 8);
                    M2C_FIELD(&D_800E5378, s32 *, 4) = (s32) ((M2C_FIELD(sp110, s32 *, 4) << 0x10) | (M2C_FIELD(&spC8, s32 *, 0) & 0xFFFF));
                    M2C_FIELD(&D_800E5378, s32 *, 0xC) = (s32) ((M2C_FIELD(&spB8, s32 *, 8) << 0x10) | (M2C_FIELD(sp110, s32 *, 8) & 0xFFFF));
                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t4, $9 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t5, $10 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t6, $11 */);
                    M2C_ERROR(/* unknown instruction: mvmva 0x1, 0x0, 0x3, 0x3, 0x0 */);
                    M2C_FIELD(&D_800E5378, s32 *, 0) = (s16) M2C_ERROR(/* unknown instruction: mfc2 $t4, $9 */);
                    M2C_FIELD(&D_800E5378, u16 *, 6) = (u16) M2C_ERROR(/* unknown instruction: mfc2 $t5, $10 */);
                    M2C_FIELD(&D_800E5378, s32 *, 0xC) = (s16) M2C_ERROR(/* unknown instruction: mfc2 $t6, $11 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t4, $9 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t5, $10 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t6, $11 */);
                    M2C_ERROR(/* unknown instruction: mvmva 0x1, 0x0, 0x3, 0x3, 0x0 */);
                    temp_a3 = &D_800E5378 + 2;
                    M2C_FIELD(&D_800E5378, u16 *, 2) = (u16) M2C_ERROR(/* unknown instruction: mfc2 $t4, $9 */);
                    M2C_FIELD(temp_a3, s16 *, 6) = (s16) M2C_ERROR(/* unknown instruction: mfc2 $t5, $10 */);
                    M2C_FIELD(temp_a3, s16 *, 0xC) = (s16) M2C_ERROR(/* unknown instruction: mfc2 $t6, $11 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t4, $9 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t5, $10 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t6, $11 */);
                    M2C_ERROR(/* unknown instruction: mvmva 0x1, 0x0, 0x3, 0x3, 0x0 */);
                    M2C_FIELD(&D_800E537C, u16 *, 0) = (u16) M2C_ERROR(/* unknown instruction: mfc2 $t4, $9 */);
                    M2C_FIELD(&D_800E537C, u16 *, 6) = (u16) M2C_ERROR(/* unknown instruction: mfc2 $t5, $10 */);
                    M2C_FIELD(&D_800E537C, u16 *, 0xC) = (u16) M2C_ERROR(/* unknown instruction: mfc2 $t6, $11 */);
                    D_800E5374 = &D_800E5378;
                    goto block_105;
                case 0xF4:                          /* switch 1 */
                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t4, $9 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t5, $10 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t6, $11 */);
                    M2C_ERROR(/* unknown instruction: mvmva 0x1, 0x0, 0x3, 0x3, 0x0 */);
                    M2C_FIELD(&D_800E5378, s32 *, 0) = (s16) M2C_ERROR(/* unknown instruction: mfc2 $t4, $9 */);
                    M2C_FIELD(&D_800E5378, u16 *, 6) = (u16) M2C_ERROR(/* unknown instruction: mfc2 $t5, $10 */);
                    M2C_FIELD(&D_800E5378, s32 *, 0xC) = (s16) M2C_ERROR(/* unknown instruction: mfc2 $t6, $11 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t4, $9 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t5, $10 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t6, $11 */);
                    M2C_ERROR(/* unknown instruction: mvmva 0x1, 0x0, 0x3, 0x3, 0x0 */);
                    temp_t8 = &D_800E5378 + 2;
                    M2C_FIELD(&D_800E5378, u16 *, 2) = (u16) M2C_ERROR(/* unknown instruction: mfc2 $t4, $9 */);
                    M2C_FIELD(temp_t8, s16 *, 6) = (s16) M2C_ERROR(/* unknown instruction: mfc2 $t5, $10 */);
                    M2C_FIELD(temp_t8, s16 *, 0xC) = (s16) M2C_ERROR(/* unknown instruction: mfc2 $t6, $11 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t4, $9 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t5, $10 */);
                    M2C_ERROR(/* unknown instruction: mtc2 $t6, $11 */);
                    M2C_ERROR(/* unknown instruction: mvmva 0x1, 0x0, 0x3, 0x3, 0x0 */);
                    M2C_FIELD(&D_800E537C, u16 *, 0) = (u16) M2C_ERROR(/* unknown instruction: mfc2 $t4, $9 */);
                    M2C_FIELD(&D_800E537C, u16 *, 6) = (u16) M2C_ERROR(/* unknown instruction: mfc2 $t5, $10 */);
                    M2C_FIELD(&D_800E537C, u16 *, 0xC) = (u16) M2C_ERROR(/* unknown instruction: mfc2 $t6, $11 */);
                    D_800E5374 = &D_800E5378;
                    goto block_105;
                case 0xF8:                          /* switch 1 */
                    temp_v1_4 = (s32) M2C_FIELD(var_s1, s16 *, 0xC);
                    if (temp_v1_4 & 0x11) {
                        M2C_FIELD(var_s1, s16 *, 0xC) = (s32) (temp_v1_4 & ~0x10);
                        var_s3 = func_80068EE8((M2C_FIELD(var_s1, u8 *, 0) - 4) * 4);
                        if (var_s3 != NULL) {
                            spE0 = var_s1 + 0x10;
                            var_a2_2 = 4;
                            var_v1 = var_s3 + 0x10;
                            if ((s32) M2C_FIELD(var_s1, u8 *, 0) > 4) {
                                var_a0 = var_s1 + 0x20;
                                do {
                                    temp_v0_10 = M2C_FIELD(var_a0, s32 *, -0x10);
                                    var_a0 += 4;
                                    var_a2_2 += 1;
                                    M2C_FIELD(var_v1, s32 *, -0x10) = temp_v0_10;
                                    var_v1 += 4;
                                } while (var_a2_2 < (s32) M2C_FIELD(var_s1, u8 *, 0));
                            }
                            temp_v1_5 = (s32) M2C_FIELD(var_s1, s16 *, 8);
                            spD8 = temp_v1_5;
                            if (temp_v1_5 == -1) {
                                *var_s3 = (*var_s3 & 0xFF000000) | (M2C_FIELD(arg0, s32 *, 4) & 0xFFFFFF);
                                M2C_FIELD(arg0, s32 *, 4) = (s32) ((M2C_FIELD(arg0, s32 *, 4) & 0xFF000000) | ((s32) var_s3 & 0xFFFFFF));
                                goto block_105;
                            }
                            if (temp_v1_5 <= 0) {
                                var_v0_4 = 1;
                                goto block_72;
                            }
                            var_v0_4 = 0xFFF;
                            if (temp_v1_5 >= 0x1000) {
block_72:
                                spD8 = var_v0_4;
                            }
                            if ((s32) M2C_FIELD(var_s1, s16 *, 0xC) & 0x20) {
                                var_s3 = func_80068EE8(0xC);
                                if (var_s3 != NULL) {
                                    *(s8 *)3 = 2;
                                    *(s8 *)4 = (s32) (0xE5000000 | ((M2C_FIELD(&spA0, s16 *, 2) & 0x7FF) << 0xB) | (M2C_FIELD(&spA0, s16 *, 0) & 0x7FF));
                                    *(s8 *)8 = 0;
                                    temp_a0 = (spD8 * 4) + arg0;
                                    *NULL = (s32) ((*NULL & 0xFF000000) | (*temp_a0 & 0xFFFFFF));
                                    *temp_a0 = (*temp_a0 & 0xFF000000) | (0 & 0xFFFFFF);
                                    goto block_76;
                                }
                            } else {
block_76:
                                temp_a0_2 = (spD8 * 4) + arg0;
                                *var_s3 = (*var_s3 & 0xFF000000) | (*temp_a0_2 & 0xFFFFFF);
                                *temp_a0_2 = (*temp_a0_2 & 0xFF000000) | ((s32) var_s3 & 0xFFFFFF);
                                if ((s32) M2C_FIELD(var_s1, s16 *, 0xC) & 0x40) {
                                    var_s3 = func_80068EE8(0xC);
                                    if (var_s3 != NULL) {
                                        *(s8 *)3 = 2;
                                        *(s8 *)4 = (s32) (0xE5000000 | ((M2C_FIELD(&sp98, s16 *, 2) & 0x7FF) << 0xB) | (M2C_FIELD(&sp98, s16 *, 0) & 0x7FF));
                                        *(s8 *)8 = 0;
                                        temp_a0_3 = (spD8 * 4) + arg0;
                                        *NULL = (s32) ((*NULL & 0xFF000000) | (*temp_a0_3 & 0xFFFFFF));
                                        *temp_a0_3 = (*temp_a0_3 & 0xFF000000) | (0 & 0xFFFFFF);
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
                temp_v1_6 = M2C_FIELD(var_s1, u8 *, 7) & 0xFC;
                switch (temp_v1_6) {                /* switch 2; irregular */
                case 0x50:                          /* switch 2 */
                    var_s0 = var_s1 + 0x24;
block_93:
                    temp_v0_11 = var_s5 << 5;
                    var_s5 += 1;
                    temp_v0_12 = temp_v0_11 + D_800E53E8;
                    M2C_FIELD(temp_v0_12, s32 *, 0) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $0 */);
                    M2C_FIELD(temp_v0_12, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $1 */);
                    M2C_FIELD(temp_v0_12, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $2 */);
                    M2C_FIELD(temp_v0_12, s32 *, 0xC) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $3 */);
                    M2C_FIELD(temp_v0_12, s32 *, 0x10) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $4 */);
                    M2C_FIELD(temp_v0_12, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                    M2C_FIELD(temp_v0_12, s32 *, 0x18) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                    M2C_FIELD(temp_v0_12, s32 *, 0x1C) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                    temp_v0_13 = temp_v0_12 + 0x14;
                    M2C_FIELD(temp_v0_12, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                    M2C_FIELD(temp_v0_13, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                    M2C_FIELD(temp_v0_13, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                    var_s4 = M2C_FIELD(var_s1, u8 *, 2);
loop_94:
                    if (((s32) var_s4 > 0) && (var_s5 < 0x200)) {
                        func_80065710(&sp10, var_s0 + 8, &sp20);
                        temp_v0_14 = var_s5 << 5;
                        var_s5 += 1;
                        temp_v0_15 = temp_v0_14 + D_800E53E8;
                        M2C_FIELD(temp_v0_15, s32 *, 0) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $0 */);
                        M2C_FIELD(temp_v0_15, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $1 */);
                        M2C_FIELD(temp_v0_15, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $2 */);
                        M2C_FIELD(temp_v0_15, s32 *, 0xC) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $3 */);
                        M2C_FIELD(temp_v0_15, s32 *, 0x10) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $4 */);
                        M2C_FIELD(temp_v0_15, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                        M2C_FIELD(temp_v0_15, s32 *, 0x18) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                        M2C_FIELD(temp_v0_15, s32 *, 0x1C) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                        temp_v0_16 = temp_v0_15 + 0x14;
                        M2C_FIELD(temp_v0_15, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                        M2C_FIELD(temp_v0_16, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                        M2C_FIELD(temp_v0_16, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                        var_s0 += *var_s0 * 4;
                        var_s4 -= 1;
                        goto loop_94;
                    }
                    break;
                case 0x40:                          /* switch 2 */
                    var_s0 = var_s1 + 0x20;
                    goto block_93;
                case 0x3C:                          /* switch 2 */
                    var_s0_2 = var_s1 + 0x2C;
block_101:
                    D_800E53BC(&sp68, &D_800E53C8, M2C_FIELD(var_s1, s16 *, 0x16));
                    temp_v0_17 = var_s5 << 5;
                    var_s5 += 1;
                    temp_v0_18 = temp_v0_17 + D_800E53E8;
                    M2C_FIELD(temp_v0_18, s32 *, 0) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $0 */);
                    M2C_FIELD(temp_v0_18, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $1 */);
                    M2C_FIELD(temp_v0_18, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $2 */);
                    M2C_FIELD(temp_v0_18, s32 *, 0xC) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $3 */);
                    M2C_FIELD(temp_v0_18, s32 *, 0x10) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $4 */);
                    M2C_FIELD(temp_v0_18, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                    M2C_FIELD(temp_v0_18, s32 *, 0x18) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                    M2C_FIELD(temp_v0_18, s32 *, 0x1C) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                    temp_v0_19 = temp_v0_18 + 0x14;
                    M2C_FIELD(temp_v0_18, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                    M2C_FIELD(temp_v0_19, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                    M2C_FIELD(temp_v0_19, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                    M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                    var_s4_2 = M2C_FIELD(var_s1, u8 *, 2);
                    if ((s32) var_s4_2 > 0) {
                        var_v0_5 = var_s5 < 0x200;
loop_103:
                        if (var_v0_5 != 0) {
                            func_80065710(&sp10, var_s0_2 + 8, &sp20);
                            D_800E53BC(&sp68, &D_800E53C8, M2C_FIELD(var_s0_2, s16 *, 0x16));
                            temp_v0_20 = var_s5 << 5;
                            var_s5 += 1;
                            temp_v0_21 = temp_v0_20 + D_800E53E8;
                            M2C_FIELD(temp_v0_21, s32 *, 0) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $0 */);
                            M2C_FIELD(temp_v0_21, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $1 */);
                            M2C_FIELD(temp_v0_21, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $2 */);
                            M2C_FIELD(temp_v0_21, s32 *, 0xC) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $3 */);
                            M2C_FIELD(temp_v0_21, s32 *, 0x10) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $4 */);
                            M2C_FIELD(temp_v0_21, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                            M2C_FIELD(temp_v0_21, s32 *, 0x18) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                            M2C_FIELD(temp_v0_21, s32 *, 0x1C) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                            temp_v0_22 = temp_v0_21 + 0x14;
                            M2C_FIELD(temp_v0_21, s32 *, 0x14) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t4, $5 */);
                            M2C_FIELD(temp_v0_22, s32 *, 4) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t5, $6 */);
                            M2C_FIELD(temp_v0_22, s32 *, 8) = (s32) M2C_ERROR(/* unknown instruction: cfc2 $t6, $7 */);
                            var_s0_2 += M2C_FIELD(var_s0_2, u8 *, 0) * 4;
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                            var_s4_2 -= 1;
                            var_v0_5 = var_s5 < 0x200;
                            if ((s32) var_s4_2 > 0) {
                                goto loop_103;
                            }
                        }
block_105:
                    }
                    break;
                case 0x2C:                          /* switch 2 */
                    var_s0_2 = var_s1 + 0x20;
                    goto block_101;
                case 0x38:                          /* switch 2 */
                    var_s0_2 = var_s1 + 0x28;
                    goto block_101;
                case 0x28:                          /* switch 2 */
                    var_s0_2 = var_s1 + 0x1C;
                    goto block_101;
                }
block_106:
                var_s1 += M2C_FIELD(var_s1, u8 *, 0) * 4;
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
        spFC = var_s5;
        var_s5_2 = 0;
        var_s1_2 = M2C_FIELD(&D_800AD9EC, void **, 0);
        D_800E5374 = &sp38;
        if (var_s1_2 != M2C_FIELD(&D_800AD9EC, s32 *, 4)) {
            sp100 = &sp58;
loop_109:
            if (var_s5_2 < spFC) {
                if (M2C_FIELD(var_s1_2, u8 *, 2) == 0) {
                    if ((u8) M2C_FIELD(var_s1_2, u8 *, 7) < 0xECU) {
                        temp_v0_23 = (M2C_FIELD(var_s1_2, u8 *, 3) + 1) * 4;
                        spE4 = temp_v0_23;
                        var_s3 = func_80068EE8(temp_v0_23);
                        if (var_s3 != NULL) {
                            temp_s2 = M2C_FIELD(var_s1_2, u16 *, 0x14) & 0x60;
                            spF0 = temp_s2;
                            if (M2C_FIELD(var_s1_2, u8 *, 7) & 4) {
                                temp_v0_24 = M2C_FIELD(var_s1_2, void **, 0x1C);
                                spE0 = var_s3;
                                M2C_FIELD(var_s3, u16 *, 0xE) = (u16) M2C_FIELD(temp_v0_24, u16 *, 2);
                                spF0 = temp_s2 | (M2C_FIELD(temp_v0_24, u16 *, 0) & 0xFF9F);
                                M2C_FIELD(var_s3, u8 *, 3) = (u8) M2C_FIELD(var_s1_2, u8 *, 3);
                                spF8 = M2C_FIELD(var_s1_2, void **, 0x1C);
                                goto block_118;
                            }
                            temp_s0 = var_s3;
                            spE0 = var_s3;
                            var_s3 += 8;
                            spE4 += 8;
                            if (func_80068EE8(8) != NULL) {
                                M2C_FIELD(var_s3, u8 *, 3) = (u8) M2C_FIELD(var_s1_2, u8 *, 3);
                                M2C_FIELD(temp_s0, u8 *, 3) = 1U;
                                M2C_FIELD(temp_s0, s32 *, 4) = (s32) (temp_s2 | 0xE1000200);
                                temp_t3 = M2C_FIELD(var_s3, u8 *, 3) + M2C_FIELD(temp_s0, u8 *, 3) + 1;
                                if (temp_t3 < 0xB) {
                                    M2C_FIELD(temp_s0, u8 *, 3) = (u8) temp_t3;
                                    M2C_FIELD(var_s3, s32 *, 0) = 0;
                                }
block_118:
                                M2C_FIELD(var_s3, s32 *, 4) = (s32) M2C_FIELD(var_s1_2, s32 *, 4);
                                goto block_119;
                            }
                        }
                    } else {
block_119:
                        temp_v1_7 = M2C_FIELD(var_s1_2, u8 *, 1) & 0xF0;
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
                        spD8 = 0;
                        sp110 = (M2C_UNK *)3;
                        temp_t3_2 = ((M2C_FIELD(var_s1_2, u8 *, 1) & 0xF) << 5) + &D_800ADA08;
                        temp_v1_8 = M2C_FIELD(var_s1_2, u8 *, 7) & ~3;
                        switch (temp_v1_8) {        /* switch 3 */
                        case 0x50:                  /* switch 3 */
                            sp110 = (M2C_UNK *)4;
                            M2C_FIELD(var_s3, void **, 0xC) = (void *) M2C_FIELD(var_s1_2, void **, 0x20);
                            /* fallthrough */
                        case 0x40:                  /* switch 3 */
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $5 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $6 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $7 */);
                            M2C_ERROR(/* unknown instruction: mtc2 $zero, $0 */);
                            M2C_ERROR(/* unknown instruction: mtc2 $zero, $1 */);
                            M2C_ERROR(/* unknown instruction: rtps */);
                            M2C_ERROR(/* unknown instruction: swc2 $14, ($v0) */);
                            M2C_ERROR(/* unknown instruction: swc2 $19, ($t9) */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $5 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $6 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $7 */);
                            var_s5_2 = var_s5_2 + 1 + 1;
                            M2C_ERROR(/* unknown instruction: lwc2 $0, ($v0) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $1, 0x4($v0) */);
                            M2C_ERROR(/* unknown instruction: rtps */);
                            M2C_ERROR(/* unknown instruction: swc2 $14, ($v0) */);
                            M2C_ERROR(/* unknown instruction: swc2 $19, ($v0) */);
block_150:
                            spD8 = (s32) (sp58 + sp5C) >> 1;
                            break;
                        case 0x48:                  /* switch 3 */
                        case 0x4C:                  /* switch 3 */
                        case 0x58:                  /* switch 3 */
                        case 0x5C:                  /* switch 3 */
                            M2C_FIELD(var_s3, void **, 0x14) = (void *)0x55555555;
                            break;
                        case 0x34:                  /* switch 3 */
                            M2C_FIELD(var_s3, void **, 0x10) = (void *) M2C_FIELD(var_s1_2, void **, 0x20);
                            M2C_FIELD(var_s3, void **, 0x1C) = (void *) M2C_FIELD(var_s1_2, void **, 0x24);
                            M2C_FIELD(var_s3, u16 *, 0x18) = (u16) M2C_FIELD(spF8, u16 *, 6);
                            M2C_FIELD(var_s3, u16 *, 0x1A) = spF0;
                            M2C_FIELD(var_s3, u16 *, 0x24) = (u16) M2C_FIELD(spF8, u16 *, 8);
block_135:
                            M2C_FIELD(var_s3, void **, 0xC) = (u16) M2C_FIELD(spF8, u16 *, 4);
                        case 0x20:                  /* switch 3 */
block_136:
                            var_a2_3 = 0;
                            var_a1 = &D_800ADB58;
                            var_a0_2 = temp_t3_2;
                            do {
                                temp_v1_9 = M2C_FIELD(var_a0_2, s16 *, 0);
                                temp_v0_25 = M2C_FIELD(var_s1_2, s16 *, 0x18);
                                sp88[0] = (MULT_HI(temp_v1_9, temp_v0_25) << 0x14) | ((u32) (temp_v1_9 * temp_v0_25) >> 0xC);
                                temp_v1_10 = M2C_FIELD(var_a0_2, s16 *, 2);
                                temp_v0_26 = M2C_FIELD(var_s1_2, s16 *, 0x1A);
                                sp8C = (MULT_HI(temp_v1_10, temp_v0_26) << 0x14) | ((u32) (temp_v1_10 * temp_v0_26) >> 0xC);
                                sp90 = (s32) M2C_FIELD(var_a0_2, s16 *, 4);
                                M2C_FIELD(var_a1, u16 *, 0) = (u16) (&sp88[0])[var_t2];
                                M2C_FIELD(var_a1, u16 *, 2) = (u16) (&sp88[0])[var_fp];
                                M2C_FIELD(var_a1, u16 *, 4) = (u16) (&sp88[0])[var_s7];
                                var_a1 += 8;
                                var_a2_3 += 1;
                                var_a0_2 += 8;
                            } while (var_a2_3 < 3);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $5 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $6 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $7 */);
                            var_s5_2 += 1;
                            M2C_ERROR(/* unknown instruction: lwc2 $0, ($t8) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $1, 0x4($t8) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $2, 0x8($t8) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $3, 0xc($t8) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $4, 0x10($t8) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $5, 0x14($t8) */);
                            M2C_ERROR(/* unknown instruction: rtpt */);
                            M2C_ERROR(/* unknown instruction: swc2 $12, 0x8($s3) */);
                            temp_v1_11 = M2C_FIELD(var_s1_2, u8 *, 7) & ~3;
                            switch (temp_v1_11) {   /* switch 4; irregular */
                            case 0x20:              /* switch 4 */
                                M2C_ERROR(/* unknown instruction: swc2 $13, 0xc($s3) */);
                                M2C_ERROR(/* unknown instruction: swc2 $14, 0x10($s3) */);
                                break;
                            case 0x30:              /* switch 4 */
                                M2C_ERROR(/* unknown instruction: swc2 $13, 0x10($s3) */);
                                M2C_ERROR(/* unknown instruction: swc2 $14, 0x18($s3) */);
                                break;
                            case 0x24:              /* switch 4 */
                                M2C_ERROR(/* unknown instruction: swc2 $13, 0x10($s3) */);
                                M2C_ERROR(/* unknown instruction: swc2 $14, 0x18($s3) */);
                                break;
                            case 0x34:              /* switch 4 */
                                M2C_ERROR(/* unknown instruction: swc2 $13, 0x14($s3) */);
                                M2C_ERROR(/* unknown instruction: swc2 $14, 0x20($s3) */);
                                break;
                            }
                            M2C_ERROR(/* unknown instruction: swc2 $17, ($a3) */);
                            M2C_ERROR(/* unknown instruction: swc2 $18, 0x4($a3) */);
                            M2C_ERROR(/* unknown instruction: swc2 $19, 0x8($a3) */);
                            goto block_150;
                        case 0x30:                  /* switch 3 */
                            M2C_FIELD(var_s3, void **, 0xC) = (void *) M2C_FIELD(var_s1_2, void **, 0x1C);
                            M2C_FIELD(var_s3, void **, 0x14) = (void *) M2C_FIELD(var_s1_2, void **, 0x20);
                            goto block_136;
                        case 0x24:                  /* switch 3 */
                            M2C_FIELD(var_s3, void **, 0x14) = (u16) M2C_FIELD(spF8, u16 *, 6);
                            M2C_FIELD(var_s3, u16 *, 0x16) = spF0;
                            M2C_FIELD(var_s3, void **, 0x1C) = (u16) M2C_FIELD(spF8, u16 *, 8);
                            goto block_135;
                        case 0x38:                  /* switch 3 */
                            M2C_FIELD(var_s3, void **, 0xC) = (void *) M2C_FIELD(var_s1_2, void **, 0x1C);
                            M2C_FIELD(var_s3, void **, 0x14) = (void *) M2C_FIELD(var_s1_2, void **, 0x20);
                            M2C_FIELD(var_s3, void **, 0x1C) = (void *) M2C_FIELD(var_s1_2, void **, 0x24);
                        case 0x28:                  /* switch 3 */
block_155:
                            var_a2_4 = 0;
                            var_a1_2 = &D_800ADB58;
                            var_a0_3 = temp_t3_2;
                            do {
                                temp_v1_12 = M2C_FIELD(var_a0_3, s16 *, 0);
                                temp_v0_27 = M2C_FIELD(var_s1_2, s16 *, 0x18);
                                sp88[0] = (MULT_HI(temp_v1_12, temp_v0_27) << 0x14) | ((u32) (temp_v1_12 * temp_v0_27) >> 0xC);
                                temp_v1_13 = M2C_FIELD(var_a0_3, s16 *, 2);
                                temp_v0_28 = M2C_FIELD(var_s1_2, s16 *, 0x1A);
                                sp8C = (MULT_HI(temp_v1_13, temp_v0_28) << 0x14) | ((u32) (temp_v1_13 * temp_v0_28) >> 0xC);
                                sp90 = (s32) M2C_FIELD(var_a0_3, s16 *, 4);
                                M2C_FIELD(var_a1_2, u16 *, 0) = (u16) (&sp88[0])[var_t2];
                                M2C_FIELD(var_a1_2, u16 *, 2) = (u16) (&sp88[0])[var_fp];
                                M2C_FIELD(var_a1_2, u16 *, 4) = (u16) (&sp88[0])[var_s7];
                                var_a1_2 += 8;
                                var_a2_4 += 1;
                                var_a0_3 += 8;
                            } while (var_a2_4 < 4);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $5 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $6 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $7 */);
                            var_s5_2 += 1;
                            M2C_ERROR(/* unknown instruction: lwc2 $0, 0x8($t8) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $1, 0xc($t8) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $2, 0x10($t8) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $3, 0x14($t8) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $4, 0x18($t8) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $5, 0x1c($t8) */);
                            M2C_ERROR(/* unknown instruction: rtpt */);
                            temp_v1_14 = M2C_FIELD(var_s1_2, u8 *, 7) & ~3;
                            switch (temp_v1_14) {   /* switch 5; irregular */
                            case 0x28:              /* switch 5 */
                                M2C_ERROR(/* unknown instruction: swc2 $12, 0xc($s3) */);
                                M2C_ERROR(/* unknown instruction: swc2 $13, 0x10($s3) */);
                                M2C_ERROR(/* unknown instruction: swc2 $14, 0x14($s3) */);
                                break;
                            case 0x38:              /* switch 5 */
                            case 0x2C:              /* switch 5 */
                                M2C_ERROR(/* unknown instruction: swc2 $12, 0x10($s3) */);
                                M2C_ERROR(/* unknown instruction: swc2 $13, 0x18($s3) */);
                                M2C_ERROR(/* unknown instruction: swc2 $14, 0x20($s3) */);
                                break;
                            case 0x3C:              /* switch 5 */
                                M2C_ERROR(/* unknown instruction: swc2 $12, 0x14($s3) */);
                                M2C_ERROR(/* unknown instruction: swc2 $13, 0x20($s3) */);
                                M2C_ERROR(/* unknown instruction: swc2 $14, 0x2c($s3) */);
                                break;
                            }
                            M2C_ERROR(/* unknown instruction: swc2 $17, 0x4($a3) */);
                            M2C_ERROR(/* unknown instruction: swc2 $18, 0x8($a3) */);
                            M2C_ERROR(/* unknown instruction: swc2 $19, 0xc($a3) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $0, ($s6) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $1, 0x4($s6) */);
                            M2C_ERROR(/* unknown instruction: rtps */);
                            M2C_ERROR(/* unknown instruction: swc2 $14, ($v0) */);
                            M2C_ERROR(/* unknown instruction: swc2 $19, ($a3) */);
                            spD8 = (s32) (sp58 + sp5C + sp60 + sp64) >> 2;
                            break;
                        case 0x3C:                  /* switch 3 */
                            M2C_FIELD(var_s3, void **, 0x10) = (void *) M2C_FIELD(var_s1_2, void **, 0x20);
                            M2C_FIELD(var_s3, void **, 0x1C) = (void *) M2C_FIELD(var_s1_2, void **, 0x24);
                            M2C_FIELD(var_s3, void **, 0x28) = (void *) M2C_FIELD(var_s1_2, void **, 0x28);
                            M2C_FIELD(var_s3, u16 *, 0x18) = (u16) M2C_FIELD(spF8, u16 *, 6);
                            M2C_FIELD(var_s3, u16 *, 0x24) = (u16) M2C_FIELD(spF8, u16 *, 8);
                            M2C_FIELD(var_s3, u16 *, 0x1A) = spF0;
                            M2C_FIELD(var_s3, u16 *, 0x30) = (u16) M2C_FIELD(spF8, u16 *, 0xA);
block_154:
                            M2C_FIELD(var_s3, void **, 0xC) = (u16) M2C_FIELD(spF8, u16 *, 4);
                            goto block_155;
                        case 0x2C:                  /* switch 3 */
                            M2C_FIELD(var_s3, void **, 0x14) = (u16) M2C_FIELD(spF8, u16 *, 6);
                            M2C_FIELD(var_s3, void **, 0x1C) = (u16) M2C_FIELD(spF8, u16 *, 8);
                            M2C_FIELD(var_s3, u16 *, 0x16) = spF0;
                            M2C_FIELD(var_s3, u16 *, 0x24) = (u16) M2C_FIELD(spF8, u16 *, 0xA);
                            goto block_154;
                        case 0xE8:                  /* switch 3 */
                            M2C_FIELD(var_s3, void **, 0xC) = (void *) M2C_FIELD(var_s1_2, void **, 0x28);
                            M2C_FIELD(var_s3, void **, 0x14) = (void *) M2C_FIELD(var_s1_2, void **, 0x2C);
                            M2C_FIELD(var_s3, s8 *, 7) = 0x38;
                            M2C_FIELD(var_s3, void **, 0x1C) = (void *) M2C_FIELD(var_s1_2, void **, 0x30);
block_173:
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $5 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $6 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $7 */);
                            var_s5_2 += 1;
                            M2C_ERROR(/* unknown instruction: mtc2 $zero, $0 */);
                            M2C_ERROR(/* unknown instruction: mtc2 $zero, $1 */);
                            M2C_ERROR(/* unknown instruction: rtps */);
                            temp_v1_15 = M2C_FIELD(var_s1_2, u8 *, 7) & ~3;
                            switch (temp_v1_15) {   /* switch 6; irregular */
                            case 0xE0:              /* switch 6 */
                                temp_t0 = M2C_ERROR(/* unknown instruction: mfc2 $t0, $14 */);
                                temp_t1 = temp_t0 >> 0x10;
                                M2C_FIELD(var_s3, void **, 0xC) = (void *) ((((s16) M2C_FIELD(var_s1_2, void **, 0x1C) + temp_t0) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x1E) + temp_t1) << 0x10));
                                M2C_FIELD(var_s3, void **, 0x10) = (void *) ((((s16) M2C_FIELD(var_s1_2, void **, 0x20) + temp_t0) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x22) + temp_t1) << 0x10));
                                M2C_FIELD(var_s3, void **, 0x14) = (void *) ((((s16) M2C_FIELD(var_s1_2, void **, 0x24) + temp_t0) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x26) + temp_t1) << 0x10));
                                break;
                            case 0xE8:              /* switch 6 */
                                temp_t0_2 = M2C_ERROR(/* unknown instruction: mfc2 $t0, $14 */);
                                temp_t1_2 = temp_t0_2 >> 0x10;
                                M2C_FIELD(var_s3, void **, 0x10) = (void *) ((((s16) M2C_FIELD(var_s1_2, void **, 0x1C) + temp_t0_2) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x1E) + temp_t1_2) << 0x10));
                                M2C_FIELD(var_s3, u16 *, 0x18) = (s32) ((((s16) M2C_FIELD(var_s1_2, void **, 0x20) + temp_t0_2) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x22) + temp_t1_2) << 0x10));
                                M2C_FIELD(var_s3, s32 *, 0x20) = (s32) ((((s16) M2C_FIELD(var_s1_2, void **, 0x24) + temp_t0_2) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x26) + temp_t1_2) << 0x10));
                                break;
                            case 0xA4:              /* switch 6 */
                                temp_t0_3 = M2C_ERROR(/* unknown instruction: mfc2 $t0, $14 */);
                                temp_t1_3 = temp_t0_3 >> 0x10;
                                M2C_FIELD(var_s3, void **, 0x10) = (void *) ((((s16) M2C_FIELD(var_s1_2, void **, 0x20) + temp_t0_3) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x22) + temp_t1_3) << 0x10));
                                M2C_FIELD(var_s3, u16 *, 0x18) = (s32) ((((s16) M2C_FIELD(var_s1_2, void **, 0x24) + temp_t0_3) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x26) + temp_t1_3) << 0x10));
                                M2C_FIELD(var_s3, s32 *, 0x20) = (s32) ((((s16) M2C_FIELD(var_s1_2, void **, 0x28) + temp_t0_3) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x2A) + temp_t1_3) << 0x10));
                                break;
                            case 0xB4:              /* switch 6 */
                                temp_t0_4 = M2C_ERROR(/* unknown instruction: mfc2 $t0, $14 */);
                                temp_t1_4 = temp_t0_4 >> 0x10;
                                M2C_FIELD(var_s3, void **, 0x14) = (void *) ((((s16) M2C_FIELD(var_s1_2, void **, 0x20) + temp_t0_4) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x22) + temp_t1_4) << 0x10));
                                M2C_FIELD(var_s3, s32 *, 0x20) = (s32) ((((s16) M2C_FIELD(var_s1_2, void **, 0x24) + temp_t0_4) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x26) + temp_t1_4) << 0x10));
                                M2C_FIELD(var_s3, s32 *, 0x2C) = (s32) ((((s16) M2C_FIELD(var_s1_2, void **, 0x28) + temp_t0_4) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x2A) + temp_t1_4) << 0x10));
                                break;
                            }
                            temp_t0_5 = M2C_ERROR(/* unknown instruction: mfc2 $t0, $14 */);
                            M2C_ERROR(/* unknown instruction: swc2 $19, ($v0) */);
                            M2C_FIELD(var_s3, s32 *, 8) = (s32) (((M2C_FIELD(var_s1_2, s16 *, 0x18) + temp_t0_5) & 0xFFFF) | ((M2C_FIELD(var_s1_2, s16 *, 0x1A) + (temp_t0_5 >> 0x10)) << 0x10));
                            break;
                        case 0xB4:                  /* switch 3 */
                            M2C_FIELD(var_s3, void **, 0x10) = (void *) M2C_FIELD(var_s1_2, void **, 0x28);
                            M2C_FIELD(var_s3, void **, 0x1C) = (void *) M2C_FIELD(var_s1_2, void **, 0x2C);
                            M2C_FIELD(var_s3, void **, 0x28) = (void *) M2C_FIELD(var_s1_2, void **, 0x30);
                            M2C_FIELD(var_s3, u16 *, 0x18) = (u16) M2C_FIELD(spF8, u16 *, 6);
                            M2C_FIELD(var_s3, u16 *, 0x24) = (u16) M2C_FIELD(spF8, u16 *, 8);
                            M2C_FIELD(var_s3, s8 *, 7) = 0x3C;
                            M2C_FIELD(var_s3, u16 *, 0x1A) = spF0;
                            M2C_FIELD(var_s3, u16 *, 0x30) = (u16) M2C_FIELD(spF8, u16 *, 0xA);
block_171:
                            M2C_FIELD(var_s3, void **, 0xC) = (u16) M2C_FIELD(spF8, u16 *, 4);
                            goto block_173;
                        case 0xA4:                  /* switch 3 */
                            M2C_FIELD(var_s3, void **, 0x14) = (u16) M2C_FIELD(spF8, u16 *, 6);
                            M2C_FIELD(var_s3, void **, 0x1C) = (u16) M2C_FIELD(spF8, u16 *, 8);
                            M2C_FIELD(var_s3, s8 *, 7) = 0x2C;
                            M2C_FIELD(var_s3, u16 *, 0x16) = spF0;
                            M2C_FIELD(var_s3, u16 *, 0x24) = (u16) M2C_FIELD(spF8, u16 *, 0xA);
                            goto block_171;
                        case 0xE0:                  /* switch 3 */
                            M2C_FIELD(var_s3, s8 *, 7) = 0x28;
                            goto block_173;
                        case 0x10:                  /* switch 3 */
                            var_s5_2 = func_80068720(var_s1_2 + 0x14, var_s1_2 + 0x1C, var_s5_2, 3);
                            break;
                        case 0xF0:                  /* switch 3 */
                            D_800E53B8 = M2C_FIELD(var_s1_2, s32 *, 8);
                            break;
                        }
                        if (spD8 != 0) {
                            temp_v1_16 = (s32) (spD8 - func_8008B984()) >> 3;
                            spD8 = temp_v1_16;
                            temp_v1_17 = temp_v1_16 + D_800E53B8;
                            spD8 = temp_v1_17;
                            if (temp_v1_17 < 2) {
                                var_v0_6 = 2;
                                goto block_192;
                            }
                            if (temp_v1_17 >= 0x1000) {
                                var_v0_6 = 0xFFF;
block_192:
                                spD8 = var_v0_6;
                            }
                            spDC = M2C_ERROR(/* unknown instruction: cfc2 $t4, $31 */);
                            if (spDC >= 0) {
                                temp_a0_4 = (spD8 * 4) + arg0;
                                *spE0 = (*spE0 & 0xFF000000) | (*temp_a0_4 & 0xFFFFFF);
                                *temp_a0_4 = (*temp_a0_4 & 0xFF000000) | ((s32) spE0 & 0xFFFFFF);
                            }
                        }
                        goto block_199;
                    }
                } else {
                    temp_v0_29 = M2C_FIELD(var_s1_2, u8 *, 7) & ~3;
                    switch (temp_v0_29) {           /* switch 7 */
                    case 0x28:                      /* switch 7 */
                    case 0x2C:                      /* switch 7 */
                    case 0x38:                      /* switch 7 */
                    case 0x3C:                      /* switch 7 */
                    case 0x40:                      /* switch 7 */
                    case 0x50:                      /* switch 7 */
                        var_s5_2 = var_s5_2 + 1 + M2C_FIELD(var_s1_2, u8 *, 2);
                        break;
                    }
block_199:
                    var_s1_2 += M2C_FIELD(var_s1_2, u8 *, 0) * 4;
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
            D_800E5374 = &sp38;
            var_s1_3 = M2C_FIELD(&D_800AD9EC, void **, 0);
            D_800E53B8 = -0xA;
            if (var_s1_3 != M2C_FIELD(&D_800AD9EC, s32 *, 4)) {
                sp104 = 0xFFFFFF;
loop_203:
                if (var_s5_2 < spFC) {
                    if (M2C_FIELD(var_s1_3, u8 *, 2) == 0) {
                        temp_v1_18 = M2C_FIELD(var_s1_3, u8 *, 7) & 0xFC;
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
                                    D_800E53B8 = M2C_FIELD(var_s1_3, s32 *, 8);
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
                    if ((u8) M2C_FIELD(var_s1_3, u8 *, 7) < 0xECU) {
                        temp_v0_30 = (M2C_FIELD(var_s1_3, u8 *, 3) + 1) * 4;
                        spE4 = temp_v0_30;
                        var_s3 = func_80068EE8(temp_v0_30);
                        if (var_s3 != NULL) {
                            temp_s2_2 = M2C_FIELD(var_s1_3, u16 *, 0x14) & 0x60;
                            spF0 = temp_s2_2;
                            if (M2C_FIELD(var_s1_3, u8 *, 7) & 4) {
                                temp_v0_31 = M2C_FIELD(var_s1_3, void **, 0x1C);
                                spE0 = var_s3;
                                M2C_FIELD(var_s3, u16 *, 0xE) = (u16) M2C_FIELD(temp_v0_31, u16 *, 2);
                                spF0 = temp_s2_2 | (M2C_FIELD(temp_v0_31, u16 *, 0) & 0xFF9F);
                                M2C_FIELD(var_s3, u8 *, 3) = (u8) M2C_FIELD(var_s1_3, u8 *, 3);
                                spF8 = M2C_FIELD(var_s1_3, void **, 0x1C);
                                goto block_244;
                            }
                            temp_s0_2 = var_s3;
                            spE0 = var_s3;
                            var_s3 += 8;
                            spE4 += 8;
                            if (func_80068EE8(8) != NULL) {
                                M2C_FIELD(var_s3, u8 *, 3) = (u8) M2C_FIELD(var_s1_3, u8 *, 3);
                                M2C_FIELD(temp_s0_2, u8 *, 3) = 1U;
                                M2C_FIELD(temp_s0_2, s32 *, 4) = (s32) (temp_s2_2 | 0xE1000200);
                                temp_t3_3 = M2C_FIELD(var_s3, u8 *, 3) + M2C_FIELD(temp_s0_2, u8 *, 3) + 1;
                                if (temp_t3_3 < 0xB) {
                                    M2C_FIELD(temp_s0_2, u8 *, 3) = (u8) temp_t3_3;
                                    M2C_FIELD(var_s3, s32 *, 0) = 0;
                                }
block_244:
                                M2C_FIELD(var_s3, s32 *, 4) = (s32) M2C_FIELD(var_s1_3, s32 *, 4);
                                goto block_245;
                            }
                        }
                    } else {
block_245:
                        temp_v1_19 = M2C_FIELD(var_s1_3, u8 *, 1) & 0xF0;
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
                        spD8 = 0;
                        sp110 = (M2C_UNK *)3;
                        var_t3 = ((M2C_FIELD(var_s1_3, u8 *, 1) & 0xF) * 0x10) + &D_800ADB28;
                        temp_v0_32 = M2C_FIELD(var_s1_3, u8 *, 7);
                        temp_v1_20 = temp_v0_32 & 0xFF & 0xFC;
                        spE8 = temp_v0_32 & 0x10;
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
                                    M2C_FIELD(var_s3, void **, 0xC) = (void *) M2C_FIELD(var_s1_3, void **, 0x1C);
                                    M2C_ERROR(/* unknown instruction: lwc2 $21, 0x1c($s0) */);
                                    sp110 = (M2C_UNK *)4;
                                    goto block_294;
                                }
                                M2C_FIELD(var_s3, u16 *, 0x14) = (u16) M2C_FIELD(spF8, u16 *, 6);
                                var_s0_3 = var_s1_3 + 0x20;
                                M2C_FIELD(var_s3, u16 *, 0x1C) = (u16) M2C_FIELD(spF8, u16 *, 8);
                                sp110 = (M2C_UNK *)4;
                                M2C_FIELD(var_s3, u16 *, 0x16) = spF0;
                                M2C_FIELD(var_s3, u16 *, 0x24) = (u16) M2C_FIELD(spF8, u16 *, 0xA);
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
                                    spD8 = 0;
                                }
                                goto block_335;
                            }
                            sp110 = (M2C_UNK *)4;
                            M2C_ERROR(/* unknown instruction: lwc2 $6, 0x4($s0) */);
block_269:
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $5 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $6 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $7 */);
                            var_s5_2 += 1;
                            M2C_ERROR(/* unknown instruction: mtc2 $zero, $0 */);
                            M2C_ERROR(/* unknown instruction: mtc2 $zero, $1 */);
                            M2C_ERROR(/* unknown instruction: rtps */);
                            M2C_ERROR(/* unknown instruction: swc2 $14, ($v0) */);
                            var_s4_3 = M2C_FIELD(var_s1_3, u8 *, 2);
                            if ((s32) var_s4_3 > 0) {
loop_271:
                                if (var_s5_2 < spFC) {
                                    M2C_ERROR(/* unknown instruction: swc2 $19, ($v0) */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $5 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $6 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t6, $7 */);
                                    var_s5_2 += 1;
                                    M2C_ERROR(/* unknown instruction: mtc2 $zero, $0 */);
                                    M2C_ERROR(/* unknown instruction: mtc2 $zero, $1 */);
                                    M2C_ERROR(/* unknown instruction: rtps */);
                                    temp_v0_33 = func_80068EE8(spE4);
                                    if (temp_v0_33 != NULL) {
                                        if (spE8 != 0) {
                                            M2C_ERROR(/* unknown instruction: swc2 $6, 0xc($s3) */);
                                        }
                                        M2C_ERROR(/* unknown instruction: swc2 $19, ($v0) */);
                                        spD8 = (s32) (sp58 + sp5C) >> 1;
                                        temp_v1_21 = (s32) (spD8 - func_8008B984()) >> 3;
                                        spD8 = temp_v1_21;
                                        temp_v1_22 = temp_v1_21 + D_800E53B8;
                                        spD8 = temp_v1_22;
                                        if (temp_v1_22 < 2) {
                                            var_v0_7 = 2;
                                            goto block_279;
                                        }
                                        if (temp_v1_22 >= 0x1000) {
                                            var_v0_7 = 0xFFF;
block_279:
                                            spD8 = var_v0_7;
                                        }
                                        spDC = M2C_ERROR(/* unknown instruction: cfc2 $t4, $31 */);
                                        if (spDC >= 0) {
                                            temp_a0_5 = (spD8 * 4) + arg0;
                                            *spE0 = (*spE0 & 0xFF000000) | (*temp_a0_5 & sp104);
                                            *temp_a0_5 = (*temp_a0_5 & 0xFF000000) | ((s32) spE0 & sp104);
                                        }
                                        M2C_ERROR(/* unknown instruction: swc2 $14, ($v0) */);
                                        var_a2_5 = ((s32) (temp_v0_33 - spE0) >> 2) - 1;
                                        if (var_a2_5 >= 0) {
                                            var_a0_4 = &temp_v0_33[var_a2_5];
                                            var_v1_2 = &spE0[var_a2_5];
                                            do {
                                                temp_v0_34 = *var_v1_2;
                                                var_v1_2 -= 4;
                                                var_a2_5 -= 1;
                                                *var_a0_4 = temp_v0_34;
                                                var_a0_4 -= 4;
                                            } while (var_a2_5 >= 0);
                                        }
                                        var_s3 = temp_v0_33 + (var_s3 - spE0);
                                        spE0 = temp_v0_33;
                                        sp58 = sp5C;
                                        M2C_ERROR(/* unknown instruction: swc2 $14, ($v0) */);
                                        if (spE8 != 0) {
                                            M2C_ERROR(/* unknown instruction: swc2 $6, 0x4($s3) */);
                                            M2C_ERROR(/* unknown instruction: lwc2 $6, 0x4($s0) */);
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
                            M2C_FIELD(var_s3, u16 *, 0x18) = (u16) M2C_FIELD(spF8, u16 *, 6);
                            M2C_FIELD(var_s3, u16 *, 0x24) = (u16) M2C_FIELD(spF8, u16 *, 8);
                            M2C_FIELD(var_s3, u16 *, 0x30) = (u16) M2C_FIELD(spF8, u16 *, 0xA);
                            var_s0_3 = var_s1_3 + 0x2C;
                            M2C_FIELD(var_s3, u16 *, 0x1A) = spF0;
                            M2C_FIELD(var_s3, s32 *, 0x10) = (s32) M2C_FIELD(var_s1_3, s32 *, 0x20);
                            M2C_ERROR(/* unknown instruction: lwc2 $21, 0x1c($s0) */);
                            sp110 = (M2C_UNK *)5;
block_292:
                            M2C_FIELD(var_s3, void **, 0xC) = (u16) M2C_FIELD(spF8, u16 *, 4);
block_294:
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t4, $5 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t5, $6 */);
                            M2C_ERROR(/* unknown instruction: ctc2 $t6, $7 */);
                            var_s5_2 += 1;
                            M2C_ERROR(/* unknown instruction: lwc2 $20, 0x4($s0) */);
                            var_a2_6 = 0;
                            var_a0_5 = &D_800ADB58;
                            var_a1_3 = var_t3;
                            do {
                                temp_v1_23 = M2C_FIELD(var_a1_3, s16 *, 0);
                                temp_v0_35 = M2C_FIELD(var_s1_3, s16 *, 0x18);
                                sp88[0] = (MULT_HI(temp_v1_23, temp_v0_35) << 0x14) | ((u32) (temp_v1_23 * temp_v0_35) >> 0xC);
                                temp_v1_24 = M2C_FIELD(var_a1_3, s16 *, 2);
                                temp_v0_36 = M2C_FIELD(var_s1_3, s16 *, 0x1A);
                                sp8C = (MULT_HI(temp_v1_24, temp_v0_36) << 0x14) | ((u32) (temp_v1_24 * temp_v0_36) >> 0xC);
                                sp90 = (s32) M2C_FIELD(var_a1_3, s16 *, 4);
                                M2C_FIELD(var_a0_5, u16 *, 0) = (u16) (&sp88[0])[var_t2_2];
                                M2C_FIELD(var_a0_5, u16 *, 2) = (u16) (&sp88[0])[var_fp_2];
                                M2C_FIELD(var_a0_5, u16 *, 4) = (u16) (&sp88[0])[var_s7_2];
                                var_a0_5 += 8;
                                var_a2_6 += 1;
                                var_a1_3 += 8;
                            } while (var_a2_6 < 2);
                            M2C_ERROR(/* unknown instruction: lwc2 $0, ($s6) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $1, 0x4($s6) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $2, 0x8($s6) */);
                            M2C_ERROR(/* unknown instruction: lwc2 $3, 0xc($s6) */);
                            M2C_ERROR(/* unknown instruction: rtpt */);
                            M2C_ERROR(/* unknown instruction: swc2 $12, 0x8($s3) */);
                            M2C_ERROR(/* unknown instruction: swc2 $13, ($v0) */);
                            var_s4_4 = M2C_FIELD(var_s1_3, u8 *, 2);
                            if ((s32) var_s4_4 > 0) {
loop_297:
                                if (var_s5_2 < spFC) {
                                    M2C_ERROR(/* unknown instruction: swc2 $17, ($v0) */);
                                    M2C_ERROR(/* unknown instruction: swc2 $18, 0x4($v0) */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t4, $5 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t5, $6 */);
                                    M2C_ERROR(/* unknown instruction: ctc2 $t6, $7 */);
                                    var_s5_2 += 1;
                                    var_a2_7 = 0;
                                    var_a0_6 = &D_800ADB58;
                                    var_a1_4 = var_t3;
                                    do {
                                        temp_v1_25 = M2C_FIELD(var_a1_4, s16 *, 0);
                                        temp_v0_37 = M2C_FIELD(var_s0_3, s16 *, 0x18);
                                        sp88[0] = (MULT_HI(temp_v1_25, temp_v0_37) << 0x14) | ((u32) (temp_v1_25 * temp_v0_37) >> 0xC);
                                        temp_v1_26 = M2C_FIELD(var_a1_4, s16 *, 2);
                                        temp_v0_38 = M2C_FIELD(var_s0_3, s16 *, 0x1A);
                                        temp_a3_2 = (u32) (temp_v1_26 * temp_v0_38) >> 0xC;
                                        sp8C = (MULT_HI(temp_v1_26, temp_v0_38) << 0x14) | temp_a3_2;
                                        sp90 = (s32) M2C_FIELD(var_a1_4, s16 *, 4);
                                        M2C_FIELD(var_a0_6, u16 *, 0) = (u16) (&sp88[0])[var_t2_2];
                                        M2C_FIELD(var_a0_6, u16 *, 2) = (u16) (&sp88[0])[var_fp_2];
                                        M2C_FIELD(var_a0_6, u16 *, 4) = (u16) (&sp88[0])[var_s7_2];
                                        var_a0_6 += 8;
                                        var_a2_7 += 1;
                                        var_a1_4 += 8;
                                    } while (var_a2_7 < 2);
                                    M2C_ERROR(/* unknown instruction: lwc2 $0, ($s6) */);
                                    M2C_ERROR(/* unknown instruction: lwc2 $1, 0x4($s6) */);
                                    M2C_ERROR(/* unknown instruction: lwc2 $2, 0x8($s6) */);
                                    M2C_ERROR(/* unknown instruction: lwc2 $3, 0xc($s6) */);
                                    M2C_ERROR(/* unknown instruction: rtpt */);
                                    sp108 = var_t2_2;
                                    sp10C = var_t3;
                                    var_s0_3 += M2C_FIELD(var_s0_3, u8 *, 0) * 4;
                                    temp_v0_39 = func_80068EE8(spE4, var_a1_4, var_a2_7, temp_a3_2);
                                    if (temp_v0_39 != NULL) {
                                        temp_v1_27 = M2C_FIELD(var_s1_3, u8 *, 7) & 0xFC;
                                        switch (temp_v1_27) { /* switch 8; irregular */
                                        case 0x28:  /* switch 8 */
                                            M2C_ERROR(/* unknown instruction: swc2 $12, 0x10($s3) */);
                                            M2C_ERROR(/* unknown instruction: swc2 $13, 0x14($s3) */);
                                            break;
                                        case 0x38:  /* switch 8 */
                                            M2C_ERROR(/* unknown instruction: swc2 $20, 0x14($s3) */);
                                            M2C_ERROR(/* unknown instruction: swc2 $21, 0x1c($s3) */);
                                            /* fallthrough */
                                        case 0x2C:  /* switch 8 */
                                            M2C_ERROR(/* unknown instruction: swc2 $12, 0x18($s3) */);
                                            M2C_ERROR(/* unknown instruction: swc2 $13, 0x20($s3) */);
                                            break;
                                        case 0x3C:  /* switch 8 */
                                            M2C_ERROR(/* unknown instruction: swc2 $12, 0x20($s3) */);
                                            M2C_ERROR(/* unknown instruction: swc2 $13, 0x2c($s3) */);
                                            M2C_ERROR(/* unknown instruction: swc2 $20, 0x1c($s3) */);
                                            M2C_ERROR(/* unknown instruction: swc2 $21, 0x28($s3) */);
                                            break;
                                        }
                                        M2C_ERROR(/* unknown instruction: swc2 $17, 0x8($v0) */);
                                        M2C_ERROR(/* unknown instruction: swc2 $18, 0xc($v0) */);
                                        sp108 = var_t2_2;
                                        sp10C = var_t3;
                                        spD8 = (s32) (sp58 + sp5C + sp60 + sp64) >> 2;
                                        temp_v1_28 = (s32) (spD8 - func_8008B984(sp64)) >> 3;
                                        spD8 = temp_v1_28;
                                        temp_v1_29 = temp_v1_28 + D_800E53B8;
                                        spD8 = temp_v1_29;
                                        if (temp_v1_29 < 2) {
                                            var_v0_8 = 2;
                                            goto block_316;
                                        }
                                        if (temp_v1_29 >= 0x1000) {
                                            var_v0_8 = 0xFFF;
block_316:
                                            spD8 = var_v0_8;
                                        }
                                        spDC = M2C_ERROR(/* unknown instruction: cfc2 $t4, $31 */);
                                        if (spDC >= 0) {
                                            temp_a0_6 = (spD8 * 4) + arg0;
                                            *spE0 = (*spE0 & 0xFF000000) | (*temp_a0_6 & sp104);
                                            *temp_a0_6 = (*temp_a0_6 & 0xFF000000) | ((s32) spE0 & sp104);
                                        }
                                        var_a2_8 = ((s32) (temp_v0_39 - spE0) >> 2) - 1;
                                        if (var_a2_8 >= 0) {
                                            var_a0_7 = &temp_v0_39[var_a2_8];
                                            var_v1_3 = &spE0[var_a2_8];
                                            do {
                                                temp_v0_40 = *var_v1_3;
                                                var_v1_3 -= 4;
                                                var_a2_8 -= 1;
                                                *var_a0_7 = temp_v0_40;
                                                var_a0_7 -= 4;
                                            } while (var_a2_8 >= 0);
                                        }
                                        var_s3 = temp_v0_39 + (var_s3 - spE0);
                                        spE0 = temp_v0_39;
                                        sp5C = sp64;
                                        sp58 = sp60;
                                        M2C_ERROR(/* unknown instruction: swc2 $12, 0x8($s3) */);
                                        M2C_ERROR(/* unknown instruction: swc2 $20, 0x4($s3) */);
                                        M2C_ERROR(/* unknown instruction: lwc2 $20, 0x4($s0) */);
                                        temp_v1_30 = M2C_FIELD(var_s1_3, u8 *, 7) & 0xFC;
                                        if (temp_v1_30 != 0x38) {
                                            if (temp_v1_30 < 0x39) {
                                                if (temp_v1_30 != 0x28) {
                                                    if (temp_v1_30 != 0x2C) {
                                                        var_s4_4 -= 1;
                                                    } else {
                                                        goto block_331;
                                                    }
                                                } else {
                                                    M2C_ERROR(/* unknown instruction: swc2 $13, 0xc($s3) */);
                                                    var_s4_4 -= 1;
                                                }
                                            } else if (temp_v1_30 != 0x3C) {
                                                var_s4_4 -= 1;
                                            } else {
                                                M2C_ERROR(/* unknown instruction: swc2 $13, 0x14($s3) */);
                                                M2C_ERROR(/* unknown instruction: swc2 $21, 0x10($s3) */);
                                                M2C_ERROR(/* unknown instruction: lwc2 $21, 0x1c($s0) */);
                                                var_s4_4 -= 1;
                                            }
                                        } else {
                                            M2C_ERROR(/* unknown instruction: swc2 $21, 0xc($s3) */);
                                            M2C_ERROR(/* unknown instruction: lwc2 $21, 0x1c($s0) */);
block_331:
                                            M2C_ERROR(/* unknown instruction: swc2 $13, 0x10($s3) */);
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
                                var_s1_3 += M2C_FIELD(var_s1_3, u8 *, 0) * 4;
                                if (var_s1_3 == M2C_FIELD(var_t9, s32 *, 4)) {
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
                M2C_ERROR(/* unknown instruction: ctc2 $t4, $0 */);
                M2C_ERROR(/* unknown instruction: ctc2 $t5, $1 */);
                M2C_ERROR(/* unknown instruction: ctc2 $t4, $2 */);
                M2C_ERROR(/* unknown instruction: ctc2 $t5, $3 */);
                M2C_ERROR(/* unknown instruction: ctc2 $t6, $4 */);
                M2C_ERROR(/* unknown instruction: ctc2 $t4, $5 */);
                M2C_ERROR(/* unknown instruction: ctc2 $t5, $6 */);
                M2C_ERROR(/* unknown instruction: ctc2 $t6, $7 */);
            }
        }
    }
}
