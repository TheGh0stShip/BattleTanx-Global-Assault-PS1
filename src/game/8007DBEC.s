/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8007DBEC
.ent func_8007DBEC
func_8007DBEC:
    sra	$t0,$t0,0x10
    sub	$t0,$t0,$t2
    bgez	$t0,L_8007DC00
    sub	$t0,$t0,$t3
    addi	$t7,$t7,1
L_8007DC00:
    bltz	$t0,L_8007DC0C
    sra	$t0,$t1,0x10
    addi	$t7,$t7,16
L_8007DC0C:
    sub	$t0,$t0,$t4
    bgez	$t0,L_8007DC1C
    sub	$t0,$t0,$t5
    addi	$t7,$t7,256
L_8007DC1C:
    bltz	$t0,L_8007DC28
    add	$ra,$ra,$a2
    addi	$t7,$t7,4096
L_8007DC28:
    jr	$ra
    nop
    j	L_8007E088
    nop
    j	L_8007E094
    nop
    j	L_8007E0A0
    nop
    j	L_8007E0AC
    nop
    j	L_8007E0B8
    nop
    j	L_8007E0EC
    nop
    j	L_8007E120
    nop
    j	L_8007E154
    nop
    j	L_8007E190
    nop
    j	L_8007E1A0
    nop
    j	L_8007E1B0
    nop
    j	L_8007E1C0
    nop
    j	L_8007E1C8
    nop
    j	L_8007E1EC
    nop
    j	L_8007E210
    nop
    j	L_8007E234
    nop
    j	L_8007E258
    nop
    j	L_8007E2A0
    nop
    j	L_8007E2E8
    nop
    j	L_8007E330
    nop
    j	L_8007E378
    nop
    j	L_8007E3C0
    nop
    j	L_8007E4AC
    nop
    j	L_8007E478
    nop
    j	L_8007E4A4
    nop
    j	L_8007E408
    nop
    j	L_8007E500
    nop
    j	L_8007E428
    nop
    j	L_8007E448
    nop
    j	L_8007E568
    nop
    j	L_8007E568
    nop
    j	L_8007E568
    nop
    j	L_8007E188
    nop
    j	L_8007E198
    nop
    j	L_8007E1A8
    nop
    j	L_8007E1B8
    nop
    j	L_8007E0B8
    nop
    j	L_8007E0EC
    nop
    j	L_8007E120
    nop
    j	L_8007E154
    nop
    j	L_8007E550
    nop
    lb	$a3,-8776($zero)
    lb	$a3,-8448($zero)
    lb	$a3,-8776($zero)
    lb	$a3,-8448($zero)
    lb	$a3,-8620($zero)
    lb	$a3,-8264($zero)
    lb	$a3,-8620($zero)
    lb	$a3,-8264($zero)
    lb	$a3,-8716($zero)
    lb	$a3,-8380($zero)
    lb	$a3,-8716($zero)
    lb	$a3,-8380($zero)
    lb	$a3,-8552($zero)
    lb	$a3,-8184($zero)
    lb	$a3,-8552($zero)
    lb	$a3,-8184($zero)
    sw	$t8,4($s0)
    swc2	$6,8($s0)
    swc2	$12,12($s0)
    swc2	$13,16($s0)
    swc2	$14,20($s0)
    addiu	$t0,$zero,34
    sb	$t0,11($s0)
    lw	$t0,0($t7)
    addiu	$s3,$s3,16384
    lui	$t1,0x500
    or	$t0,$t0,$t1
    sw	$t0,0($s0)
    sw	$s0,0($t7)
    jr	$ra
    addiu	$s0,$s0,24
    swc2	$6,4($s0)
    swc2	$12,8($s0)
    swc2	$13,16($s0)
    swc2	$14,24($s0)
    addiu	$t0,$zero,38
    sb	$t0,7($s0)
    lhu	$t0,132($s2)
    lw	$t1,116($s2)
    lw	$t2,120($s2)
    lw	$t3,124($s2)
    add	$t1,$t1,$t0
    add	$t2,$t2,$t0
    add	$t3,$t3,$t0
    sw	$t1,12($s0)
    sw	$t2,20($s0)
    sw	$t3,28($s0)
    lw	$t0,0($t7)
    addiu	$s3,$s3,16384
    lui	$t1,0x700
    or	$t0,$t0,$t1
    sw	$t0,0($s0)
    sw	$s0,0($t7)
    jr	$ra
    addiu	$s0,$s0,32
    sw	$t8,4($s0)
    swc2	$6,8($s0)
    swc2	$12,12($s0)
    swc2	$20,16($s0)
    swc2	$13,20($s0)
    swc2	$21,24($s0)
    swc2	$14,28($s0)
    addiu	$t0,$zero,50
    sb	$t0,11($s0)
    lw	$t0,0($t7)
    addiu	$s3,$s3,16384
    lui	$t1,0x700
    or	$t0,$t0,$t1
    sw	$t0,0($s0)
    sw	$s0,0($t7)
    jr	$ra
    addiu	$s0,$s0,32
    swc2	$6,4($s0)
    swc2	$12,8($s0)
    swc2	$20,16($s0)
    swc2	$13,20($s0)
    swc2	$21,28($s0)
    swc2	$14,32($s0)
    addiu	$t0,$zero,54
    sb	$t0,7($s0)
    lhu	$t0,132($s2)
    lw	$t1,116($s2)
    lw	$t2,120($s2)
    lw	$t3,124($s2)
    add	$t1,$t1,$t0
    add	$t2,$t2,$t0
    add	$t3,$t3,$t0
    sw	$t1,12($s0)
    sw	$t2,24($s0)
    sw	$t3,36($s0)
    lw	$t0,0($t7)
    addiu	$s3,$s3,16384
    lui	$t1,0x900
    or	$t0,$t0,$t1
    sw	$t0,0($s0)
    sw	$s0,0($t7)
    jr	$ra
    addiu	$s0,$s0,40
    sw	$t8,4($s0)
    lw	$t0,0($s2)
    swc2	$6,8($s0)
    swc2	$12,12($s0)
    swc2	$13,16($s0)
    sw	$t0,20($s0)
    swc2	$14,24($s0)
    addiu	$t0,$zero,42
    sb	$t0,11($s0)
    lw	$t0,0($t7)
    addiu	$s3,$s3,1
    lui	$t1,0x600
    or	$t0,$t0,$t1
    sw	$t0,0($s0)
    sw	$s0,0($t7)
    jr	$ra
    addiu	$s0,$s0,28
    lw	$t0,0($s2)
    swc2	$6,4($s0)
    swc2	$12,8($s0)
    swc2	$13,16($s0)
    sw	$t0,24($s0)
    swc2	$14,32($s0)
    addiu	$t0,$zero,46
    sb	$t0,7($s0)
    lhu	$t0,132($s2)
    lw	$t1,116($s2)
    lw	$t2,120($s2)
    lw	$t3,128($s2)
    lw	$t4,124($s2)
    add	$t1,$t1,$t0
    add	$t2,$t2,$t0
    add	$t3,$t3,$t0
    add	$t4,$t4,$t0
    sw	$t1,12($s0)
    sw	$t2,20($s0)
    sw	$t3,28($s0)
    sw	$t4,36($s0)
    lw	$t0,0($t7)
    addiu	$s3,$s3,1
    lui	$t1,0x900
    or	$t0,$t0,$t1
    sw	$t0,0($s0)
    sw	$s0,0($t7)
    jr	$ra
    addiu	$s0,$s0,40
    sw	$t8,4($s0)
    lw	$t0,0($s2)
    swc2	$6,8($s0)
    swc2	$12,12($s0)
    swc2	$20,16($s0)
    swc2	$13,20($s0)
    swc2	$22,24($s0)
    sw	$t0,28($s0)
    swc2	$21,32($s0)
    swc2	$14,36($s0)
    addiu	$t0,$zero,58
    sb	$t0,11($s0)
    lw	$t0,0($t7)
    addiu	$s3,$s3,1
    lui	$t1,0x900
    or	$t0,$t0,$t1
    sw	$t0,0($s0)
    sw	$s0,0($t7)
    jr	$ra
    addiu	$s0,$s0,40
    lw	$t0,0($s2)
    swc2	$6,4($s0)
    swc2	$12,8($s0)
    swc2	$20,16($s0)
    swc2	$13,20($s0)
    swc2	$22,28($s0)
    sw	$t0,32($s0)
    swc2	$21,40($s0)
    swc2	$14,44($s0)
    addiu	$t0,$zero,62
    sb	$t0,7($s0)
    lhu	$t0,132($s2)
    lw	$t1,116($s2)
    lw	$t2,120($s2)
    lw	$t3,128($s2)
    lw	$t4,124($s2)
    add	$t1,$t1,$t0
    add	$t2,$t2,$t0
    add	$t3,$t3,$t0
    add	$t4,$t4,$t0
    sw	$t1,12($s0)
    sw	$t2,24($s0)
    sw	$t3,36($s0)
    sw	$t4,48($s0)
    lw	$t0,0($t7)
    addiu	$s3,$s3,1
    lui	$t1,0xc00
    or	$t0,$t0,$t1
    sw	$t0,0($s0)
    sw	$s0,0($t7)
    jr	$ra
    addiu	$s0,$s0,52
