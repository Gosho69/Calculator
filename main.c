#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *valid_operations[] = {
    "+", "-", "*", "/", "ln", "log", "pi", "e"};
const int num_operations = 8;

int is_valid_operation(const char *token)
{
    for (int i = 0; i < num_operations; i++)
    {
        if (strcmp(token, valid_operations[i]) == 0)
            return 1;
    }
    return 0;
}