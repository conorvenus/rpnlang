#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"
#include "char.h"

static const char *KEYWORDS[] = {};

void lex(FILE *file);

void eval(Token tokens[], size_t size);

Token consume_number(FILE *file, char character);

Token consume_symbol_keyword(FILE *file, char character);