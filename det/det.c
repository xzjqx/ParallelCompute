#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double calDet(double **matrix, int size) {
	if (size == 1) {
		return matrix[0][0];
	}

	int subk;
	double result = 0.0;
	double **submatrix = (double **)malloc(sizeof(double *) * (size - 1));
	for (int i = 0; i < size - 1; i++) {
		submatrix[i] = (double *)malloc(sizeof(double) * (size - 1));
	}
	for (int i = 0; i < size; i++) {
		for (int j = 1; j < size; j++) {
			for (int k = 0; k < size; k++) {
				if (k < i) subk = k;
				else if (k > i) subk = k - 1;
				else continue;
				submatrix[j-1][subk] = matrix[j][k];
			}
		}
		if (i % 2 == 0) {
			result += matrix[0][i] * calDet(submatrix, size - 1);
		}
		else {
			result -= matrix[0][i] * calDet(submatrix, size - 1);
		}
	}
	for (int i = 0; i < size - 1; i++) {
		free(submatrix[i]);
	}
	free(submatrix);
	return result;
}


int main(int argc, char *argv[]) {
	if (argc < 3) {
		printf("%s MATRIX_SIZE INPUT_FILE\n");
		exit(1);
	}
	struct timeval start,end;
	gettimeofday(&start, NULL);

	int matrixSize = atoi(argv[1]);
	char *input = argv[2];
	double **matrix = (double **)malloc(sizeof(double *) * matrixSize);
	for (int i = 0; i < matrixSize; i++) {
		matrix[i] = (double *)malloc(sizeof(double) *  matrixSize);
	}

	freopen(input, "r", stdin);
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			scanf("%lf", &matrix[i][j]);
		}
	}

	/*printf("%d\n", matrixSize);
	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			printf("%lf ", matrix[i][j]);
		}
		printf ("\n");
	}*/

	printf("%lf\n", calDet(matrix, matrixSize));
    gettimeofday(&end,NULL);
	double duration = 1000000*(end.tv_sec - start.tv_sec )+end.tv_usec - start.tv_usec;
	duration /=1000000;
	printf("It takes %.3fs to get answer.\n",duration);

	return 0;
}
