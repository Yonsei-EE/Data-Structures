#define CHUNK 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h> //malloc
#include <ctype.h>  //isdigit
#include <math.h>
#include "stack.h"

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

short parenthesisMatch(char *equation)
{
    int i = 0;
    short error = 0, open = 0;

    while (equation[i] != '\0' && error != 1)
    {
        if (open <= 0)
        {
            if (equation[i] == ')')
            {
                open--;
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

    return open;
}

int isOperator(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else if (c == '!')
        return 4;
    else if (c == '(')
        return -1;
    return 0;
}

void infixToPostfix(char *infix, char *postfix)
{
    int rank;
    char val[12], c[3];
    Stack S;

    S = CreateStack();

    while (infix[0] != '\0')
    {
        rank = isOperator(infix[0]);
        if (isdigit(infix[0]))
        {
            sprintf(val, "%d ", (int)strtol(infix, &infix, 10));
            strcat(postfix, val);
        }
        else if (infix[0] == '(')
        {
            Push(infix[0], S);
            infix++;
        }
        else if (infix[0] == ')')
        {
            while (Top(S) != '(')
            {
                c[0] = Top(S);
                c[1] = ' ';
                c[2] = 0;
                strcat(postfix, c);
                Pop(S);
                infix++;
            }
            Pop(S);
        }
        else if (rank)
        {
            if (rank == 3)
                rank++;

            while (!IsEmpty(S))
            {
                if (isOperator(Top(S)) < rank)
                {
                    Push(infix[0], S);
                    break;
                }
                else
                {
                    c[0] = Top(S);
                    c[1] = ' ';
                    c[2] = 0;
                    strcat(postfix, c);

                    Pop(S);
                }
            }

            if (IsEmpty(S))
            {
                Push(infix[0], S);
            }

            infix++;
        }
        else
            infix++;
    }

    while (!IsEmpty(S))
    {
        c[0] = Top(S);
        c[1] = ' ';
        c[2] = 0;
        strcat(postfix, c);
        Pop(S);
    }

    MakeEmpty(S);
    DisposeStack(S);
}

int evaluate(char *postfix)
{
    int *tmp, ans, i = 0;
    char val[12];

    tmp = (int *)malloc(sizeof(int) * strlen(postfix));

    while (postfix[0] != '\0')
    {
        if (isdigit(postfix[0]))
        {
            tmp[i] = (int)strtol(postfix, &postfix, 10);
            i++;
        }
        else if (isOperator(postfix[0]))
        {
            switch (postfix[0])
            {
            case '+':
                tmp[i - 2] = tmp[i - 2] + tmp[i - 1];
                i--;
                break;

            case '-':
                tmp[i - 2] = tmp[i - 2] - tmp[i - 1];
                i--;
                break;
            case '*':
                tmp[i - 2] = tmp[i - 2] * tmp[i - 1];
                i--;
                break;
            case '/':
                tmp[i - 2] = tmp[i - 2] / tmp[i - 1];
                i--;
                break;
            case '^':
                tmp[i - 2] = (int)pow(tmp[i - 2], tmp[i - 1]);
                i--;
                break;
            case '!':
                tmp[i - 1] = -tmp[i - 1];
                break;
            }
            postfix++;
        }
        else
            postfix++;
    }

    ans = tmp[0];
    free(tmp);

    return ans;
}

int main()
{
    char *infix, *postfix;
    short match;
    
    infix = getln();
    postfix = (char *)malloc(sizeof(char) * (strlen(infix) + 1) * 4);

    match = parenthesisMatch(infix);
    if (match != 0)
        printf("Not Matched\n");
    else
        printf("Matched\n");

    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    printf("Ans: %d\n", evaluate(postfix));

    free(infix);
    free(postfix);

    return 0;
}