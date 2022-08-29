#include "lexer.h"

#define EXEC_INSTRUCTION(op)      \
    int a = stack[stack_index--]; \
    int b = stack[stack_index];   \
    stack[stack_index] = b op a;

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
    char number[16] = {initial_char};
    unsigned char number_index = 0;
    char character;
    while ((character = consume_char(file)) && character != EOF && isdigit(character))
    {
        number[++number_index] = character;
    }
    if (character != EOF)
        fseek(file, -1, SEEK_CUR);
    Token token = {Integer};
    strcpy(token.Value, number);
    return token;
}

void lex(FILE *file)
{
    size_t tokens_index = 0;
    Token tokens[100]; // TODO: malloc

    char character;
    while ((character = consume_char(file)) && character != EOF)
    {
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

int check_args(size_t stack_index, size_t expected)
{
    if (stack_index < expected - 1)
    {
        printf("Received %d args for +, expected %d args", stack_index + 1, expected);
        return 0;
    }
    return 1;
}

void eval(Token tokens[], size_t size)
{
    int stack[STACK_CAPACITY];
    size_t stack_index = -1;

    for (size_t i = 0; i < size; i++)
    {
        Token token = tokens[i];
        switch (token.Type)
        {
        case Integer:
            stack[++stack_index] = atoi(token.Value);
            break;
        case Plus:
        {
            if (!check_args(stack_index, 2))
                return;
            EXEC_INSTRUCTION(+);
            break;
        }
        case Minus:
        {
            if (!check_args(stack_index, 2))
                return;
            EXEC_INSTRUCTION(-);
            break;
        }
        case Multiply:
        {
            if (!check_args(stack_index, 2))
                return;
            EXEC_INSTRUCTION(*);
            break;
        }
        case Divide:
        {
            if (!check_args(stack_index, 2))
                return;
            EXEC_INSTRUCTION(/);
            break;
        }
        }
    }
    printf("%d", stack[stack_index]);
}