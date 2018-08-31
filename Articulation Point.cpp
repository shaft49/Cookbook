vector<int>adj[N];
int disc[N], low[N], vis[N], art_point[N];
int tym, root;
void init(int n){
    tym = 0; CLR(vis); CLR(art_point);
    for(int i = 0; i <= n; i++){
        adj[i].clear();
    }
}
void tarjan(int s, int par){
    disc[s] = low[s] = tym++;
    vis[s] = 1;
    int child = 0; //Needed for root only
    int art = 0;
    for (int i = 0; i < adj[s].size(); i++){
        int u = adj[s][i];
        if( u == par ) continue;
        if(!vis[u]) {
            child++;
            tarjan (u, s);
            low[s]=min(low[s],low[u]); //Update back edge extension for S
            if (low[u] >= disc[s]){ //Back edge of u did not go above S
                art++; //s is articulation point for u
            }
        }
        else if(vis[u]){///Back Edge
            low[s]=min(low[s],disc[u]);
        }
    }
    if ((s == root && child > 1) || (s != root && art)){
        //Edit in this block
        art_point[s] = 1;
    }
}
void FindArt(int n){
    for(int i = 0; i < n; i++){
        if(!vis[i]){
            root = i;
            tarjan (i, -1);
        }
    }
}
