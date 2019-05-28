/* Per thread arena example. */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>

void* threadFunc(void* arg) {
        // 8192 kB: higher address (8MB: stack overflow)
        // 7fce477e8000-7fce47fe8000 rw-p 00000000 00:00 0                          [stack:13367]
        printf("Before malloc in thread 1\n");
        getchar();

        char* addr = (char*) malloc(1000);
        printf("After malloc and before free in thread 1\n");
        getchar();

        free(addr);
        printf("After free in thread 1\n");
        getchar();
}

int main() {
        pthread_t t1;
        void* s;
        int ret;
        char* addr;

        printf("Welcome to per thread arena example::%d\n",getpid());
        printf("Before malloc in main thread\n");
        getchar();

        // 132 kB: Since this arena is created by main thread its called main arena.
        // 02332000-02353000 rw-p 00000000 00:00 0                                  [heap]
        addr = (char*) malloc(1000);
        printf("After malloc and before free in main thread\n");
        getchar();

        // Allocated memory region (of size 1000 bytes) is released only to ‘glibc malloc’ library, which adds this freed block to main arenas bin(referred as bins)
        // instead of getting released to the operating system immediately.
        // 02332000-02353000 rw-p 00000000 00:00 0                                  [heap]
        free(addr);
        printf("After free in main thread\n");
        getchar();
        ret = pthread_create(&t1, NULL, threadFunc, NULL);
        if(ret)
        {
                printf("Thread creation error\n");
                return -1;
        }
        ret = pthread_join(t1, &s);
        if(ret)
        {
                printf("Thread join error\n");
                return -1;
        }
        return 0;
}
