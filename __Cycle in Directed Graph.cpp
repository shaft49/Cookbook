int vis[N];
bool Cycle(int src){
    if(vis[src] == 1)return true;
    if(vis[src] == 2) return false;
    vis[src] = 1;
    for(int u : adj[src]){
        if(Cycle(u)) return true;
    }
    vis[src] = 2;
    return false;
}
