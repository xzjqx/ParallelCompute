#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int sum, num, i;
double *x, *y;


int main(int argc, char *argv[])
{
        sum = atoi(argv[1]);
        struct timeval start,end;

        x = (double *)malloc(sizeof(double) * sum);
        y = (double *)malloc(sizeof(double) * sum);
        int i;
        for(i = 0; i < sum; i++) {
                unsigned int seed = i;
                x[i] = (double)(rand_r(&seed)) / RAND_MAX;
                y[i] = (double)(rand_r(&seed)) / RAND_MAX;
        }

        gettimeofday(&start, NULL);
        for(i = 0; i < sum; i++) {
                double xi = x[i];
                double yi = y[i];
                if(xi*xi + yi*yi <= 1) {
                        num++;
                }
        }

        printf("Pi is %lf\n", num*4.0/sum);
        gettimeofday(&end,NULL);
        double duration = 1000000*(end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
        duration /=1000;
        printf("It takes %.3fms to get answer.\n",duration);
        return 0;
}
