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
    s32 spC8;
    s32 spC4;
    void *spC0;
    s16 spBE;
    s16 spBC;
    s16 spBA;
    s16 spB8;
    s16 spB6;
    s16 spB4;
    s16 spB2;
    s16 spB0;
    s32 spAC;
    s8 unkspAF;
    s8 spAB;
    s32 spA8;
    M2C_UNK sp30[0x60];
    M2C_UNK sp90[0x2C];
    M2C_UNK *var_a0;
    M2C_UNK *var_a0_2;
    M2C_UNK *var_a0_3;
    M2C_UNK *var_a0_4;
    M2C_UNK *var_a1;
    M2C_UNK *var_a1_2;
    M2C_UNK *var_a1_3;
    s16 temp_v0;
    s16 temp_v1_7;
    GteOpcode *var_v1_2;
    GteOpcode *var_v1;
    s32 temp_a2;
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
    s32 temp_v1_4;
    s32 temp_v1_5;
    s32 temp_v1_6;
    s32 var_a2;
    s32 var_a2_2;
    s32 var_fp;
    s32 var_fp_2;
    s32 var_s0;
    s32 var_s0_2;
    s32 var_s0_3;
    s32 var_s0_4;
    s32 var_s0_5;
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
    u32 temp_fp;
    u32 temp_t0;
    u32 temp_v1;
    u32 temp_v1_2;
    u32 var_v0;
    u32 var_v0_3;
    void *temp_t1;
    void *var_s1_2;
    var_s4 = 0;
    spC8 = 0;
    func_8007E8E0();
    temp_fp = (func_80094178() >> 2) & 0xF;
    if (temp_fp < 0xDU) {
        var_s2 = (u32 *) D_800B0B94[temp_fp];
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
    func_8008AFB0(&D_800EC180, &D_800C4784);
    func_80091D4C(0, 0x20, 0x20, 0xFFFFFF, 1, &D_800EC180);
    temp_t1_2 = spC8 + 8;
    spC8 = temp_t1_2;
    spC4 = 0;
    var_fp = 0;
    func_8008AFB0(&D_800EC180, &D_800C47AC, var_s2, (u32 **)((u8 *)temp_t1 + 0x88), *(u32 **)((u8 *)temp_t1 + 0x88));
    func_80091D4C(0, 0x20, temp_t1_2 + 0x20, 0xFFFFFF, 1, &D_800EC180);
    spC8 = temp_t1_2 + 0x14;
    var_s3 = *(u32 **)((u8 *)temp_t1 + 0x88) - 0xB;
    do {
        if (((s32) var_s3 & 0xFF000000) == 0xFF000000) {
            var_s3 = 0;
        }
        temp_t0 = *var_s3;
        var_s4 |= 0xA0000000;
        temp_v1 = temp_t0 >> 0x1A;
        temp_a2 = temp_t0 & 0xFFFF;
        switch (temp_v1) {
        case 0x0:
            temp_v1_2 = temp_t0 & 0x3F;
            if (temp_t0 == 0) {
                func_8008AFB0(&D_800EC100, &D_800C47C0, var_s3, D_800B090C);
            } else {
                switch (temp_v1_2) {
                case 8:
                    temp_s0 = (temp_t0 >> 0x15) & 0x1F;
                    func_8008AFB0(&D_800EC100 - 0x3F00, &D_800C47CC, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) (&D_800B0A14)[temp_s0]);
                    var_s0 = 1 << temp_s0;
block_50:
                    var_s4 |= var_s0;
                    break;
                case 9:
                    var_s1 = (temp_t0 >> 0x15) & 0x1F;
                    temp_s0_2 = (temp_t0 >> 0xB) & 0x1F;
                    func_8008AFB0(&D_800EC100 - 0x3F00, &D_800C47D8, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) (&D_800B0A14)[var_s1], (&D_800B0A14)[temp_s0_2]);
                    var_s0_2 = 1 << temp_s0_2;
block_32:
                    var_s4 |= var_s0_2 | (1 << var_s1);
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
                    temp_s0_3 = (temp_t0 >> 0xB) & 0x1F;
                    temp_s2 = (temp_t0 >> 0x15) & 0x1F;
                    var_s1 = (temp_t0 >> 0x10) & 0x1F;
                    func_8008AFB0(&D_800EC100 - 0x3F00, &D_800C47E8, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) (&D_800B0A14)[temp_s0_3], (&D_800B0A14)[temp_s2], (s32) (&D_800B0A14)[var_s1]);
                    var_s0_2 = (1 << temp_s0_3) | (1 << temp_s2);
                    goto block_32;
                case 24:
                case 25:
                case 26:
                case 27:
                    temp_s0_4 = (temp_t0 >> 0x15) & 0x1F;
                    var_s1 = (temp_t0 >> 0x10) & 0x1F;
                    func_8008AFB0(&D_800EC100 - 0x3F00, &D_800C47D8, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) (&D_800B0A14)[temp_s0_4], (&D_800B0A14)[var_s1]);
                    var_s0_2 = 1 << temp_s0_4;
                    goto block_32;
                case 16:
                case 17:
                case 18:
                case 19:
                    temp_s0_5 = (temp_t0 >> 0xB) & 0x1F;
                    func_8008AFB0(&D_800EC100 - 0x3F00, &D_800C47CC, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) (&D_800B0A14)[temp_s0_5]);
                    var_s0 = 1 << temp_s0_5;
                    goto block_50;
                case 0:
                case 2:
                case 3:
                    var_s0_3 = (temp_t0 >> 0xB) & 0x1F;
                    var_s1 = (temp_t0 >> 0x10) & 0x1F;
                    var_a0 = &D_800EC100 - 0x3F00;
                    var_a1 = &D_800C47E8;
                    var_t1 = &D_800B080C;
                    var_v0 = temp_t0 & 0x3F;
