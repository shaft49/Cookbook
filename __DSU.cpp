int par[N];
int Find(int n){
    if(par[n]==n)return n;
    return par[n]=Find(par[n]);
}
void MakeSet(int n){
    par[n]=n;
}
void Union(int x,int y){
    int u=Find(x);
    int v=Find(y);
    if(u==v)return;
    else{
        par[u]=v;
    }
}

