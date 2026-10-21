/* Hand-written GTE packet renderer recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8007D580
.ent func_8007D580
func_8007D580:
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
    nop
    sw	$t0,188($s2)
    sw	$zero,0($t0)
    lw	$t0,92($sp)
    lw	$t1,96($sp)
    sw	$t0,216($s2)
    sll	$t1,$t1,0x2
    sw	$t1,220($s2)
    lw	$v1,100($sp)
    nop
    andi	$t0,$v1,0x800
    beqz	$t0,L_8007D61C
    sw	$v1,224($s2)
    lw	$t0,104($sp)
    lw	$t1,108($sp)
    lw	$t2,112($sp)
    lw	$t3,116($sp)
    sh	$t0,248($s2)
    sub	$t1,$t1,$t0
    sh	$t1,250($s2)
    sh	$t2,252($s2)
    sub	$t3,$t3,$t2
    sh	$t3,254($s2)
L_8007D61C:
    lw	$t0,76($sp)
    lw	$t1,80($sp)
    lw	$t2,84($sp)
    lui	$s2,0x1f80
    ori	$s2,$s2,0x300
    sw	$t1,156($s2)
    sw	$t2,160($s2)
    andi	$s4,$t0,0x1
    beqz	$s4,L_8007D648
    sw	$zero,200($s2)
    addiu	$s4,$zero,-1
L_8007D648:
    andi	$t3,$t0,0x2
    beqz	$t3,L_8007D658
    nop
    ori	$v1,$v1,0x10
L_8007D658:
    andi	$t3,$t0,0x4
    beqz	$t3,L_8007D668
    andi	$v1,$v1,0xffdf
    ori	$v1,$v1,0x20
L_8007D668:
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
    blez	$v0,L_EXT_8007E500
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
    addiu	$s1,$s1,-9168
    lw	$v1,224($s2)
L_8007D76C:
    lw	$s7,0($a0)
    addiu	$a0,$a0,4
    andi	$t0,$s7,0xfc
    sll	$t0,$t0,0x1
    add	$t0,$t0,$s1
    jalr	$t0
    srl	$s8,$s7,0x8
    c2	0x1400006
    andi	$s7,$s7,0x3
    beqz	$s7,L_8007D76C
    addiu	$s7,$s7,-3
    lw	$a2,216($s2)
    beqz	$s7,L_8007D7CC
    addiu	$s7,$s7,2
    beqz	$s7,L_8007D7B0
    addiu	$t1,$zero,-1
    add	$t1,$zero,$zero
L_8007D7B0:
    mfc2	$t0,$24
    xor	$t1,$t1,$s4
    xor	$t0,$t0,$t1
    bgez	$t0,L_8007D7E4
    andi	$v1,$v1,0xefff
    j	L_8007D76C
    nop
L_8007D7CC:
    mfc2	$t0,$24
    andi	$v1,$v1,0xefff
    sra	$t1,$t0,0x1f
    bnez	$t1,L_8007D7E4
    xor	$t0,$t0,$t1
    ori	$v1,$v1,0x1000
L_8007D7E4:
    sub	$a2,$t0,$a2
    sw	$a2,192($s2)
    bltz	$a2,L_8007D7F8
    addu	$a2,$zero,$zero
    addi	$a2,$zero,4
L_8007D7F8:
    andi	$t0,$v1,0x800
    beqz	$t0,L_8007D884
    addu	$t7,$zero,$zero
    lh	$t2,248($s2)
    lh	$t3,250($s2)
    lh	$t4,252($s2)
    lh	$t5,254($s2)
    andi	$t1,$v1,0x1
    beqz	$t1,L_8007D838
    addi	$t6,$zero,4369
    addu	$t6,$zero,$zero
    lw	$t1,0($s2)
    nop
    jal	func_8007DBEC
    sll	$t0,$t1,0x10
    beqz	$t7,L_8007D874
L_8007D838:
    mfc2	$t1,$12
    jal	func_8007DBEC
    sll	$t0,$t1,0x10
    beqz	$t7,L_8007D874
    mfc2	$t1,$13
    jal	func_8007DBEC
    sll	$t0,$t1,0x10
    beqz	$t7,L_8007D874
    mfc2	$t1,$14
    jal	func_8007DBEC
    sll	$t0,$t1,0x10
    beqz	$t7,L_8007D874
    add	$t0,$t7,$t6
    andi	$t0,$t0,0x4444
    bnez	$t0,L_8007D76C
L_8007D874:
    nop
    bnez	$t7,L_8007D884
    addi	$t0,$zero,-1
    sw	$t0,192($s2)
L_8007D884:
    andi	$t0,$s6,0xff
    beqz	$t0,L_8007D9F8
    nop
    mfc2	$t3,$6
    mfc2	$t4,$20
    mfc2	$t5,$21
    mfc2	$t6,$22
    andi	$t0,$s6,0x11
    beqz	$t0,L_8007D8F0
    nop
    lw	$t0,84($s2)
    lh	$t1,100($s2)
    andi	$t2,$v1,0x1000
    beqz	$t2,L_8007D8D0
    lw	$t2,68($s2)
    addi	$t2,$zero,-1
    xor	$t0,$t0,$t2
    xor	$t1,$t1,$t2
    lw	$t2,68($s2)
L_8007D8D0:
    mtc2	$t0,$0
    mtc2	$t1,$1
    mtc2	$t2,$6
    nop
    nop
    c2	0x108041b
    nop
    mfc2	$t3,$22
L_8007D8F0:
    andi	$t0,$s6,0x22
    beqz	$t0,L_8007D940
    nop
    lw	$t0,88($s2)
    lh	$t1,102($s2)
    andi	$t2,$v1,0x1000
    beqz	$t2,L_8007D920
    lw	$t2,72($s2)
    addi	$t2,$zero,-1
    xor	$t0,$t0,$t2
    xor	$t1,$t1,$t2
    lw	$t2,72($s2)
L_8007D920:
    mtc2	$t0,$0
    mtc2	$t1,$1
    mtc2	$t2,$6
    nop
    nop
    c2	0x108041b
    nop
    mfc2	$t4,$22
L_8007D940:
    andi	$t0,$s6,0x44
    beqz	$t0,L_8007D990
    nop
    lw	$t0,92($s2)
    lh	$t1,104($s2)
    andi	$t2,$v1,0x1000
    beqz	$t2,L_8007D970
    lw	$t2,76($s2)
    addi	$t2,$zero,-1
    xor	$t0,$t0,$t2
    xor	$t1,$t1,$t2
    lw	$t2,76($s2)
L_8007D970:
    mtc2	$t0,$0
    mtc2	$t1,$1
    mtc2	$t2,$6
    nop
    nop
    c2	0x108041b
    nop
    mfc2	$t5,$22
L_8007D990:
    andi	$t0,$s6,0x88
    beqz	$t0,L_8007D9E0
    nop
    lw	$t0,96($s2)
    lh	$t1,106($s2)
    andi	$t2,$v1,0x1000
    beqz	$t2,L_8007D9C0
    lw	$t2,80($s2)
    addi	$t2,$zero,-1
    xor	$t0,$t0,$t2
    xor	$t1,$t1,$t2
    lw	$t2,80($s2)
L_8007D9C0:
    mtc2	$t0,$0
    mtc2	$t1,$1
    mtc2	$t2,$6
    nop
    nop
    c2	0x108041b
    nop
    mfc2	$t6,$22
L_8007D9E0:
    mtc2	$t3,$6
    mtc2	$t4,$20
    mtc2	$t5,$21
    mtc2	$t6,$22
    andi	$t0,$s6,0xff
    xor	$s6,$s6,$t0
L_8007D9F8:
    lh	$t1,226($s2)
    andi	$t4,$v1,0x700
    beqz	$t4,L_8007DAAC
    addu	$t0,$zero,$zero
    andi	$t4,$v1,0x100
    bnez	$t4,L_8007DA7C
    lh	$t0,224($s2)
    addu	$t5,$zero,$zero
    andi	$t4,$v1,0x200
    beqz	$t4,L_8007DA28
    lh	$t2,228($s2)
    addi	$t5,$zero,-1
L_8007DA28:
    sub	$t4,$t0,$t1
    xor	$t4,$t4,$t5
    bgez	$t4,L_8007DA3C
    andi	$t3,$v1,0x1
    addu	$t0,$t1,$zero
L_8007DA3C:
    lh	$t1,230($s2)
    beqz	$t3,L_8007DA58
    sub	$t4,$t0,$t1
    xor	$t4,$t4,$t5
    bgez	$t4,L_8007DA58
    nop
    addu	$t0,$t1,$zero
L_8007DA58:
    sub	$t4,$t0,$t2
    xor	$t4,$t4,$t5
    bgez	$t4,L_8007DA6C
    nop
    addu	$t0,$t2,$zero
L_8007DA6C:
    blez	$t0,L_8007D76C
    sra	$t0,$t0,0x3
    b	L_8007DAAC
    sll	$t0,$t0,0x2
L_8007DA7C:
    lh	$t2,228($s2)
    andi	$t4,$v1,0x1
    beqz	$t4,L_8007DA98
    add	$t4,$t2,$t2
    lh	$t3,230($s2)
    nop
    add	$t4,$t3,$t2
L_8007DA98:
    add	$t4,$t4,$t1
    add	$t4,$t4,$t0
    blez	$t4,L_8007D76C
    sra	$t0,$t4,0x5
    sll	$t0,$t0,0x2
L_8007DAAC:
    lw	$t3,240($s2)
    lw	$t1,192($s2)
    sw	$zero,204($s2)
    blez	$t1,L_8007DAE0
    add	$t2,$t0,$t3
    lw	$t1,220($s2)
    lw	$t2,188($s2)
    sub	$t1,$t1,$t0
    bgtz	$t1,L_8007DADC
    sw	$t0,196($s2)
    sw	$zero,192($s2)
    add	$t2,$t0,$t3
L_8007DADC:
    sw	$s0,200($s2)
L_8007DAE0:
    jalr	$v0
    add	$t7,$zero,$t2
    lw	$t0,192($s2)
    lw	$t2,200($s2)
    blez	$t0,L_8007DBD0
    lw	$t0,0($t2)
    lw	$t1,188($s2)
    sll	$t0,$t0,0x8
    lw	$t3,0($t1)
    srl	$t0,$t0,0x8
    lw	$t4,0($t3)
    sw	$t2,0($t1)
    srl	$t4,$t4,0x18
    sll	$t4,$t4,0x18
    or	$t4,$t4,$t0
    sw	$t4,0($t3)
    lbu	$t4,7($t2)
    lw	$t0,208($s2)
    lw	$t1,212($s2)
    addi	$t5,$t4,-225
    bnez	$t5,L_8007DB40
    addu	$t3,$t2,$zero
    lbu	$t4,11($t2)
    addi	$t2,$t2,4
L_8007DB40:
    andi	$t5,$t4,0x4
    andi	$t4,$t4,0x10
    srl	$t4,$t4,0x2
    add	$t4,$t4,$t5
    addi	$t4,$t4,4
    addi	$t5,$t2,8
    add	$t2,$t5,$t4
    add	$t4,$t2,$t4
    sw	$t0,0($t5)
    lw	$t0,196($s2)
    sw	$t1,0($t2)
    sll	$t1,$s5,0x10
    lw	$t5,204($s2)
    andi	$t1,$t1,0x3ff
    or	$t0,$t0,$t1
    sw	$t0,0($t4)
    addi	$t5,$t5,-1
    bltz	$t5,L_8007DBD0
    lw	$t1,0($t3)
    nop
L_8007DB90:
    srl	$t1,$t1,0x18
    sll	$t6,$t1,0x18
    sll	$t1,$t1,0x2
    addi	$t1,$t1,4
    add	$t2,$t3,$t1
    or	$t6,$t2,$t6
    sw	$t6,0($t3)
    lbu	$t4,7($t2)
    addu	$t3,$t2,$zero
    addi	$t1,$t4,-225
    bnez	$t1,L_8007DBC4
    addi	$t5,$t5,-1
    addi	$t2,$t2,4
L_8007DBC4:
    lw	$t1,0($t3)
    bgez	$t5,L_8007DB90
    sw	$zero,8($t2)
L_8007DBD0:
    lw	$t1,244($s2)
    nop
    sub	$t0,$t1,$s0
    bgez	$t0,L_8007D76C
    nop
    j	L_EXT_8007E500
    nop
.end func_8007D580
