#define N 5
int count = 0;
int smallestPathSum = (2 * N - 1) * 100;
int P[(2 * N - 1) * 2];
path(A, i, j, sum) // A: array, (i,j) location
int A[N][N]; // sum: cost sum
int i, j, sum; // n : parameter for indentation
{
	int k; int cost;
	cost = sum + A[i][j]; // adding the cost in the path
	if (i == N - 1 && j == N - 1) { // reached the goal position
		if (smallestPathSum > cost) smallestPathSum = cost;
		P[cost / 50]++;
		count++;
	}
	if (i + 1< N)
		path(A, i + 1, j, cost); // check the path to A[i+1][j], depth n+1
	if (j + 1< N)
		path(A, i, j + 1, cost); // check the path to A[i][j+1], depth n+1
}
main()
{
	int A[N][N] = { 0 };
	int i, j;
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			A[i][j] = rand() % 100;
	path(A, 0, 0, 0); // starting from A[0][0] with the cost 0, depth 0
	printf("smallest path sum : %d\nnumber of paths : %d\n", smallestPathSum, count);
	for (i = 0; i < (2 * N - 1) * 2; i++) {
		if (P[i] != 0) printf("Range %d-%d: %d\n", i * 50, (i + 1) * 50, P[i]);
	}
}