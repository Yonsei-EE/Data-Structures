#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int IsEmpty(Stack S)
{
    return S->Next == NULL;
}

Stack CreateStack()
{
    Stack S;

    S = malloc(sizeof(struct Node));
    if(S == NULL)
    printf("Out of space!");
    MakeEmpty(S);

    return S;
}

void DisposeStack(Stack S)
{
    if(S != NULL)
        free(S);
}

void MakeEmpty(Stack S)
{
    if(S == NULL)
        printf("Must use CreateStack first");
    else
    {
        while(!IsEmpty(S))
            Pop(S);
    }
}

void Push(ElementType X, Stack S)
{
    PtrToNode TmpCell;
    
    TmpCell = malloc(sizeof(struct Node));
    if(TmpCell == NULL)
        printf("Out of space!");
    else
    {
        TmpCell->Element = X;
        TmpCell->Next = S->Next;
        S->Next = TmpCell;
    }
}

ElementType Top(Stack S)
{
    if(!IsEmpty(S))
        return S->Next->Element;
    else
        printf("Empty Stack");

    return 0;
}

void Pop(Stack S)
{
    PtrToNode FirstCell;

    if(IsEmpty(S))
        printf("Empty Stack");
    else
    {
        FirstCell = S->Next;
        S->Next = S->Next->Next;
        free(FirstCell);
    }
}