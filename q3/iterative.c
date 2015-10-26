#include <stdio.h>
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

struct TreeNode 
{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

void freeNode(struct TreeNode *ptr)
{
    if(ptr -> left)
    {
        freeNode(ptr -> left);
    }
    if(ptr -> right)
    {
        freeNode(ptr -> right);
    }
    free(ptr);
}
void flatten(struct TreeNode* root)
{
    if(root==NULL) return ;
    struct TreeNode *ptr, *tmp;
    while(root) 
    {
        tmp=root->right;
        root->right=root->left;
        root->left=NULL;

        ptr=root;
        while(ptr->right)
            ptr=ptr->right;
        ptr->right=tmp;
        root=root->right;
    }
}
void CreateNode(struct TreeNode *tmp,char *route,int num)
{
    int i=0;
    for(; i<strlen(route); i++) 
    {
        if(route[i]=='L') {
            if(tmp->left==NULL) {
                tmp->left=malloc(sizeof(struct TreeNode));
                tmp=tmp->left;
                tmp->right=NULL;
                tmp->left=NULL;
            } else {
                tmp=tmp->left;
            }
        } 
        else if(route[i]=='R') {
            if(tmp->right==NULL) {
                tmp->right=malloc(sizeof(struct TreeNode));
                tmp=tmp->right;
                tmp->right=NULL;
                tmp->left=NULL;
            } else {
                tmp=tmp->right;
            }
        }
    }
    tmp->val=num;
}
void output_node(struct TreeNode* tmp)
{
    if(tmp==NULL)return;
    else printf("%d\n",tmp->val);
    while(tmp->right) { //printf all
        tmp=tmp->right;
        printf("%d\n",tmp->val);
    }
}
void BuildRandomTree(struct TreeNode *root,int nodeNum)
{
    srand(time(0));
    char branch[][2]={"L","R"};
    char store[nodeNum][nodeNum];
    int mark[nodeNum][2];
    int Num[nodeNum];
    memset(store,0,sizeof(store));
    memset(mark,0,sizeof(mark));
    memset(Num,0,sizeof(Num));
    Num[0] = 1;
    int curNum = 1;
    for(curNum;curNum < nodeNum ;curNum++)
    {
        int num;
        do
        {
            num=rand()%nodeNum;
        }while(Num[num]);
       Num[num]=1;
        int LR=rand()%2;
        int randNode;
        do
        {
            randNode=rand()%curNum;
        }while(mark[randNode][LR]);
        mark[randNode][LR]=1;
        char newNode[nodeNum];
        memset(newNode,0,sizeof(newNode));
        strcpy(newNode,store[randNode]);
        strcat(newNode,branch[LR]);
        CreateNode(root,newNode,num);
        strcpy(store[curNum],newNode);
    }
}
int main()
{
    FILE *file = fopen("q3_iterative.txt", "a");
    double cpu_time1;
    struct timespec start, end;
    struct TreeNode *a;
    a = malloc(sizeof(struct TreeNode));
    a->right=NULL;
    a->left=NULL;
    CreateNode(a,"",0);
    int nodeNum = 10;
    BuildRandomTree(a,nodeNum);
    clock_gettime(CLOCK_REALTIME, &start);
    flatten(a);
    clock_gettime(CLOCK_REALTIME, &end);
    cpu_time1 = diff_in_second(start, end);
    freeNode(a);
    printf("execution time: %lf sec\n", cpu_time1);
    fprintf(file, "%f\n", cpu_time1);
    return 0;
}