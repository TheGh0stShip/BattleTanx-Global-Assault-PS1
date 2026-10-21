/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8007E810
.ent func_8007E810
func_8007E810:
    mtc2	$t0,$0
    mtc2	$t1,$1
    cfc2	$at,$26
    nop
    nop
    c2	0x480012
    sll	$at,$at,0x10
    mfc2	$t0,$27
    mfc2	$t3,$25
    div	$zero,$at,$t0
    mfc2	$t4,$26
    mflo	$at
    nop
    nop
    mult	$at,$t3
    cfc2	$t2,$24
    nop
    srl	$t2,$t2,0x10
    mflo	$t3
    mfhi	$t0
    srl	$t3,$t3,0x10
    sll	$t0,$t0,0x10
    or	$t3,$t3,$t0
    add	$t3,$t3,$t2
    sra	$t0,$t3,0x1f
    xor	$t0,$t3,$t0
    addi	$t0,$t0,-2048
    bgez	$t0,L_8007E8D0
    mult	$at,$t4
    cfc2	$t2,$25
    nop
    srl	$t2,$t2,0x10
    mflo	$t4
    mfhi	$t0
    srl	$t4,$t4,0x10
    sll	$t0,$t0,0x10
    ori	$t4,$t4,0x10
    add	$t4,$t4,$t2
    sra	$t0,$t4,0x1f
    xor	$t0,$t4,$t0
    addi	$t0,$t0,-1024
    bgez	$t0,L_8007E8D0
    sll	$t4,$t4,0x10
    andi	$t3,$t3,0xffff
    or	$t3,$t4,$t3
    addu	$t1,$t0,$zero
    jr	$ra
    addu	$t0,$t3,$zero
L_8007E8D0:
    addu	$t0,$s6,$zero
    jr	$ra
    addu	$t1,$t9,$zero
.end func_8007E810
