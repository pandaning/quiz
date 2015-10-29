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
    for(i=1; i<n; i++) {
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

    FILE *fp = fopen("test.txt","r");
    char txtEachLine[700];
    char txtAns[100];
    while(fgets(txtEachLine, sizeof(txtEachLine), fp)) {
        txtEachLine[strlen(txtEachLine)-1] = '\0';
        int arr[200];
        int index = 0;
        char *pch = strtok(txtEachLine,",");
        while(pch) {
            arr[index++] = atoi(pch);
            pch = strtok(NULL, ",");
        }
        int ans = 0;
        fgets(txtAns, sizeof(txtAns), fp);
        txtAns[strlen(txtAns)-1] = '\0';
        ans = atoi(txtAns);
        clock_gettime(CLOCK_REALTIME, &start);
        assert(maxSubArray(arr,index) == ans);
        clock_gettime(CLOCK_REALTIME, &end);

        cpu_time1 = diff_in_second(start, end);
        printf("execution time: %lf sec\n", cpu_time1);
        fprintf(file, "%f\n", cpu_time1);
    }
    return 0;
}