/*---------Preprocessing----------*/
vector<int>adj[N];
int del[N];
/*------LCA Code will be here----*/
int parent[N],sparse[N][22],level[N];
void dfs(int u,int from, int d){
    level[u]=d;
    for(int v : adj[u]){
        if(from==v)continue;
        parent[v]=u;
        dfs(v,u,d+1);
    }
}
void lca(int n){
    SET(sparse);
    for(int i=0;i<n;i++)sparse[i][0]=parent[i];
    for(int j=1;(1<<j)<n;j++){
        for(int i=0;i<n;i++){
            if(sparse[i][j-1]!=-1)
                sparse[i][j]=sparse[sparse[i][j-1]][j-1];
        }
    }
}
int LCA(int p,int q){
    if(level[p]<level[q])swap(p,q);
    int log;
    for(log=1;1<<log<=level[p];log++);
    log--;
    for(int i=log;i>=0;i--)
        if(level[p]-(1<<i)>=level[q]) p=sparse[p][i];
    if(p==q)return p;
    for(int i=log;i>=0;i--){
        if(sparse[p][i]!=-1 && sparse[p][i]!=sparse[q][i]){
            p=sparse[p][i];
            q=sparse[q][i];
        }
    }
    return parent[p];
}

int dist(int p, int q){
    int res = level[p]+level[q]-(2*level[LCA(p,q)]);
    return res;
}
/*-------Decomposition Part--------*/
int sub[N], par[N];
void dfs(int u, int from){
    sub[u] = 1;
    for(int v : adj[u]){
        if(v == from || del[v])continue;
        dfs(v, u);
        sub[u] += sub[v];
    }
}
int find_centroid(int u, int from, int range){
    for(int v : adj[u]){
        if(v == from || del[v])continue;
        if(sub[v] > range) return find_centroid(v, u, range);
    }
    return u;
}
void build_tree(int u, int from){
    dfs(u, -1);
    int c = find_centroid(u, -1, sub[u]/2);
    //Delete all the edges that are linked with current centroid
    del[c] = 1;
    par[c] = from;
    for(int v : adj[c]){
        if(v == from || del[v])continue;
        build_tree(v, c);
    }
}
/*------Handle Queries------*/
int ans[N];
void update(int node){
    int src = node;
    while(node != -1){
        ans[node] = min(ans[node], dist(node,src));
        node = par[node];
    }
}
int query(int node){
    int res = inf, src = node;
    while(node != -1){
        res = min(res, ans[node]+dist(node,src));
        node = par[node];
    }
    return res;
}
