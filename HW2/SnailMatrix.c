#include<stdio.h>

#define rows 15
#define cols 15

void createSnail(int *arr[rows][cols], int size) {
	int i, j, k, a = 0, count = 0;

	for (i = 0; i<size; i++)
	{
		for (j = 0; j<size; j++)
		{
			arr[i][j] = 0;
		}
	}

	for (k = 1; k<size; k++, a++)
	{
		for (i = a, j = a; j<size - k; j++)
		{
			arr[i][j] = ++count;
		}
		for (i = a, j = size - k; i<size - k; i++)
		{
			arr[i][j] = ++count;
		}
		for (i = size - k, j = size - k; j >= a; j--)
		{
			arr[i][j] = ++count;
		}
		for (i = size - (k + 1), j = a; i >= k; i--)
		{
			arr[i][j] = ++count;
		}
	} 
}

void printMatrix(int arr[rows][cols], int size) {
	int i, j;

	for (i = 0; i<size; i++)
	{
		for (j = 0; j<size; j++)
		{
			printf("%10d", arr[i][j]);
			if (j == size - 1)
			{
				printf("\n\n");
			}
		}
	}
}

main()
{
	int arr[rows][cols];
	int i, j, k, size, count = 0, a = 0, b = 1;
	printf("Enter the size of Snail Matrix (size < 16) :");
	scanf("%d", &size);
	if (size > 15 || size < 1)  //limiting the size of matrix
	{
		printf("Size of matrix should be a natural number equal to or less than 15\n");
		return;
	}
	
	createSnail(arr, size);
	printMatrix(arr, size);
}
