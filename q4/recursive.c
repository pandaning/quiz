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

int maxsum(int A[],int x,int y)
{
    int v,L,R,maxs,i;
    if(y-x==1) return A[x];
    int m=x+(y-x)/2;
    maxs=max(maxsum(A,x,m),maxsum(A,m,y));
    v=0;
    L=A[m-1];
    for(i=m-1; i>=x; i--) {
        v+=A[i];
        L=max(L,v);
    }
    v=0;
    R=A[m];
    for(i=m; i<y; i++) {
        v+=A[i];
        R=max(R,v);
    }
    return max(maxs,L+R);
}
int maxSubArray(int A[],int n)
{
    return maxsum(A,0,n);
}

int main()
{
    FILE *file = fopen("q4_recursive.txt", "a");
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
