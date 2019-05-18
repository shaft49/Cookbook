/*call dfs(start,-1,1)->call lca(n) -> call query(p,q)
https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/*/
vector<int>adj[N];
int parent[N],sparse[N][22],level[N];
void dfs(int u,int from,int d){
    level[u]=d;
    for(int i=0;i<adj[u].size();i++){
        int v=adj[u][i];
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
    //if p is situated on a higher level than q then we swap them
    if(level[p]<level[q])swap(p,q);
    int log;
    //we compute the value of [log(level[p)]
    for(log=1;1<<log<=level[p];log++);
    log--;
    //we find the ancestor of node p situated on the same level
    //with q using the values in P
    for(int i=log;i>=0;i--){
        if(level[p]-(1<<i)>=level[q]){
                p=sparse[p][i];
        }
    }
    if(p==q)return p;
    //we compute LCA(p, q) using the values in P
    for(int i=log;i>=0;i--){
        if(sparse[p][i]!=-1 &&sparse[p][i]!=sparse[q][i]){
            p=sparse[p][i];
            q=sparse[q][i];
        }
    }
    return parent[p];
}
int dist(int p, int q){
    return level[p]+level[q]-(2*level[LCA(p,q)]);
}
