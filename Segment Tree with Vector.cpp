int arr[N];
struct info{
    vector<int>v;
}tree[N*4];
info call(info a, info b){
    info temp;
    ///merge two info
    temp.v.resize(a.v.size() + b.v.size());
    merge(ALL(a.v),ALL(b.v),temp.v.begin());
    return temp;
}
void build(int node, int b, int e){
    if(b == e){
        ///Do Something
        tree[node].v.resize(1);
        tree[node].v[0] = arr[b];
        return;
    }
    int mid = (b + e) / 2;
    int Left = node * 2, Right = node * 2 + 1;
    build(Left, b, mid);
    build(Right, mid+1, e);
    tree[node] = call(tree[Left], tree[Right]);
}
int query(int node,int b,int e,int i,int j,int k){
    if(i > e || j < b)return 0;
    if(b >= i && e <= j){
        ///Do something
        int l = upper_bound(ALL(tree[node].v), k) - tree[node].v.begin();
        int tmp = tree[node].v.size() - l;
        return tmp;
    }
    int mid = (b + e) / 2;
    int Left = node * 2,Right = node * 2 + 1;
    return (query(Left, b, mid, i, j, k) + query(Right, mid + 1, e, i, j, k));
}
