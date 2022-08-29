#include <stdio.h>
#include <string.h>

#include "lexer.h"

void print_usage(char *file_path)
{
    char *file_path_segment;
    char *prev_file_path_segment = strtok(file_path, "/\\");
    while (prev_file_path_segment != NULL)
    {
        file_path_segment = prev_file_path_segment;
        prev_file_path_segment = strtok(NULL, "/\\");
    }
    printf("Usage: %s [FILE_PATH]", file_path_segment);
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        print_usage(argv[0]);
        return 0;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Error! Failed to read \"%s\"", argv[1]);
        return 0;
    }
    lex(file);
    return 0;
}