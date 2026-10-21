/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008AE30
.ent func_8008AE30
func_8008AE30:
    addu	$a2,$zero,$zero
    bgez	$a1,L_8008AE44
    addu	$a3,$zero,$zero
    addiu	$a2,$zero,1
    negu	$a1,$a1
L_8008AE44:
    bgez	$a0,L_8008AE54
    nop
    addiu	$a3,$zero,1
    negu	$a0,$a0
L_8008AE54:
    bnez	$a1,L_8008AE68
    slt	$v0,$a0,$a1
    beqz	$a0,L_8008AF9C
    addu	$v0,$zero,$zero
    slt	$v0,$a0,$a1
L_8008AE68:
    beqz	$v0,L_8008AEF8
    lui	$v0,0x7fe0
    and	$v0,$a0,$v0
    beqz	$v0,L_8008AEB0
    sra	$v0,$a1,0xa
    div	$zero,$a0,$v0
    bnez	$v0,L_8008AE8C
    nop
    break	0x7
L_8008AE8C:
    addiu	$at,$zero,-1
    bne	$v0,$at,L_8008AEA4
    lui	$at,0x8000
    bne	$a0,$at,L_8008AEA4
    nop
    break	0x6
L_8008AEA4:
    mflo	$a0
    j	L_8008AEE4
    sll	$v0,$a0,0x1
L_8008AEB0:
    sll	$v0,$a0,0xa
    div	$zero,$v0,$a1
    bnez	$a1,L_8008AEC4
    nop
    break	0x7
L_8008AEC4:
    addiu	$at,$zero,-1
    bne	$a1,$at,L_8008AEDC
    lui	$at,0x8000
    bne	$v0,$at,L_8008AEDC
    nop
    break	0x6
L_8008AEDC:
    mflo	$a0
    sll	$v0,$a0,0x1
L_8008AEE4:
    lui	$v1,0x800b
    addu	$v1,$v1,$v0
    lh	$v1,20620($v1)
    j	L_8008AF80
    nop
L_8008AEF8:
    and	$v0,$a1,$v0
    beqz	$v0,L_8008AF38
    sra	$v0,$a0,0xa
    div	$zero,$a1,$v0
    bnez	$v0,L_8008AF14
    nop
    break	0x7
L_8008AF14:
    addiu	$at,$zero,-1
    bne	$v0,$at,L_8008AF2C
    lui	$at,0x8000
    bne	$a1,$at,L_8008AF2C
    nop
    break	0x6
L_8008AF2C:
    mflo	$a0
    j	L_8008AF6C
    sll	$v0,$a0,0x1
L_8008AF38:
    sll	$v0,$a1,0xa
    div	$zero,$v0,$a0
    bnez	$a0,L_8008AF4C
    nop
    break	0x7
L_8008AF4C:
    addiu	$at,$zero,-1
    bne	$a0,$at,L_8008AF64
    lui	$at,0x8000
    bne	$v0,$at,L_8008AF64
    nop
    break	0x6
L_8008AF64:
    mflo	$a0
    sll	$v0,$a0,0x1
L_8008AF6C:
    lui	$v1,0x800b
    addu	$v1,$v1,$v0
    lh	$v1,20620($v1)
    addiu	$v0,$zero,1024
    subu	$v1,$v0,$v1
L_8008AF80:
    beqz	$a2,L_8008AF8C
    addiu	$v0,$zero,2048
    subu	$v1,$v0,$v1
L_8008AF8C:
    beqz	$a3,L_8008AF9C
    addu	$v0,$v1,$zero
    negu	$v1,$v1
    addu	$v0,$v1,$zero
L_8008AF9C:
    jr	$ra
    nop
.end func_8008AE30
