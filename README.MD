# rpnlang

A simple stack-based evaluating **'virtual machine'** written in C based on **reverse-polish notation**!

## Initial Plan

_Initially, this project was intended to be a proper **virtual machine** that could execute a bytecode instruction set, which could then be a compilation target for various *'toy'* languages, I decided that considering this is my first C project, that would a bit more challenging than anticipated, however, this is still most definitely the end goal._

## Build

```
make
```

## Syntax

Push an integer onto the stack by simply writing that integer to a file, perform `+`, `-`, `*`, `/` on the two integers that are on top of the stack, the two integers will be compressed into a single resultant integer on the stack which you can then continue to use operations on.

```c
5 10 + 3 * -> 45
```

## TODO

- Make memory allocation dynamic as currently `char[16]` is used to represent any given token and the array of tokens is limited to `100`
- Extend the lexer for use in a **proper** virtual machine project so that it can successfully consume symbols, keywords and a wider-range of special characters and operators
