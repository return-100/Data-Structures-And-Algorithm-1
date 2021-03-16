#include <bits/stdc++.h>

using namespace std;

#define i64 long long
#define endl "\n"
#define maxn 100005
#define mod 1000000007

char str[100];
int *arr, length = 0, idx = 0;

void showItem()
{
    for(int i = 0; i < idx; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

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

    showItem();
}

void insertItemAtPos(int value, int pos)
{
    int temp = arr[pos];
    ++idx, arr[pos] = value;

    if(length == idx)
        increaseSize();

    for(int i = pos + 1; i < idx; ++i)
    {
        int var = arr[i];
        arr[i] = temp;
        temp = var;
    }

    showItem();
}

int deleteItem()
{
    int value = arr[idx - 1];
    --idx, arr[idx] = 0;
    if(idx == 0)
        cout << "Empty List" << endl;
    else
        showItem();

    return value;
}

int deleteFirstItem(int value)
{
    bool isFound = false;

    for(int i = 0; i < idx; ++i)
    {
        if(arr[i] == value)
        {
            for(int j = i + 1; j < idx; ++j)
                arr[j - 1] = arr[j];
            --idx, isFound = true;
            break;
        }
    }

    if(isFound)
        showItem();
    else
        cout << "Element not Found" << endl;

    return (isFound ? value : -1);
}

int deleteLastItem(int value)
{
    bool isFound = false;

    for(int i = idx - 1; i >= 0; --i)
    {
        if(arr[i] == value)
        {
            for(int j = i + 1; j < idx; ++j)
                arr[j - 1] = arr[j];
            --idx, isFound = true;
            break;
        }
    }

    if(isFound)
        showItem();
    else
        cout << "Element not Found" << endl;

    return (isFound ? value : -1);
}

void clearList()
{
    delete arr, idx = 0;
    cout << "Clear Completed" << endl;
}

int searchItem(int value)
{
    int pos = -1;

    for(int i = 0; i < idx; ++i)
    {
        if(arr[i] == value)
        {
            pos = i;
            break;
        }
    }

    if(pos != -1)
    {
        cout << "Found At Position " << pos << endl;
        return value;
    }
    else
    {
        cout << "Not Found" << endl;
        return pos;
    }
}

int getValue(int &pos)
{
    int ret = 0;

    while(str[pos] && str[pos] != ' ')
    {
        ret = ret * 10 + (int) (str[pos] - '0');
        ++pos;
    }

    return ret;
}

int main()
{
    /*ios_base::sync_with_stdio(0);
    cin.tie(0);*/

    while(1)
    {
        gets(str);

        if(str[0] == 'T')
        {
            delete arr;
            break;
        }
        else if(str[0] == 'C')
        {
            clearList();
        }
        else if(str[0] == 'I')
        {
            int temp[2], pos = 2;

            if(str[2] == '-')
                ++pos, temp[0] = (-1) * getValue(pos);
            else
                temp[0] = getValue(pos);

            if(str[pos] == NULL)
                insertItem(temp[0]);
            else
            {
                temp[1] = getValue(++pos);
                insertItemAtPos(temp[0], temp[1]);
            }
        }
        else if(str[0] == 'D')
        {
            if(strlen(str) == 1)
                deleteItem();
            else if(str[2] == 'F')
            {
                int var, pos = 4;

                if(str[pos] == '-')
                    ++pos, var = (-1) * getValue(pos);
                else
                    var = getValue(pos);

                deleteFirstItem(var);
            }
            else
            {
                int var, pos = 4;

                if(str[pos] == '-')
                    ++pos, var = (-1) * getValue(pos);
                else
                    var = getValue(pos);

                deleteLastItem(var);
            }
        }
        else
        {
            int var, pos = 2;

            if(str[pos] == '-')
                ++pos, var = (-1) * getValue(pos);
            else
                var = getValue(pos);

            searchItem(var);
        }
    }

    return 0;
}

