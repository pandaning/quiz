#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#define max(x,y) x>y ? x:y

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

int maxSubArray(int A[],int n)
{
    int i;
    int curMax[n];
    int sumMax=A[0];
    curMax[0]=A[0];
    for(i=1; i<n-1; i++) {
        curMax[i]=max(curMax[i-1]+A[i],A[i]);
        sumMax=max(sumMax,curMax[i]);
    }
    return sumMax;
}
int main()
{
    FILE *file = fopen("q4_iterative.txt", "a");
    double cpu_time1;
    struct timespec start, end;

    int arr[10]= {-2,1,-3,4,-1,2,1,-5,4};
    int arr1[4]= {-2,-5,-3};
    int arr2[2]= {-2};

    clock_gettime(CLOCK_REALTIME, &start);
    assert(maxSubArray(arr,10)==6);
    clock_gettime(CLOCK_REALTIME, &end);

    assert(maxSubArray(arr1,4)==-2);
    assert(maxSubArray(arr2,2)==-2);
    cpu_time1 = diff_in_second(start, end);
    printf("execution time: %lf sec\n", cpu_time1);
    fprintf(file, "%f\n", cpu_time1);
    return 0;
}