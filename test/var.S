	.text
	.globl main
main:
	addi sp, sp, -20
	li t0, 10
	sw t0, 16(sp)
	lw t0, 16(sp)
	sw t0, 12(sp)
	li t0, 1
	sw t0, 8(sp)
	lw t1, 12(sp)
	lw t2, 8(sp)
	add t0, t1, t2
	sw t0, 4(sp)
	lw t0, 4(sp)
	sw t0, 16(sp)
	lw t0, 16(sp)
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	addi sp, sp, 20
	ret
