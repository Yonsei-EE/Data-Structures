#define CHUNK 10

#include "stdio.h"
#include "string.h"
#include "stdlib.h"

char *getln()
{
    char *line = NULL, *tmp = NULL;
    size_t size = 0, index = 0;
    int ch = EOF;

    while (ch)
    {
        ch = getc(stdin);

        /* Check if we need to stop. */
        if (ch == EOF || ch == '\n')
            ch = 0;

        /* Check if we need to expand. */
        if (size <= index)
        {
            size += CHUNK;
            tmp = realloc(line, size);
            if (!tmp)
            {
                free(line);
                line = NULL;
                break;
            }
            line = tmp;
        }

        /* Store in string. */
        line[index++] = ch;
    }

    return line;
}

int main()
{
    char *equation;
    int i = 0;
    short error = 0, open = 0;

    equation = getln();

    while (equation[i] != '\0' && error != 1)
    {
        if (open <= 0)
        {
            if (equation[i] == ')')
            {
                error = 1;
                break;
            }
            else if (equation[i] == '(')
                open += 1;
        }
        else
        {
            if (equation[i] == '(')
                open++;
            else if (equation[i] == ')')
                open--;
        }

        i++;
    }

    if (open != 0)
        printf("Not Matched\n");
    else
        printf("Matched\n");

    return 0;
}