block_31:
                    func_8008AFB0(var_a0, var_a1, var_s3, var_t1[var_v0]);
                    var_s0_2 = 1 << var_s0_3;
                    goto block_32;
                case 4:
                case 6:
                case 7:
                    temp_s0_6 = (temp_t0 >> 0xB) & 0x1F;
                    temp_s2_2 = (temp_t0 >> 0x10) & 0x1F;
                    var_s1 = (temp_t0 >> 0x15) & 0x1F;
                    func_8008AFB0(&D_800EC100 - 0x3F00, &D_800C47E8, var_s3, (&D_800B080C)[temp_t0 & 0x3F], (u32) (&D_800B0A14)[temp_s0_6], (&D_800B0A14)[temp_s2_2], (s32) (&D_800B0A14)[var_s1]);
                    var_s0_2 = (1 << temp_s0_6) | (1 << temp_s2_2);
                    goto block_32;
                default:
                    func_8008AFB0(&D_800EC100, &D_800C47FC, var_s3, (u32 *) temp_t0);
                    break;
                }
            }
            break;
        case 0x1:
            temp_s0_7 = (temp_t0 >> 0x15) & 0x1F;
            func_8008AFB0(&D_800EC100 - 0x3F00, &D_800C480C, var_s3, *(((temp_t0 >> 0xE) & 0x7C) + &D_800B0804), (u32) (&D_800B0A14)[temp_s0_7], &var_s3[(s32) (temp_a2 << 0x10) >> 0x10] + 1);
            var_s0 = 1 << temp_s0_7;
            goto block_50;
        case 0xF:
            temp_s0_8 = (temp_t0 >> 0x10) & 0x1F;
            func_8008AFB0(&D_800EC100 - 0x3F00, &D_800C480C, var_s3, (&D_800B090C)[temp_t0 >> 0x1A], (u32) (&D_800B0A14)[temp_s0_8], (u32 *) temp_a2);
            var_s0 = 1 << temp_s0_8;
            goto block_50;
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
            if (((s32) (temp_a2 << 0x10) >> 0x10) < 0) {
            }
            var_a0_2 = &D_800EC100 - 0x3F00;
            var_s0_4 = (temp_t0 >> 0x15) & 0x1F;
            var_a1_2 = &D_800C4828;
            var_a3 = (&D_800B090C)[temp_t0 >> 0x1A];
