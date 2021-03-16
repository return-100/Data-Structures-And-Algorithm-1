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

    if(idx)
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

void insertItem(int value, int pos)
{
    if(length == idx)
        increaseSize();

    if(pos >= idx)
        arr[idx++] = value;
    else
    {
        int temp = arr[pos];
        ++idx, arr[pos] = value;

        for(int i = pos + 1; i < idx; ++i)
        {
            int var = arr[i];
            arr[i] = temp;
            temp = var;
        }
    }

    showItem();
}

int deleteItem(int value)
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

    if(!idx)
        cout << "Empty List" << endl;

    return (isFound ? value : -1);
}

int findItem(int value)
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
        cout << "not Found" << endl;
        return pos;
    }
}

/*int binSearch(int value)
{
    int low = 0, high = idx, mid, ans = 0;

    while(low <= high)
    {
        mid = (low + high) / 2;

        if(arr[mid] <= value)
            low = mid + 1, ans = mid + 1;
        else if(arr[mid] > value)
            high = mid - 1, ans = mid;
    }

    return ans;
}*/

int binSearch(int value)
{
    int low = 0, high = idx, mid;

    while(low <= high)
    {
        mid = (low + high) / 2;

        if(arr[mid] <= value)
            low = mid + 1;
        else if(arr[mid] > value)
            high = mid - 1;
    }

    return low;
}

int getValue(int &pos)
{
    int ret = 0;

    while(str[pos])
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
        else if(str[0] == 'I')
        {
            int var, pos = 2;

            if(str[2] == '-')
                ++pos, var = (-1) * getValue(pos);
            else
                var = getValue(pos);

            if(idx)
                pos = binSearch(var);
            else
                pos = 0;

            insertItem(var, pos);
        }
        else if(str[0] == 'D')
        {
            int var, pos = 2;

            if(str[pos] == '-')
                ++pos, var = (-1) * getValue(pos);
            else
                var = getValue(pos);

            deleteItem(var);
        }
        else
        {
            int var, pos = 2;

            if(str[pos] == '-')
                ++pos, var = (-1) * getValue(pos);
            else
                var = getValue(pos);

            findItem(var);
        }
    }

    return 0;
}
