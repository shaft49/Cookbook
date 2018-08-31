struct query{
    int l,r,id;
    query(){}
    query(int l, int r, int id):l(l), r(r), id(id){}
}Q[N];
int magic = 200, sum;
int arr[N], cnt[N], ans[N];
bool comp(query a,query b){
    int l1 = a.l/magic, l2 = b.l/magic;
    if(l1 != l2) return l1 < l2;
    return a.r < b.r;
}
void Add(int pos){
    cnt[arr[pos]] += 1;
    if(cnt[arr[pos]] == 1) sum += 1;
}
void Remove(int pos){
    cnt[arr[pos]] -= 1;
    if(cnt[arr[pos]] == 0) sum -= 1;
}
int get_ans(){
    return sum;
}
void MO(int q){
    sort(Q,Q+q,comp);
    int l = 0, r = -1;
    for(int i = 0; i < q; i++){
        while(l > Q[i].l)Add(--l);
        while(r < Q[i].r)Add(++r);
        while(l < Q[i].l)Remove(l++);
        while(r > Q[i].r)Remove(r--);
        ans[Q[i].id] = get_ans();
    }
    for(int i=0;i<q;i++){
        cout << ans[i] << endl;
    }
}
void InputProcess(int n, int q){
    for(int i=0;i<q;i++){
        cin >> Q[i].l >> Q[i].r;
        Q[i].l--, Q[i].r--, Q[i].id=i;
    }
    MO(q);
}

