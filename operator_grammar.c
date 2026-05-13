#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

void push(char ch)
{
    stack[++top] = ch;
}

int reduce()
{
    // Reduce i -> E
    if(stack[top] == 'i')
    {
        stack[top] = 'E';
        printf("Reduced: i -> E\n");
        return 1;
    }

    // Reduce E+E -> E
    if(top >= 2 &&
       stack[top] == 'E' &&
       stack[top-1] == '+' &&
       stack[top-2] == 'E')
    {
        top = top - 2;
        stack[top] = 'E';

        printf("Reduced: E+E -> E\n");
        return 1;
    }

    // Reduce E*E -> E
    if(top >= 2 &&
       stack[top] == 'E' &&
       stack[top-1] == '*' &&
       stack[top-2] == 'E')
    {
        top = top - 2;
        stack[top] = 'E';

        printf("Reduced: E*E -> E\n");
        return 1;
    }

    return 0;
}

int main()
{
    char input[100];
    int i;

    printf("Enter input string: ");
    scanf("%s", input);

    strcat(input, "$");

    push('$');

    printf("\nParsing Process:\n");

    for(i = 0; input[i] != '$'; i++)
    {
        push(input[i]);

        printf("Shifted: %c\n", input[i]);

        while(reduce());
    }

    // Final reductions
    while(reduce());

    // Acceptance check
    if(top == 1 &&
       stack[0] == '$' &&
       stack[1] == 'E')
    {
        printf("\nString can be parsed\n");
    }
    else
    {
        printf("\nString cannot be parsed\n");
    }

    return 0;
}