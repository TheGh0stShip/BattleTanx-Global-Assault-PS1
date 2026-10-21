/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008AFB0
.ent func_8008AFB0
func_8008AFB0:
    sw	$a1,4($sp)
    sw	$a2,8($sp)
    sw	$a3,12($sp)
    addiu	$sp,$sp,-584
    sw	$s3,564($sp)
    addu	$s3,$a0,$zero
    addiu	$v0,$sp,592
    sw	$ra,580($sp)
    sw	$s6,576($sp)
    sw	$s5,572($sp)
    sw	$s4,568($sp)
    sw	$s2,560($sp)
    sw	$s1,556($sp)
    sw	$s0,552($sp)
    sw	$a1,588($sp)
    sw	$v0,544($sp)
    lb	$a1,0($a1)
    nop
    beqz	$a1,L_8008B7FC
    addu	$s2,$zero,$zero
    addiu	$s5,$zero,45
    addiu	$s6,$zero,43
    addiu	$s4,$zero,32
    addiu	$v0,$zero,37
L_8008B010:
    bne	$a1,$v0,L_8008B744
    addu	$v0,$s3,$s2
    lui	$a1,0x800b
    addiu	$a1,$a1,22684
    lw	$v0,0($a1)
    lw	$v1,4($a1)
    lw	$a0,8($a1)
    sw	$v0,528($sp)
    sw	$v1,532($sp)
    sw	$a0,536($sp)
    addiu	$a0,$zero,35
    addiu	$v1,$zero,48
L_8008B040:
    lw	$a2,588($sp)
    nop
    addiu	$v0,$a2,1
    sw	$v0,588($sp)
    lb	$a1,1($a2)
    nop
    bne	$a1,$s5,L_8008B074
    nop
    lw	$v0,528($sp)
    nop
    ori	$v0,$v0,0x1
    j	L_8008B040
    sw	$v0,528($sp)
L_8008B074:
    bne	$a1,$s6,L_8008B090
    nop
    lw	$v0,528($sp)
    nop
    ori	$v0,$v0,0x2
    j	L_8008B040
    sw	$v0,528($sp)
L_8008B090:
    bne	$a1,$s4,L_8008B0A0
    nop
    j	L_8008B040
    sb	$a1,529($sp)
L_8008B0A0:
    bne	$a1,$a0,L_8008B0BC
    nop
    lw	$v0,528($sp)
    nop
    ori	$v0,$v0,0x4
    j	L_8008B040
    sw	$v0,528($sp)
L_8008B0BC:
    bne	$a1,$v1,L_8008B0D8
    addiu	$v0,$zero,42
    lw	$v0,528($sp)
    nop
    ori	$v0,$v0,0x8
    j	L_8008B040
    sw	$v0,528($sp)
L_8008B0D8:
    bne	$a1,$v0,L_8008B160
    addiu	$v0,$a1,-48
    lw	$v0,544($sp)
    nop
    lw	$a0,0($v0)
    addiu	$v0,$v0,4
    sw	$v0,544($sp)
    bgez	$a0,L_8008B110
    sw	$a0,532($sp)
    lw	$v1,528($sp)
    negu	$v0,$a0
    sw	$v0,532($sp)
    ori	$v1,$v1,0x1
    sw	$v1,528($sp)
L_8008B110:
    addiu	$v0,$a2,2
    sw	$v0,588($sp)
    lb	$a1,2($a2)
    j	L_8008B16C
    addiu	$v0,$zero,46
L_8008B124:
    lw	$v1,532($sp)
    nop
    sll	$v0,$v1,0x2
    addu	$v0,$v0,$v1
    sll	$v0,$v0,0x1
    addiu	$v0,$v0,-48
    addu	$v0,$v0,$a1
    sw	$v0,532($sp)
    lw	$v1,588($sp)
    nop
    addiu	$v0,$v1,1
    sw	$v0,588($sp)
    lb	$a1,1($v1)
    nop
    addiu	$v0,$a1,-48
L_8008B160:
    sltiu	$v0,$v0,10
    bnez	$v0,L_8008B124
    addiu	$v0,$zero,46
L_8008B16C:
    bne	$a1,$v0,L_8008B228
    nop
    lw	$a0,588($sp)
    nop
    addiu	$v0,$a0,1
    sw	$v0,588($sp)
    lb	$a1,1($a0)
    addiu	$v0,$zero,42
    bne	$a1,$v0,L_8008B1FC
    addiu	$v0,$a1,-48
    lw	$v0,544($sp)
    nop
    lw	$v1,0($v0)
    addiu	$v0,$v0,4
    sw	$v0,544($sp)
    addiu	$v0,$a0,2
    sw	$v1,536($sp)
    sw	$v0,588($sp)
    lb	$a1,2($a0)
    j	L_8008B208
    nop
