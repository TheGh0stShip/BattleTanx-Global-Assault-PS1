/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8007C0D4
.ent func_8007C0D4
func_8007C0D4:
    addiu	$sp,$sp,-60
    sw	$s0,16($sp)
    sw	$s1,20($sp)
    sw	$s2,24($sp)
    sw	$s3,28($sp)
    sw	$s4,32($sp)
    sw	$s5,36($sp)
    sw	$s6,40($sp)
    sw	$s7,44($sp)
    sw	$s8,48($sp)
    sw	$ra,52($sp)
    lui	$s2,0x1f80
    ori	$s2,$s2,0x300
    sw	$a3,236($s2)
    sw	$a2,240($s2)
    lw	$t0,88($sp)
    lui	$s2,0x1f80
    ori	$s2,$s2,0x300
    lh	$t1,4($t0)
    nop
    sh	$t1,184($s2)
    lw	$t0,92($sp)
    nop
    sw	$t0,188($s2)
    sw	$zero,0($t0)
    lw	$t0,96($sp)
    lw	$t1,100($sp)
    sw	$t0,216($s2)
    sll	$t1,$t1,0x2
    sw	$t1,220($s2)
    lw	$v1,104($sp)
    nop
    andi	$t0,$v1,0x800
    beqz	$t0,L_8007C188
    sw	$v1,224($s2)
    lw	$t0,108($sp)
    lw	$t1,112($sp)
    lw	$t2,116($sp)
    lw	$t3,120($sp)
    sh	$t0,248($s2)
    sub	$t1,$t1,$t0
    sh	$t1,250($s2)
    sh	$t2,252($s2)
    sub	$t3,$t3,$t2
    sh	$t3,254($s2)
L_8007C188:
    lw	$t0,76($sp)
    lw	$t1,80($sp)
    lw	$t2,84($sp)
    lui	$s2,0x1f80
    ori	$s2,$s2,0x300
    sw	$t1,156($s2)
    sw	$t2,160($s2)
    andi	$s4,$t0,0x1
    beqz	$s4,L_8007C1B4
    sw	$zero,200($s2)
    addiu	$s4,$zero,-1
L_8007C1B4:
    andi	$t3,$t0,0x2
    beqz	$t3,L_8007C1C4
    nop
    ori	$v1,$v1,0x10
L_8007C1C4:
    andi	$t3,$t0,0x4
    beqz	$t3,L_8007C1D4
    andi	$v1,$v1,0xffdf
    ori	$v1,$v1,0x20
L_8007C1D4:
    sw	$v1,224($s2)
    addiu	$sp,$sp,-40
    sw	$a0,16($sp)
    sw	$a1,20($sp)
    sw	$a2,24($sp)
    sw	$a3,28($sp)
    sw	$ra,32($sp)
    jal	func_8008DC68
    nop
    sll	$v0,$v0,0x6
    jal	func_8007F7D8
    sh	$v0,232($s2)
    sll	$s0,$v0,0x8
    jal	func_8007F7F4
    srl	$s0,$s0,0x8
    addiu	$v0,$v0,-192
    add	$v0,$v0,$s0
    jal	func_8008DC24
    sw	$v0,244($s2)
    addu	$s3,$v0,$zero
    jal	func_8008DC40
    sll	$s3,$s3,0xe
    jal	func_8003BD84
    or	$s3,$s3,$v0
    sll	$s5,$v0,0x10
    jal	func_8003BD94
    ori	$s5,$s5,0x400
    jal	func_8003BDA4
    sll	$s6,$v0,0x10
    sw	$v0,164($s2)
    lw	$t0,244($s2)
    lw	$a0,16($sp)
    lw	$a1,20($sp)
    lw	$a2,24($sp)
    lw	$a3,28($sp)
    lw	$ra,32($sp)
    addiu	$sp,$sp,40
    sub	$v0,$t0,$s0
    blez	$v0,L_EXT_8007D510
    nop
    lui	$s2,0x1f80
    ori	$s2,$s2,0x300
    lw	$t0,8($a0)
    addiu	$a0,$a0,24
    sll	$t0,$t0,0x3
    addu	$a0,$a0,$t0
    lhu	$t8,10($s2)
    lui	$t0,0xe100
    or	$t8,$t8,$t0
    sw	$zero,168($s2)
    sw	$zero,172($s2)
    sw	$zero,176($s2)
    sw	$zero,180($s2)
    addiu	$t0,$t0,4096
    sw	$zero,84($s2)
    sw	$zero,88($s2)
    sw	$zero,92($s2)
    sw	$zero,96($s2)
    sh	$t0,100($s2)
    sh	$t0,102($s2)
    sh	$t0,104($s2)
    sh	$t0,106($s2)
    lui	$s1,0x8008
    addiu	$s1,$s1,-13984
    lw	$v1,224($s2)
