/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_800A40D4
.ent func_800A40D4
func_800A40D4:
    addiu	$t2,$zero,176
    jr	$t2
    addiu	$t1,$zero,74
    nop
    lhu	$t7,10($v1)
    lui	$t0,0x0
    or	$t8,$t7,$v0
    ori	$t9,$t8,0x12
    sh	$t9,10($v1)
    addiu	$t0,$zero,40
L_800A40FC:
    addiu	$t0,$t0,-1
    bnez	$t0,L_800A40FC
    nop
    jr	$ra
    nop
    lw	$v0,4212($v1)
    nop
    andi	$v0,$v0,0x80
    beqz	$v0,L_800A414C
    nop
L_800A4124:
    lw	$v0,4164($v1)
    nop
    andi	$v0,$v0,0x80
    bnez	$v0,L_800A4124
    nop
    lui	$v0,0x1
    lw	$v0,-8196($v0)
    nop
    jr	$v0
    nop
L_800A414C:
    jr	$ra
    nop
    lui	$v0,0xa001
    addiu	$v0,$v0,-8276
    jr	$v0
    nop
    nop
    lui	$t0,0xa001
    addiu	$t0,$t0,-8320
    jalr	$t0
    nop
.end func_800A40D4