L_8007E088:
    ori	$s6,$s6,0x110
    jr	$ra
    sw	$s8,68($s2)
L_8007E094:
    ori	$s6,$s6,0x220
    jr	$ra
    sw	$s8,72($s2)
L_8007E0A0:
    ori	$s6,$s6,0x440
    jr	$ra
    sw	$s8,76($s2)
L_8007E0AC:
    ori	$s6,$s6,0x880
    jr	$ra
    sw	$s8,80($s2)
L_8007E0B8:
    ori	$s6,$s6,0x111
    sra	$t0,$s7,0x3
    srl	$t0,$t0,0x10
    sll	$t1,$s7,0x8
    sra	$t1,$t1,0x18
    sll	$t1,$t1,0x15
    or	$t0,$t0,$t1
    sw	$t0,84($s2)
    sll	$t1,$s8,0x18
    sra	$t1,$t1,0x18
    sll	$t1,$t1,0x5
    jr	$ra
    sh	$t1,100($s2)
L_8007E0EC:
    ori	$s6,$s6,0x222
    sra	$t0,$s7,0x3
    srl	$t0,$t0,0x10
    sll	$t1,$s7,0x8
    sra	$t1,$t1,0x18
    sll	$t1,$t1,0x15
    or	$t0,$t0,$t1
    sw	$t0,88($s2)
    sll	$t1,$s8,0x18
    sra	$t1,$t1,0x18
    sll	$t1,$t1,0x5
    jr	$ra
    sh	$t1,102($s2)
