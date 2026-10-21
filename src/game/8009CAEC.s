/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8009CAEC
.ent func_8009CAEC
func_8009CAEC:
    lui	$t0,0x800c
    addiu	$t0,$t0,-29764
    addi	$a2,$a2,2048
    lui	$at,0x1
    add	$a3,$a2,$at
    bnez	$a0,L_8009CB40
    lw	$t1,0($t0)
    lui	$t0,0x800c
    addiu	$t0,$t0,-29760
    lw	$a0,0($t0)
    lw	$a1,4($t0)
    lw	$v0,8($t0)
    lw	$v1,12($t0)
    lw	$t4,16($t0)
    lw	$t5,20($t0)
    lw	$t7,24($t0)
    lw	$t8,28($t0)
    lw	$t9,32($t0)
    add	$t1,$t1,$t1
    b	L_8009CCCC
    add	$t6,$a1,$t1
L_8009CB40:
    add	$t5,$zero,$zero
    add	$t7,$zero,$zero
    add	$t8,$zero,$zero
    add	$t9,$zero,$zero
    add	$t1,$t1,$t1
    add	$t6,$a1,$t1
    lw	$t1,0($a0)
    lhu	$t4,4($a0)
    lhu	$t2,6($a0)
    lhu	$v0,8($a0)
    lhu	$v1,10($a0)
    addi	$t2,$t2,-3
    bltz	$t2,L_8009CB7C
    sll	$t4,$t4,0xa
    addi	$t5,$zero,1
L_8009CB7C:
    addi	$a0,$a0,12
    sll	$v0,$v0,0x10
    or	$v0,$v0,$v1
    or	$v1,$zero,$zero
    sw	$t1,0($a1)
    andi	$t1,$t1,0xffff
    sll	$t1,$t1,0x2
    addiu	$t1,$t1,4
    add	$t1,$t1,$a1
    lui	$t0,0x800c
    addiu	$t0,$t0,-29724
    sw	$t1,0($t0)
    addi	$a1,$a1,2
L_8009CBB0:
    beqz	$t5,L_8009CC88
    srl	$t0,$v0,0x16
    xori	$at,$t0,0x3ff
    beqz	$at,L_8009CDD4
    addi	$a1,$a1,2
    addi	$at,$t5,-3
    bltz	$at,L_8009CBD4
    addi	$at,$a2,-1024
    addi	$at,$at,-1024
L_8009CBD4:
    srl	$t0,$v0,0x18
    sll	$t0,$t0,0x2
    add	$t0,$t0,$at
    lhu	$t1,0($t0)
    lhu	$t2,2($t0)
    and	$t0,$zero,$zero
    beqz	$t2,L_8009CC18
    sllv	$v0,$v0,$t1
    addi	$at,$zero,32
    sub	$at,$at,$t2
    srlv	$t0,$v0,$at
    bltz	$v0,L_8009CC14
    sllv	$v0,$v0,$t2
    addi	$t3,$zero,-1
    srlv	$t3,$t3,$at
    sub	$t0,$t0,$t3
L_8009CC14:
    add	$v1,$v1,$t2
L_8009CC18:
    add	$v1,$v1,$t1
    andi	$at,$v1,0x10
    beqz	$at,L_8009CC38
    andi	$v1,$v1,0xf
    lhu	$t1,0($a0)
    addi	$a0,$a0,2
    sllv	$t1,$t1,$v1
    or	$v0,$v0,$t1
L_8009CC38:
    addi	$at,$t5,-2
    bgtz	$at,L_8009CC60
    add	$t1,$t9,$t0
    beqz	$at,L_8009CC58
    add	$t1,$t8,$t0
    add	$t1,$t7,$t0
    b	L_8009CC64
    add	$t7,$t7,$t0
L_8009CC58:
    b	L_8009CC64
    add	$t8,$t8,$t0
L_8009CC60:
    add	$t9,$t9,$t0
L_8009CC64:
    sll	$t1,$t1,0x2
    andi	$t1,$t1,0x3ff
    or	$t1,$t4,$t1
    addi	$t5,$t5,1
    addi	$at,$t5,-7
    bnez	$at,L_8009CCC0
    sh	$t1,0($a1)
    b	L_8009CCC0
    addi	$t5,$t5,-6
