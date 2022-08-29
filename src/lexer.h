#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"

typedef enum CharType
{
    Digit,
    Letter,
    Special
} CharType;

CharType map_char(char character);

int consume_char(FILE *file);

void lex(FILE *file);

void eval(Token tokens[], size_t size);