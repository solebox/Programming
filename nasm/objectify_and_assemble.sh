#!/bin/bash
echo $1
nasm -f elf -ggdb $1.asm
gcc -m32 -o $1 array1.c $1.o asm_io.o 
