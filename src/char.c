#include "char.h"

CharType map_char(char character)
{
    if (isalpha(character))
    {
        return Letter;
    }
    else if (isdigit(character))
    {
        return Digit;
    }
    return Special;
}
