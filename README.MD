# rpnlang

A simple stack-based evaluating **'virtual machine'** written in C based on **reverse-polish notation**!

## Initial Plan

_Initially, this project was intended to be a proper **virtual machine** that could execute a bytecode instruction set, which could then be a compilation target for various *'toy'* languages, I decided that considering this is my first C project, that would a bit more challenging than anticipated, however, this is still most definitely the end goal._

## Quickstart

Uses `gcc` to compile the C source code into an executable, generates a `build` directory and copies the resulting executable into said directory.

```console
$ make build
```

Uses the `build` Makefile dependency to first build the executable, and then proceeds to execute the executable with optional arguments through `ARGS=examples/basic.rpn` for example.

```console
$ make run
$ make run ARGS=examples/basic.rpn
```

## Syntax

Push an integer onto the stack by simply writing that integer to a file, perform `+`, `-`, `*`, `/` on the two integers that are on top of the stack, the two integers will be compressed into a single resultant integer on the stack which you can then continue to use operations on.

```c
5 10 + 3 * -> 45
```

## TODO

- Extend the lexer for use in a **proper** virtual machine project so that it can successfully consume symbols, keywords and a wider-range of special characters and operators

## COMPLETED

- Made memory allocation dynamic for a theoretically infinite amount of tokens as input and a reduction in storage usage, allowed token values to be dynamic, allowing for larger integer sizes and future-proofing for string tokens
