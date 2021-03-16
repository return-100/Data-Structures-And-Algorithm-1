#include <bits/stdc++.h>

using namespace std;

#define i64 long long
#define endl "\n"
#define maxn 100005
#define mod 1000000007

int *arr, length = 0, idx = 0;

void increaseSize()
{
    if(!length)
        length = 1;

    int *temp = new int[length];
    for(int i = 0; i < idx; ++i)
        temp[i] = arr[i];
    delete arr;
    arr = new int[length * 2];
    for(int i = 0; i < idx; ++i)
        arr[i] = temp[i];
    delete temp;
    length *= 2;
}

void insertItem(int value)
{
    if(length == idx)
    {
        increaseSize();
        arr[idx++] = value;
    }
    else
        arr[idx++] = value;
}

void deleteItem()
{
    int value = arr[idx - 1];
    --idx, arr[idx] = 0;
}

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);*/

    int i = 0;
    bool isBalanced = true;
    string str;

    cin >> str;

    while(str[i])
     {
        if(str[i] == '(' || str[i] == '{' || str[i] == '[')
        {
            insertItem(str[i]);
        }
        else if(idx == 0)
        {
            isBalanced = false;
            break;
        }
        else if((arr[idx - 1] == '(' && str[i] == ')') || (arr[idx - 1] == '{' && str[i] == '}') ||
                (arr[idx - 1] == '[' && str[i] == ']'))
        {
            deleteItem();
        }
        else
        {
            isBalanced = false;
            break;
        }
        ++i;
    }

    if(!idx && isBalanced)
        cout << "Balanced" << endl;
    else
        cout << "Not Balanced" << endl;

    return 0;
}
