#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "main.h"

int main()
{
    char tokens[MAX_TOKENS][32] = {0};
    int token_count = 0;
    while (1)
    {
        if (!tokenize_input(tokens, &token_count))
        {
            printf("Try again or enter 'exit' to quit\n");
            continue;
        }
        // Излизане от калкулатора
        if (token_count == 1 && strcmp(tokens[0], "exit") == 0)
        {
            printf("Exiting calculator...\n");
            break;
        }

        if (!validate_equation(tokens, &token_count))
        {
            break;
        }
        double result = evaluate_calc(tokens, token_count);
        printf("Result: %f\n\n", result);
    }

    return 0;
}