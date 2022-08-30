#include "ctype.h"

typedef enum CharType
{
    Digit,
    Letter,
    Special
} CharType;

CharType map_char(char character);