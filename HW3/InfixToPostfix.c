#define CHUNK 10

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // for malloc and relloc
#include <ctype.h>  // for isdigit
#include <math.h>
#include "stack.h"

// prompts for a line of notation and gives a dynamically allocated string
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

// checks whether the parenthesis in a given notation has no errors
short parenthesisMatch(char *notation)
{
    int i = 0;
    short error = 0, open = 0;

    // count and keep track of how many parenthesises are open
    while (notation[i] != '\0' && error != 1)
    {
        if (open <= 0)
        {
            if (notation[i] == ')')
            {
                open--;
                error = 1;
                break;
            }
            else if (notation[i] == '(')
                open += 1;
        }
        else
        {
            if (notation[i] == '(')
                open++;

            else if (notation[i] == ')')
                open--;
        }

        i++;
    }

    // returns number of open parenthesises. Error if non-zero
    return open;
}

// checks if character is an operator and what rank it is. Higher rank means higher precedence.
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

// converts a given infix notation to postfix
void infixToPostfix(char *infix, char *postfix)
{
    int rank;
    char val[12], c[3];
    Stack S;

    S = CreateStack();

    // checks each character of infix by incrementing the pointer position
    while (infix[0] != '\0')
    {
        rank = isOperator(infix[0]);
        // if character is a digit, concatenate it to the postfix notation string
        if (isdigit(infix[0]))
        {
            sprintf(val, "%d ", (int)strtol(infix, &infix, 10));
            strcat(postfix, val);
        }

        // if character is a open parenthesis, push it into the stack
        else if (infix[0] == '(')
        {
            Push(infix[0], S);
            infix++;
        }

        //if character is a closing parenthesis, pop everything on the stack until it reaches the corresponding open parenthesis
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

        // if character is a operator..
        else if (rank)
        {
            if (rank == 3)
                rank++;

            // compare the the precedence of the character with the element on top of the stack
            while (!IsEmpty(S))
            {
                // if the character has a higher precedence than the top of the stack push it into the stack
                if (isOperator(Top(S)) < rank)
                {
                    Push(infix[0], S);
                    break;
                }
                // if not then pop the stack and contatenate it to the postfix notation
                else
                {
                    c[0] = Top(S);
                    c[1] = ' ';
                    c[2] = 0;
                    strcat(postfix, c);
                    Pop(S);
                }
            }// repeat until the stack is not empty

            // if the stack is empty push the operator into the stack
            if (IsEmpty(S))
            {
                Push(infix[0], S);
            }

            infix++;
        }
        else
            infix++;
    }//  repeat until all characters of the infix are scanned

    // after all characters are scanned add any character that the stack may have to the postfix string
    while (!IsEmpty(S))
    {
        c[0] = Top(S);
        c[1] = ' ';
        c[2] = 0;
        strcat(postfix, c);
        Pop(S);
    }

    // dispose of stack
    MakeEmpty(S);
    DisposeStack(S);
}

// evaluates a postfix notation and returns the answer
double evaluate(char *postfix)
{
    double *tmp, ans;
    int i = 0;
    char val[12];

    // we use an integer array instead of the character stack for direct calculation
    // for better intuitive understanding I will use the word 'stack' instead of 'integer array'
    tmp = (double *)malloc(sizeof(double) * strlen(postfix));

    // we scan the postfix notation until all characters are scanned
    while (postfix[0] != '\0')
    {
        // if character is a digit we push it into the stack
        if (isdigit(postfix[0]))
        {
            tmp[i] = (double)strtol(postfix, &postfix, 10);
            i++;
        }
        // if character is an operator, the last two elements of our stack are popped.
        // the two elements are then evaluated and pushed into the stack.
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
                tmp[i - 2] = (double)pow(tmp[i - 2], tmp[i - 1]);
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

    // return answer and dispose stack.
    ans = tmp[0];
    free(tmp);

    return ans;
}

// trim floating point number
void morphNumericString (char *s, int n) {
    char *p;
    int count;

    p = strchr (s,'.');         // Find decimal point, if any.
    if (p != NULL) {
        count = n;              // Maximum decimals allowed.
        while (count >= 0) {    
             count--;
             if (*p == '\0')    // If there's less than desired.
                 break;
             p++;               // Next character.
        }

        *p-- = '\0';            // Truncate string.
        while (*p == '0')       // Remove trailing zeros.
            *p-- = '\0';

        if (*p == '.') {        // If all decimals were zeros, remove ".".
            *p = '\0';
        }
    }
}

int main()
{
    char *infix, *postfix;
    short match;
    char ans[10];

    // gets infix notation
    infix = getln();
    // allocates memory for the postfix notation. For readability we will space the characters with 3 times more space
    postfix = (char *)malloc(sizeof(char) * (strlen(infix) + 1) * 3);

    // execute penthesis matching
    match = parenthesisMatch(infix);
    if (match != 0)
        printf("Not Matched\n");
    else
        printf("Matched\n");

    // convert infix notation to postfix
    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    // evaluate the postfix notation
    sprintf(ans, "%lf", evaluate(postfix));
    morphNumericString(ans, 10);
    printf("Ans: %s\n", ans);

    free(infix);
    free(postfix);

    return 0;
}
