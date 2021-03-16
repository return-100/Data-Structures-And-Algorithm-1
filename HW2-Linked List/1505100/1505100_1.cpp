#include<stdio.h>
#include<stdlib.h>

#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

struct listNode
{
    int item;
    struct listNode * next;
};

struct listNode * list;

void initializeList()
{
    list = 0;  //initially set to NULL
}

int insertItem(int item) //insert at the beginning of the linked list
{
    struct listNode * newNode ;
    newNode = (struct listNode*) malloc (sizeof(struct listNode)) ;
    newNode->item = item ;
    newNode->next = list ; //point to previous first node
    list = newNode ; //set list to point to newnode as this is now the first node
    return SUCCESS_VALUE ;
}

int deleteItem(int item)
{
    struct listNode *temp, *prev ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) break ;
        prev = temp;
        temp = temp->next ; //move to next node
    }
    if (temp == 0) return NULL_VALUE ; //item not found to delete
    if (temp == list) //delete the first node
    {
        list = list->next ;
        free(temp) ;
    }
    else
    {
        prev->next = temp->next ;
        free(temp);
    }
    return SUCCESS_VALUE ;
}


struct listNode * searchItem(int item)
{
    struct listNode * temp ;
    temp = list ; //start at the beginning
    while (temp != 0)
    {
        if (temp->item == item) return temp ;
        temp = temp->next ; //move to next node
    }
    return 0 ; //0 means invalid pointer in C, also called NULL value in C
}

void printList()
{
    struct listNode * temp;
    temp = list;
    while(temp!=0)
    {
        printf("%d->", temp->item);
        temp = temp->next;
    }
    printf("\n");
}

int insertLast(int item)
{
    struct listNode * newNode, * temp;
    newNode = (struct listNode*) malloc (sizeof(struct listNode));
    newNode->item = item;
    newNode->next = NULL;

    if(list == NULL)
    {
        list = newNode;
    }
    else
    {
        temp = list;
        while(temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }

    return SUCCESS_VALUE;
}

int insertBefore(int oldItem, int newItem)
{
    struct listNode * temp, * prev = NULL, * newNode;
    newNode = (struct listNode*) malloc(sizeof(struct listNode));
    newNode->item = newItem;
    temp = list;

    if(list == NULL)
    {
        insertItem(newItem);
        free(newNode);
        return SUCCESS_VALUE;
    }

    while(temp != 0)
    {
        if(temp->item == oldItem)
            break;
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL)
    {
        insertItem(newItem);
        free(newNode);
        return SUCCESS_VALUE;
    }

    if(prev == NULL)
        list = newNode;
    else
        prev->next = newNode;

    newNode->next = temp;
    return SUCCESS_VALUE;
}

int deleteAfter(int item)
{
    if(list == NULL)
        return NULL_VALUE;

    struct listNode * temp, * var;
    temp = list;

    while(temp != 0)
    {
        if(temp->item == item)
            break;

        temp = temp->next;
    }

    if(temp == NULL)
        return NULL_VALUE;

    var = temp->next;

    if(var != NULL)
    {
        temp->next = temp->next->next;
        free(var);
    }
    else
    {
        return NULL_VALUE;
    }

    return SUCCESS_VALUE;
}

int deleteLast()
{
    if(list == NULL)
        return NULL_VALUE;

    struct listNode * temp, * prev = NULL;
    temp = list;

    while(temp->next != NULL)
    {
        prev = temp;
        temp = temp->next;
    }

    if(prev != NULL)
        prev->next = NULL;

    if(temp == list)
        list = 0;
    else
        free(temp);

    return SUCCESS_VALUE;
}

int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert item last. 5. Insert item before. 6. Delete element after. \n");
        printf("7. Delete last element. 8. Print. 9. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch == 1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch == 2)
        {
            int item;
            scanf("%d", &item);
            deleteItem(item);
        }
        else if(ch == 3)
        {
            int item;
            scanf("%d", &item);
            struct listNode * res = searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch == 4)
        {
            int item;
            scanf("%d", &item);
            insertLast(item);
        }
        else if(ch == 5)
        {
            int oldItem, newItem;
            scanf("%d %d", &oldItem, &newItem);
            insertBefore(oldItem, newItem);
        }
        else if(ch == 6)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch == 7)
        {
            deleteLast();
        }
        else if(ch == 8)
        {
            printList();
        }
        else if(ch == 9)
        {
            break;
        }
    }
}
