#include <bits/stdc++.h>

using namespace std;

int ans;

void go(int *arr, int ss, int se)
{
    int mid = (ss + se) / 2;
    int *left = new int[mid - ss + 1], *right = new int[se - mid];

    for(int i = 0, j = ss; j <= mid; ++i, ++j)
        left[i] = arr[j];

    for(int i = 0, j = mid + 1; j <= se; ++i, ++j)
        right[i] = arr[j];

    int l = 0, r = 0, idx = ss;

    while(l < mid - ss + 1 && r < se - mid)
    {
        if(left[l] > right[r])
            arr[idx++] = right[r++], ans += (mid - ss + 1 - l);
        else
            arr[idx++] = left[l++];
    }

    while(l < mid - ss + 1)
        arr[idx++] = left[l++];

    while(r < se - mid)
        arr[idx++] = right[r++];

    delete left;
    delete right;
}

void mergeSort(int *arr, int ss, int se)
{
    if(ss == se)
        return;

    int mid = (ss + se) / 2;

    mergeSort(arr, ss, mid), mergeSort(arr, mid + 1, se);

    go(arr, ss, se);
}

int main()
{
    while(1)
    {
        int *arr, sz;
        cin >> sz, ans = 0;
        arr = new int[sz];
        for(int i = 0; i < sz; ++i)
            cin >> arr[i];
        mergeSort(arr, 0, sz - 1);
        cout << "Total Inversions : " << ans << endl;
        delete arr;
    }
    return 0;
}
