/**Persistent Segment Tree
Requires nlogn memory
call init() in main function
*/

const int N=(int)2e5+10;
int arr[N],root[N*21],id,Left[N*21],Right[N*21],n,q;
struct info{
    int sum;
}tree[N*21];
info call(info a,info b)
{
    info temp;
    ///merge two info
    temp.sum=a.sum+b.sum;
    return temp;
}
void build(int node,int b,int e){
    if(b==e){
        ///do something
        return;
    }
    Left[node]=id++;
    Right[node]=id++;
    int mid=(b+e) >> 1;
    build(Left[node],b,mid);
    build(Right[node],mid+1,e);
    ///tree[node]=call(tree[Left[node]],tree[Right[node]]);
}
int update(int node,int b,int e,int i,int val){
    if(e<i || b>i)return node;
    int idx=id++;
    if(b==e){
        tree[idx].sum=tree[node].sum+val;
        return idx;
    }
    int mid=(b+e) >> 1;
    Left[idx]=update(Left[node],b,mid,i,val);
    Right[idx]=update(Right[node],mid+1,e,i,val);
    tree[idx]=call(tree[Left[idx]],tree[Right[idx]]);
    return idx;
}
int query(int node,int b,int e,int i,int j){
    if(e<i || b>j)return 0;
    if(b>=i && e<=j)return tree[node].sum;
    int mid=(b+e)>>1;
    return query(Left[node],b,mid,i,j)+query(Right[node],mid+1,e,i,j);
}
int search(int a, int b, int l, int r, int k) {
	if(l == r) return l;
	int cnt = tree[Left[a]].sum - tree[Left[b]].sum;
	int mid = l + r >> 1;
	if(cnt >= k)
		return search(Left[a], Left[b], l, mid, k);
	return search(Right[a], Right[b], mid+1, r, k - cnt);
}
int kthnum(int l, int r, int k) {
	return search(root[r], root[l-1], 1, n, k);
}
void init(){
    root[0]=id++;
    build(root[0],1,n);
    for(int i=1;i<=n;i++){
        root[i]=update(root[i-1],1,n,arr[i],1);
    }
}
/**
Persistent Segment Tree
Dynamic node creation
call init() in main function
*/
const int N =  2e5 + 10;
int n,arr[N];
struct node {
	ll val;
	node *left, *right;
	node(ll _val = 0, node *_left = NULL, node *_right = NULL) :
		val(_val), left(_left), right(_right){}

	void build(int b, int e) {
		if(b == e) return;
		left = new node();
		right = new node();
		int mid = b + e >> 1;
		left -> build(b, mid);
		right -> build(mid+1, e);
	}
	node *update(int b, int e, int idx, ll v) {
		if(e < idx || b > idx) return this;
		if(b == e) {
			node *p = new node(val, left, right);
			p -> val += v;
			return p;
		} int mid = b + e >> 1;
		node *p = new node(val);
		p -> left = left -> update(b, mid, idx, v);
		p -> right = right -> update(mid+1, e, idx, v);
		p -> val = p -> left -> val + p -> right -> val;
		return p;
	}
	ll query(int b, int e, int i, int j) {
		if(e < i || b > j) return 0;
		if(i <= b && e <= j) return val;
		int mid = b + e >> 1;
		return left -> query(b, mid, i, j) +
			  right -> query(mid+1,e,i, j);
	}
} *root[N];
void init() {
	root[0] = new node();
	root[0] -> build(1, n);
	for(int i = 1; i <= n; i++)
		root[i] = root[i-1] -> update(1, n, arr[i], +1);
}
