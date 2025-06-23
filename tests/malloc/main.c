#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../utils.h"

static inline int getRandom(int min, int max) {
   return min + rand() % (max - min + 1);
}

typedef struct {
   int minChunk;
   int maxChunk;
   int allocCount;
} Args;

void mallocTask(void *void_args) {
   Args *args = (Args*)void_args;
   int minChunk = args->minChunk;
   int maxChunk = args->maxChunk;
   int allocCount = args->allocCount;

   while (allocCount--) {
      volatile void *chunk = malloc(getRandom(minChunk, maxChunk));
      if (chunk) {
         *((volatile char *)chunk) = 0;
         free((void *)chunk);
      }
   }

}

int main() {
   srand(time(NULL));
   Args args[] = {
           {1, 2, 100000000},
           {10, 20, 100000000},
           {10000, 10500, 100000000},
           {100000, 100500, 100000000},
           {10000000, 10000500, 100000000},

   };

   for(int i = 0; i < sizeof(args) / sizeof(Args); ++i) {
      double multithreadTime = measureExecutionTime(mallocTask, &args[i]);
      printf("%-25s%d\n", "Min Chunk:", args[i].minChunk);
      printf("%-25s%d\n", "Max Chunk:", args[i].maxChunk);
      printf("%-25s%d\n", "Iterations:", args[i].allocCount);
      printf("%-25s%.6f seconds\n", "Execution time:", multithreadTime);
      printf("================================================\n");
   }
   return 0;
}
