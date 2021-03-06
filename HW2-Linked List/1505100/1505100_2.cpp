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
struct listNode * tail;

void initializeList()
{
    list = 0;  //initially set to NULL
	tail = 0;
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

//add required codes to insert item at the beginning, remember to properly set the tail pointer!
int insertItem(int newItem)
{
	struct listNode * newNode, * temp;
	newNode = (struct listNode*) malloc(sizeof(struct listNode));
	newNode->item = newItem;

	if(list == NULL)
    {
        newNode->next = NULL;
        list = tail = newNode;
        return SUCCESS_VALUE;
    }

    temp = list;
    list = newNode;
    newNode->next = temp;
    return SUCCESS_VALUE;
}

//add required codes to delete item, remember to properly set the tail pointer!
int deleteAfter(int item)
{
    struct listNode * temp, * cur = NULL;

    temp = list;

    if(list == NULL)
        return NULL_VALUE;

    while(temp != NULL)
    {
        if(temp->item == item)
            break;
        temp = temp->next;
    }

    if(temp == tail)
        return NULL_VALUE;

    cur = temp->next;

    if(cur == tail)
        tail = temp, tail->next = NULL;
    else
        temp->next = cur->next;

    free(cur);
    return SUCCESS_VALUE;
}

int insertLast(int item)
{
    if(list == NULL)
    {
        insertItem(item);
        return SUCCESS_VALUE;
    }

    struct listNode * newNode;
	newNode = (struct listNode*) malloc(sizeof(struct listNode));
    newNode->item = item;
    newNode->next = NULL;
    tail->next = newNode;
    tail = newNode;

    return SUCCESS_VALUE;
}


int main(void)
{
    initializeList();
    while(1)
    {
        printf("1. Insert new item. 2. Delete item. 3. Search item. \n");
        printf("4. Insert last. 5. Print. 6. exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            insertItem(item);
        }
        else if(ch==2)
        {
            int item;
            scanf("%d", &item);
            deleteAfter(item);
        }
        else if(ch==3)
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
        else if(ch==5)
        {
            printList();
        }
        else if(ch==6)
        {
            break;
        }
    }

}
