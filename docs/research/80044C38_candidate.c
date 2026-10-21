typedef signed char s8;
typedef signed short s16;
typedef signed int s32;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef signed int M2C_UNK;
s32 func_8001F294(void *);
M2C_UNK func_80040380(void *, s32);
M2C_UNK func_80042BAC(void *, M2C_UNK, s32);
M2C_UNK func_80043454(void *, s32);
M2C_UNK func_800437A4(void *, s32, s32, s32);
M2C_UNK func_80043F40(void *, s32, s32, u16);
M2C_UNK func_80044480(void *, M2C_UNK);
s32 func_80047688(void *);
M2C_UNK func_80048D24(void *);
M2C_UNK func_80048F68(void *);
M2C_UNK func_80048F7C(void *, s8 *, s32, s32);
M2C_UNK func_80053E14(void *);
M2C_UNK func_80053FF4(void *);
M2C_UNK func_80061CC0(s16, s16, u16, u16, s32);
M2C_UNK func_800629A0(void *, u16);
M2C_UNK func_80063BD4(u16);
M2C_UNK func_80063C68(void *, u16, void *, M2C_UNK);
s32 func_8007906C(M2C_UNK, u8, s32 *, s32 *, s32 *);
M2C_UNK func_800791C8(u8, s8 *, u8 *, s8 *);
s32 func_8008ACC0(u32);
s32 func_8008AD60(u32);
extern s32 D_800A4D30;
extern M2C_UNK D_800A4EF4;
extern s32 D_800A6070;
extern u8 D_800AED50;
extern u32 D_800C60E8;
extern s32 D_800D2FE0;
extern M2C_UNK D_800D2FE4;
extern s32 D_800D2FE8;
extern M2C_UNK D_800D3034;
extern s32 D_800DE30C;
extern s32 D_800E46BC;
extern M2C_UNK D_800EC0F8;
extern M2C_UNK D_800EE028;

static __inline__ void store_leading_sign_count(s32 value, s32 *result) {
    __asm__ volatile(
        "mtc2 %1,$30\n\t"
        "nop\n\t"
        "nop\n\t"
        "swc2 $31,%0"
        : "=m" (*result)
        : "r" (value));
}

static __inline__ s32 fixed_mul(s32 left, s32 right) {
    s32 low;
    s32 high;
    __asm__ volatile(
        "mult %2,%3\n\t"
        "mflo %0\n\t"
        "mfhi %1\n\t"
        "srl %0,%0,12\n\t"
        "sll %1,%1,20\n\t"
        "or %0,%0,%1"
        : "=&r" (low), "=&r" (high)
        : "r" (left), "r" (right));
    return low;
}