L_8008B1C0:
    lw	$v1,536($sp)
    nop
    sll	$v0,$v1,0x2
    addu	$v0,$v0,$v1
    sll	$v0,$v0,0x1
    addiu	$v0,$v0,-48
    addu	$v0,$v0,$a1
    sw	$v0,536($sp)
    lw	$v1,588($sp)
    nop
    addiu	$v0,$v1,1
    sw	$v0,588($sp)
    lb	$a1,1($v1)
    nop
    addiu	$v0,$a1,-48
L_8008B1FC:
    sltiu	$v0,$v0,10
    bnez	$v0,L_8008B1C0
    nop
L_8008B208:
    lw	$v0,536($sp)
    nop
    bltz	$v0,L_8008B228
    nop
    lw	$v0,528($sp)
    nop
    ori	$v0,$v0,0x10
    sw	$v0,528($sp)
L_8008B228:
    lw	$v1,528($sp)
    nop
    andi	$v0,$v1,0x1
    beqz	$v0,L_8008B248
    addiu	$s1,$sp,528
    addiu	$v0,$zero,-9
    and	$v0,$v1,$v0
    sw	$v0,528($sp)
L_8008B248:
    addiu	$v1,$a1,-76
L_8008B24C:
    sltiu	$v0,$v1,45
    beqz	$v0,L_8008B738
    sll	$v0,$v1,0x2
    lui	$at,0x800c
    addu	$at,$at,$v0
    lw	$v0,20020($at)
    nop
    jr	$v0
    nop
    lw	$v0,528($sp)
    j	L_8008B294
    ori	$v0,$v0,0x20
    lw	$v0,528($sp)
    j	L_8008B294
    ori	$v0,$v0,0x40
    lw	$v0,528($sp)
    nop
    ori	$v0,$v0,0x80
L_8008B294:
    sw	$v0,528($sp)
    lw	$v1,588($sp)
    nop
    addiu	$v0,$v1,1
    sw	$v0,588($sp)
    lb	$a1,1($v1)
    j	L_8008B24C
    addiu	$v1,$a1,-76
    lw	$v0,544($sp)
    nop
    lw	$a0,0($v0)
    addiu	$v0,$v0,4
    sw	$v0,544($sp)
    lw	$v1,528($sp)
    nop
    srl	$v0,$v1,0x5
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B2E4
    sll	$v0,$a0,0x10
    sra	$a0,$v0,0x10
L_8008B2E4:
    bgez	$a0,L_8008B2F8
    srl	$v0,$v1,0x1
    negu	$a0,$a0
    j	L_8008B340
    sb	$s5,529($sp)
L_8008B2F8:
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B340
    nop
    j	L_8008B340
    sb	$s6,529($sp)
    lw	$v0,544($sp)
    nop
    lw	$a0,0($v0)
    addiu	$v0,$v0,4
    sw	$v0,544($sp)
    lw	$v0,528($sp)
    nop
    srl	$v0,$v0,0x5
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B33C
    nop
    andi	$a0,$a0,0xffff
L_8008B33C:
    sb	$zero,529($sp)
L_8008B340:
    lw	$v1,528($sp)
    nop
    srl	$v0,$v1,0x4
    andi	$v0,$v0,0x1
    bnez	$v0,L_8008B394
    srl	$v0,$v1,0x3
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B380
    nop
    lw	$v1,532($sp)
    lb	$v0,529($sp)
    nop
    beqz	$v0,L_8008B380
    sw	$v1,536($sp)
    addiu	$v0,$v1,-1
    sw	$v0,536($sp)
L_8008B380:
    lw	$v0,536($sp)
    nop
    bgtz	$v0,L_8008B394
    addiu	$v0,$zero,1
    sw	$v0,536($sp)
L_8008B394:
    beqz	$a0,L_8008B3D8
    addu	$s0,$zero,$zero
    lui	$a1,0xcccc
    ori	$a1,$a1,0xcccd
L_8008B3A4:
    multu	$a0,$a1
    addiu	$s1,$s1,-1
    addiu	$s0,$s0,1
    mfhi	$t0
    srl	$v1,$t0,0x3
    sll	$v0,$v1,0x2
    addu	$v0,$v0,$v1
    sll	$v0,$v0,0x1
    subu	$v0,$a0,$v0
    addiu	$v0,$v0,48
    addu	$a0,$v1,$zero
    bnez	$a0,L_8008B3A4
    sb	$v0,0($s1)
L_8008B3D8:
    lw	$v0,536($sp)
    nop
    slt	$v0,$s0,$v0
    beqz	$v0,L_8008B40C
    addiu	$v1,$zero,48
    addiu	$s1,$s1,-1
