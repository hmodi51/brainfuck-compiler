# Brainfuck Compiler

A simple **Brainfuck-to-C transpiler** that converts Brainfuck code into equivalent C code, allowing you to compile it using a C compiler like `gcc`.

## Features

- **Translates Brainfuck to C**

## How to build the compiler
 - First do `gcc bf.c -o bf` This will compile the transpiler.
 - Then run `bf <source code>`
- then you can notice output.c file in the dir
- so again compile it using gcc `gcc output.c -o output`

**I am too lazy too make a Makefile but maybe later.**

### Currently this is a very basic transpiler but I have plans to actually make it compiler by making it compiled to assembly and also the c code is not perfect as I tried to write it in 30 min.