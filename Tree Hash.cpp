const long long HMOD = 2078526727;
const long long BASE = 1572872831;
ll pw[N];
int subtree[N], level[N];
vector<int>adj[N]; //assuming edges are directed
void dfs(int root, int lvl = 1){
    subtree[root] = 1;level[root] = lvl;
    for(int i = 0; i < adj[root].size(); i++){
        int nxt = adj[root][i];
        dfs(nxt, lvl + 1);
        subtree[root] += subtree[nxt];
    }
}
ll calc_hash(int root){
    ll X = 0;
    for(int i = 0; i < adj[root].size(); i++){
        int nxt = adj[root][i];
        X += calc_hash(nxt); if(X >= HMOD) X -= HMOD;
    }
    ll res = X + (subtree[root] * (pw[level[root]] + adj[root].size())) % HMOD;
    return res % HMOD;
}
ll tree_hash(int root){
    pw[0] = 1;
    for(int i = 1; i < N; i++){
        pw[i] = (pw[i-1] * BASE) % HMOD;
    }
    dfs(root);
    return calc_hash(root);
}
