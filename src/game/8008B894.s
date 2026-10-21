/* Hand-written PlayStation routine recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl func_8008B894
.ent func_8008B894
func_8008B894:
    lui	$at,0x800b
    sw	$ra,22700($at)
    jal	func_80098C30
    nop
    lui	$ra,0x800b
    lw	$ra,22700($ra)
    nop
    mfc0	$v0,$12
    lui	$v1,0x4000
    or	$v0,$v0,$v1
    mtc0	$v0,$12
    nop
    addiu	$t0,$zero,341
    ctc2	$t0,$29
    nop
    addiu	$t0,$zero,256
    ctc2	$t0,$30
    nop
    addiu	$t0,$zero,1000
    ctc2	$t0,$26
    nop
    addiu	$t0,$zero,-4194
    ctc2	$t0,$27
    nop
    lui	$t0,0x140
    ctc2	$t0,$28
    nop
    ctc2	$zero,$24
    ctc2	$zero,$25
    nop
    jr	$ra
    nop
.end func_8008B894