block_49:
            var_s0 = 1 << var_s0_4;
            func_8008AFB0(var_a0_2, var_a1_2, var_s3, var_a3);
            goto block_50;
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
            if (((s32) (temp_a2 << 0x10) >> 0x10) < 0) {
            }
            var_a0_2 = &D_800EC100 - 0x3F00;
            var_s0_4 = (temp_t0 >> 0x15) & 0x1F;
            var_a1_2 = &D_800C4828;
            var_a3 = (&D_800B090C)[temp_t0 >> 0x1A];
            goto block_49;
        case 0x8:
        case 0x9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
        case 0xE:
            var_s1 = (temp_t0 >> 0x10) & 0x1F;
            var_a0 = &D_800EC100 - 0x3F00;
            var_s0_3 = (temp_t0 >> 0x15) & 0x1F;
            var_a1 = &D_800C4840;
            var_t1 = &D_800B090C;
            var_v0 = temp_t0 >> 0x1A;
            goto block_31;
        case 0x4:
        case 0x5:
        case 0x6:
        case 0x7:
            var_s0_4 = (temp_t0 >> 0x15) & 0x1F;
            var_a0_2 = &D_800EC100 - 0x3F00;
            var_a1_2 = &D_800C4840;
            var_a3 = (&D_800B090C)[temp_t0 >> 0x1A];
            goto block_49;
        case 0x2:
        case 0x3:
            var_a0_3 = &D_800EC100 - 0x3F00;
            var_a1_3 = &D_800C4858;
            var_v0_2 = &(&D_800B090C)[temp_t0 >> 0x1A];
