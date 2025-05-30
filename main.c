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

    int has_decimal = 0;

    while (*token)
    {
        if (*token == '.' && !has_decimal)
        {
            has_decimal = 1;
        }
        else if (!isdigit(*token))
        {
            return 0;
        }
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

    if (strcmp(input, "exit") == 0)
    {
        strcpy(tokens[0], "exit");
        *token_count = 1;
        return 1;
    }

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

struct Stack *createStack(int cap)
{
    struct Stack *stack = (struct Stack *)malloc(sizeof(struct Stack));
    stack->cap = cap;
    stack->top = -1;
    stack->arr = (double *)malloc(cap * sizeof(double));
    return stack;
}

void deleteStack(struct Stack *stack)
{
    free(stack->arr);
    free(stack);
}

int isFull(struct Stack *stack)
{
    return stack->top >= stack->cap - 1;
}

int isEmpty(struct Stack *stack)
{
    return stack->top < 0;
}

int push(struct Stack *stack, double x)
{
    if (isFull(stack))
    {
        printf("Stack Overflow\n");
        return 0;
    }
    stack->arr[++stack->top] = x;
    return 1;
}

double pop(struct Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack Underflow\n");
        return 0;
    }
    return stack->arr[stack->top--];
}

double evaluate_calc(char tokens[][32], int token_count)
{
    struct Stack *stack = createStack(MAX_TOKENS);
    double result = 0;

    for (int i = 0; i < token_count; i++)
    {
        char *token = tokens[i];

        if (!is_valid_operation(token))
        {
            double num = atof(token);
            push(stack, num);
        }
        else
        {
            if (strcmp(token, "+") == 0)
            {
                if (stack->top < 1)
                {
                    printf("Error: Not enough operands for addition\n");
                    deleteStack(stack);
                    return 0;
                }
                double b = stack->arr[stack->top--];
                double a = stack->arr[stack->top--];
                push(stack, add(a, b));
            }
            else if (strcmp(token, "-") == 0)
            {
                if (stack->top < 1)
                {
                    printf("Error: Not enough operands for subtraction\n");
                    deleteStack(stack);
                    return 0;
                }
                double b = stack->arr[stack->top--];
                double a = stack->arr[stack->top--];
                push(stack, subtract(a, b));
            }
            else if (strcmp(token, "*") == 0)
            {
                if (stack->top < 1)
                {
                    printf("Error: Not enough operands for multiplication\n");
                    deleteStack(stack);
                    return 0;
                }
                double b = stack->arr[stack->top--];
                double a = stack->arr[stack->top--];
                push(stack, multiply(a, b));
            }
            else if (strcmp(token, "/") == 0)
            {
                if (stack->top < 1)
                {
                    printf("Error: Not enough operands for division\n");
                    deleteStack(stack);
                    return 0;
                }
                double b = stack->arr[stack->top--];
                double a = stack->arr[stack->top--];
                push(stack, divide(a, b));
            }
            else if (strcmp(token, "ln") == 0)
            {
                if (stack->top < 0)
                {
                    printf("Error: Not enough operands for ln\n");
                    deleteStack(stack);
                    return 0;
                }
                double a = stack->arr[stack->top--];
                push(stack, ln(a));
            }
            else if (strcmp(token, "log") == 0)
            {
                if (stack->top < 1)
                {
                    printf("Error: Not enough operands for log\n");
                    deleteStack(stack);
                    return 0;
                }
                double base = stack->arr[stack->top--];
                double a = stack->arr[stack->top--];
                push(stack, log_base(a, base));
            }
            else if (strcmp(token, "pi") == 0)
            {
                push(stack, pi());
            }
            else if (strcmp(token, "e") == 0)
            {
                push(stack, e());
            }
        }
    }
    if (stack->top == 0)
    {
        result = stack->arr[stack->top];
    }
    else
    {
        printf("Error: Invalid expression (too many operands left on stack)\n");
    }

    deleteStack(stack);
    return result;
}