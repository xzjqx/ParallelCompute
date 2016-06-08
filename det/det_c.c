#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

int matrixSize, num, thr;
double matrix[15][15];
double result[1000], sum;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

double calDet(double **matrix, int size) {
        if (size == 1)
                return matrix[0][0];

        int subk;
        double result = 0.0;
        double **submatrix = (double **)malloc(sizeof(double *) * (size - 1));
        for (int i = 0; i < size - 1; i++)
                submatrix[i] = (double *)malloc(sizeof(double) * (size - 1));

        for (int i = 0; i < size; i++) {
                for (int j = 1; j < size; j++) {
                        for (int k = 0; k < size; k++) {
                                if (k < i) subk = k;
                                else if (k > i) subk = k - 1;
                                else continue;
                                submatrix[j-1][subk] = matrix[j][k];
                        }
                }
                if (i % 2 == 0)
                        result += matrix[0][i] * calDet(submatrix, size - 1);
                else
                        result -= matrix[0][i] * calDet(submatrix, size - 1);
        }
        for (int i = 0; i < size - 1; i++)
                free(submatrix[i]);
        free(submatrix);
        return result;
}

void *thread(void *data) {
        int n = (long)data;
        int subk;
        double **submatrix = (double **)malloc(sizeof(double *) * (matrixSize - 1));
        for (int i = 0; i < matrixSize - 1; i++)
                submatrix[i] = (double *)malloc(sizeof(double) * (matrixSize - 1));

        for (int i = n*num; i < (n+1)*num; i++) {
                for (int j = 1; j < matrixSize; j++) {
                        for (int k = 0; k < matrixSize; k++) {
                                if (k < i) subk = k;
                                else if (k > i) subk = k - 1;
                                else continue;
                                submatrix[j-1][subk] = matrix[j][k];
                        }
                }
                if (i % 2 == 0)
                        result[n] += matrix[0][i] * calDet(submatrix, matrixSize - 1);
                else
                        result[n] -= matrix[0][i] * calDet(submatrix, matrixSize - 1);
        }
        if(matrixSize-(n+1)*num > 0 && n == thr-1) {
                for (int i = (n+1)*num; i < matrixSize; i++) {
                        for (int j = 1; j < matrixSize; j++) {
                                for (int k = 0; k < matrixSize; k++) {
                                        if (k < i) subk = k;
                                        else if (k > i) subk = k - 1;
                                        else continue;
                                        submatrix[j-1][subk] = matrix[j][k];
                                }
                        }
                        if (i % 2 == 0)
                                result[n] += matrix[0][i] * calDet(submatrix, matrixSize - 1);
                        else
                                result[n] -= matrix[0][i] * calDet(submatrix, matrixSize - 1);
                }
        }

        pthread_mutex_lock(&mutex);
        sum += result[n];
        pthread_mutex_unlock(&mutex);
        for (int i = 0; i < matrixSize - 1; i++)
                free(submatrix[i]);
        free(submatrix);
        pthread_exit(0);
}

int main(int argc, char *argv[])
{
        struct timeval start,end;
        matrixSize = atoi(argv[1]);
        char *input = argv[2];
        thr = atoi(argv[3]);
        num = matrixSize / thr;
        /*double **matrix = (double **)malloc(sizeof(double *) * matrixSize);
           for (int i = 0; i < matrixSize; i++) {
                matrix[i] = (double *)malloc(sizeof(double) *  matrixSize);
           }*/

        freopen(input, "r", stdin);
        for (int i = 0; i < matrixSize; i++) {
                for (int j = 0; j < matrixSize; j++) {
                        scanf("%lf", &matrix[i][j]);
                }
        }

        pthread_t array[thr];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
        sum = 0;
        //printf("%lf\n", calDet(matrix, matrixSize));
        gettimeofday(&start, NULL);
        for(long i = 0; i < thr; i++) {
                pthread_create(&array[i], &attr, thread, (void *)i);
        }
        for(int i = 0; i < thr; i++) {
                pthread_join(array[i], NULL);
        }
        gettimeofday(&end,NULL);
        printf("%.3lf\n", sum);
        double duration = 1000000*(end.tv_sec - start.tv_sec )+end.tv_usec - start.tv_usec;
        duration /= 1000000;
        printf("It takes %.3fs to get answer.\n",duration);

        return 0;
}
