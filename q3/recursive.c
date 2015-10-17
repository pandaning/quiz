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

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *head, *ptr;
void init()
{
    head=malloc(sizeof(struct TreeNode));
    ptr=head;
    ptr->right=NULL;
    ptr->left=NULL;
}
void preorder(struct TreeNode *root)
{
    if(root==NULL) return ;
    ptr->val=root->val;
    ptr->right=malloc(sizeof(struct TreeNode));
    ptr->left=NULL;
    ptr=ptr->right;
    preorder(root->left);
    preorder(root->right);
}
void flatten(struct TreeNode* root)
{
    if(root==NULL) return ;
    init();
    preorder(root);
    ptr=head;
    while(ptr->right->right) {
        ptr=ptr->right;
    }
    ptr->right=NULL;
    root->right=head->right;
    root->left=NULL;
}
void CreateNode(struct TreeNode *tmp,char *route,int num)
{
    int i=0;
    for(; i<strlen(route); i++) {
        if(route[i]=='L') {
            if(tmp->left==NULL) {
                tmp->left=malloc(sizeof(struct TreeNode));
                tmp=tmp->left;
                tmp->right=NULL;
                tmp->left=NULL;
            } else {
                tmp=tmp->left;
            }
        } else if(route[i]=='R') {
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
int main()
{
    FILE *file = fopen("q3_recursive.txt", "a");
    double cpu_time1;
    struct timespec start, end;
    struct TreeNode *a;
    a = malloc(sizeof(struct TreeNode));
    a->right=NULL;
    a->left=NULL;
    CreateNode(a,"",5);
    CreateNode(a,"L",2);
    CreateNode(a,"LL",3);
    CreateNode(a,"LR",6);
    CreateNode(a,"R",1);
    CreateNode(a,"RR",4);
    clock_gettime(CLOCK_REALTIME, &start);
    flatten(a);
    clock_gettime(CLOCK_REALTIME, &end);
    output_node(a);
    printf("execution time: %lf sec\n", cpu_time1);
    fprintf(file, "%f\n", cpu_time1);
    return 0;
}
/*
  *              5
  *             / \
  *            2   1
  *           / \   \
  *          3   6   4
  */