L_8007C2D8:
    lw	$s7,0($a0)
    addiu	$a0,$a0,4
    andi	$t0,$s7,0xfc
    sll	$t0,$t0,0x1
    add	$t0,$t0,$s1
    jalr	$t0
    srl	$s8,$s7,0x8
    c2	0x1400006
    andi	$s7,$s7,0x3
    beqz	$s7,L_8007C2D8
    addiu	$s7,$s7,-3
    lw	$a2,216($s2)
    beqz	$s7,L_8007C338
    addiu	$s7,$s7,2
    beqz	$s7,L_8007C31C
    addiu	$t1,$zero,-1
    add	$t1,$zero,$zero
L_8007C31C:
    mfc2	$t0,$24
    xor	$t1,$t1,$s4
    xor	$t0,$t0,$t1
    bgez	$t0,L_8007C350
    andi	$v1,$v1,0xefff
    j	L_8007C2D8
    nop
L_8007C338:
    mfc2	$t0,$24
    andi	$v1,$v1,0xefff
    sra	$t1,$t0,0x1f
    bnez	$t1,L_8007C350
    xor	$t0,$t0,$t1
    ori	$v1,$v1,0x1000
L_8007C350:
    sub	$a2,$t0,$a2
    sw	$a2,192($s2)
    bltz	$a2,L_8007C364
    addu	$a2,$zero,$zero
    addi	$a2,$zero,4
L_8007C364:
    andi	$t0,$v1,0x800
    beqz	$t0,L_8007C3F0
    addu	$t7,$zero,$zero
    lh	$t2,248($s2)
    lh	$t3,250($s2)
    lh	$t4,252($s2)
    lh	$t5,254($s2)
    andi	$t1,$v1,0x1
    beqz	$t1,L_8007C3A4
    addi	$t6,$zero,4369
    addu	$t6,$zero,$zero
    lw	$t1,0($s2)
    nop
    jal	func_8007C91C
    sll	$t0,$t1,0x10
    beqz	$t7,L_8007C3E0
L_8007C3A4:
    mfc2	$t1,$12
    jal	func_8007C91C
    sll	$t0,$t1,0x10
    beqz	$t7,L_8007C3E0
    mfc2	$t1,$13
    jal	func_8007C91C
    sll	$t0,$t1,0x10
    beqz	$t7,L_8007C3E0
    mfc2	$t1,$14
    jal	func_8007C91C
    sll	$t0,$t1,0x10
    beqz	$t7,L_8007C3E0
    add	$t0,$t7,$t6
    andi	$t0,$t0,0x4444
    bnez	$t0,L_8007C2D8
L_8007C3E0:
    nop
    bnez	$t7,L_8007C3F0
    addi	$t0,$zero,-1
    sw	$t0,192($s2)
L_8007C3F0:
    andi	$t0,$s6,0xff
    beqz	$t0,L_8007C564
    nop
    mfc2	$t3,$6
    mfc2	$t4,$20
    mfc2	$t5,$21
    mfc2	$t6,$22
    andi	$t0,$s6,0x11
    beqz	$t0,L_8007C45C
    nop
    lw	$t0,84($s2)
    lh	$t1,100($s2)
    andi	$t2,$v1,0x1000
    beqz	$t2,L_8007C43C
    lw	$t2,68($s2)
    addi	$t2,$zero,-1
    xor	$t0,$t0,$t2
    xor	$t1,$t1,$t2
    lw	$t2,68($s2)
L_8007C43C:
    mtc2	$t0,$0
    mtc2	$t1,$1
    mtc2	$t2,$6
    nop
    nop
    c2	0x108041b
    nop
    mfc2	$t3,$22
L_8007C45C:
    andi	$t0,$s6,0x22
    beqz	$t0,L_8007C4AC
    nop
    lw	$t0,88($s2)
    lh	$t1,102($s2)
    andi	$t2,$v1,0x1000
    beqz	$t2,L_8007C48C
    lw	$t2,72($s2)
    addi	$t2,$zero,-1
    xor	$t0,$t0,$t2
    xor	$t1,$t1,$t2
    lw	$t2,72($s2)
L_8007C48C:
    mtc2	$t0,$0
    mtc2	$t1,$1
    mtc2	$t2,$6
    nop
    nop
    c2	0x108041b
    nop
    mfc2	$t4,$22
