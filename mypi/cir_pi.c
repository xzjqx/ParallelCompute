#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

int sum, thr, num, len_per_thread;
double x[100000001], y[100000001];
pthread_mutex_t mutex;

void *thread(void *data) {
        int n = (long)data, thr_id = 0;
        //pthread_mutex_lock(&mutex);
        //for(j = n*len_per_thread; j < (n+1)*len_per_thread; j ++) {
        for(int j = 0; j < len_per_thread; j++) {
                if(x[j]*x[j] + y[j]*y[j] < 1)
                        thr_id++;
                //printf("%f %f\n", x[j], y[j]);
        }
        //printf("%d\n", n);
        num += thr_id;
        //pthread_mutex_unlock(&mutex);
        pthread_exit(0);
}

int main(int argc, char *argv[])
{
        sum = atoi(argv[1]);
        thr = atoi(argv[2]);
        len_per_thread = sum / thr;
        sum = len_per_thread * thr;

        pthread_t array[thr];
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setscope(&attr, PTHREAD_SCOPE_SYSTEM);
        struct timeval start,end;

        int i;
        for(i = 0; i < sum; i++) {
                unsigned int seed = i;
                x[i] = (double)(rand_r(&seed)) / RAND_MAX;
                y[i] = (double)(rand_r(&seed)) / RAND_MAX;
        }

        //pthread_mutex_init(&mutex,NULL);

        gettimeofday(&start, NULL);
        long l;
        for(l = 0; l < thr; l++) {
                pthread_create(&array[l], &attr, thread, (void *)l);
        }
        int m;
        for(m = 0; m < thr; m++) {
                pthread_join(array[m], NULL);
        }
        gettimeofday(&end,NULL);

        printf("Pi is %lf\n", num*4.0/sum);
        double duration = 1000000*(end.tv_sec - start.tv_sec ) + end.tv_usec - start.tv_usec;
        duration /= 1000;
        printf("It takes %.3fms to get answer.\n", duration);
        return 0;
}