L_8009CC88:
    xori	$at,$t0,0x1ff
    beqz	$at,L_8009CDD4
    addi	$a1,$a1,2
    sll	$v0,$v0,0xa
    addi	$v1,$v1,10
    andi	$at,$v1,0x10
    beqz	$at,L_8009CCB8
    andi	$v1,$v1,0xf
    lhu	$t1,0($a0)
    addi	$a0,$a0,2
    sllv	$t1,$t1,$v1
    or	$v0,$v0,$t1
L_8009CCB8:
    or	$t0,$t4,$t0
    sh	$t0,0($a1)
L_8009CCC0:
    subu	$at,$a1,$t6
    bgez	$at,L_8009CE18
    addi	$a1,$a1,2
L_8009CCCC:
    srl	$t0,$v0,0x13
    sll	$t0,$t0,0x3
    add	$t0,$t0,$a2
    lw	$t1,0($t0)
    nop
    bnez	$t1,L_8009CD28
    andi	$at,$t1,0xff
    sll	$v0,$v0,0x8
    addi	$v1,$v1,8
    andi	$at,$v1,0x10
    beqz	$at,L_8009CD0C
    andi	$v1,$v1,0xf
    lhu	$t0,0($a0)
    addi	$a0,$a0,2
    sllv	$t0,$t0,$v1
    or	$v0,$v0,$t0
L_8009CD0C:
    srl	$t0,$v0,0x17
    sll	$t0,$t0,0x2
    add	$t0,$t0,$a3
    lw	$t1,0($t0)
    add	$t3,$zero,$zero
    b	L_8009CD2C
    andi	$at,$t1,0xff
L_8009CD28:
    lw	$t3,4($t0)
L_8009CD2C:
    sllv	$v0,$v0,$at
    add	$v1,$v1,$at
    andi	$at,$v1,0x10
    beqz	$at,L_8009CD50
    andi	$v1,$v1,0xf
    lhu	$t0,0($a0)
    addi	$a0,$a0,2
    sllv	$t0,$t0,$v1
    or	$v0,$v0,$t0
L_8009CD50:
    srl	$t1,$t1,0x10
    xori	$at,$t1,0x7c1f
    beqz	$at,L_8009CDB0
    xori	$at,$t1,0xfe00
    beqz	$at,L_8009CBB0
    sh	$t1,0($a1)
    beqz	$t3,L_8009CCCC
    addi	$a1,$a1,2
    andi	$t2,$t3,0xffff
    xori	$at,$t2,0x7c1f
    beqz	$at,L_8009CDB0
    xori	$at,$t2,0xfe00
    beqz	$at,L_8009CBB0
    sh	$t2,0($a1)
    srl	$t2,$t3,0x10
    beqz	$t2,L_8009CCCC
    addi	$a1,$a1,2
    xori	$at,$t2,0x7c1f
    beqz	$at,L_8009CDB0
    xori	$at,$t2,0xfe00
    beqz	$at,L_8009CBB0
    sh	$t2,0($a1)
    b	L_8009CCCC
    addi	$a1,$a1,2
L_8009CDB0:
    srl	$t0,$v0,0x10
    sh	$t0,0($a1)
    addi	$a1,$a1,2
    lhu	$t0,0($a0)
    addi	$a0,$a0,2
    sll	$v0,$v0,0x10
    sllv	$t0,$t0,$v1
    b	L_8009CCCC
    or	$v0,$v0,$t0
L_8009CDD4:
    lui	$t0,0x800c
    addiu	$t0,$t0,-29724
    lw	$t1,0($t0)
    ori	$t0,$zero,0xfe00
L_8009CDE4:
    subu	$at,$a1,$t1
    bgez	$at,L_8009CDFC
    nop
    sh	$t0,0($a1)
    b	L_8009CDE4
    addi	$a1,$a1,2
L_8009CDFC:
    mfc0	$t1,$12
    nop
    lui	$at,0x2
    or	$t1,$t1,$at
    mtc0	$t1,$12
    jr	$ra
    add	$v0,$zero,$zero
L_8009CE18:
    lui	$t0,0x800c
    addiu	$t0,$t0,-29760
    sw	$a0,0($t0)
    sw	$a1,4($t0)
    sw	$v0,8($t0)
    sw	$v1,12($t0)
    sw	$t4,16($t0)
    sw	$t5,20($t0)
    sw	$t7,24($t0)
    sw	$t8,28($t0)
    sw	$t9,32($t0)
    jr	$ra
    addi	$v0,$zero,1
.end func_8009CAEC
