#include <stdio.h>
#include "stack.h"

int main()
{
    PtrToCell Parent;
    Parent->Element = '*';
    Parent->Parent = NULL;
    Parent->x = 0;
    Parent->y = 0;

    PtrToCell Child;
    Child->Element = '1';
    Child->Parent = Parent;
    Child->x = 1;
    Child->y = 0;

    Stack S = CreateStack();
    Push(Parent, S);
    Push(Child,S);

    PtrToCell Temp;
    Pop(S);

    return 0;
}