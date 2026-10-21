/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8007C68C
.ent func_8007C68C
func_8007C68C:
    mtc2	$t0,$8
    mtc2	$t1,$9
    sll	$t0,$t2,0x4
    andi	$t0,$t0,0xff0
    c2	0x198003d
    srl	$t1,$t2,0x4
    andi	$t1,$t1,0xff0
    srl	$t2,$t2,0xc
    andi	$t2,$t2,0xff0
    mtc2	$t0,$9
    mtc2	$t1,$10
    mtc2	$t2,$11
    mfc2	$t0,$25
    addiu	$t1,$zero,4096
    sub	$t1,$t1,$t0
    addi	$t2,$t0,-4096
    blez	$t2,L_8007C6D8
    mtc2	$t1,$8
    addiu	$t0,$zero,4096
L_8007C6D8:
    lw	$t2,164($s2)
    nop
    c2	0x198003d
    sll	$t1,$t2,0x4
    andi	$t1,$t1,0xff0
    mtc2	$t1,$9
    srl	$t1,$t2,0x4
    andi	$t1,$t1,0xff0
    mtc2	$t1,$10
    srl	$t1,$t2,0xc
    andi	$t1,$t1,0xff0
    mtc2	$t1,$11
    mfc2	$t2,$22
    mtc2	$t0,$8
    nop
    nop
    c2	0x198003d
    mfc2	$t0,$22
    jr	$ra
    nop
    lh	$t1,226($s2)
    andi	$t4,$v1,0x700
    beqz	$t4,L_8007C7DC
    addu	$t0,$zero,$zero
    andi	$t4,$v1,0x100
    bnez	$t4,L_8007C7AC
    lh	$t0,224($s2)
    addu	$t5,$zero,$zero
    andi	$t4,$v1,0x200
    beqz	$t4,L_8007C758
    lh	$t2,228($s2)
    addi	$t5,$zero,-1
L_8007C758:
    sub	$t4,$t0,$t1
    xor	$t4,$t4,$t5
    bgez	$t4,L_8007C76C
    andi	$t3,$v1,0x1
    addu	$t0,$t1,$zero
L_8007C76C:
    lh	$t1,230($s2)
    beqz	$t3,L_8007C788
    sub	$t4,$t0,$t1
    xor	$t4,$t4,$t5
    bgez	$t4,L_8007C788
    nop
    addu	$t0,$t1,$zero
L_8007C788:
    sub	$t4,$t0,$t2
    xor	$t4,$t4,$t5
    bgez	$t4,L_8007C79C
    nop
    addu	$t0,$t2,$zero
L_8007C79C:
    blez	$t0,L_EXT_8007C2D8
    sra	$t0,$t0,0x3
    b	L_8007C7DC
    sll	$t0,$t0,0x2
L_8007C7AC:
    lh	$t2,228($s2)
    andi	$t4,$v1,0x1
    beqz	$t4,L_8007C7C8
    add	$t4,$t2,$t2
    lh	$t3,230($s2)
    nop
    add	$t4,$t3,$t2
L_8007C7C8:
    add	$t4,$t4,$t1
    add	$t4,$t4,$t0
    blez	$t4,L_EXT_8007C2D8
    sra	$t0,$t4,0x5
    sll	$t0,$t0,0x2
L_8007C7DC:
    lw	$t3,240($s2)
    lw	$t1,192($s2)
    sw	$zero,204($s2)
    blez	$t1,L_8007C810
    add	$t2,$t0,$t3
    lw	$t1,220($s2)
    lw	$t2,188($s2)
    sub	$t1,$t1,$t0
    bgtz	$t1,L_8007C80C
    sw	$t0,196($s2)
    sw	$zero,192($s2)
    add	$t2,$t0,$t3
L_8007C80C:
    sw	$s0,200($s2)
L_8007C810:
    jalr	$v0
    add	$t7,$zero,$t2
    lw	$t0,192($s2)
    lw	$t2,200($s2)
    blez	$t0,L_8007C900
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
    bnez	$t5,L_8007C870
    addu	$t3,$t2,$zero
    lbu	$t4,11($t2)
    addi	$t2,$t2,4
L_8007C870:
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
    bltz	$t5,L_8007C900
    lw	$t1,0($t3)
    nop
L_8007C8C0:
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
    bnez	$t1,L_8007C8F4
    addi	$t5,$t5,-1
    addi	$t2,$t2,4
L_8007C8F4:
    lw	$t1,0($t3)
    bgez	$t5,L_8007C8C0
    sw	$zero,8($t2)
L_8007C900:
    lw	$t1,244($s2)
    nop
    sub	$t0,$t1,$s0
    bgez	$t0,L_EXT_8007C2D8
    nop
    j	L_EXT_8007D510
    nop
.end func_8007C68C