L_8007E120:
    ori	$s6,$s6,0x444
    sra	$t0,$s7,0x3
    srl	$t0,$t0,0x10
    sll	$t1,$s7,0x8
    sra	$t1,$t1,0x18
    sll	$t1,$t1,0x15
    or	$t0,$t0,$t1
    sw	$t0,92($s2)
    sll	$t1,$s8,0x18
    sra	$t1,$t1,0x18
    sll	$t1,$t1,0x5
    jr	$ra
    sh	$t1,104($s2)
L_8007E154:
    ori	$s6,$s6,0x888
    sra	$t0,$s7,0x3
    srl	$t0,$t0,0x10
    sll	$t1,$s7,0x8
    sra	$t1,$t1,0x18
    sll	$t1,$t1,0x15
    or	$t0,$t0,$t1
    sw	$t0,96($s2)
    sll	$t1,$s8,0x18
    sra	$t1,$t1,0x18
    sll	$t1,$t1,0x5
    jr	$ra
    sh	$t1,106($s2)
L_8007E188:
    srl	$t0,$s7,0x16
    sh	$t0,64($s2)
L_8007E190:
    jr	$ra
    sh	$s8,116($s2)
L_8007E198:
    srl	$t0,$s7,0x16
    sh	$t0,64($s2)
L_8007E1A0:
    jr	$ra
    sh	$s8,120($s2)
L_8007E1A8:
    srl	$t0,$s7,0x16
    sh	$t0,64($s2)
L_8007E1B0:
    jr	$ra
    sh	$s8,124($s2)
L_8007E1B8:
    srl	$t0,$s7,0x16
    sh	$t0,64($s2)
L_8007E1C0:
    jr	$ra
    sh	$s8,128($s2)
L_8007E1C8:
    ori	$s6,$s6,0x110
    sll	$t0,$s8,0x3
    addu	$t0,$t0,$a1
    sh	$s8,208($s2)
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$12
    jr	$ra
    sh	$t2,224($s2)
L_8007E1EC:
    ori	$s6,$s6,0x220
    sll	$t0,$s8,0x3
    addu	$t0,$t0,$a1
    sh	$s8,210($s2)
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$13
    jr	$ra
    sh	$t2,226($s2)
L_8007E210:
    ori	$s6,$s6,0x440
    sll	$t0,$s8,0x3
    addu	$t0,$t0,$a1
    sh	$s8,212($s2)
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$14
    jr	$ra
    sh	$t2,228($s2)
L_8007E234:
    ori	$s6,$s6,0x880
    sll	$t0,$s8,0x3
    addu	$t0,$t0,$a1
    sh	$s8,214($s2)
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    sw	$t1,0($s2)
    jr	$ra
    sh	$t2,230($s2)
