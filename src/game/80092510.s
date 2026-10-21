/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_80092510
.ent func_80092510
func_80092510:
    addiu	$sp,$sp,-28
    sw	$s0,16($sp)
    sw	$ra,20($sp)
    addiu	$sp,$sp,-40
    sw	$a0,16($sp)
    sw	$a1,20($sp)
    sw	$a2,24($sp)
    sw	$a3,28($sp)
    sw	$ra,32($sp)
    jal	func_8008B984
    nop
    sub	$s0,$zero,$v0
    jal	func_8008B994
    nop
    sub	$t8,$zero,$v0
    lw	$a0,16($sp)
    lw	$a1,20($sp)
    lw	$a2,24($sp)
    lw	$a3,28($sp)
    lw	$ra,32($sp)
    addiu	$sp,$sp,40
    cfc2	$t5,$26
    nop
    srl	$t5,$t5,0x1
    lw	$t0,0($a0)
    lw	$t1,4($a0)
    ctc2	$t0,$0
    ctc2	$t1,$1
    lw	$t0,8($a0)
    lw	$t1,12($a0)
    ctc2	$t0,$2
    ctc2	$t1,$3
    lw	$t0,16($a0)
    lw	$t1,20($a0)
    ctc2	$t0,$4
    ctc2	$t1,$5
    lw	$t0,24($a0)
    lw	$t1,28($a0)
    ctc2	$t0,$6
    ctc2	$t1,$7
    addi	$a0,$a0,32
    ori	$t9,$zero,0xffff
    lw	$v0,4($a1)
    lw	$t6,0($a1)
    andi	$t7,$v0,0xffff
L_800925C4:
    mtc2	$t6,$0
    mtc2	$t7,$1
    srl	$v1,$v0,0x1f
    addiu	$a1,$a1,8
    c2	0x180001
L_800925D8:
    lw	$v0,4($a1)
    lw	$t6,0($a1)
    mfc2	$t0,$19
    swc2	$14,0($a2)
    add	$at,$t0,$s0
    bgez	$at,L_800925FC
    andi	$t7,$v0,0xffff
L_800925F4:
    j	L_800926DC
    sw	$t9,4($a2)
L_800925FC:
    add	$at,$t0,$t8
    bgez	$at,L_800925F4
    nop
    mfc2	$t1,$8
    sub	$t4,$t0,$t5
    bgtz	$t4,L_800926D4
    sll	$t1,$t1,0x10
    cfc2	$at,$26
    nop
    nop
    c2	0x480012
    mfc2	$t0,$27
    mfc2	$t3,$25
    mfc2	$t4,$26
    sll	$at,$at,0x10
    nop
    div	$zero,$at,$t0
    nop
    nop
    mflo	$at
    nop
    nop
    mult	$at,$t3
    cfc2	$t2,$24
    nop
    srl	$t2,$t2,0x10
    mflo	$t3
    sra	$t3,$t3,0x10
    add	$t3,$t3,$t2
    addu	$t2,$t3,$zero
    bgez	$t2,L_80092680
    nop
    sub	$t2,$zero,$t2
L_80092680:
    addiu	$t2,$t2,-1024
    bgez	$t2,L_800925F4
    nop
    mult	$at,$t4
    cfc2	$t2,$25
    nop
    srl	$t2,$t2,0x10
    mflo	$t4
    sra	$t4,$t4,0x10
    add	$t4,$t4,$t2
    addu	$t2,$t4,$zero
    bgez	$t2,L_800926B8
    nop
    sub	$t2,$zero,$t2
L_800926B8:
    addiu	$t2,$t2,-1024
    bgez	$t2,L_800925F4
    nop
    sll	$t4,$t4,0x10
    andi	$t3,$t3,0xffff
    or	$t3,$t4,$t3
    sw	$t3,0($a2)
L_800926D4:
    or	$t0,$t1,$t0
    sw	$t0,4($a2)
L_800926DC:
    beqz	$v1,L_800925C4
    addiu	$a2,$a2,8
    addi	$a3,$a3,-1
    beqz	$a3,L_8009274C
    addi	$a0,$a0,32
    lw	$t0,-32($a0)
    lw	$t1,-28($a0)
    ctc2	$t0,$0
    ctc2	$t1,$1
    lw	$t0,-24($a0)
    lw	$t1,-20($a0)
    ctc2	$t0,$2
    ctc2	$t1,$3
    lw	$t0,-16($a0)
    lw	$t1,-12($a0)
    ctc2	$t0,$4
    ctc2	$t1,$5
    lw	$t0,-8($a0)
    lw	$t1,-4($a0)
    ctc2	$t0,$6
    ctc2	$t1,$7
    mtc2	$t6,$0
    mtc2	$t7,$1
    srl	$v1,$v0,0x1f
    nop
    c2	0x180001
    j	L_800925D8
    addiu	$a1,$a1,8
L_8009274C:
    lw	$s0,16($sp)
    lw	$ra,20($sp)
    addiu	$sp,$sp,28
    jr	$ra
    nop
.end func_80092510