L_8007C4AC:
    andi	$t0,$s6,0x44
    beqz	$t0,L_8007C4FC
    nop
    lw	$t0,92($s2)
    lh	$t1,104($s2)
    andi	$t2,$v1,0x1000
    beqz	$t2,L_8007C4DC
    lw	$t2,76($s2)
    addi	$t2,$zero,-1
    xor	$t0,$t0,$t2
    xor	$t1,$t1,$t2
    lw	$t2,76($s2)
L_8007C4DC:
    mtc2	$t0,$0
    mtc2	$t1,$1
    mtc2	$t2,$6
    nop
    nop
    c2	0x108041b
    nop
    mfc2	$t5,$22
L_8007C4FC:
    andi	$t0,$s6,0x88
    beqz	$t0,L_8007C54C
    nop
    lw	$t0,96($s2)
    lh	$t1,106($s2)
    andi	$t2,$v1,0x1000
    beqz	$t2,L_8007C52C
    lw	$t2,80($s2)
    addi	$t2,$zero,-1
    xor	$t0,$t0,$t2
    xor	$t1,$t1,$t2
    lw	$t2,80($s2)
L_8007C52C:
    mtc2	$t0,$0
    mtc2	$t1,$1
    mtc2	$t2,$6
    nop
    nop
    c2	0x108041b
    nop
    mfc2	$t6,$22
L_8007C54C:
    mtc2	$t3,$6
    mtc2	$t4,$20
    mtc2	$t5,$21
    mtc2	$t6,$22
    andi	$t0,$s6,0xff
    xor	$s6,$s6,$t0
L_8007C564:
    andi	$t0,$s6,0xf00
    beqz	$t0,L_EXT_8007C728
    nop
    mfc2	$t3,$6
    mfc2	$t4,$20
    mfc2	$t5,$21
    mfc2	$t6,$22
    andi	$t0,$s6,0x100
    beqz	$t0,L_8007C5BC
    srl	$t0,$s6,0x10
    andi	$t1,$s6,0x1000
    xor	$s6,$s6,$t1
    lh	$t1,224($s2)
    srl	$t2,$s5,0x10
    sub	$t1,$t1,$t2
    blez	$t1,L_8007C5BC
    sw	$zero,168($s2)
    add	$t2,$zero,$t3
    jal	func_8007C68C
    ori	$s6,$s6,0x1000
    add	$t3,$zero,$t2
    sw	$t0,168($s2)
L_8007C5BC:
    andi	$t0,$s6,0x200
    beqz	$t0,L_8007C5F8
    srl	$t0,$s6,0x10
    andi	$t1,$s6,0x2000
    xor	$s6,$s6,$t1
    lh	$t1,226($s2)
    srl	$t2,$s5,0x10
    sub	$t1,$t1,$t2
    blez	$t1,L_8007C5F8
    sw	$zero,172($s2)
    add	$t2,$zero,$t4
    jal	func_8007C68C
    ori	$s6,$s6,0x2000
    add	$t4,$zero,$t2
    sw	$t0,172($s2)
L_8007C5F8:
    andi	$t0,$s6,0x400
    beqz	$t0,L_8007C634
    srl	$t0,$s6,0x10
    andi	$t1,$s6,0x4000
    xor	$s6,$s6,$t1
    lh	$t1,228($s2)
    srl	$t2,$s5,0x10
    sub	$t1,$t1,$t2
    blez	$t1,L_8007C634
    sw	$zero,176($s2)
    add	$t2,$zero,$t5
    jal	func_8007C68C
    ori	$s6,$s6,0x4000
    add	$t5,$zero,$t2
    sw	$t0,176($s2)
L_8007C634:
    andi	$t0,$s6,0x800
    beqz	$t0,L_8007C670
    srl	$t0,$s6,0x10
    andi	$t1,$s6,0x8000
    xor	$s6,$s6,$t1
    lh	$t1,230($s2)
    srl	$t2,$s5,0x10
    sub	$t1,$t1,$t2
    blez	$t1,L_8007C670
    sw	$zero,180($s2)
    add	$t2,$zero,$t6
    jal	func_8007C68C
    ori	$s6,$s6,0x8000
    add	$t6,$zero,$t2
    sw	$t0,180($s2)
L_8007C670:
    mtc2	$t3,$6
    mtc2	$t4,$20
    mtc2	$t5,$21
    mtc2	$t6,$22
    andi	$t0,$s6,0xf00
    j	L_EXT_8007C728
    xor	$s6,$s6,$t0
.end func_8007C0D4
