#include<stdio.h>
#include<stdlib.h>

#define FALSE_VALUE 0
#define TRUE_VALUE 1

struct treeNode
{
    int item;
    struct treeNode * left; //points to left child
    struct treeNode * right; //points to right child
};

struct treeNode * root;

void initializeTree()
{
    root = 0;
}

struct treeNode * searchItem(struct treeNode * node, int item)
{
    if(node==0) return 0;
    if(node->item==item) return node; //found, return node
    struct treeNode * t = 0;
    if(item < node->item)
        t = searchItem(node->left, item); //search in the left sub-tree
    else
        t = searchItem(node->right, item); //search in the right sub-tree
    return t;
};

struct treeNode * makeTreeNode(int item)
{
    struct treeNode * node ;
    node = (struct treeNode *)malloc(sizeof(struct treeNode));
    node->item = item;
    node->left = 0;
    node->right = 0;
    return node;
};

struct treeNode * insertItem(struct treeNode * node, int item)
{
    if(node==0) //insert as the root as the tree is empty
    {
        struct treeNode * newNode = makeTreeNode(item);
        root = newNode;
        return newNode;
    }

    if(node->item==item) return 0; //already an item exists, so return NULL

    if(item<node->item && node->left==0) //insert as the left child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->left = newNode;
        return newNode;
    }

    if(item>node->item && node->right==0) //insert as the right child
    {
        struct treeNode * newNode = makeTreeNode(item);
        node->right = newNode;
        return newNode;
    }

    if(item<node->item)
        return insertItem(node->left, item); //insert at left sub-tree
    else
        return insertItem(node->right, item); //insert at right sub-tree
}

int calcNodeHeight(struct treeNode * node) //return height of a node
{
    if(node==0) return -1;
    int l, r;
    l = calcNodeHeight(node->left);
    r = calcNodeHeight(node->right);
    if(l>r) return l+1;
    else return r+1;
}

int calcHeight(int item) //return height of an item in the tree
{
    struct treeNode * node = 0;
    node = searchItem(root, item);
    if(node==0) return -1; //not found
    else return calcNodeHeight(node);
}

int getSize(struct treeNode * node)
{
    if(node == 0) return 0;
    return 1 + getSize(node->left) + getSize(node->right);
}

int calcNodeDepth(struct treeNode * node) //return depth of a node
{
    int depth = 0;
    struct treeNode * temp = root;
    while(temp->item != node->item)
    {
        (node->item > temp->item) ? (temp = temp->right) : (temp = temp->left);
        ++depth;
    }
    return depth;
}

int calcDepth(int item) //return depth of an item in the tree
{
    struct treeNode * temp = searchItem(root, item);
    if(temp == 0) return -1;
    return calcNodeDepth(temp);
}

struct treeNode * searchParent(int item)
{
    struct treeNode * pre = NULL, * temp = root;
    while(temp->item != item)
    {
        pre = temp;
        (item > temp->item) ? (temp = temp->right) : (temp = temp->left);
    }
    return pre;
};

int deleteItem(struct treeNode * node, int item)
{
    if(node == NULL)
        return FALSE_VALUE;
    else if(item > node->item)
        return deleteItem(node->right, item);
    else if(item < node->item)
        return deleteItem(node->left, item);
    else
    {
        struct treeNode * parent = searchParent(item);
        /*if(node->left == NULL && node->right == NULL)
            free(node), node = NULL;*/
        if(node->left == NULL)
        {
            if(parent == NULL)
                root = root->right;
            else if(node->item > parent->item)
                parent->right = node->right, free(node);
            else
                parent->left = node->right, free(node);
        }
        else if(root->right == NULL)
        {
            if(parent == NULL)
                root = root->left;
            else if(node->item > parent->item)
                parent->right = node->left, free(node);
            else
                parent->left = node->left, free(node);
        }
        else
        {
            int var;
            struct treeNode * temp = node->right;
            while(temp->left != 0)
                temp = temp->left;
            var = temp->item;
            deleteItem(node->right, var);
            node->item = var;
        }
        return TRUE_VALUE;
    }
}

