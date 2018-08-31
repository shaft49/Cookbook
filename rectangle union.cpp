#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define CLR(a) memset(a, 0, sizeof(a))
const int N=(int)2e5+5;
struct data{
    int x1, x2, y, val;
    data(){}
    data(int x1, int x2, int y, int val):x1(x1), x2(x2), y(y), val(val){}
}node[N];
int arr[N], lazy[N * 4];
ll sum[N * 4];
bool comp(data a, data b){
    return a.y < b.y;
}
void push(int node, int b, int e){
    if(lazy[node]){
        sum[node] = arr[e] - arr[b - 1];
    }
    else sum[node] = sum[node * 2] + sum[node * 2 + 1];
}
void update(int node, int b, int e, int i, int j, int val){
    if(e < i || b > j) return;
    if(b >= i && e <= j){
        lazy[node] += val;
        push(node, b, e);
        return;
    }
    int L = node * 2, R = L + 1, mid = (b + e) / 2;
    update(L, b, mid, i, j, val);
    update(R, mid + 1, e, i, j, val);
    push(node, b, e);
}
int main(){
    //union of all rectangles(sum of union area)
    int q; scanf("%d", &q);
    int n = 0, m = 0;
    for(int i = 1; i <= q; i++){
        int x1, y1, x2, y2;
        scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
        arr[n++] = x1, arr[n++] = x2;
        node[m++] = data(x1, x2, y1, 1);
        node[m++] = data(x1, x2, y2, -1);
    }
    sort(arr, arr + n);
    n = unique(arr, arr + n) - arr;
    sort(node, node + m, comp);
    ll res = 0;
    CLR(sum); CLR(lazy);
    for(int i = 0; i < m; i++){
        int l = lower_bound(arr, arr + n, node[i].x1) - arr;
        int r = lower_bound(arr, arr + n, node[i].x2) - arr;
        // query range will be (l+1, r), otherwise over count happens
        if(!i) update(1, 0, n - 1, l + 1, r, node[i].val);
        else{
            res += (sum[1] * (ll)(node[i].y - node[i-1].y));
            update(1, 0, n - 1, l + 1, r, node[i].val);
        }
    }
    printf("%lld\n", res);
    return 0;
}
