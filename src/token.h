typedef enum TokenType
{
    Plus,
    Minus,
    Multiply,
    Divide,
    Integer,
    Symbol,
    Keyword
} TokenType;

typedef struct Token
{
    TokenType Type;
    char *Value;
} Token;
