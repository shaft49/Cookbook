int vis[N];
vector<int>adj[N];
bool bipartite(int src){
    vis[src] = 1;
    queue<int>q; q.push(src);
    while(!q.empty()){
        int src = q.front();
        q.pop();
        for(int i = 0; i < adj[src].size(); i++){
            int tx = adj[src][i];
            if(vis[tx] == -1){
                vis[tx] = 1-vis[src];
                q.push(tx);
            }
            if(vis[src] == vis[tx]) return false;
        }
    }
    return true;
}