L_8007E258:
    ori	$s6,$s6,0x330
    andi	$t0,$s8,0xfff
    sh	$t0,210($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$13
    sh	$t2,226($s2)
    srl	$t0,$s8,0xc
    sh	$t0,208($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$12
    jr	$ra
    sh	$t2,224($s2)
L_8007E2A0:
    ori	$s6,$s6,0x660
    andi	$t0,$s8,0xfff
    sh	$t0,212($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$14
    sh	$t2,228($s2)
    srl	$t0,$s8,0xc
    sh	$t0,210($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$13
    jr	$ra
    sh	$t2,226($s2)
L_8007E2E8:
    ori	$s6,$s6,0xcc0
    andi	$t0,$s8,0xfff
    sh	$t0,214($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    sw	$t1,0($s2)
    sh	$t2,230($s2)
    srl	$t0,$s8,0xc
    sh	$t0,212($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$14
    jr	$ra
    sh	$t2,228($s2)
L_8007E330:
    ori	$s6,$s6,0x550
    andi	$t0,$s8,0xfff
    sh	$t0,212($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$14
    sh	$t2,228($s2)
    srl	$t0,$s8,0xc
    sh	$t0,208($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$12
    jr	$ra
    sh	$t2,224($s2)
L_8007E378:
    ori	$s6,$s6,0x990
    andi	$t0,$s8,0xfff
    sh	$t0,214($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    sw	$t1,0($s2)
    sh	$t2,230($s2)
    srl	$t0,$s8,0xc
    sh	$t0,208($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$12
    jr	$ra
    sh	$t2,224($s2)
L_8007E3C0:
    ori	$s6,$s6,0xaa0
    andi	$t0,$s8,0xfff
    sh	$t0,214($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    sw	$t1,0($s2)
    sh	$t2,230($s2)
    srl	$t0,$s8,0xc
    sh	$t0,210($s2)
    sll	$t0,$t0,0x3
    addu	$t0,$t0,$a1
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    mtc2	$t1,$13
    jr	$ra
    sh	$t2,226($s2)
L_8007E408:
    lw	$t0,0($a0)
    lw	$t1,156($s2)
    addiu	$a0,$a0,4
    and	$t0,$t0,$t1
    bnez	$t0,L_EXT_8007D76C
    addiu	$t0,$s8,-8
    j	L_EXT_8007D76C
    add	$a0,$a0,$t0
L_8007E428:
    lw	$t0,0($a0)
    lw	$t1,156($s2)
    addiu	$a0,$a0,20
    and	$t0,$t0,$t1
    bnez	$t0,L_EXT_8007D76C
    addiu	$t0,$s8,-24
    j	L_EXT_8007D76C
    add	$a0,$a0,$t0
L_8007E448:
    lw	$t0,0($a0)
    lw	$t1,4($a0)
    lw	$t2,156($s2)
    lw	$t3,160($s2)
    and	$t0,$t0,$t2
    and	$t1,$t1,$t3
    or	$t0,$t0,$t1
    bnez	$t0,L_EXT_8007D76C
    addiu	$a0,$a0,24
    addiu	$t0,$s8,-28
    j	L_EXT_8007D76C
    add	$a0,$a0,$t0
L_8007E478:
    andi	$t1,$v1,0x10
    beqz	$t1,L_8007E488
    srl	$t1,$s8,0x14
    ori	$t1,$t1,0x2
L_8007E488:
    andi	$v1,$v1,0xfff0
    or	$v1,$v1,$t1
    sll	$t1,$t1,0x2
    add	$t1,$t1,$s1
    lw	$v0,328($t1)
    jr	$ra
    nop
L_8007E4A4:
    jr	$ra
    nop
L_8007E4AC:
    lw	$t2,236($s2)
    srl	$t0,$s7,0x18
    sll	$t0,$t0,0x2
    add	$t0,$t0,$t2
    lw	$t0,0($t0)
    nop
    lw	$t1,0($t0)
    lh	$t2,4($t0)
    sh	$t1,132($s2)
    srl	$t1,$t1,0x10
    andi	$t3,$t8,0x60
    andi	$t1,$t1,0xff9f
    or	$t1,$t1,$t3
    andi	$t0,$t1,0x4000
    bnez	$t0,L_8007E4F8
    sh	$t1,122($s2)
    lw	$t0,232($s2)
    nop
    add	$t2,$t2,$t0
L_8007E4F8:
    jr	$ra
    sh	$t2,118($s2)
L_8007E500:
    jal	func_8008DC34
    srl	$a0,$s3,0xe
    jal	func_8008DC50
    andi	$a0,$s3,0x3fff
    lui	$a0,0x8000
    jal	func_8007F7E8
    or	$a0,$a0,$s0
    lw	$s0,16($sp)
    lw	$s1,20($sp)
    lw	$s2,24($sp)
    lw	$s3,28($sp)
    lw	$s4,32($sp)
    lw	$s5,36($sp)
    lw	$s6,40($sp)
    lw	$s7,44($sp)
    lw	$s8,48($sp)
    lw	$ra,52($sp)
    addiu	$sp,$sp,60
    jr	$ra
    nop
L_8007E550:
    srl	$t0,$s7,0x10
    andi	$t0,$t0,0x3
    sll	$t0,$t0,0x8
    andi	$v1,$v1,0xf8ff
    jr	$ra
    or	$v1,$v1,$t0
L_8007E568:
    jr	$ra
    nop
.end func_8007DBEC
