#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

static double diff_in_second(struct timespec t1, struct timespec t2)
{
    struct timespec diff;
    if (t2.tv_nsec-t1.tv_nsec < 0) {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec - 1;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec + 1000000000;
    } else {
        diff.tv_sec  = t2.tv_sec - t1.tv_sec;
        diff.tv_nsec = t2.tv_nsec - t1.tv_nsec;
    }
    return (diff.tv_sec + diff.tv_nsec / 1000000000.0);
}

char smallest_character(char str[],char fc)
{
    int n=strlen(str);
    int i;
    for(i=0; i<n; i++) {
        if(str[i]>fc)return str[i];
    }
    return str[0];
}
int main()
{
    FILE *file = fopen("q2_iterative.txt", "a");
    double cpu_time1;
    struct timespec start, end;
    char i;
    char str[]= {'a','d','g','j','m','p','s','v','z'}; //input test
    for(i=97; i<123; i++) { //test from a to z
        printf("Test: [%c]\n",i);
        clock_gettime(CLOCK_REALTIME, &start);
        smallest_character(str,i);
        clock_gettime(CLOCK_REALTIME, &end);
        printf("Output: %c\n",smallest_character(str,i));
        cpu_time1 = diff_in_second(start, end);
        printf("execution time: %lf sec\n", cpu_time1);
        fprintf(file, "%f\n", cpu_time1);
    }
    return 0;
}
