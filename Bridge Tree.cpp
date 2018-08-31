vector<pii> adj[N];
vector<int>adj_shrink[N];
int disc[N], low[N], vis[N], isBridge[N];
int color[N], tym, comp;
void init(int n){
    tym = 0; comp = 0; CLR(vis);
    CLR(isBridge); CLR(color);
    for(int i = 0; i <= n; i++){
        adj[i].clear(); adj_shrink[i].clear();
    }
}
void tarjan(int s, int parentEdge){
    disc[s] = low[s] = tym++;
    vis[s] = 1;
    for (int i = 0; i < adj[s].size(); ++i){
        int v = adj[s][i].ff;
        int edge = adj[s][i].ss;
        if (edge == parentEdge) continue; //Handles Multiple Edge
        if(!vis[v]){
            tarjan (v, edge);
            low[s]=min(low[s],low[v]);
            if (low[v] > disc[s]){
                //This edge is Bridge
                isBridge[edge] = 1;
            }
        }
        else if (vis[v]){
            low[s]=min(low[s], disc[v]);
        }
    }
}
void FindBridge(int n){
    for(int i = 0; i < n; i++){
        if (!vis[i]){
            tarjan (i, -1);
        }
    }
}
void BridgeTree(int s){
    queue<int>q;
    q.push(s); color[s] = 1;
    int cur = comp;
    while(!q.empty()){
        int u = q.front();q.pop();
        for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i].ff;
            int edge = adj[u][i].ss;
            if(color[v]) continue;
            color[v] = 1;
            if(isBridge[edge]){
                comp += 1;
                adj_shrink[cur].pb(comp);
                adj_shrink[comp].pb(cur);
                BridgeTree(v);
            }
            else{
                q.push(v);
            }
        }
    }
}
