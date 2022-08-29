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
    char Value[16];
} Token;

void dump_token(Token token);