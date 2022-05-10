	.data
	.globl VAR_1
VAR_1:
	.zero 4

	.text
	.globl main
main:
	addi sp, sp, -16
	sw ra, 12(sp)
entry_1:
	la t0, VAR_1
	lw t0, 0(t0)
	sw t0, 8(sp)
	li t0, 1
	sw t0, 4(sp)
	lw t1, 8(sp)
	lw t2, 4(sp)
	add t0, t1, t2
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	lw ra, 12(sp)
	addi sp, sp, 16
	ret

