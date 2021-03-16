#include <bits/stdc++.h>

using namespace std;

struct pii
{
    int x, y;
};

int n, idx;
pii cur, arr[100000], ans[100000];

void go(int ss, int se)
{
    int mid = (ss + se) / 2;
    pii *left = new pii[mid - ss + 1], *right = new pii[se - mid];

    for(int i = 0, j = ss; j <= mid; ++i, ++j)
        left[i] = arr[j];

    for(int i = 0, j = mid + 1; j <= se; ++i, ++j)
        right[i] = arr[j];

    int l = 0, r = 0, idx = ss;

    while(l < mid - ss + 1 && r < se - mid)
    {
        if(left[l].x > right[r].x)
            arr[idx++] = right[r++];
        else if(left[l].x == right[r].x && left[l].y > right[r].y)
            arr[idx++] = right[r++];
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

void mergeSort(int ss, int se)
{
    if(ss == se)
        return;

    int mid = (ss + se) / 2;

    mergeSort(ss, mid), mergeSort(mid + 1, se);

    go(ss, se);
}

int main()
{
    cin >> n;

    for(int i = 0; i < n; ++i)
        cin >> arr[i].x >> arr[i].y;

    mergeSort(0, n - 1);

    cout << endl;

    for(int i = 0; i < n; ++i)
        cout << arr[i].x << " " << arr[i].y << endl;

    cout << endl;

    cur = arr[0];

    for(int i = 1; i < n; ++i)
    {
        if(arr[i].x >= cur.y)
            ans[idx++] = cur, cur = arr[i];
        else if(arr[i].y < cur.y)
            cur = arr[i];
    }

    ans[idx++] = cur;

    cout << idx << endl;

    for(int i = 0; i < idx; ++i)
        cout << ans[i].x << " " << ans[i].y << endl;

    return 0;
}