L_8008B3F0:
    sb	$v1,0($s1)
    lw	$v0,536($sp)
    addiu	$s0,$s0,1
    slt	$v0,$s0,$v0
    bnez	$v0,L_8008B3F0
    addiu	$s1,$s1,-1
    addiu	$s1,$s1,1
L_8008B40C:
    lb	$v0,529($sp)
    lbu	$v1,529($sp)
    beqz	$v0,L_8008B750
    nop
    addiu	$s1,$s1,-1
    sb	$v1,0($s1)
    j	L_8008B750
    addiu	$s0,$s0,1
    lw	$v0,544($sp)
    nop
    lw	$a0,0($v0)
    addiu	$v0,$v0,4
    sw	$v0,544($sp)
    lw	$v1,528($sp)
    nop
    srl	$v0,$v1,0x5
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B45C
    srl	$v0,$v1,0x4
    andi	$a0,$a0,0xffff
L_8008B45C:
    andi	$v0,$v0,0x1
    bnez	$v0,L_8008B494
    srl	$v0,$v1,0x3
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B480
    nop
    lw	$v0,532($sp)
    nop
    sw	$v0,536($sp)
L_8008B480:
    lw	$v0,536($sp)
    nop
    bgtz	$v0,L_8008B494
    addiu	$v0,$zero,1
    sw	$v0,536($sp)
L_8008B494:
    beqz	$a0,L_8008B4B8
    addu	$s0,$zero,$zero
L_8008B49C:
    addiu	$s1,$s1,-1
    andi	$v0,$a0,0x7
    addiu	$v0,$v0,48
    sb	$v0,0($s1)
    srl	$a0,$a0,0x3
    bnez	$a0,L_8008B49C
    addiu	$s0,$s0,1
L_8008B4B8:
    lw	$v0,528($sp)
    nop
    srl	$v0,$v0,0x2
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B4F4
    nop
    beqz	$s0,L_8008B4F4
    addiu	$v1,$zero,48
    lb	$v0,0($s1)
    nop
    beq	$v0,$v1,L_8008B4F4
    nop
    addiu	$s1,$s1,-1
    sb	$v1,0($s1)
    addiu	$s0,$s0,1
L_8008B4F4:
    lw	$v0,536($sp)
    nop
    slt	$v0,$s0,$v0
    beqz	$v0,L_8008B750
    addiu	$v1,$zero,48
    addiu	$s1,$s1,-1
L_8008B50C:
    sb	$v1,0($s1)
    lw	$v0,536($sp)
    addiu	$s0,$s0,1
    slt	$v0,$s0,$v0
    bnez	$v0,L_8008B50C
    addiu	$s1,$s1,-1
    j	L_8008B750
    addiu	$s1,$s1,1
    lw	$v1,528($sp)
    addiu	$v0,$zero,8
    sw	$v0,536($sp)
    ori	$v1,$v1,0x50
    sw	$v1,528($sp)
    lui	$a3,0x800c
    j	L_8008B554
    addiu	$a3,$a3,19980
    lui	$a3,0x800c
    addiu	$a3,$a3,20000
L_8008B554:
    lw	$v0,544($sp)
    nop
    lw	$a0,0($v0)
    addiu	$v0,$v0,4
    sw	$v0,544($sp)
    lw	$v1,528($sp)
    nop
    srl	$v0,$v1,0x5
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B584
    srl	$v0,$v1,0x4
    andi	$a0,$a0,0xffff
L_8008B584:
    andi	$v0,$v0,0x1
    bnez	$v0,L_8008B5C8
    srl	$v0,$v1,0x3
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B5B4
    srl	$v0,$v1,0x2
    lw	$a2,532($sp)
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B5B4
    sw	$a2,536($sp)
    addiu	$v0,$a2,-2
    sw	$v0,536($sp)
L_8008B5B4:
    lw	$v0,536($sp)
    nop
    bgtz	$v0,L_8008B5C8
    addiu	$v0,$zero,1
    sw	$v0,536($sp)
L_8008B5C8:
    beqz	$a0,L_8008B5F0
    addu	$s0,$zero,$zero
L_8008B5D0:
    addiu	$s1,$s1,-1
    andi	$v0,$a0,0xf
    srl	$a0,$a0,0x4
    addu	$v0,$a3,$v0
    lbu	$v0,0($v0)
    addiu	$s0,$s0,1
    bnez	$a0,L_8008B5D0
    sb	$v0,0($s1)
L_8008B5F0:
    lw	$v0,536($sp)
    nop
    slt	$v0,$s0,$v0
    beqz	$v0,L_8008B628
    nop
    addiu	$v1,$zero,48
    addiu	$s1,$s1,-1
L_8008B60C:
    sb	$v1,0($s1)
    lw	$v0,536($sp)
    addiu	$s0,$s0,1
    slt	$v0,$s0,$v0
    bnez	$v0,L_8008B60C
    addiu	$s1,$s1,-1
    addiu	$s1,$s1,1
