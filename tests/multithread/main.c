#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include "../utils.h"


typedef struct {
   int iterations;
} ThreadData;

void *task(void *arg) {
   ThreadData *data = (ThreadData *)arg;
   for (int i = 0; i < data->iterations; ++i) {
      double x = 0;
      for (int j = 0; j < 1000; ++j) {
         x += sin(rand()) * cos(rand());
      }
   }
   return NULL;
}

typedef struct {
   int threadCount;
   int iterationsPerThread;
} Args;

void performThreadedTasks(void *void_args) {
   Args *args = (Args*)void_args;
   int threadCount = args->threadCount;
   int iterationsPerThread = args->iterationsPerThread;

   pthread_t *threads = malloc(threadCount * sizeof(pthread_t));
   ThreadData *threadData = malloc(threadCount * sizeof(ThreadData));

   for (int i = 0; i < threadCount; ++i) {
      threadData[i].iterations = iterationsPerThread;
      pthread_create(&threads[i], NULL, task, &threadData[i]);
   }

   for (int i = 0; i < threadCount; ++i) {
      pthread_join(threads[i], NULL);
   }

   free(threads);
   free(threadData);
}


int main() {
   srand(time(NULL));
   int countThreads[] = {28};

   int iterationsPerThread = 10000;
   for(int i = 0; i < sizeof(countThreads) / sizeof(int); ++i) {
      int threadCount = countThreads[i];
      Args args = {threadCount, 100000};
      double multithreadTime = measureExecutionTime(performThreadedTasks, &args);
      printf("%-25s%d\n", "Threads:", threadCount);
      printf("%-25s%d\n", "Iterations per thread:", iterationsPerThread);
      printf("%-25s%.6f seconds\n", "Execution time:", multithreadTime);
      printf("================================================\n");
   }
   return 0;
}
