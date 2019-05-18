vector<pii> adj[N];
int mark[N], dist[N];
bool NegativeCycle;
void init(int n){
    for(int i = 0; i <= n; i++) adj[i].clear();
    CLR(mark);
}
void BellmanFord(int s, int n){
    NegativeCycle = false;
    for(int i=0;i<=n;i++) dist[i]=inf;
    dist[s]=0;
    for(int i=1; i < n; i++){
        for(int cur=1; cur <= n; cur++){
            for(int j=0; j<adj[cur].size(); j++){
                int u=adj[cur][j].ff;
                if(dist[cur]<inf && dist[cur]+adj[cur][j].ss<dist[u]){
                    //first condition is necessary when dist[cur]=inf & cur-u<0
                    dist[u]=dist[cur]+adj[cur][j].ss;
                }
            }
        }
    }
    for(int i=1; i<= n; i++){
        for(int j=0;j<adj[i].size();j++){
            int u=adj[i][j].ff;
            if(dist[i]<inf && dist[i]+adj[i][j].ss<dist[u]){
                dist[u]=dist[i]+adj[i][j].ss;
                NegativeCycle = true;
                if(!mark[u])dfs(u); //mark which nodes are in the negative cycle
            }
        }
    }
}
