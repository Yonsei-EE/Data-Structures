#include <stdio.h>
#include <stdlib.h>
#include "binheap.h"

int main()
{
	PriorityQueue Q = Initialize(1000);
	PtrToCell temp = malloc(sizeof(struct Cell));

	printf("%d\n", IsEmpty(Q));

	Insert(temp, Q);

	printf("%d\n", IsEmpty(Q));

	temp = GetMin(Q);

	printf("%d\n", IsEmpty(Q));

	return 0;
}
