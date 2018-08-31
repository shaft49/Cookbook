///Printed
void merge(int u,int v){
    if(st[P[u]].size()<st[P[v]].size())swap(P[u],P[v]);
    for(auto i: st[P[v]]){
        st[P[u]].insert(i);
    }
}
void dfs(int u,int from){
    st[P[u]].insert(col[u]);
    for(int v : adj[u]){
        if(v==from)continue;
        dfs(v,u);
        merge(u,v);
    }
    ans[u]=st[P[u]].size();
}
///Initially P[i] = i
