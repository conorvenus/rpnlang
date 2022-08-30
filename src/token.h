typedef enum TokenType
{
    Plus,
    Minus,
    Multiply,
    Divide,
    Integer
} TokenType;

typedef struct Token
{
    TokenType Type;
    char *Value;
} Token;
