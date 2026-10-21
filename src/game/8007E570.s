/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8007E570
.ent func_8007E570
func_8007E570:
    addiu	$sp,$sp,-56
    sw	$ra,16($sp)
    sw	$s0,20($sp)
    sw	$s1,24($sp)
    sw	$s2,28($sp)
    sw	$s3,32($sp)
    sw	$s4,36($sp)
    sw	$s5,40($sp)
    sw	$s6,44($sp)
    sw	$ra,48($sp)
    addiu	$sp,$sp,-40
    sw	$a0,16($sp)
    sw	$a1,20($sp)
    sw	$a2,24($sp)
    sw	$a3,28($sp)
    sw	$ra,32($sp)
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
    addi	$at,$zero,3
    divu	$zero,$a3,$at
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
    ori	$t9,$zero,0xffff
    mflo	$t6
    mfhi	$a3
    beqz	$t6,L_8007E768
    addi	$t6,$t6,-1
    lw	$s0,0($a1)
    lw	$s1,4($a1)
    lw	$s2,8($a1)
    lw	$s3,12($a1)
    lw	$s4,16($a1)
    lw	$s5,20($a1)
L_8007E654:
    mtc2	$s0,$0
    mtc2	$s1,$1
    mtc2	$s2,$2
    mtc2	$s3,$3
    mtc2	$s4,$4
    mtc2	$s5,$5
    addiu	$a1,$a1,24
    nop
    c2	0x280030
    lw	$s0,0($a1)
    lw	$s1,4($a1)
    lw	$s2,8($a1)
    lw	$s3,12($a1)
    lw	$s4,16($a1)
    lw	$s5,20($a1)
    mfc2	$a0,$17
    mfc2	$v0,$18
    mfc2	$v1,$19
    swc2	$12,0($a2)
    swc2	$13,8($a2)
    swc2	$14,16($a2)
    add	$at,$a0,$t8
    bltz	$at,L_8007E6BC
    sub	$at,$a0,$t5
    sub	$a0,$zero,$t8
    sub	$at,$a0,$t5
L_8007E6BC:
    bgtz	$at,L_8007E6E4
    sw	$a0,4($a2)
    beqz	$a0,L_8007E6E4
    sw	$t9,4($a2)
    lw	$t0,-24($a1)
    lw	$t1,-20($a1)
    jal	func_8007E810
    mfc2	$s6,$12
    sw	$t0,0($a2)
    sw	$t1,4($a2)
L_8007E6E4:
    add	$at,$v0,$t8
    bltz	$at,L_8007E6F8
    sub	$at,$v0,$t5
    sub	$v0,$zero,$t8
    sub	$at,$v0,$t5
L_8007E6F8:
    bgtz	$at,L_8007E720
    sw	$v0,12($a2)
    beqz	$v0,L_8007E720
    sw	$t9,12($a2)
    lw	$t0,-16($a1)
    lw	$t1,-12($a1)
    jal	func_8007E810
    mfc2	$s6,$13
    sw	$t0,8($a2)
    sw	$t1,12($a2)
L_8007E720:
    add	$at,$v1,$t8
    bltz	$at,L_8007E734
    sub	$at,$v1,$t5
    sub	$v1,$zero,$t8
    sub	$at,$v1,$t5
L_8007E734:
    bgtz	$at,L_8007E75C
    sw	$v1,20($a2)
    beqz	$v1,L_8007E75C
    sw	$t9,20($a2)
    lw	$t0,-8($a1)
    lw	$t1,-4($a1)
    jal	func_8007E810
    mfc2	$s6,$14
    sw	$t0,16($a2)
    sw	$t1,20($a2)
L_8007E75C:
    addiu	$a2,$a2,24
    bgtz	$t6,L_8007E654
    addi	$t6,$t6,-1
L_8007E768:
    beqz	$a3,L_8007E7E0
    lw	$s0,0($a1)
    lw	$s1,4($a1)
L_8007E774:
    mtc2	$s0,$0
    mtc2	$s1,$1
    addiu	$a1,$a1,8
    nop
    c2	0x180001
    lw	$s0,0($a1)
    lw	$s1,4($a1)
    mfc2	$a0,$19
    swc2	$14,0($a2)
    add	$at,$a0,$t8
    bltz	$at,L_8007E7AC
    sub	$at,$a0,$t5
    sub	$a0,$zero,$t8
    sub	$at,$a0,$t5
L_8007E7AC:
    bgtz	$at,L_8007E7D4
    sw	$a0,4($a2)
    beqz	$a0,L_8007E7D4
    sw	$t9,4($a2)
    lw	$t0,-8($a1)
    lw	$t1,-4($a1)
    jal	func_8007E810
    mfc2	$s6,$14
    sw	$t0,0($a2)
    sw	$t1,4($a2)
L_8007E7D4:
    addiu	$a3,$a3,-1
    bnez	$a3,L_8007E774
    addiu	$a2,$a2,8
L_8007E7E0:
    lw	$ra,16($sp)
    lw	$s0,20($sp)
    lw	$s1,24($sp)
    lw	$s2,28($sp)
    lw	$s3,32($sp)
    lw	$s4,36($sp)
    lw	$s5,40($sp)
    lw	$s6,44($sp)
    lw	$ra,48($sp)
    addiu	$sp,$sp,56
    jr	$ra
    nop
.end func_8007E570
