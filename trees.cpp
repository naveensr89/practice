/* ---------------------------------------------------------------------------
** This software is in the public domain, furnished "as is", without technical
** support, and with no warranty, express or implied, as to its usefulness for
** any purpose.
**
** trees.cpp
** Implemented frequently asked interview questions on trees (Reference: geeksforgeeks.org)
**
** Author: Naveen SR
** @author Naveen SR
** -------------------------------------------------------------------------*/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

struct bt{
    struct bt * left;
    struct bt * right;
    int val;
};


struct bt* createBt(int a)
{
    struct bt* node = new bt;
    node->val = a;
    node->left = NULL;
    node->right = NULL;
    return node;
}

/*http://www.geeksforgeeks.org/lowest-common-ancestor-binary-tree-set-1/*/
int LCA(struct bt *root, int v1, int v2)
{
    if(root == NULL)
        return 0;

    if(root->val == v1 || root->val == v2)
        return root->val;

    int findL = LCA(root->left, v1,v2);

    int findR = LCA(root->right, v1,v2);

    if(findL && findR)
        return root->val;

    return (findL != 0 ? findL : findR);
}

int countNodes(struct bt* root) {
  if(root==NULL)
    return 0;
  int nodes = 0;
  nodes=1;
  nodes+= countNodes(root->left);
  nodes+= countNodes(root->right);
  return nodes;
}

/*http://www.geeksforgeeks.org/618/*/
void printInOrder(struct bt *root)
{
    if(root == NULL)
        return;
    printInOrder(root->left);
    printf("%d ",root->val);
    printInOrder(root->right);
}

/* http://www.geeksforgeeks.org/write-a-c-program-to-calculate-size-of-a-tree/ */
int size(struct bt* root)
{
    if(root == NULL)
        return 0;
    return size(root->left)+sizeof(root->val)+size(root->right);
}

struct bt* copy(struct bt* t1)
{
    if(t1==NULL)
    {
        return NULL;
    }
    struct bt *t2 = createBt(t1->val);
    t2->left = copy(t1->left);
    t2->right = copy(t1->right);
    return t2;
}

/*http://www.geeksforgeeks.org/write-c-code-to-determine-if-two-trees-are-identical/*/
int isIdentical(struct bt* t1, struct bt* t2)
{
    if(t1 == NULL && t2 == NULL)
        return 1;
    if((t1== NULL && t2 != NULL )|| (t2== NULL && t1 != NULL ))
        return 0;
    return isIdentical(t1->left,t2->left) && (t1->val == t2->val) && isIdentical(t1->right,t2->right);
}

#define MAX(a,b) ((a)>(b) ? (a): (b))

/*http://www.geeksforgeeks.org/write-a-c-program-to-find-the-maximum-depth-or-height-of-a-tree/*/
int maxDepth(struct bt* t1, int curDepth)
{
    if(t1==NULL)
        return curDepth;
    return MAX(maxDepth(t1->left,curDepth+1),maxDepth(t1->right,curDepth+1));
}

/*http://www.geeksforgeeks.org/write-a-c-program-to-delete-a-tree/*/
int deleteBt(struct bt *t)
{
    if(t == NULL)
        return 0;
    deleteBt(t->left);
    deleteBt(t->right);
    delete t;
    return 1;
}

/*http://www.geeksforgeeks.org/write-an-efficient-c-function-to-convert-a-tree-into-its-mirror-tree/*/
int mirrorTree(struct bt *t)
{
    if(t == NULL)
        return 0;
    mirrorTree(t->left);
    mirrorTree(t->right);

    struct bt *temp = t->left;
    t->left = t->right;
    t->right = temp;
    return 1;
}

int nodes[100];

void printArr(int *arr, int l)
{
    for(int i=0; i<l; i++)
        cout<< arr[i] << " ";
    printf("\n");
}

/*http://www.geeksforgeeks.org/given-a-binary-tree-print-out-all-of-its-root-to-leaf-paths-one-per-line/*/
void printRootToLeaf(struct bt * t, int l)
{
    if(t == NULL)
        return;
    nodes[l] = t->val;

    // If leaf print
    if(t->left == NULL && t->right == NULL)
    {
        printArr(nodes,l+1);
        return;
    }

    printRootToLeaf(t->left, l+1);
    printRootToLeaf(t->right, l+1);
}

int memMap[100][100] = {0};

void buildLevelOrder(struct bt* t, int l)
{
    if(t== NULL)
        return;
    int v = memMap[l][0];
    memMap[l][v+1] = t->val;
    memMap[l][0] = v+1;
    buildLevelOrder(t->left,l+1);
    buildLevelOrder(t->right,l+1);
}

