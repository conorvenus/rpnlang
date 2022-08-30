#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "token.h"
#include "char.h"

void lex(FILE *file);

void eval(Token tokens[], size_t size);