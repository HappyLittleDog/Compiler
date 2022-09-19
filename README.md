# My Compiler Project
## Basic intro.
Compiler project built for the [compiler course @ PKU](https://pku-minic.github.io/online-doc/#/), which can compile SysY (a language which is very similar to C) code into risc-v assembly code.

## Compile the Code
To compile the code, you need to pull the docker image first using the following command:
```
docker pull maxxing/compiler-dev
```
Then type `make` command, the compiler will be built and located at `build/compiler`.

## Usage
The `compiler` needs 4 command line arguments:
```
compiler [mode] [input file] -o [output file]
```
* `mode` is to indicate the generated file. Specifically, risc-v assembly will be generated if `-riscv` flag is passed, koopa IR code will be generated if `-koopa` flag is passed.
* `input file` is the path of the input SysY code.
* `output file` is the desired path of the target code.

## Example
If we have the following SysY code `hello.c`:
```C
// ASCII code w.r.t Hello world!
int str[13]={72, 101, 108, 108, 111, 32, 119, 111, 114, 108, 100, 33, 10};

int main()
{
    int i=0;
    while (i<13)
    {
        putch(str[i]);
        i=i+1;
    }
    return 0;
}
```
If we want the compiler to generate koopa IR code, input the following command in the shell:
```
build/compiler -koopa test/hello.c -o test/hello.koopa
```
Then the following koopa IR code will be generated:
```asm
decl @getint(): i32
decl @getch(): i32
decl @getarray(*i32): i32
decl @putint(i32)
decl @putch(i32)
decl @putarray(i32, *i32)
decl @starttime()
decl @stoptime()

global @VAR_1 = alloc [i32, 13], {72, 101, 108, 108, 111, 32, 119, 111, 114, 108, 100, 33, 10} //! w.r.t symbol str
fun @main(): i32 {
%entry_1:
	@VAR_2 = alloc i32 //! w.r.t. symbol i
	store 0, @VAR_2
	jump %while_exp_2

%while_exp_2:
	%2 = load @VAR_2
	%3 = add 0, 13
	%1 = lt %2, %3
	br %1, %while_loop_3, %while_end_4

%while_loop_3:
	%5 = load @VAR_2
	%6 = getelemptr @VAR_1, %5
	%4 = load %6
	call @putch(%4)
	%8 = load @VAR_2
	%9 = add 0, 1
	%7 = add %8, %9
	store %7, @VAR_2
	jump %while_exp_2

%while_end_4:
	%10 = add 0, 0
	ret %10
}
```
If we want the compiler to generate riscv code, input the following command in the shell:
```
build/compiler -riscv test/hello.c -o test/hello.S
```
Then the following riscv assembly code will be generated:
```asm
.data
        .globl VAR_1
    VAR_1:
        .word 72
        .word 101
        .word 108
        .word 108
        .word 111
        .word 32
        .word 119
        .word 111
        .word 114
        .word 108
        .word 100
        .word 33
        .word 10
    
        .text
        .globl main
    main:
        li t0, 52
        sub sp, sp, t0
        li t0, 48
        add t0, t0, sp
        sw ra, 0(t0)
    entry_1:
        li t0, 40
        add t0, sp, t0
        addi t1, t0, 4
        sw t1, 0(t0)
        li t0, 0
        li t1, 40
        add t1, t1, sp
        lw t1, 0(t1)
        sw t0, 0(t1)
        j while_exp_2
    while_exp_2:
        lw t0, 40(sp)
        lw t0, 0(t0)
        sw t0, 36(sp)
        li t0, 13
        sw t0, 32(sp)
        lw t1, 36(sp)
        lw t2, 32(sp)
        slt t0, t1, t2
        sw t0, 28(sp)
        lw t0, 28(sp)
        bnez t0, while_loop_3
        j while_end_4
    while_loop_3:
        lw t0, 40(sp)
        lw t0, 0(t0)
        sw t0, 24(sp)
        lw t0, 24(sp)
        li t1, 4
        mul t0, t1, t0
        la t1, VAR_1
        add t0, t1, t0
        sw t0, 20(sp)
        lw t0, 20(sp)
        lw t0, 0(t0)
        sw t0, 16(sp)
        lw a0, 16(sp)
        call putch
        lw t0, 40(sp)
        lw t0, 0(t0)
        sw t0, 12(sp)
        li t0, 1
        sw t0, 8(sp)
        lw t1, 12(sp)
        lw t2, 8(sp)
        add t0, t1, t2
        sw t0, 4(sp)
        lw t0, 4(sp)
        li t1, 40
        add t1, t1, sp
        lw t1, 0(t1)
        sw t0, 0(t1)
        j while_exp_2
    while_end_4:
        li t0, 0
        sw t0, 0(sp)
        lw t0, 0(sp)
        mv a0, t0
        li t0, 48
        add t0, t0, sp
        lw ra, 0(t0)
        li t0, 52
        add sp, sp, t0
        ret
```