/*http://www.geeksforgeeks.org/level-order-tree-traversal/*/
void printLevelOrderTraversal(struct bt* t)
{
    buildLevelOrder(t,0);
    int l=0;
    int v = memMap[l][0];
    while(v != 0)
    {
        for(int i=0; i<v; i++)
            printf("%d ",memMap[l][i+1]);

        printf("\n");
        l++;
        v = memMap[l][0];
    }
}

class queue
{
    private:
    int first,last;
    struct bt* array[500];

    public:
    void q()
    {
        first = 0;
        last = 0;
    }
    void enqueue(struct bt *n)
    {
        array[last] = n;
        last++;
    }
    struct bt* dequeue()
    {
        return array[first++];
    }

};

void printLevelOrderTraversalQueue(struct bt* t)
{
    struct bt* tmp;
    queue q = queue();

    tmp = t;
    if(tmp == NULL)
        return;

    while(tmp != 0)
    {
        printf("%d ", tmp->val);
        if(tmp->left)
            q.enqueue(tmp->left);
        if(tmp->right)
            q.enqueue(tmp->right);
        tmp = q.dequeue();
    }
}


/*http://www.geeksforgeeks.org/write-a-c-program-to-get-count-of-leaf-nodes-in-a-binary-tree/*/
int countLeafNodes(struct bt *t)
{
    if(t == NULL)
        return 0;
    if(t->left == NULL && t->right == NULL)
        return 1;
    return countLeafNodes(t->left) + countLeafNodes(t->right);
}

/*http://www.geeksforgeeks.org/check-for-children-sum-property-in-a-binary-tree/*/
int checkNodeEqualsChildrenSum(struct bt *t)
{
    if(t == NULL)
        return 0;
    if(t->left == NULL && t->right == NULL)
        return 1;
    if(t->left == NULL)
        return t->val == t->right->val;
    else
        return t->val == t->left->val;

    return checkNodeEqualsChildrenSum(t->left) && checkNodeEqualsChildrenSum(t->right) && (t->left->val + t->right->val  == t->val);
}

/* http://www.geeksforgeeks.org/convert-an-arbitrary-binary-tree-to-a-tree-that-holds-children-sum-property/ */
void convertNodeEqualsChildrenSum(struct bt *t)
{
    if(t== NULL)
        return;
    if(t->left == NULL && t->right == NULL)
        return;
    if(t->left == NULL)
    {
        t->val = MAX(t->val, t->right->val);
        t->right->val = MAX(t->val, t->right->val);
        return ;
    }

    if(t->right == NULL)
    {
        t->val = MAX(t->val, t->left->val);
        t->left->val = MAX(t->val, t->left->val);
        return ;
    }

    convertNodeEqualsChildrenSum(t->left);
    convertNodeEqualsChildrenSum(t->right);

    int sum = t->left->val + t->right->val;
    if(sum >= t->val)
        t->val = sum;
    else
    {
        t->left->val += t->val - sum;
        convertNodeEqualsChildrenSum(t->left);
    }
}
/* http://www.geeksforgeeks.org/diameter-of-a-binary-tree/ */
int diameterOfTree(struct bt *t, int *diameter)
{
    if(t == NULL)
        return 0;
    int ld = diameterOfTree(t->left, diameter);
    int rd = diameterOfTree(t->right, diameter);
    int cd = ld + 1 + rd;
    *diameter = MAX(*diameter, cd);

    return MAX(ld,rd)+1;
}

/* http://www.geeksforgeeks.org/how-to-determine-if-a-binary-tree-is-balanced/ */
int isBalancedTree(struct bt *t, int *h)
{
    if(t==NULL)
    {
        *h = 0;
        return 1;
    }
    int lh, rh;
    if(isBalancedTree(t->left,&lh) && isBalancedTree(t->right,&rh) && abs(lh-rh) <= 1)
    {
        *h = MAX(lh,rh)+1;
        return 1;
    }
    else
        return 0;
}

class stack{
private:
    int cur;
    struct bt *array[500];
public:
    stack()
    {
        cur = 0;
    }
    void push(struct bt* n)
    {
        array[cur] = n;
        cur++;
    }
    struct bt* pop()
    {
        if(cur == 0)
            return NULL;
        cur--;
        return array[cur];
    }
};

void addToStack(struct bt*t, stack &s)
{
    while(t != NULL)
    {
        s.push(t);
        t = t->left;
    }
}
/* http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion/ */
void inOrderTraversalLoopStack(struct bt *t)
{
    int done=0;
    stack s;
    struct bt *tmp = t;
    while(done == 0)
    {
        addToStack(tmp,s);
        tmp = s.pop();
        if(tmp == NULL)
            done = 1;
        else
        {
            printf("%d ",tmp->val);
            tmp = tmp->right;
        }
    }
}

