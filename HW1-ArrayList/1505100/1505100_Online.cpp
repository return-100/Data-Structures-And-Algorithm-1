#include <iostream>

using namespace std;


char str[100];
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

int deleteItem()
{
    int value = arr[idx - 1];
    --idx, arr[idx] = 0;
    return value;
}

int main()
{
    int i, sz;
    string str;
    cin >> str;
    sz = (int) str.size(), i = sz - 1;

    while(i >= 0)
    {
        int var;

        if(idx < 2)
        {
            var = str[i] - '0';
            insertItem(var);
        }
        else
        {
            if(str[i] == '+')
            {
                var = deleteItem() + deleteItem(), insertItem(var);
            }
            else if(str[i] == '-')
            {
                int num1 = deleteItem();
                int num2 = deleteItem();
                var = num2 - num1, insertItem(var);
            }
            else if(str[i] == '*')
            {
                var = deleteItem() * deleteItem(), insertItem(var);
            }
        }

        --i;
    }

    cout << deleteItem() << endl;

    return 0;
}
