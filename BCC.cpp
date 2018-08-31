vector<int>adj[N], adj_shrink[N], tarjan;
int disc[N], low[N], vis[N], cycle[N];
int tym, comp;
void init(int n){
    tym = 0; comp = 0; CLR(vis); tarjan.clear();
    for(int i = 0; i <= n; i++){
        adj[i].clear(); adj_shrink[i].clear();
    }
}
void BCC(int s, int par){
    disc[s] = low[s] = tym ++;
    vis[s] = 1;
    tarjan.push_back(s);
    for(int i = 0; i < adj[s].size(); i++){
        int v = adj[s][i];
        if(v == par) continue;
        if(vis[v]) low[s] = min(low[s], disc[v]);
        else{
            BCC(v, s);
            low[s] = min(low[s], low[v]);
        }
    }
    if(low[s] == disc[s]){
        comp += 1;
        while(1){
            int lst = tarjan.back();
            tarjan.pop_back();
            cycle[lst] = comp;
            if(lst == s) break;
        }
    }
}
void shrink(int n){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < adj[i].size(); j++){
            int v = adj[i][j];
            if(cycle[i] != cycle[v]){
                adj_shrink[cycle[i]].pb(cycle[v]);
            }
        }
    }
}
