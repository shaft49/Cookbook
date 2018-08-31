int arr[N], delta[N], n, magic  = 320;
int cnt[320][N];
void updateElement(int pos, int add){
    int id = pos / magic;
    int prv = arr[pos];
    cnt[id][prv] -= 1;
    arr[pos] += add;
    cnt[id][arr[pos]] += 1;
}
void updateBlock(int id, int add){
    delta[id] += add;
}
void update(int l, int r, int add){
    int i;
    for(i=l; i <= r && i % magic ; i ++ ) {
        updateElement(i, add);
    }
    for(; i + magic-1 <= r; i += magic) {
        updateBlock(i/magic, add);
    }
    for(;i <= r ; i ++ ) updateElement(i, add);
}
int queryElement(int pos, int val){
    int id = pos/magic;
    if(arr[pos] + delta[id] == val) return 1;
    return 0;
}
int queryBlock(int id, int val){
    int p = delta[id];
    val -= p;
    return cnt[id][val];
}
int query(int l, int r, int val){
    int i,j;
    int res = 0;
    for(i = l; i <= r && i % magic; i++){
        res += queryElement(i, val);
    }
    for( ; i + magic -1 <= r ; i+= magic){
        res += queryBlock(i/magic, val);
    }
    for( ; i <= r; i++) res += queryElement(i, val);
    return res;
}