L_8008B628:
    lw	$v0,528($sp)
    nop
    srl	$v0,$v0,0x2
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B750
    addiu	$v0,$zero,48
    addiu	$s1,$s1,-1
    sb	$a1,0($s1)
    addiu	$s1,$s1,-1
    addiu	$s0,$s0,2
    j	L_8008B750
    sb	$v0,0($s1)
    addiu	$s1,$s1,-1
    lw	$v0,544($sp)
    addiu	$s0,$zero,1
    lbu	$v1,0($v0)
    addiu	$v0,$v0,4
    sb	$v1,0($s1)
    j	L_8008B750
    sw	$v0,544($sp)
    lw	$v0,544($sp)
    lw	$v1,528($sp)
    lw	$s1,0($v0)
    addiu	$v0,$v0,4
    sw	$v0,544($sp)
    srl	$v0,$v1,0x2
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B6C8
    srl	$v0,$v1,0x4
    lbu	$s0,0($s1)
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B750
    addiu	$s1,$s1,1
    lw	$v1,536($sp)
    nop
    slt	$v0,$v1,$s0
    beqz	$v0,L_8008B750
    nop
    j	L_8008B750
    addu	$s0,$v1,$zero
L_8008B6C8:
    andi	$v0,$v0,0x1
    bnez	$v0,L_8008B6E4
    addu	$a0,$s1,$zero
    jal	func_80090184
    addu	$a0,$s1,$zero
    j	L_8008B750
    addu	$s0,$v0,$zero
L_8008B6E4:
    lw	$a2,536($sp)
    jal	func_8008A974
    addu	$a1,$zero,$zero
    bnez	$v0,L_8008B750
    subu	$s0,$v0,$s1
    lw	$s0,536($sp)
    j	L_8008B750
    nop
    lw	$v0,544($sp)
    lw	$v1,528($sp)
    lw	$s1,0($v0)
    addiu	$v0,$v0,4
    sw	$v0,544($sp)
    srl	$v0,$v1,0x5
    andi	$v0,$v0,0x1
    beqz	$v0,L_8008B730
    nop
    j	L_8008B7DC
    sh	$s2,0($s1)
L_8008B730:
    j	L_8008B7DC
    sw	$s2,0($s1)
L_8008B738:
    addiu	$v0,$zero,37
    bne	$a1,$v0,L_8008B7FC
    addu	$v0,$s3,$s2
L_8008B744:
    sb	$a1,0($v0)
    j	L_8008B7DC
    addiu	$s2,$s2,1
L_8008B750:
    lw	$v0,532($sp)
    nop
    slt	$v0,$s0,$v0
    beqz	$v0,L_8008B7A0
    addu	$a0,$s3,$s2
    lw	$v0,528($sp)
    nop
    andi	$v0,$v0,0x1
    bnez	$v0,L_8008B7A4
    addu	$a1,$s1,$zero
L_8008B778:
    addu	$v0,$s3,$s2
    sb	$s4,0($v0)
    lw	$v0,532($sp)
    nop
    addiu	$v0,$v0,-1
    sw	$v0,532($sp)
    slt	$v0,$s0,$v0
    bnez	$v0,L_8008B778
    addiu	$s2,$s2,1
    addu	$a0,$s3,$s2
L_8008B7A0:
    addu	$a1,$s1,$zero
L_8008B7A4:
    jal	func_8008A884
    addu	$a2,$s0,$zero
    lw	$v0,532($sp)
    nop
    slt	$v0,$s0,$v0
    beqz	$v0,L_8008B7DC
    addu	$s2,$s2,$s0
L_8008B7C0:
    addu	$v0,$s3,$s2
    sb	$s4,0($v0)
    lw	$v0,532($sp)
    addiu	$s0,$s0,1
    slt	$v0,$s0,$v0
    bnez	$v0,L_8008B7C0
    addiu	$s2,$s2,1
L_8008B7DC:
    lw	$v1,588($sp)
    nop
    addiu	$v0,$v1,1
    sw	$v0,588($sp)
    lb	$a1,1($v1)
    nop
    bnez	$a1,L_8008B010
    addiu	$v0,$zero,37
L_8008B7FC:
    addu	$v0,$s3,$s2
    sb	$zero,0($v0)
    addu	$v0,$s2,$zero
    lw	$ra,580($sp)
    lw	$s6,576($sp)
    lw	$s5,572($sp)
    lw	$s4,568($sp)
    lw	$s3,564($sp)
    lw	$s2,560($sp)
    lw	$s1,556($sp)
    lw	$s0,552($sp)
    jr	$ra
    addiu	$sp,$sp,584
.end func_8008AFB0
