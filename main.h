#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX_INPUT 1024
#define MAX_TOKENS 256

#define MY_PI 3.14159265358979323846
#define MY_E 2.71828182845904523536
// тея макрота са MY, за да не стане грещка със вече съществуващи макрота

struct Stack
{
    int top, cap;
    double *arr;
};

void deleteStack(struct Stack *stack);
int isFull(struct Stack *stack);
int isEmpty(struct Stack *stack);
int push(struct Stack *stack, double x);
double pop(struct Stack *stack);

int is_valid_operation(const char *token);
int is_integer(const char *token);
int tokenize_input(char tokens[][32], int *token_count);

double add(double a, double b);
double subtract(double a, double b); // второто се вади от първото
double multiply(double a, double b);
double divide(double a, double b); // първото се дели на второто
double pi(void);
double e(void);
double ln(double a);                    // Натурален логаритъм
double log_base(double a, double base); // Логаритъм при произволна основа
double evaluate_calc(char tokens[][32], int token_count);

#endif