void func_80044C38(void *arg0) {
    s32 sp98;
    s32 sp94;
    s32 sp90;
    s32 sp8C;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    s32 sp78;
    s32 sp74;
    s32 sp70;
    s32 sp6C;
    s32 sp68;
    s32 sp64;
    s32 sp60;
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 sp4C;
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s8 sp22;
    u8 sp21;
    s8 sp20;
    s32 sp1C;
    s32 sp18;
    M2C_UNK *var_a2;
    u8 *var_v1;
    M2C_UNK var_s2;
    s32 *var_a0;
    s32 temp_a0;
    s32 temp_a0_10;
    s32 temp_a0_12;
    s32 temp_a0_13;
    s32 temp_a0_15;
    s32 temp_a0_16;
    s32 temp_a0_17;
    s32 temp_a0_2;
    s32 temp_a0_3;
    s32 temp_a0_4;
    s32 temp_a0_5;
    s32 temp_a0_6;
    s32 temp_a0_7;
    s32 temp_a0_8;
    s32 temp_a0_9;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_a1_3;
    s32 temp_a1_4;
    s32 temp_a1_5;
    s32 temp_a1_6;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_a2_4;
    s32 temp_a2_5;
    s32 temp_a2_6;
    s32 temp_a2_7;
    s32 temp_a2_8;
    s32 temp_a2_9;
    s32 temp_a3_10;
    s32 temp_a3_2;
    s32 temp_a3_3;
    s32 temp_a3_4;
    s32 temp_a3_5;
    s32 temp_a3_6;
    s32 temp_a3_7;
    s32 temp_a3_8;
    s32 temp_a3_9;
    s32 temp_lo;
    s32 temp_lo_2;
    s32 temp_s0;
    s32 temp_s0_2;
    s32 temp_s2;
    s32 temp_s2_2;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t1_3;
    s32 temp_t1_4;
    s32 temp_t2;
    s32 temp_t2_2;
    s32 temp_t2_3;
    s32 temp_v0;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_14;
    s32 temp_v0_15;
    s32 temp_v0_17;
    s32 temp_v0_18;
    s32 temp_v0_20;
    s32 temp_v0_21;
    s32 temp_v0_23;
    s32 temp_v0_24;
    s32 temp_v0_26;
    s32 temp_v0_27;
    s32 temp_v0_28;
    s32 temp_v0_29;
    s32 temp_v0_2;
    s32 temp_v0_30;
    s32 temp_v0_31;
    s32 temp_v0_33;
    s32 temp_v0_34;
    s32 temp_v0_35;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 temp_v1;
    s32 temp_v1_10;
    s32 temp_v1_11;
    s32 temp_v1_13;
    s32 temp_v1_15;
    s32 temp_v1_17;
    s32 temp_v1_20;
    s32 temp_v1_22;
    s32 temp_v1_24;
    s32 temp_v1_26;
    s32 temp_v1_28;
    s32 temp_v1_29;
    s32 temp_v1_31;
    s32 temp_v1_3;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 temp_v1_7;
    s32 var_a0_5;
    s32 var_a0_7;
    s32 var_a1;
    s32 var_a2_2;
    s32 var_a2_3;
    s32 var_a2_4;
    s32 var_a3;
    s32 var_lo;
    s32 var_lo_2;
    s32 var_lo_3;
    s32 var_lo_4;
    s32 var_lo_5;
    s32 var_lo_6;
    s32 var_lo_7;
    s32 var_lo_8;
    s32 var_s0;
    s32 var_s2_2;
    s32 var_s5;
    s32 var_t0;
    s32 var_t0_2;
    s32 var_v0;
    s32 var_v0_11;
    s32 var_v0_12;
    s32 var_v0_15;
    s32 var_v0_17;
    s32 var_v0_18;
    s32 var_v0_19;
    s32 var_v0_22;
    s32 var_v0_24;
    s32 var_v0_26;
    s32 var_v0_27;
    s32 var_v0_29;
    s32 var_v0_2;
    s32 var_v0_30;
    s32 var_v0_31;
    s32 var_v0_32;
    s32 var_v0_33;
    s32 var_v0_34;
    s32 var_v0_35;
    s32 var_v0_3;
    s32 var_v0_4;
    s32 var_v0_5;
    s32 var_v0_6;
    s32 var_v0_8;
    s32 var_v0_9;
    s32 var_v1_10;
    s32 var_v1_12;
    s32 var_v1_15;
    s32 var_v1_6;
    s32 var_v1_8;
    s8 temp_v0_10;
    s8 temp_v0_13;
    s8 temp_v0_16;
    s8 temp_v0_19;
    s8 temp_v1_8;
    s8 temp_v1_9;
    u16 temp_v0_32;
    u16 temp_v1_19;
    u16 temp_v1_30;
    s32 var_a0_4;
    u16 var_s4;
    u16 var_v0_14;
    u16 var_v0_21;
    u32 temp_a0_14;
    register u32 temp_s6 asm("$22");
    u32 temp_v1_12;
    u32 temp_v1_14;
    u32 temp_v1_16;
    u32 temp_v1_18;
    u32 temp_v1_21;
    u32 temp_v1_23;
    u32 temp_v1_25;
    u32 temp_v1_27;
    u32 temp_v1_2;
    u32 temp_v1_32;
    u32 temp_v1_4;
    u32 var_a0_2;
    u32 var_a1_2;
    u32 var_v0_10;
    u32 var_v0_13;
    u32 var_v0_16;
    u32 var_v0_20;
    u32 var_v0_23;
    u32 var_v0_25;
    u32 var_v0_28;
    u32 var_v0_7;
    u32 var_v1_11;
    u32 var_v1_13;
    u32 var_v1_14;
    u32 var_v1_16;
    u32 var_v1_2;
    u32 var_v1_3;
    u32 var_v1_4;
    u32 var_v1_5;
    u32 var_v1_7;
    u32 var_v1_9;
    u8 temp_v0_22;
    u8 temp_v0_25;
    u8 var_a0_3;
    void *temp_a0_11;
    void *temp_a3;
    void *var_a0_6;
    void *var_a0_8;
    var_a1 = 0;
    var_s5 = 0;
    temp_s6 = (u32) D_800C60E8 >> 4;
    var_v1 = (u8 *)&D_800EE028;
    if ((*(u8 *)((u8 *)(&D_800D2FE4) + 8)) != 0) {
        var_a2 = &D_800D2FE4;
        var_a0 = &D_800A4D30;
        do {
            if (!((*(u16 *)((u8 *)(var_v1)+(4))) & 0x4000)) {
                *var_a0 = 0;
            }
            var_a0 += 1;
            var_a1 += 1;
            var_v1 += 0x8C;
        } while (var_a1 < (s32) (*(u8 *)((u8 *)(&D_800D2FE4) + 8)));
    }
    if ((*(s32 *)((u8 *)(arg0)+(0x218))) & 1) {
        temp_v1 = (*(s32 *)((u8 *)(arg0)+(0x58C)));
        if (temp_v1 > 0) {
            temp_v0 = temp_v1 - D_800DE30C;
            (*(s32 *)((u8 *)(arg0)+(0x58C))) = temp_v0;
            if (temp_v0 <= 0) {
                (*(s32 *)((u8 *)(arg0)+(0x58C))) = 0;
            }
        }
        if (D_800DE30C > 0) {
            var_a2 = (M2C_UNK *) D_800DE30C;
            if (D_800DE30C < 0) {
                var_a2 = (M2C_UNK *) -(s32) var_a2;
            }
            store_leading_sign_count(0x1000, &sp18);
            var_a1 = sp18;
            var_a3 = sp18 - 0xC;
            if (var_a3 < 0) {
                temp_v1_2 = var_a1 << sp18;
                store_leading_sign_count((s32)var_a2, &sp1C);
                var_a2 = (M2C_UNK *)sp1C;
                var_a1 = sp1C;
                temp_a0 = var_a1 - sp18;
                if (temp_a0 >= 0) {
                    temp_v0_2 = 0xC - var_a1;
                    if (temp_v0_2 >= 0) {
                        var_v0 = (s32) var_a2 >> temp_v0_2;
                    } else {
                        var_v0 = (s32) var_a2 << -temp_v0_2;
                    }
                    var_v1_2 = (temp_v1_2 / (u32) var_v0) << temp_a0;
                    goto block_20;
                }
                var_a0_2 = temp_v1_2 / (u32) ((s32) var_a2 >> -var_a3);
            } else {
                var_v1_2 = 0x01000000U / (u32) var_a2;
block_20:
                var_a0_2 = var_v1_2;
            }
            if (D_800DE30C & 0x80000000) {
                var_a0_2 = (u32) -(s32) var_a0_2;
            }
            temp_v0_3 = (*(s32 *)((u8 *)(arg0)+(8))) - (*(s32 *)((u8 *)(arg0)+(0x14)));
            (*(s32 *)((u8 *)(arg0)+(0x20))) = fixed_mul(var_a0_2, temp_v0_3);
            temp_v0_4 = (*(s32 *)((u8 *)(arg0)+(0x10))) - (*(s32 *)((u8 *)(arg0)+(0x1C)));
            (*(s32 *)((u8 *)(arg0)+(0x28))) = fixed_mul(var_a0_2, temp_v0_4);
            (*(s32 *)((u8 *)(arg0)+(0x24))) = 0;
        } else {
            (*(s32 *)((u8 *)(arg0)+(0x24))) = 0;
            (*(s32 *)((u8 *)(arg0)+(0x28))) = 0;
            (*(s32 *)((u8 *)(arg0)+(0x20))) = 0;
        }
        var_s4 = (*(u16 *)((u8 *)(arg0)+(0x2C)));
        (*(u16 *)((u8 *)(arg0)+(0x2E))) = var_s4;
        (*(s32 *)((u8 *)(arg0)+(0x14))) = (s32) (*(s32 *)((u8 *)(arg0)+(8)));
        (*(s32 *)((u8 *)(arg0)+(0x1C))) = (s32) (*(s32 *)((u8 *)(arg0)+(0x10)));
        if ((*(u32 *)((u8 *)(arg0)+(0x584))) != 0) {
            temp_v1_3 = (*(s32 *)((u8 *)(arg0)+(0x57C))) - D_800DE30C;
            (*(s32 *)((u8 *)(arg0)+(0x57C))) = temp_v1_3;
            if ((temp_v1_3 < 0) || ((D_800D2FE8 == 1) && ((*(s32 *)((u8 *)(arg0)+(0xA4))) != 0))) {
                (*(u32 *)((u8 *)(arg0)+(0x584))) = 0U;
                (*(s32 *)((u8 *)(arg0)+(0x218))) = (s32) ((*(s32 *)((u8 *)(arg0)+(0x218))) & ~0x80);
            } else {
                temp_v1_4 = (*(u32 *)((u8 *)(arg0)+(0x584)));
                if ((temp_v1_4 < 4U) && (temp_v1_4 >= 2U)) {
                    temp_v1_5 = (*(s32 *)((u8 *)(arg0)+(0x580))) - D_800DE30C;
                    (*(s32 *)((u8 *)(arg0)+(0x580))) = temp_v1_5;
                    if (temp_v1_5 < 0) {
                        (*(u32 *)((u8 *)(arg0)+(0x584))) = 1U;
                    }
                }
            }
        }
        temp_v1_6 = (*(s32 *)((u8 *)(arg0)+(0x264)));
        if ((temp_v1_6 != 0) && (temp_v1_6 < D_800D2FE0)) {
            (*(s32 *)((u8 *)(arg0)+(0x264))) = 0;
        }
        temp_v1_7 = (*(s32 *)((u8 *)(arg0)+(0x218)));
        if (temp_v1_7 & 8) {
            func_800437A4(arg0, var_a1, (s32) var_a2, var_a3);
            return;
        }
        if (!(temp_v1_7 & 2)) {
            func_80048F7C(arg0, &sp20, (s32) var_a2, var_a3);
            func_80048D24(arg0);
            if (func_80047688(arg0) != 0) {
                var_t0 = 0;
                if (((D_800D2FE8 == 0xB) || (D_800D2FE8 == 3) || (D_800D2FE8 == 1)) && ((*(s32 *)((u8 *)(arg0)+(0xA4))) != 0)) {
                    var_t0 = 0x8000;
                }
                temp_v0_5 = (*(s32 *)((u8 *)(arg0)+(8)));
                if (temp_v0_5 >= 0) {
                    var_v0_2 = temp_v0_5 >> 0xC;
                } else {
                    var_v0_2 = -((s32) -temp_v0_5 >> 0xC);
                }
                temp_a1 = (*(s32 *)((u8 *)(arg0)+(0x10)));
                if (temp_a1 >= 0) {
                    var_v0_3 = temp_a1 >> 0xC;
                } else {
                    var_v0_3 = -((s32) -temp_a1 >> 0xC);
                }
                func_80061CC0((s16) var_v0_2, (s16) var_v0_3, (*(u16 *)((u8 *)(arg0)+(0x2C))), (*(u16 *)((u8 *)(arg0)+(0x98))), var_t0 & 0xFFFF);
            }
            goto block_310;
        }
        func_800791C8((u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp20, &sp21, &sp22);
        func_80048F68(arg0);
        if ((*(s32 *)((u8 *)((((s32) (*(u16 *)((u8 *)(arg0)+(0x98))) * 0x9C) + &D_800D3034))+(0x4C))) == (*(s32 *)((u8 *)(arg0)+(0)))) {
            if ((*(s32 *)((u8 *)(arg0)+(0x94))) != 0) {
                sp24 = 0;
                sp28 = 0;
                sp2C = 0;
                var_s4 = (*(u16 *)((u8 *)(arg0)+(0x2C))) - 0x4000;
                if (func_8007906C(0xD, (u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp24, &sp28, &sp2C) != 0) {
                    var_s5 = D_800DE30C;
                } else if (func_8007906C(0xC, (u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp24, &sp28, &sp2C) == 0) {
                    if ((*(((s32) (*(u16 *)((u8 *)(arg0)+(0x98))) * 4) + &D_800EC0F8) == 1) && (D_800A6070 != 7)) {
                        var_v0_4 = sp2C < -0x28;
                        if (sp2C >= 0x29) {
                            var_s5 = D_800DE30C;
                            var_v0_4 = sp2C < -0x28;
                        }
                        if (var_v0_4 != 0) {
                            goto block_63;
                        }
                    } else {
                        var_s5 = 0;
                    }
                } else {
block_63:
                    var_s5 = -D_800DE30C;
                }
                if (sp22 < -0x28) {
                    temp_v1_8 = (u8) sp22 + 0x28;
                    sp22 = temp_v1_8;
                    (*(u16 *)((u8 *)(arg0)+(0x30))) = (u16) ((*(u16 *)((u8 *)(arg0)+(0x30))) + (-temp_v1_8 * temp_s6));
                } else if (sp22 >= 0x29) {
                    temp_v1_9 = (u8) sp22 - 0x28;
                    sp22 = temp_v1_9;
                    (*(u16 *)((u8 *)(arg0)+(0x30))) = (u16) ((*(u16 *)((u8 *)(arg0)+(0x30))) - (temp_v1_9 * temp_s6));
                }
            } else {
                var_s2 = 0;
                sp30 = 0;
                sp34 = 0;
                sp38 = 0;
                if (func_8007906C(0xD, (u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp30, &sp34, &sp38) != 0) {
                    var_s2 = 1;
                } else if (func_8007906C(0xC, (u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp30, &sp34, &sp38) != 0) {
                    var_s2 = -1;
                }
                func_80044480(arg0, var_s2);
                temp_a3 = ((*(s32 *)((u8 *)(arg0)+(0x9C))) * 0xD0) + &D_800A4EF4;
                temp_lo = ((u16) (*(u16 *)((u8 *)(temp_a3)+(0x98))) >> 1) * temp_s6;
                temp_a0_2 = (s32) (*(u16 *)((u8 *)(arg0)+(0x98)));
                var_s5 = -(sp20 << 5);
                temp_s2 = temp_lo + (temp_lo >> 1);
                var_s2_2 = temp_s2 + (temp_s2 >> 3);
                temp_a1_2 = *((temp_a0_2 * 4) + &D_800EC0F8);
                if (temp_a1_2 == 5) {
                    var_s2_2 += var_s2_2 >> 1;
                }
                var_s4 = (*(u16 *)((u8 *)(arg0)+(0x2C)));
                if ((*(s32 *)((u8 *)(((temp_a0_2 * 0x9C) + &D_800D3034))+(0x4C))) == (*(s32 *)((u8 *)(arg0)+(0)))) {
                    if (!((*(s32 *)((u8 *)(temp_a3)+(0x10))) & 1)) {
                        if (((temp_a1_2 == 1) || (temp_a1_2 == 6)) && (D_800A6070 != 7)) {
                            var_a0_3 = (u8) sp22;
                            var_v0_5 = var_a0_3 << 0x18;
                        } else {
                            var_a0_3 = sp21;
                            var_v0_5 = var_a0_3 << 0x18;
                        }
                        temp_v1_10 = var_v0_5 >> 0x18;
                        if (temp_v1_10 < -0x28) {
                            temp_v0_6 = -((s32) ((var_a0_3 + 0x28) << 0x18) >> 0xC);
                            if (temp_v0_6 < 0) {
                            }
                            store_leading_sign_count(temp_v0_6 < 0 ? -temp_v0_6 : temp_v0_6, &sp3C);
                            temp_v1_11 = sp3C;
                            temp_a3_2 = sp3C - 0xC;
                            if (temp_a3_2 < 0) {
                                temp_v1_12 = temp_v1_11 << sp3C;
                                store_leading_sign_count(0x58000, &sp40);
                                temp_a2 = sp40;
                                temp_a0_3 = sp40 - sp3C;
                                if (temp_a0_3 >= 0) {
                                    temp_v0_7 = 0xC - sp40;
                                    if (temp_v0_7 >= 0) {
                                        var_v0_6 = temp_a2 >> temp_v0_7;
                                    } else {
                                        var_v0_6 = temp_a2 << -temp_v0_7;
                                    }
                                    var_v1_3 = (temp_v1_12 / (u32) var_v0_6) << temp_a0_3;
                                    goto block_94;
                                }
                                var_v0_7 = temp_v1_12 / (u32) (temp_a2 >> -temp_a3_2);
                            } else {
                                var_v1_3 = (u32) (temp_v1_11 << 0xC) / (u32)temp_a2;
block_94:
                                var_v0_7 = var_v1_3;
                            }
                            var_lo = var_v0_7 * var_s2_2;
                            if (temp_v0_6 & 0x80000000) {
                                var_lo = -(s32) var_v0_7 * var_s2_2;
                            }
                            if (var_lo >= 0) {
                                var_v0_8 = var_lo >> 0xC;
                            } else {
                                var_v0_8 = -((s32) -var_lo >> 0xC);
                            }
                            var_s4 += var_v0_8;
                        } else if (temp_v1_10 >= 0x29) {
                            temp_v0_8 = (s32) ((var_a0_3 - 0x28) << 0x18) >> 0xC;
                            if (temp_v0_8 < 0) {
                            }
                            store_leading_sign_count(temp_v0_8 < 0 ? -temp_v0_8 : temp_v0_8, &sp44);
                            temp_v1_13 = sp44;
                            temp_a3_3 = sp44 - 0xC;
                            if (temp_a3_3 < 0) {
                                temp_v1_14 = temp_v1_13 << sp44;
                                store_leading_sign_count(0x58000, &sp48);
                                temp_a2_2 = sp48;
                                temp_a0_4 = sp48 - sp44;
                                if (temp_a0_4 >= 0) {
                                    temp_v0_9 = 0xC - sp48;
                                    if (temp_v0_9 >= 0) {
                                        var_v0_9 = temp_a2_2 >> temp_v0_9;
                                    } else {
                                        var_v0_9 = temp_a2_2 << -temp_v0_9;
                                    }
                                    var_v1_4 = (temp_v1_14 / (u32) var_v0_9) << temp_a0_4;
                                    goto block_112;
                                }
                                var_v0_10 = temp_v1_14 / (u32) (temp_a2_2 >> -temp_a3_3);
                            } else {
                                var_v1_4 = (u32) (temp_v1_13 << 0xC) / (u32)temp_a2_2;
block_112:
                                var_v0_10 = var_v1_4;
                            }
                            var_lo_2 = var_v0_10 * var_s2_2;
                            if (temp_v0_8 & 0x80000000) {
                                var_lo_2 = -(s32) var_v0_10 * var_s2_2;
                            }
                            if (var_lo_2 >= 0) {
                                var_v0_11 = var_lo_2 >> 0xC;
                            } else {
                                var_v0_11 = -((s32) -var_lo_2 >> 0xC);
                            }
                            var_s4 -= var_v0_11;
                        }
                        (*(u16 *)((u8 *)(arg0)+(0x30))) = 0U;
                    } else if (((temp_a1_2 == 1) || (temp_a1_2 == 6) || (func_8007906C(0x10, (u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp30, &sp34, &sp38) != 0)) && (D_800A6070 != 7)) {
                        if (sp22 < -0x28) {
                            temp_v0_10 = (u8) sp22 + 0x28;
                            sp22 = temp_v0_10;
                            temp_v0_11 = -((s32) (temp_v0_10 << 0x18) >> 0xC);
                            if (temp_v0_11 < 0) {
                            }
                            store_leading_sign_count(temp_v0_11 < 0 ? -temp_v0_11 : temp_v0_11, &sp4C);
                            temp_v1_15 = sp4C;
                            temp_a3_4 = sp4C - 0xC;
                            if (temp_a3_4 < 0) {
                                temp_v1_16 = temp_v1_15 << sp4C;
                                store_leading_sign_count(0x58000, &sp50);
                                temp_a2_3 = sp50;
                                temp_a0_5 = sp50 - sp4C;
                                if (temp_a0_5 >= 0) {
                                    temp_v0_12 = 0xC - sp50;
                                    if (temp_v0_12 >= 0) {
                                        var_v0_12 = temp_a2_3 >> temp_v0_12;
                                    } else {
                                        var_v0_12 = temp_a2_3 << -temp_v0_12;
                                    }
                                    var_v1_5 = (temp_v1_16 / (u32) var_v0_12) << temp_a0_5;
                                    goto block_135;
                                }
                                var_v0_13 = temp_v1_16 / (u32) (temp_a2_3 >> -temp_a3_4);
                            } else {
                                var_v1_5 = (u32) (temp_v1_15 << 0xC) / (u32)temp_a2_3;
block_135:
                                var_v0_13 = var_v1_5;
                            }
                            var_lo_3 = var_v0_13 * var_s2_2;
                            if (temp_v0_11 & 0x80000000) {
                                var_lo_3 = -(s32) var_v0_13 * var_s2_2;
                            }
                            var_v1_6 = var_lo_3 >> 0xC;
                            if (var_lo_3 < 0) {
                                var_v1_6 = -((s32) -var_lo_3 >> 0xC);
                            }
                            var_v0_14 = (*(u16 *)((u8 *)(arg0)+(0x30))) + var_v1_6;
                            goto block_158;
                        }
                        if (sp22 >= 0x29) {
                            temp_v0_13 = (u8) sp22 - 0x28;
                            sp22 = temp_v0_13;
                            temp_v0_14 = (s32) (temp_v0_13 << 0x18) >> 0xC;
                            if (temp_v0_14 < 0) {
                            }
                            store_leading_sign_count(temp_v0_14 < 0 ? -temp_v0_14 : temp_v0_14, &sp54);
                            temp_v1_17 = sp54;
                            temp_a3_5 = sp54 - 0xC;
                            if (temp_a3_5 < 0) {
                                temp_v1_18 = temp_v1_17 << sp54;
                                store_leading_sign_count(0x58000, &sp58);
                                temp_a2_4 = sp58;
                                temp_a0_6 = sp58 - sp54;
                                if (temp_a0_6 >= 0) {
                                    temp_v0_15 = 0xC - sp58;
                                    if (temp_v0_15 >= 0) {
                                        var_v0_15 = temp_a2_4 >> temp_v0_15;
                                    } else {
                                        var_v0_15 = temp_a2_4 << -temp_v0_15;
                                    }
                                    var_v1_7 = (temp_v1_18 / (u32) var_v0_15) << temp_a0_6;
                                    goto block_152;
                                }
                                var_v0_16 = temp_v1_18 / (u32) (temp_a2_4 >> -temp_a3_5);
                            } else {
                                var_v1_7 = (u32) (temp_v1_17 << 0xC) / (u32)temp_a2_4;
block_152:
                                var_v0_16 = var_v1_7;
                            }
                            var_lo_4 = var_v0_16 * var_s2_2;
                            if (temp_v0_14 & 0x80000000) {
                                var_lo_4 = -(s32) var_v0_16 * var_s2_2;
                            }
                            var_v1_8 = var_lo_4 >> 0xC;
                            if (var_lo_4 < 0) {
                                var_v1_8 = -((s32) -var_lo_4 >> 0xC);
                            }
                            var_v0_14 = (*(u16 *)((u8 *)(arg0)+(0x30))) - var_v1_8;
block_158:
                            (*(u16 *)((u8 *)(arg0)+(0x30))) = var_v0_14;
                        }
                        temp_v1_19 = (*(u16 *)((u8 *)(arg0)+(0x30)));
                        if (temp_v1_19 > 0x8000U) {
                            var_a0_4 = temp_v1_19 + 0xFFFF0000;
                        } else {
                            var_a0_4 = (*(u16 *)((u8 *)(arg0)+(0x30)));
                        }
                        temp_s2_2 = var_s2_2 * 4;
                        var_v0_17 = var_s5;
                        if (var_s5 < 0) {
                            var_v0_17 = -var_v0_17;
                        }
                        temp_lo_2 = fixed_mul(0x72, var_v0_17) * ((s32) (var_a0_4 * var_a0_4) >> 8);
                        if (temp_lo_2 >= 0) {
                            var_v0_18 = temp_lo_2 >> 0xC;
                        } else {
                            var_v0_18 = -((s32) -temp_lo_2 >> 0xC);
                        }
                        var_s0 = var_v0_18;
                        if (temp_s2_2 < var_s0) {
                            var_s0 = temp_s2_2;
                        }
                        if ((s32) var_a0_4 < 0) {
                            var_s0 = 0x10000 - var_s0;
                        }
                        if (func_8007906C(0xA, (u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp5C, &sp60, &sp64) != 0) {
                            var_s4 = (*(u16 *)((u8 *)(arg0)+(0x2C)));
                        } else {
                            var_s4 = (*(u16 *)((u8 *)(arg0)+(0x2C))) + var_s0;
                            (*(u16 *)((u8 *)(arg0)+(0x30))) = (u16) ((*(u16 *)((u8 *)(arg0)+(0x30))) - var_s0);
                        }
                    } else {
                        if (sp22 < -0x28) {
                            temp_v0_16 = (u8) sp22 + 0x28;
                            sp22 = temp_v0_16;
                            temp_v0_17 = -((s32) (temp_v0_16 << 0x18) >> 0xC);
                            if (temp_v0_17 < 0) {
                            }
                            store_leading_sign_count(temp_v0_17 < 0 ? -temp_v0_17 : temp_v0_17, &sp68);
                            temp_v1_20 = sp68;
                            temp_a3_6 = sp68 - 0xC;
                            if (temp_a3_6 < 0) {
                                temp_v1_21 = temp_v1_20 << sp68;
                                store_leading_sign_count(0x58000, &sp6C);
                                temp_a2_5 = sp6C;
                                temp_a0_7 = sp6C - sp68;
                                if (temp_a0_7 >= 0) {
                                    temp_v0_18 = 0xC - sp6C;
                                    if (temp_v0_18 >= 0) {
                                        var_v0_19 = temp_a2_5 >> temp_v0_18;
                                    } else {
                                        var_v0_19 = temp_a2_5 << -temp_v0_18;
                                    }
                                    var_v1_9 = (temp_v1_21 / (u32) var_v0_19) << temp_a0_7;
                                    goto block_185;
                                }
                                var_v0_20 = temp_v1_21 / (u32) (temp_a2_5 >> -temp_a3_6);
                            } else {
                                var_v1_9 = (u32) (temp_v1_20 << 0xC) / (u32)temp_a2_5;
block_185:
                                var_v0_20 = var_v1_9;
                            }
                            var_lo_5 = var_v0_20 * var_s2_2;
                            if (temp_v0_17 & 0x80000000) {
                                var_lo_5 = -(s32) var_v0_20 * var_s2_2;
                            }
                            var_v1_10 = var_lo_5 >> 0xC;
                            if (var_lo_5 < 0) {
                                var_v1_10 = -((s32) -var_lo_5 >> 0xC);
                            }
                            var_v0_21 = (*(u16 *)((u8 *)(arg0)+(0x30))) + var_v1_10;
                            goto block_208;
                        }
                        if (sp22 >= 0x29) {
                            temp_v0_19 = (u8) sp22 - 0x28;
                            sp22 = temp_v0_19;
                            temp_v0_20 = (s32) (temp_v0_19 << 0x18) >> 0xC;
                            if (temp_v0_20 < 0) {
                            }
                            store_leading_sign_count(temp_v0_20 < 0 ? -temp_v0_20 : temp_v0_20, &sp70);
                            temp_v1_22 = sp70;
                            temp_a3_7 = sp70 - 0xC;
                            if (temp_a3_7 < 0) {
                                temp_v1_23 = temp_v1_22 << sp70;
                                store_leading_sign_count(0x58000, &sp74);
                                temp_a2_6 = sp74;
                                temp_a0_8 = sp74 - sp70;
                                if (temp_a0_8 >= 0) {
                                    temp_v0_21 = 0xC - sp74;
                                    if (temp_v0_21 >= 0) {
                                        var_v0_22 = temp_a2_6 >> temp_v0_21;
                                    } else {
                                        var_v0_22 = temp_a2_6 << -temp_v0_21;
                                    }
                                    var_v1_11 = (temp_v1_23 / (u32) var_v0_22) << temp_a0_8;
                                    goto block_202;
                                }
                                var_v0_23 = temp_v1_23 / (u32) (temp_a2_6 >> -temp_a3_7);
                            } else {
                                var_v1_11 = (u32) (temp_v1_22 << 0xC) / (u32)temp_a2_6;
block_202:
                                var_v0_23 = var_v1_11;
                            }
                            var_lo_6 = var_v0_23 * var_s2_2;
                            if (temp_v0_20 & 0x80000000) {
                                var_lo_6 = -(s32) var_v0_23 * var_s2_2;
                            }
                            var_v1_12 = var_lo_6 >> 0xC;
                            if (var_lo_6 < 0) {
                                var_v1_12 = -((s32) -var_lo_6 >> 0xC);
                            }
                            var_v0_21 = (*(u16 *)((u8 *)(arg0)+(0x30))) - var_v1_12;
block_208:
                            (*(u16 *)((u8 *)(arg0)+(0x30))) = var_v0_21;
                        }
                        if ((s8) sp21 < -0x28) {
                            temp_v0_22 = sp21 + 0x28;
                            sp21 = temp_v0_22;
                            temp_v0_23 = -((s32) (temp_v0_22 << 0x18) >> 0xC);
                            if (temp_v0_23 < 0) {
                            }
                            store_leading_sign_count(temp_v0_23 < 0 ? -temp_v0_23 : temp_v0_23, &sp78);
                            temp_v1_24 = sp78;
                            temp_a3_8 = sp78 - 0xC;
                            if (temp_a3_8 < 0) {
                                temp_v1_25 = temp_v1_24 << sp78;
                                store_leading_sign_count(0x58000, &sp7C);
                                temp_a2_7 = sp7C;
                                temp_a0_9 = sp7C - sp78;
                                if (temp_a0_9 >= 0) {
                                    temp_v0_24 = 0xC - sp7C;
                                    if (temp_v0_24 >= 0) {
                                        var_v0_24 = temp_a2_7 >> temp_v0_24;
                                    } else {
                                        var_v0_24 = temp_a2_7 << -temp_v0_24;
                                    }
                                    var_v1_13 = (temp_v1_25 / (u32) var_v0_24) << temp_a0_9;
                                    goto block_220;
                                }
                                var_v0_25 = temp_v1_25 / (u32) (temp_a2_7 >> -temp_a3_8);
                            } else {
                                var_v1_13 = (u32) (temp_v1_24 << 0xC) / (u32)temp_a2_7;
block_220:
                                var_v0_25 = var_v1_13;
                            }
                            var_lo_7 = var_v0_25 * var_s2_2;
                            if (temp_v0_23 & 0x80000000) {
                                var_lo_7 = -(s32) var_v0_25 * var_s2_2;
                            }
                            if (var_lo_7 >= 0) {
                                var_v0_26 = var_lo_7 >> 0xC;
                            } else {
                                var_v0_26 = -((s32) -var_lo_7 >> 0xC);
                            }
                            var_s4 += var_v0_26;
                        } else if ((s8) sp21 >= 0x29) {
                            temp_v0_25 = sp21 - 0x28;
                            sp21 = temp_v0_25;
                            temp_v0_26 = (s32) (temp_v0_25 << 0x18) >> 0xC;
                            if (temp_v0_26 < 0) {
                            }
                            store_leading_sign_count(temp_v0_26 < 0 ? -temp_v0_26 : temp_v0_26, &sp80);
                            temp_v1_26 = sp80;
                            temp_a3_9 = sp80 - 0xC;
                            if (temp_a3_9 < 0) {
                                temp_v1_27 = temp_v1_26 << sp80;
                                store_leading_sign_count(0x58000, &sp84);
                                temp_a2_8 = sp84;
                                temp_a0_10 = sp84 - sp80;
                                if (temp_a0_10 >= 0) {
                                    temp_v0_27 = 0xC - sp84;
                                    if (temp_v0_27 >= 0) {
                                        var_v0_27 = temp_a2_8 >> temp_v0_27;
                                    } else {
                                        var_v0_27 = temp_a2_8 << -temp_v0_27;
                                    }
                                    var_v1_14 = (temp_v1_27 / (u32) var_v0_27) << temp_a0_10;
                                    goto block_238;
                                }
                                var_v0_28 = temp_v1_27 / (u32) (temp_a2_8 >> -temp_a3_9);
                            } else {
                                var_v1_14 = (u32) (temp_v1_26 << 0xC) / (u32)temp_a2_8;
block_238:
                                var_v0_28 = var_v1_14;
                            }
                            var_lo_8 = var_v0_28 * var_s2_2;
                            if (temp_v0_26 & 0x80000000) {
                                var_lo_8 = -(s32) var_v0_28 * var_s2_2;
                            }
                            if (var_lo_8 >= 0) {
                                var_v0_29 = var_lo_8 >> 0xC;
                            } else {
                                var_v0_29 = -((s32) -var_lo_8 >> 0xC);
                            }
                            var_s4 -= var_v0_29;
                        }
                    }
                }
            }
        }
        if ((D_800AED50 & 1) && ((*(s32 *)((u8 *)(arg0)+(0x218))) & 2)) {
            var_s5 = ((u32) (0x1800 * var_s5) >> 0xC) | ((var_s5 / 699051) << 0x14);
        }
        temp_a0_11 = arg0 + 0x34;
        if ((*(s32 *)((u8 *)(arg0)+(0x264))) != 0) {
            var_s5 = 0x2000;
        }
        if ((*(s32 *)((u8 *)(temp_a0_11)+(0x60))) == 0) {
            var_s4 += func_8001F294(temp_a0_11);
        }
        func_80043F40(arg0, var_s5, var_s4 & 0xFFFF, (*(u16 *)((u8 *)(arg0)+(0x2E))));
        if ((*(s32 *)((u8 *)(arg0)+(0x218))) & 1) {
            if ((*(s32 *)((u8 *)((((s32) (*(u16 *)((u8 *)(arg0)+(0x98))) * 0x9C) + &D_800D3034))+(0x4C))) == (*(s32 *)((u8 *)(arg0)+(0)))) {
                if (func_8007906C(8, (u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp88, &sp8C, &sp90) != 0) {
                    if (sp88 != 0) {
                        temp_a1_3 = (*(s32 *)((u8 *)(arg0)+(0x254)));
                        if (temp_a1_3 != 0) {
                            var_a0_5 = temp_a1_3 + 0xE;
loop_259:
                            var_a2_2 = (var_a0_5 % 15) + 2;
                            if (var_a2_2 != temp_a1_3) {
                                var_a0_5 = var_a2_2 + 0xE;
                                if ((*(u16 *)((u8 *)((arg0 + (var_a2_2 * 2)))+(0x22C))) == 0) {
                                    goto loop_259;
                                }
                            }
                            temp_a0_12 = var_a2_2 * 2;
                            if ((*(u16 *)((u8 *)((arg0 + temp_a0_12))+(0x22C))) == 0) {
                                var_a0_6 = 0;
                                var_a2_2 = 0;
                                (*(s32 *)((u8 *)(arg0)+(0x254))) = 0;
                            } else {
                                var_a0_6 = arg0 + (temp_a0_12 + 0x22C);
                                (*(s32 *)((u8 *)(arg0)+(0x254))) = var_a2_2;
                            }
                            func_80063C68(var_a0_6, (*(u16 *)((u8 *)(arg0)+(0x98))), (void *) var_a2_2, 0x88888889);
                            (*(s32 *)((u8 *)(arg0)+(0x260))) = (s32) D_800D2FE0;
                        }
                    }
                }
                if (func_8007906C(9, (u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp88, &sp8C, &sp90) != 0) {
                    if (sp88 != 0) {
                        temp_a1_4 = (*(s32 *)((u8 *)(arg0)+(0x254)));
                        if (temp_a1_4 != 0) {
                            var_a0_7 = temp_a1_4 + 0xC;
loop_270:
                            var_a2_3 = (var_a0_7 % 15) + 2;
                            if (var_a2_3 != temp_a1_4) {
                                var_a0_7 = var_a2_3 + 0xC;
                                if ((*(u16 *)((u8 *)((arg0 + (var_a2_3 * 2)))+(0x22C))) == 0) {
                                    goto loop_270;
                                }
                            }
                            temp_a0_13 = var_a2_3 * 2;
                            if ((*(u16 *)((u8 *)((arg0 + temp_a0_13))+(0x22C))) == 0) {
                                var_a0_8 = 0;
                                var_a2_3 = 0;
                                (*(s32 *)((u8 *)(arg0)+(0x254))) = 0;
                            } else {
                                var_a0_8 = arg0 + (temp_a0_13 + 0x22C);
                                (*(s32 *)((u8 *)(arg0)+(0x254))) = var_a2_3;
                            }
                            func_80063C68(var_a0_8, (*(u16 *)((u8 *)(arg0)+(0x98))), (void *) var_a2_3, 0x88888889);
                            (*(s32 *)((u8 *)(arg0)+(0x260))) = (s32) D_800D2FE0;
                        }
                    }
                }
                if (func_8007906C(6, (u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp88, &sp8C, &sp90) != 0) {
                    func_80042BAC(arg0, 0, sp88);
                    temp_v1_28 = (*(s32 *)((u8 *)(arg0)+(0x9C)));
                    if (temp_v1_28 == 6) {
                        if ((*(s8 *)((u8 *)((*(void **)((u8 *)(&D_800A4EF4)+(0x5AC))))+(8))) != -1) {
                            (*(s32 *)((u8 *)(arg0)+(0x550))) = 0xB00;
                        }
                        if ((*(s8 *)((u8 *)((*(void **)((u8 *)((((*(s32 *)((u8 *)(arg0)+(0x9C))) * 0xD0) + &D_800A4EF4))+(0xCC))))+(0xC))) != -1) {
                            (*(s32 *)((u8 *)(arg0)+(0x560))) = 0xB00;
                        }
                    } else {
                        if ((*(s8 *)((u8 *)((*(void **)((u8 *)(((temp_v1_28 * 0xD0) + &D_800A4EF4))+(0xCC))))+(8))) != -1) {
                            (*(s32 *)((u8 *)(arg0)+(0x550))) = 0x3000;
                        }
                        if ((*(s8 *)((u8 *)((*(void **)((u8 *)((((*(s32 *)((u8 *)(arg0)+(0x9C))) * 0xD0) + &D_800A4EF4))+(0xCC))))+(0xC))) != -1) {
                            (*(s32 *)((u8 *)(arg0)+(0x560))) = 0x3000;
                        }
                    }
                } else {
                    temp_v1_29 = (*(s32 *)((u8 *)(arg0)+(0x9C)));
                    var_v0_30 = temp_v1_29 * 2;
                    if ((*(s8 *)((u8 *)((*(void **)((u8 *)(((temp_v1_29 * 0xD0) + &D_800A4EF4))+(0xCC))))+(8))) != -1) {
                        (*(s32 *)((u8 *)(arg0)+(0x550))) = 0;
                        var_v0_30 = (*(s32 *)((u8 *)(arg0)+(0x9C))) * 2;
                    }
                    if ((*(s8 *)((u8 *)((*(void **)((u8 *)((((((var_v0_30 + (*(s32 *)((u8 *)(arg0)+(0x9C)))) * 4) + (*(s32 *)((u8 *)(arg0)+(0x9C)))) * 0x10) + &D_800A4EF4))+(0xCC))))+(0xC))) != -1) {
                        (*(s32 *)((u8 *)(arg0)+(0x560))) = 0;
                    }
                }
                if (func_8007906C(7, (u8) (*(u16 *)((u8 *)(arg0)+(0x98))), &sp88, &sp8C, &sp90) != 0) {
                    func_80042BAC(arg0, 1, sp88);
                }
            }
            if (func_80047688(arg0) != 0) {
                var_t0_2 = 1;
                if (((D_800D2FE8 == 0xB) || (D_800D2FE8 == 3) || (D_800D2FE8 == 1)) && ((*(s32 *)((u8 *)(arg0)+(0xA4))) != 0)) {
                    var_t0_2 = 1 | 0x8000;
                }
                temp_v0_28 = (*(s32 *)((u8 *)(arg0)+(0x170)));
                if (temp_v0_28 >= 0) {
                    var_v0_31 = temp_v0_28 >> 0xC;
                } else {
                    var_v0_31 = -((s32) -temp_v0_28 >> 0xC);
                }
                temp_a1_5 = (*(s32 *)((u8 *)(arg0)+(0x178)));
                if (temp_a1_5 >= 0) {
                    var_v0_32 = temp_a1_5 >> 0xC;
                } else {
                    var_v0_32 = -((s32) -temp_a1_5 >> 0xC);
                }
                func_80061CC0((s16) var_v0_31, (s16) var_v0_32, (*(u16 *)((u8 *)(arg0)+(0x2C))), (*(u16 *)((u8 *)(arg0)+(0x98))), var_t0_2 & 0xFFFF);
            }
            if ((*(s32 *)((u8 *)(arg0)+(0x218))) & 0x1000) {
                func_800629A0(arg0, (*(u16 *)((u8 *)(arg0)+(0x98))));
            } else {
                func_80063BD4((*(u16 *)((u8 *)(arg0)+(0x98))));
            }
block_310:
            if (!((*(s32 *)((u8 *)(arg0)+(0x218))) & 8)) {
                temp_v0_29 = func_8008AD60((u16) (*(u16 *)((u8 *)(arg0)+(0x2C))) >> 4);
                temp_t1 = (*(s32 *)((u8 *)(arg0)+(0x34)));
                temp_s0 = fixed_mul(temp_t1, temp_v0_29);
                temp_v0_30 = func_8008ACC0((u16) (*(u16 *)((u8 *)(arg0)+(0x2C))) >> 4);
                temp_t1_2 = (*(s32 *)((u8 *)(arg0)+(0x38)));
                temp_s0_2 = temp_s0 + fixed_mul(temp_t1_2, temp_v0_30);
                if (temp_s0_2 < 0) {
                    var_v0_33 = (*(s32 *)((u8 *)(arg0)+(0x218))) | 0x800;
                } else {
                    var_v0_33 = (*(s32 *)((u8 *)(arg0)+(0x218))) & ~0x800;
                }
                (*(s32 *)((u8 *)(arg0)+(0x218))) = var_v0_33;
                temp_t2 = (*(s32 *)((u8 *)(arg0)+(0x3C)));
                temp_a0_15 = fixed_mul(temp_s0_2, temp_t2);
                temp_v0_32 = (*(u16 *)((u8 *)(arg0)+(0x2C)));
                temp_v1_30 = (*(u16 *)((u8 *)(arg0)+(0x2E)));
                temp_v1_31 = fixed_mul(0x14000, temp_v0_32 - temp_v1_30);
                (*(s32 *)((u8 *)(arg0)+(0x530))) = fixed_mul(0x140, temp_a0_15) - temp_v1_31;
                (*(s32 *)((u8 *)(arg0)+(0x540))) = temp_v1_31 + fixed_mul(0x140, temp_a0_15);
                if ((*(s32 *)((u8 *)(arg0)+(0x218))) & 1) {
                    func_80040380(arg0, temp_a1_6);
                    if (D_800E46BC != 0) {
                        func_80053E14(arg0);
                    } else {
                        func_80053FF4(arg0);
                    }
                    var_v1_15 = D_800DE30C;
                    var_a1_2 = 0xA66;
                    if (var_v1_15 >= 0x1001) {
                        if (var_v1_15 == 0) {
                            var_v1_15 = 2;
                        }
                        var_a2_4 = var_v1_15;
                        if (var_v1_15 < 0) {
                            var_a2_4 = -var_a2_4;
                        }
                        store_leading_sign_count(var_a1_2, &sp94);
                        temp_a3_10 = sp94 - 0xC;
                        if (temp_a3_10 < 0) {
                            temp_v1_32 = var_a1_2 << sp94;
                            store_leading_sign_count(var_a2_4, &sp98);
                            temp_a2_9 = sp98;
                            temp_a0_16 = sp98 - sp94;
                            if (temp_a0_16 >= 0) {
                                temp_v0_33 = 0xC - sp98;
                                if (temp_v0_33 >= 0) {
                                    var_v0_34 = temp_a2_9 >> temp_v0_33;
                                } else {
                                    var_v0_34 = temp_a2_9 << -temp_v0_33;
                                }
                                var_v1_16 = (temp_v1_32 / (u32) var_v0_34) << temp_a0_16;
                                goto block_331;
                            }
                            var_a1_2 = temp_v1_32 / (u32) (temp_a2_9 >> -temp_a3_10);
                        } else {
                            var_v1_16 = 0xA66000U / (u32) var_a2_4;
block_331:
                            var_a1_2 = var_v1_16;
                        }
                        if (var_v1_15 & 0x80000000) {
                            var_a1_2 = (u32) -(s32) var_a1_2;
                        }
                    }
                    temp_t2_2 = (*(s32 *)((u8 *)(arg0)+(0x21C)));
                    temp_v0_34 = (*(s32 *)((u8 *)(arg0)+(0x220))) + fixed_mul(-0x999, temp_t2_2);
                    temp_t1_3 = fixed_mul(var_a1_2, temp_v0_34);
                    (*(s32 *)((u8 *)(arg0)+(0x220))) = temp_t1_3;
                    temp_t2_3 = (*(s32 *)((u8 *)(arg0)+(0x224)));
                    (*(s32 *)((u8 *)(arg0)+(0x21C))) += fixed_mul(D_800DE30C, temp_t1_3);
                    temp_v0_35 = (*(s32 *)((u8 *)(arg0)+(0x228))) + fixed_mul(-0x999, temp_t2_3);
                    temp_t1_4 = fixed_mul(var_a1_2, temp_v0_35);
                    (*(s32 *)((u8 *)(arg0)+(0x228))) = temp_t1_4;
                    temp_a0_17 = (*(s32 *)((u8 *)(arg0)+(0x218)));
                    (*(s32 *)((u8 *)(arg0)+(0x224))) += fixed_mul(D_800DE30C, temp_t1_4);
                    var_v0_35 = temp_a0_17 | 0x400;
                    if (!(temp_a0_17 & 0x200)) {
                        var_v0_35 = temp_a0_17 & ~0x400;
                    }
                    (*(s32 *)((u8 *)(arg0)+(0x218))) = var_v0_35;
                    (*(s32 *)((u8 *)(arg0)+(0x218))) = (s32) ((*(s32 *)((u8 *)(arg0)+(0x218))) & ~0x200);
                    func_80043454(arg0, (s32) var_a1_2);
                }
            }
        }
    }
}
