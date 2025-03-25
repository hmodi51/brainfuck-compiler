# Brainfuck Compiler

A simple **Brainfuck-to-x86-64 assembly** that converts Brainfuck code into lower level assembly code, allowing you to compile it using a C compiler like `gcc`.

## Features

- **Translates Brainfuck to Assembly**

## How to build the compiler
 - First do `gcc bf.c -o bf` This will compile the transpiler.
 - Then run `bf <source code>` for example u can run `./bf examples/tic-tac-toe.bf`
- then you can notice output.s file in the dir
- so again compile it using gcc `gcc -nostdlib -o output output.s`

**I am too lazy too make a Makefile but maybe later.**

### Currently this is a very basic compiler and have plans later to optimize it and make it more robust