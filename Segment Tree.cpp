ll arr[N], val;
struct info{
    ll sum, prop;
}tree[N*4];
info call(info a, info b){
    info temp;
    ///merge two info
    temp.sum = a.sum + b.sum;
    temp.prop = 0;
    return temp;
}
void propagate(int node, int b, int e){
    if(b == e){
        tree[node].prop = 0;
        return;
    }
    int Left = node << 1;
    int Right = Left + 1;
    int mid = (b + e) >> 1;
    ll prop = tree[node].prop;
    tree[node].prop = 0;
    tree[Left].prop += prop;
    tree[Right].prop += prop;
    tree[Left].sum += (mid - b + 1) * prop;
    tree[Right].sum += (e - mid) * prop;
}
void build(int node, int b, int e){
    tree[node].sum = 0;
    tree[node].prop = 0;
    if(b == e){
        ///Do Something
        return;
    }
    int mid = (b + e) / 2;
    int Left = node * 2, Right = node * 2 + 1;
    build(Left, b, mid);
    build(Right, mid+1, e);
    ///tree[node] = call(tree[Left], tree[Right]);
}
void update(int node, int b, int e, int i, int j){
    if(tree[node].prop) propagate(node, b, e);
    if(i > e || j < b)return;
    if(b >= i && e <= j){
        tree[node].prop += val;
        tree[node].sum += (e - b + 1) * tree[node].prop;
        return;
    }
    int mid = (b + e) / 2;
    int Left = node * 2, Right = Left+1;
    update(Left, b, mid, i, j);
    update(Right, mid+1, e, i, j);
    tree[node] = call(tree[Left], tree[Right]);
}
ll query(int node, int b, int e, int i, int j){
    if(i > e || j < b) return 0;
    if(tree[node].prop) propagate(node, b, e);
    if(b >= i && e <= j){
        ///Do something
        return tree[node].sum;
    }
    int mid = (b + e) / 2;
    int Left = node * 2, Right = Left + 1;
    ll p1 = query(Left, b, mid, i, j);
    ll p2 = query(Right, mid+1, e, i, j);
    return p1 + p2;
}
