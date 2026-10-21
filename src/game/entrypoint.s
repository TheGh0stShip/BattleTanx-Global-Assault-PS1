/* Hand-written startup recovered as labeled MIPS assembly. */
.set noreorder
.set noat
.text
.globl entrypoint
.ent entrypoint
entrypoint:
    lui	$a0,0x8001
    addiu	$a0,$a0,16476
    addu	$sp,$a0,$zero
    addu	$s8,$a0,$zero
    lui	$gp,0x800c
    addiu	$gp,$gp,24692
    lui	$a0,0x800b
    addiu	$a0,$a0,27616
    lui	$a0,0x1f80
    lui	$a1,0x1f80
    ori	$a1,$a1,0x400
    lui	$a2,0x5555
    ori	$a2,$a2,0x5555
    jal	func_800861B8
    nop
    lui	$a0,0x8001
    addiu	$a0,$a0,116
    lui	$a1,0x8001
    addiu	$a1,$a1,16500
    lui	$a2,0x5555
    ori	$a2,$a2,0x5555
    jal	func_800861B8
    nop
    lui	$a0,0x800c
    addiu	$a0,$a0,24740
    lui	$a1,0x800f
    addiu	$a1,$a1,-348
    addiu	$a2,$zero,0
    jal	func_800861B8
    nop
    lui	$a0,0x800f
    addiu	$a0,$a0,-348
    lui	$a1,0x8020
    lui	$a2,0x5555
    ori	$a2,$a2,0x5555
    jal	func_800861B8
    nop
    lui	$a0,0x8008
    addiu	$a0,$a0,24720
    lui	$a1,0x1fc0
    ori	$a1,$a1,0x129
    jal	func_800861DC
    nop
    addu	$t0,$v0,$zero
    lui	$a0,0x8008
    addiu	$a0,$a0,24730
    lui	$a1,0x1fc0
    ori	$a1,$a1,0x12c
    jal	func_800861DC
    nop
    or	$t0,$t0,$v0
    lui	$a0,0x8008
    addiu	$a0,$a0,24740
    lui	$a1,0x1fc0
    ori	$a1,$a1,0x12c
    jal	func_800861DC
    nop
    or	$t0,$t0,$v0
    lui	$a0,0x8008
    addiu	$a0,$a0,24664
    sw	$t0,0($a0)
    jal	func_80014454
    nop
    break	0x0,0x1
.end entrypoint
