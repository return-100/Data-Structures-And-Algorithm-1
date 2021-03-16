#include<bits/stdc++.h>

#define MAX_HEAP_SIZE 100000

using namespace std;

class node
{
public:
    char ch;
    int freq;
    node *left;
    node *right;
};

class heap
{
public:
    node * A;
    int len;

    heap()
    {
        A = new node[MAX_HEAP_SIZE];
        len = 0;
    }

    ~heap()
    {
        if(A)
            delete[] A;

        A = 0;
    }

    void insertItem(int f, char c, node *l, node *r)
    {
        ++len;
        A[len].freq = f;
        A[len].ch = c;
        A[len].right = r;
        A[len].left = l;
        buHeapify(len);
    }

    node* removeMin()
    {
        node *temp = new node;
        temp->freq = A[1].freq;
        temp->ch = A[1].ch;
        temp->left = A[1].left;
        temp->right = A[1].right;
        A[1] = A[len], --len;
        heapify(1);

        return temp;
    }

    void heapify(int i)
    {
        int l, r, smallest;

        while(1)
        {
            l = 2 * i;
            r = 2 * i + 1;
            smallest = i;

            if(l > len && r > len)
                break;
            else if(r > len)
                smallest = l;
            else if(l > len)
                smallest = r;
            else if(A[l].freq < A[r].freq)
                smallest = l;
            else
                smallest = r;

            if(A[i].freq <= A[smallest].freq)
                break;
            else
            {
                node t;
                t = A[i];
                A[i] = A[smallest];
                A[smallest] = t;
                i = smallest;
            }
        }
    }

    void buHeapify(int i)
    {
        node temp;

        while(i > 1)
        {
            if(A[i].freq < A[i / 2].freq)
            {
                temp = A[i];
                A[i] = A[i / 2];
                A[i / 2] = temp;
            }
            else
                break;

            i /= 2;
        }
    }
};

heap pq;
node *head;
int n, var;
char ch, str[100];

void printCode(int idx, node *cur)
{
    if(cur->left == 0 && cur->right == 0)
        cout << cur->ch << " " << str << endl;

    if(cur->left)
    {
        str[idx] = '0';
        printCode(idx + 1, cur->left);
    }

    if(cur->right)
    {
        str[idx] = '1';
        printCode(idx + 1, cur->right);
    }

    str[idx] = '\0';
}

void Hauffman()
{
    cout << endl;

    while(pq.len != 1)
    {
        node *l = pq.removeMin();
        node *r = pq.removeMin();

        pq.insertItem(l->freq + r->freq, '$', l, r);
    }

    head = pq.removeMin();

    if(n == 1)
        cout << head->ch << " " << 0 << endl;
    else
        printCode(0, head);
}

int main()
{
    cin >> n;

    for(int i = 0; i < n; ++i)
    {
        cin >> ch >> var;
        pq.insertItem(var, ch, 0, 0);
    }

    Hauffman();

    return 0;
}

/*
6
a 45
b 13
c 12
d 16
e 9
f 5
*/