block_188:
            func_8008AFB0(var_a0_3, var_a1_3, var_s3, *var_v0_2);
            break;
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
            temp_v1_3 = (temp_t0 >> 0x15) & 0x1F;
            var_a0_2 = &D_800EC100 - 0x3F00;
            if (temp_v1_3 != 2) {
                if (temp_v1_3 < 3) {
                    if (temp_v1_3 != 0) {
                        var_v0_3 = temp_t0 >> 0x19;
                        goto block_52;
                    }
                    var_s0_4 = (temp_t0 >> 0x10) & 0x1F;
                    var_a1_2 = &D_800C4868;
                    var_a3 = D_800B07C0[0].name;
                    goto block_46;
                }
                if (temp_v1_3 != 4) {
                    var_a0_2 = &D_800EC100 - 0x3F00;
                    if (temp_v1_3 != 6) {
                        var_v0_3 = temp_t0 >> 0x19;
block_52:
                        var_a2 = 0x16;
                        if (var_v0_3 & 1) {
                            var_v1 = &D_800B0588[0x16];
loop_54:
                            if ((temp_t0 & 0xFFFF) != var_v1->opcode) {
                                var_a2 -= 1;
                                var_v1 -= 1;
                                if (var_a2 >= 0) {
                                    goto loop_54;
                                }
                            }
                            temp_v1_4 = temp_t0 & 0xFFFF;
                            if (var_a2 < 0) {
                                var_a2 = 0;
                            }
                            if (temp_v1_4 != 0x107F) {
                                if (temp_v1_4 < 0x1080) {
                                    if (temp_v1_4 != 0xE7F) {
                                        if (temp_v1_4 < 0xE80) {
                                            if (temp_v1_4 != 0xBF) {
                                                if (temp_v1_4 < 0xC0) {
                                                    var_a0_3 = &D_800EC100 - 0x3F00;
                                                    if (temp_v1_4 != 0x7F) {
                                                        var_a2_2 = 0x2F;
                                                        goto block_98;
                                                    }
                                                    goto block_96;
                                                }
                                                var_a0_3 = &D_800EC100 - 0x3F00;
                                                if (temp_v1_4 != 0xDFF) {
                                                    if (temp_v1_4 != 0xE3F) {
                                                        var_a2_2 = 0x2F;
                                                        goto block_98;
                                                    }
                                                    goto block_97;
                                                }
                                                goto block_96;
                                            }
                                            goto block_95;
                                        }
                                        var_a0_3 = &D_800EC100 - 0x3F00;
                                        if (temp_v1_4 != 0xFBF) {
                                            if (temp_v1_4 < 0xFC0) {
                                                if ((temp_v1_4 != 0xEBF) && (temp_v1_4 != 0xF7F)) {
                                                    var_a2_2 = 0x2F;
                                                    goto block_98;
                                                }
                                                goto block_97;
                                            }
                                            var_a0_3 = &D_800EC100 - 0x3F00;
                                            if (temp_v1_4 != 0xFFF) {
                                                if (temp_v1_4 != 0x103F) {
                                                    var_a2_2 = 0x2F;
                                                    goto block_98;
                                                }
                                                goto block_97;
                                            }
                                            goto block_96;
                                        }
                                        goto block_96;
                                    }
                                    goto block_95;
                                    goto block_188;
                                }
                                var_a0_3 = &D_800EC100 - 0x3F00;
                                if (temp_v1_4 != 0x11FF) {
                                    if (temp_v1_4 < 0x1200) {
                                        if (temp_v1_4 != 0x113F) {
                                            if (temp_v1_4 < 0x1140) {
                                                if ((temp_v1_4 != 0x10BF) && (temp_v1_4 != 0x10FF)) {
                                                    var_a2_2 = 0x2F;
                                                    goto block_98;
                                                }
                                                goto block_97;
                                            }
                                            var_a0_3 = &D_800EC100 - 0x3F00;
                                            if (temp_v1_4 != 0x117F) {
                                                if (temp_v1_4 != 0x11BF) {
                                                    var_a2_2 = 0x2F;
                                                    goto block_98;
                                                }
                                                goto block_97;
                                            }
                                            goto block_96;
                                        }
                                        goto block_97;
                                        goto block_188;
                                    }
                                    if (temp_v1_4 != 0x143F) {
                                        if (temp_v1_4 < 0x1440) {
                                            if (temp_v1_4 != 0x13BF) {
                                                var_a0_4 = &D_800EC100 - 0x3F00;
                                                if (temp_v1_4 != 0x13FF) {
                                                    var_a2_2 = 0x2F;
                                                    goto block_98;
                                                }
                                                goto block_185;
                                            }
                                            func_8008AFB0(&D_800EC100 - 0x3F00, &D_800C489C, var_s3, D_800B07C0[temp_t0 >> 0x1C].name, (temp_t0 >> 0x1A) & 3, D_800B0588[var_a2].name, (temp_t0 >> 0x18) & 1, (temp_t0 >> 0x16) & 3, (temp_t0 >> 0x14) & 3, (temp_t0 >> 0x12) & 3, (temp_t0 >> 0x11) & 1);
                                        } else {
                                            if (temp_v1_4 != 0x147F) {
                                                var_a0_4 = &D_800EC100 - 0x3F00;
                                                if (temp_v1_4 != 0x14BF) {
                                                    var_a2_2 = 0x2F;
block_98:
                                                    var_v1_2 = &D_800B0640[0x2F];
loop_99:
                                                    if ((temp_t0 & 0x01FFFFFF) != var_v1_2->opcode) {
                                                        var_a2_2 -= 1;
                                                        var_v1_2 -= 1;
                                                        if (var_a2_2 >= 0) {
                                                            goto loop_99;
                                                        }
                                                    }
                                                    if (var_a2_2 < 0) {
                                                        var_a2_2 = 0;
                                                    }
                                                    temp_v1_5 = temp_t0 & 0x01FFFFFF;
                                                    if (temp_v1_5 != 0x4B8012) {
                                                        if (temp_v1_5 <= 0x4B8012) {
                                                            if (temp_v1_5 != 0x49A012) {
                                                                if (temp_v1_5 <= 0x49A012) {
                                                                    if (temp_v1_5 != 0x48A012) {
                                                                        if (temp_v1_5 <= 0x48A012) {
                                                                            if (temp_v1_5 != 0x482012) {
                                                                                if (temp_v1_5 <= 0x482012) {
                                                                                    var_a0_3 = &D_800EC100 - 0x3F00;
                                                                                    if (temp_v1_5 != 0x41E012) {
                                                                                        var_v0_4 = 0x480000;
                                                                                        goto block_129;
                                                                                    }
                                                                                    goto block_178;
                                                                                }
                                                                                var_a0_3 = &D_800EC100 - 0x3F00;
                                                                                if (temp_v1_5 != 0x486012) {
                                                                                    var_v0_5 = 0x480000;
                                                                                    goto block_121;
                                                                                }
                                                                                goto block_178;
                                                                            }
                                                                            goto block_177;
                                                                        }
                                                                        var_a0_3 = &D_800EC100 - 0x3F00;
                                                                        if (temp_v1_5 != 0x492012) {
                                                                            if (temp_v1_5 <= 0x492012) {
                                                                                if (temp_v1_5 != 0x48E012) {
                                                                                    var_v0_4 = 0x490000;
                                                                                    goto block_129;
                                                                                }
                                                                                goto block_179;
                                                                            }
                                                                            var_a0_3 = &D_800EC100 - 0x3F00;
                                                                            if (temp_v1_5 != 0x496012) {
                                                                                var_v0_5 = 0x490000;
block_121:
                                                                                if (temp_v1_5 != (var_v0_5 | 0x8012)) {
                                                                                    goto block_181;
                                                                                }
                                                                                goto block_177;
                                                                            }
                                                                            goto block_178;
                                                                        }
                                                                        goto block_178;
                                                                    }
                                                                    goto block_177;
                                                                }
                                                                var_a0_3 = &D_800EC100 - 0x3F00;
                                                                if (temp_v1_5 != 0x4A8012) {
                                                                    if (temp_v1_5 <= 0x4A8012) {
                                                                        if (temp_v1_5 != 0x4A2012) {
                                                                            if (temp_v1_5 <= 0x4A2012) {
                                                                                if (temp_v1_5 != 0x49E012) {
                                                                                    var_v0_4 = 0x4A0000;
block_129:
                                                                                    if (temp_v1_5 != (var_v0_4 | 0x12)) {
                                                                                        goto block_181;
                                                                                    }
                                                                                    goto block_177;
                                                                                }
                                                                                goto block_179;
                                                                            }
                                                                            var_a0_3 = &D_800EC100 - 0x3F00;
                                                                            if ((temp_v1_5 != 0x4A6012) && (temp_v1_5 != 0x4A6412)) {
                                                                                goto block_182;
                                                                            }
                                                                            goto block_178;
                                                                        }
                                                                        goto block_178;
                                                                    }
                                                                    var_a0_3 = &D_800EC100 - 0x3F00;
                                                                    if (temp_v1_5 != 0x4B0012) {
                                                                        if (temp_v1_5 <= 0x4B0012) {
                                                                            if (temp_v1_5 != 0x4AA012) {
                                                                                var_v0_6 = 0x4A0000;
                                                                                goto block_154;
                                                                            }
                                                                            goto block_179;
                                                                        }
                                                                        var_a0_3 = &D_800EC100 - 0x3F00;
                                                                        if (temp_v1_5 != 0x4B2012) {
                                                                            var_v0_7 = 0x4B0000;
                                                                            goto block_158;
                                                                        }
                                                                        goto block_178;
                                                                    }
                                                                    goto block_178;
                                                                }
                                                                goto block_178;
                                                            }
                                                            goto block_177;
                                                        }
                                                        var_a0_3 = &D_800EC100 - 0x3F00;
                                                        if (temp_v1_5 != 0x4D8012) {
                                                            if (temp_v1_5 <= 0x4D8012) {
                                                                if (temp_v1_5 != 0x4C8012) {
                                                                    if (temp_v1_5 <= 0x4C8012) {
                                                                        if (temp_v1_5 != 0x4C0012) {
                                                                            if (temp_v1_5 <= 0x4C0012) {
                                                                                if (temp_v1_5 != 0x4BA012) {
                                                                                    var_v0_6 = 0x4B0000;
                                                                                    goto block_154;
                                                                                }
                                                                                goto block_179;
                                                                            }
                                                                            var_a0_3 = &D_800EC100 - 0x3F00;
                                                                            if (temp_v1_5 != 0x4C2012) {
                                                                                var_v0_7 = 0x4C0000;
                                                                                goto block_158;
                                                                            }
                                                                            goto block_178;
                                                                        }
                                                                        goto block_178;
                                                                    }
                                                                    var_a0_3 = &D_800EC100 - 0x3F00;
                                                                    if (temp_v1_5 != 0x4D0012) {
                                                                        if (temp_v1_5 <= 0x4D0012) {
                                                                            if (temp_v1_5 != 0x4CA012) {
                                                                                var_v0_6 = 0x4C0000;
block_154:
                                                                                if (temp_v1_5 != (var_v0_6 | 0xE012)) {
                                                                                    goto block_181;
                                                                                }
                                                                                goto block_177;
                                                                            }
                                                                            goto block_179;
                                                                        }
                                                                        var_a0_3 = &D_800EC100 - 0x3F00;
                                                                        if (temp_v1_5 != 0x4D2012) {
                                                                            var_v0_7 = 0x4D0000;
block_158:
                                                                            if (temp_v1_5 != (var_v0_7 | 0x6012)) {
                                                                                goto block_181;
                                                                            }
                                                                            goto block_177;
                                                                        }
                                                                        goto block_178;
                                                                    }
                                                                    goto block_178;
                                                                }
                                                                goto block_178;
                                                            }
                                                            var_a0_3 = &D_800EC100 - 0x3F00;
                                                            if (temp_v1_5 != 0x90003D) {
                                                                if (temp_v1_5 <= 0x90003D) {
                                                                    if (temp_v1_5 != 0x4DE012) {
                                                                        if (temp_v1_5 <= 0x4DE012) {
                                                                            if (temp_v1_5 != 0x4DA012) {
                                                                                if (temp_v1_5 != 0x4DA412) {
                                                                                    goto block_182;
                                                                                }
                                                                                goto block_178;
                                                                            }
                                                                            goto block_179;
                                                                        }
                                                                        var_a0_3 = &D_800EC100 - 0x3F00;
                                                                        if ((temp_v1_5 != 0x70000C) && (temp_v1_5 != 0x78000C)) {
                                                                            goto block_182;
                                                                        }
                                                                        goto block_178;
                                                                    }
                                                                    goto block_178;
                                                                }
                                                                var_a0_3 = &D_800EC100 - 0x3F00;
                                                                if (temp_v1_5 != 0xA00428) {
                                                                    if (temp_v1_5 <= 0xA00428) {
                                                                        if (temp_v1_5 != 0x98003D) {
                                                                            if (temp_v1_5 != 0xA0003E) {
                                                                                goto block_182;
                                                                            }
                                                                            goto block_178;
                                                                        }
                                                                        goto block_179;
                                                                    }
                                                                    var_a0_3 = &D_800EC100 - 0x3F00;
                                                                    if (temp_v1_5 != 0xA8003E) {
                                                                        if (temp_v1_5 == 0xA80428) {
                                                                            goto block_177;
                                                                        }
block_181:
                                                                        var_a0_3 = &D_800EC100 - 0x3F00;
block_182:
                                                                        var_a1_3 = &D_800C488C;
                                                                        var_v0_2 = &D_800B07C0[temp_t0 >> 0x1C].name;
                                                                    } else {
                                                                        goto block_178;
                                                                    }
                                                                } else {
                                                                    goto block_178;
                                                                }
                                                            } else {
                                                                goto block_178;
                                                            }
                                                        } else {
                                                            goto block_178;
                                                        }
                                                    } else {
block_177:
                                                        var_a0_3 = &D_800EC100 - 0x3F00;
block_178:
block_179:
                                                        var_a1_3 = &D_800C487C;
                                                        var_v0_8 = (temp_t0 >> 0x1C) * 0x10;
                                                        goto block_187;
                                                    }
                                                    goto block_188;
                                                }
                                                goto block_185;
                                            }
                                            goto block_184;
                                        }
                                    } else {
block_184:
                                        var_a0_4 = &D_800EC100 - 0x3F00;
block_185:
                                        func_8008AFB0(var_a0_4, &D_800C48C0, var_s3, D_800B07C0[temp_t0 >> 0x1C].name, (temp_t0 >> 0x1A) & 3, D_800B0588[var_a2].name, (temp_t0 >> 0x18) & 1);
                                    }
                                } else {
                                    goto block_96;
                                }
                            } else {
block_95:
                                var_a0_3 = &D_800EC100 - 0x3F00;
block_96:
block_97:
                                var_a1_3 = &D_800C487C;
                                var_v0_8 = (temp_t0 >> 0x1C) * 0x10;
                                goto block_187;
                            }
                        } else {
                            var_a0_3 = &D_800EC100 - 0x3F00;
                            var_a1_3 = &D_800C48D4;
                            var_v0_8 = (temp_t0 >> 0x1C) * 0x10;
block_187:
                            var_v0_2 = &D_800B07C0[var_v0_8 >> 4].name;
                            goto block_188;
                        }
                    } else {
                        var_a3 = D_800B07C0[0].name;
                        var_s0_4 = (temp_t0 >> 0x10) & 0x1F;
                        var_a1_2 = &D_800C4868;
                        goto block_47;
                    }
                } else {
                    var_a0_2 = &D_800EC100 - 0x3F00;
                    var_a3 = D_800B07C0[0].name;
                    var_s0_4 = (temp_t0 >> 0x10) & 0x1F;
                    var_a1_2 = &D_800C4868;
block_46:
block_47:
                    goto block_48;
                }
            } else {
                var_a3 = D_800B07C0[0].name;
                var_s0_4 = (temp_t0 >> 0xB) & 0x1F;
                var_a1_2 = &D_800C4868;
block_48:
                goto block_49;
            }
            break;
        default:
            func_8008AFB0(&D_800EC100, &D_800C48E8, var_s3);
            break;
        }
        if (var_s3 == (spC0)) {
            temp_v1_6 = var_fp * 8;
            spB0 = 0;
            spB4 = 0x200;
            spB8 = 0;
            spBC = 0x200;
            temp_v0 = spC8 + (temp_v1_6 + 0x20);
            temp_v1_7 = spC8 + (temp_v1_6 + 0x28);
            spB2 = temp_v0;
            spB6 = temp_v0;
            spAC = 0x80;
            spBA = temp_v1_7;
            spBE = temp_v1_7;
            spAB = 5;
            unkspAF = 0x28;
            spA8 |= 0xFFFFFF;
            func_8007FE4C(&spA8, 0x200, 0xFFFFFF);
        }
        func_80091D4C(0, 0x20, spC8 + ((var_fp * 8) + 0x20), 0xFFFFFF, 1, &D_800EC100);
        var_s3 += 4;
        var_fp += 1;
        temp_t1_3 = spC4 + 1;
        spC4 = temp_t1_3;
    } while (temp_t1_3 < 0x14);
    var_fp_2 = 0;
    var_s2_2 = &D_800B0A14;
    var_s1_2 = spC0;
    var_s0_5 = 0x20;
    do {
        if (var_s4 & ~1 & (1 << var_fp_2)) {
            func_8008AFB0(&D_800EC100, &D_800C4904, *var_s2_2, (var_s1_2));
            func_80091D4C(0, 0x16A, spC8 + var_s0_5, 0xFFFFFF, 1, &D_800EC100);
            var_s0_5 += 8;
        }
        var_s2_2 += 4;
        var_fp_2 += 1;
        var_s1_2 += 4;
    } while (var_fp_2 < 0x20);
    return 0;
}