int getMinItem() //returns the minimum item in the tree
{
    if(root == 0) return FALSE_VALUE;
    int ret = 0;
    struct treeNode * temp = root;
    while(temp != 0)
        ret = temp->item, temp = temp->left;
    return ret;
}

int getMaxItem() //returns the maximum item in the tree
{
    if(root == 0) return FALSE_VALUE;
    int ret = 0;
    struct treeNode * temp = root;
    while(temp != 0)
        ret = temp->item, temp = temp->right;
    return ret;
}

int rangeSearch(struct treeNode * node, int leftBound, int rightBound) //returns number of items in the
{
    if(node == 0) return 0;
    if(leftBound <= node->item && node->item <= rightBound)
        return 1 + rangeSearch(node->left, leftBound, rightBound) + rangeSearch(node->right, leftBound, rightBound);
    else
        return rangeSearch(node->left, leftBound, rightBound) + rangeSearch(node->right, leftBound, rightBound);
}

void printInOrder(struct treeNode * node, int height)
{
    if(node==0) return ;

    //print left sub-tree
    printInOrder(node->left, height-1);

    //print item
    for(int i=0; i<height; i++)printf("   ");
    printf("%03d\n",node->item);

    //print right sub-tree
    printInOrder(node->right, height-1);
}

int main(void)
{
    initializeTree();
    while(1)
    {
        printf("1. Insert item. 2. Delete item. 3. Search item. \n");
        printf("4. Print height of tree. 5. Print height of an item. \n");
        printf("6. PrintInOrder. 7. Size of the tree 8. Depth of an item.\n");
        printf("9. Get Min Item. 10. Get Max Item 11. Range Search 12. Quit.\n");

        printf("\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(root, item);
            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("\n--------------------------------\n");
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            int var = deleteItem(root, item);
            if(var == FALSE_VALUE)
                printf("No Item Found\n");
            else
                printf("Deleted Item %d\n", item);
            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("\n--------------------------------\n");
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            struct treeNode * res = searchItem(root, item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("\n--------------------------------\n");
        }
        else if(ch==4)
        {
            int height = calcNodeHeight(root);
            printf("Height of tree = %d\n", height);
            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("\n--------------------------------\n");
        }
        else if(ch==5)
        {
            int item;
            scanf("%d", &item);
            int height = calcHeight(item);
            printf("Height of %d = %d\n", item, height);
            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("\n--------------------------------\n");
        }
        else if(ch==6)
        {
            int h = calcNodeHeight(root);
            printf("\n--------------------------------\n");
            printInOrder(root, h);
            printf("--------------------------------\n");
        }
        else if(ch == 7)
        {
            int sz = getSize(root);
            printf("Size of the tree is %d\n", sz);
            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("\n--------------------------------\n");
        }
        else if(ch == 8)
        {
            int value, var;
            scanf("%d", &value);
            var = calcDepth(value);
            if(var == -1)
                printf("Item Not Found\n");
            else
                printf("The depth of item %d is %d\n", value, var);
            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("\n--------------------------------\n");
        }
        else if(ch == 9)
        {
            int value = getMinItem();
            if(value == FALSE_VALUE)
                printf("No item inserted yet\n");
            else
                printf("The Min item is %d\n", value);
            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("\n--------------------------------\n");
        }
        else if(ch == 10)
        {
            int value = getMaxItem();
            if(value == FALSE_VALUE)
                printf("No item inserted yet\n");
            else
                printf("The Max item is %d\n", value);
            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("\n--------------------------------\n");
        }
        else  if(ch == 11)
        {
            int left, right;
            scanf("%d %d", &left, &right);
            printf("No of item found between (%d - %d) : %d\n", left, right, rangeSearch(root, left, right));
            printf("\n--------------------------------\n");
            printInOrder(root, calcNodeHeight(root));
            printf("\n--------------------------------\n");
        }
        else if(ch==12)
        {
            break;
        }

        printf("\n");
    }
}
