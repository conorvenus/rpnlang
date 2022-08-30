#include "lexer.h"

#define EXEC_INSTRUCTION(op)      \
    int a = stack[stack_index--]; \
    int b = stack[stack_index];   \
    stack[stack_index] = b op a;

#define CHECK_ARGS(expected, op)                                                             \
    if (stack_index + 1 < expected)                                                          \
    {                                                                                        \
        printf("Received %d args for " #op ", expected %d args", stack_index + 1, expected); \
        return;                                                                              \
    }

const size_t STACK_CAPACITY = 64;

void dump_token(Token token)
{
    printf("Type: %d\nValue: %s\n", token.Type, token.Value);
}

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

int consume_char(FILE *file)
{
    return fgetc(file);
}

Token consume_number(FILE *file, char initial_char)
{
    size_t number_capacity = 1;
    size_t number_index = 0;
    char *number = malloc(number_capacity * sizeof(char));
    *number = initial_char;
    char character;
    while ((character = consume_char(file)) && character != EOF && isdigit(character))
    {
        if (number_index == number_capacity - 1)
        {
            number_capacity *= 2;
            number = realloc(number, number_capacity * sizeof(char));
        }
        number[++number_index] = character;
    }
    number[++number_index] = '\0';
    if (character != EOF)
        fseek(file, -1, SEEK_CUR);
    return (Token){Integer, number};
}

void lex(FILE *file)
{
    size_t tokens_index = 0;
    size_t tokens_capacity = 1;
    Token *tokens = malloc(tokens_capacity * sizeof(Token));

    char character;
    while ((character = consume_char(file)) && character != EOF)
    {
        if (tokens_index == tokens_capacity)
        {
            tokens_capacity *= 2;
            tokens = realloc(tokens, tokens_capacity * sizeof(Token));
        }
        switch (map_char(character))
        {
        case Letter:
            break;
        case Digit:
            tokens[tokens_index++] = consume_number(file, character);
            break;
        case Special:
            switch (character)
            {
            case '+':
                tokens[tokens_index++] = (Token){Plus, "+"};
                break;
            case '-':
                tokens[tokens_index++] = (Token){Minus, "-"};
                break;
            case '*':
                tokens[tokens_index++] = (Token){Multiply, "*"};
                break;
            case '/':
                tokens[tokens_index++] = (Token){Divide, "/"};
                break;
            }
            break;
        }
    }
    eval(tokens, tokens_index);
}

void eval(Token *tokens, size_t size)
{
    int stack[STACK_CAPACITY];
    size_t stack_index = -1;

    for (size_t i = 0; i < size; i++)
    {
        Token token = tokens[i];
        switch (token.Type)
        {
        case Integer:
            if (stack_index == STACK_CAPACITY - 1)
            {
                printf("ERROR: STACK_OVERFLOW (STACK_CAPACITY: %d)", STACK_CAPACITY);
                return;
            }
            stack[++stack_index] = atoi(token.Value);
            break;
        case Plus:
        {
            CHECK_ARGS(2, +);
            EXEC_INSTRUCTION(+);
            break;
        }
        case Minus:
        {
            CHECK_ARGS(2, -);
            EXEC_INSTRUCTION(-);
            break;
        }
        case Multiply:
        {
            CHECK_ARGS(2, *);
            EXEC_INSTRUCTION(*);
            break;
        }
        case Divide:
        {
            CHECK_ARGS(2, /);
            EXEC_INSTRUCTION(/);
            break;
        }
        }
    }
    printf("%d", stack[stack_index]);
}