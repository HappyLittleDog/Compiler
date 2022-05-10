	.text
	.globl main
main:
	addi sp, sp, -32
entry_1:
	li t0, 1
	sw t0, 28(sp)
	li t0, 2
	sw t0, 24(sp)
	li t0, 3
	sw t0, 20(sp)
	li t0, 4
	sw t0, 16(sp)
	lw t0, 16(sp)
	sw t0, 12(sp)
	lw t0, 12(sp)
	sw t0, 20(sp)
	lw t0, 20(sp)
	sw t0, 8(sp)
	lw t0, 8(sp)
	sw t0, 24(sp)
	lw t0, 24(sp)
	sw t0, 4(sp)
	lw t0, 4(sp)
	sw t0, 28(sp)
	lw t0, 24(sp)
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	addi sp, sp, 32
	ret
