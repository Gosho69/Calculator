#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "main.h"

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

int is_integer(const char *token)
{
    if (*token == '-' || *token == '+')
        token++;
    if (!*token)
        return 0;

    while (*token)
    {
        if (!isdigit(*token))
            return 0;
        token++;
    }
    return 1;
}

int tokenize_input(char tokens[][32], int *token_count)
{
    char input[MAX_INPUT];
    printf("Enter postfix equation\n> ");

    if (!fgets(input, sizeof(input), stdin))
    {
        fprintf(stderr, "There was an error with the input\n");
        return 0;
    }

    input[strcspn(input, "\n")] = 0;

    char *token = strtok(input, " \t");
    *token_count = 0;

    while (token != NULL)
    {
        if (*token_count >= MAX_TOKENS)
        {
            fprintf(stderr, "Too many tokens\n");
            return 0;
        }

        if (!is_integer(token) && !is_valid_operation(token))
        {
            fprintf(stderr, "Invalid token: '%s'\n", token);
            return 0;
        }

        strcpy(tokens[(*token_count)++], token);
        token = strtok(NULL, " \t");
    }

    if (*token_count == 0)
    {
        fprintf(stderr, "The equation is empty\n");
        return 0;
    }

    return 1;
}

double add(double a, double b)
{
    return a + b;
}

double subtract(double a, double b)
{
    return a - b;
}

double multiply(double a, double b)
{
    return a * b;
}

double divide(double a, double b)
{
    if (b == 0)
    {
        printf("Error. Can't divide by zero!");
        return 0;
    }
    return a / b;
}

double pi()
{
    return MY_PI;
}

double e()
{
    return MY_E;
}

double ln(double a)
{
    if (a <= 0)
    {
        printf("Error: ln(x), x must be > 0.\n");
        return 0;
    }
    return log(a);
}

double log_base(double a, double base)
{
    if (a <= 0 || base <= 0 || base == 1)
    {
        printf("Error: log_b(a), a > 0, base > 0 , base != 1.\n");
        return 0;
    }
    return log(a) / log(base);
}