/* http://www.geeksforgeeks.org/inorder-tree-traversal-without-recursion-and-without-stack/ */
void printThreadedMorrisTravel(struct bt* t)
{
    struct bt *current = t, *pre;
    while(current != NULL)
    {
        if(current->left == NULL)
        {
            printf("%d ",current->val);
            current = current->right;
        }
        else
        {
            pre = current->left;
            while(pre->right != NULL && pre->right != current)
                pre = pre->right;

            if(pre->right == NULL)
            {
                pre->right = current;
                current = current->left;
            }
            else
            {
                pre->right = NULL;
                printf("%d ",current->val);
                current = current->right;
            }
        }
    }
}
int main()
{
    int diameter = 0;
    struct bt* t1;
    struct bt * t2 = NULL;
    struct bt * t3 = NULL;
    struct bt * t4 = NULL;
    struct bt * t5 = NULL;

    t1 = createBt(1);
    t1->left = createBt(2);
    t1->right = createBt(3);
    t1->left->left = createBt(4);
    t1->left->right = createBt(5);
    t1->right->left = createBt(6);
    t1->right->right = createBt(7);
    t1->left->left->left = createBt(8);
    t1->left->left->right = createBt(9);
    t1->left->right->left = createBt(10);
    t1->left->right->right = createBt(11);

    t3 = createBt(20);
    t3->left = createBt(20);
    t3->right = createBt(10);
    t3->left->left = createBt(6);
    t3->left->right = createBt(4);
    t3->right->left = createBt(5);
    t3->right->right = createBt(5);
    t3->left->left->left = createBt(2);
    t3->left->left->right = createBt(4);
    t3->left->right->left = createBt(1);
    t3->left->right->right = createBt(3);

    t4 = copy(t1);
    t4->left->left->left->left = createBt(12);
    t4->left->left->left->right = createBt(13);
    t4->left->right->right->left = createBt(14);
    t4->left->right->right->right = createBt(15);

    t5 = copy(t1);
    t5->right->left->left = createBt(12);
    t5->right->left->right = createBt(13);
    t5->right->right->left = createBt(14);
    t5->right->right->right = createBt(15);

    int v1,v2;
    v1 = 8;
    v2 = 11;

    cout << countNodes(t1) << endl;
    cout << LCA(t1,v1,v2);
    cout << "\nprintInorder:";     printInOrder(t1);
    cout << "\nSize " << size(t1);

    t2 = copy(t1);

    cout << "\nprintInorder:" ;  printInOrder(t2);
    cout << "\nisIdentical = " << isIdentical(t1,t2);

    t2->left->right->right->val = 10;

    cout << "\nisIdentical = " << isIdentical(t1,t2);
    cout << "\nmaxDepth = "<<maxDepth(t1,0);
    cout << "\ndeleteBT = "<< deleteBt(t2);
    cout << "\nmirrorTree = "<< mirrorTree(t1);
    cout << "\nprintInorder:" ;   printInOrder(t1);
    cout << "\nprintRootToLeaf:\n" ; printRootToLeaf(t1,0);
    cout << "\nlevelOrderTraversal:\n" ; printLevelOrderTraversal(t1);
    cout << "\nlevelOrderTraversalQueue:\n" ;printLevelOrderTraversalQueue(t1);
    cout << "\ncountLeafNodes: "<< countLeafNodes(t1);
    cout << "\ncheckNodeEqualsChildrenSum: t1:" << checkNodeEqualsChildrenSum(t1);
    cout << "\ncheckNodeEqualsChildrenSum: t3:" << checkNodeEqualsChildrenSum(t3);
    cout << "\nprintInorder: t1:" ;  printInOrder(t1);
    cout << "\nconvertNodeEqualsChildrenSum: t1:"; convertNodeEqualsChildrenSum(t1);
    cout << "\nprintInorder: t1:" ;  printInOrder(t1);
    t1->val = 60;
    cout << "\nprintInorder: t1:" ;  printInOrder(t1);
    cout << "\nconvertNodeEqualsChildrenSum: t1:"; convertNodeEqualsChildrenSum(t1);
    cout << "\nprintInorder: t1:" ;  printInOrder(t1);
    diameter = 0;
    diameterOfTree(t1,&diameter);
    cout << "\ndiameterOfTree: t1:" << diameter;
    diameter = 0;
    diameterOfTree(t4,&diameter);
    cout << "\ndiameterOfTree: t4:" << diameter;
    int height;
    cout << "\nisBalancedTree: t1:" << isBalancedTree(t1,&height);
    cout << "\nisBalancedTree: t4:" << isBalancedTree(t4,&height);
    cout << "\nisBalancedTree: t5:" << isBalancedTree(t5,&height);
    cout << "\ninOrderTraversalLoop: t1:"; inOrderTraversalLoopStack(t1);
    cout << "\nprintThreadedMorrisTravel: t1:"; printThreadedMorrisTravel(t1);
    cout << endl << endl << endl;
    return 0;
}
