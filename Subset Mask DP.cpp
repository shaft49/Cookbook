/*LOJ - 1406
A directed graph consists of 15 nodes, A person can start
from any vertex and visit edges & nodes multiple times
but he can't visit a node if it visited by another
person. Find minimum number of person to cover all the nodes.
for all nodes generate mask of nodes that are reachable using dfs(i, 1<<i)
then take a subset of reachable mask and find the minimum number in call((1<<n)-1)
*/
int vis[1<<16], col[16][1<<16];
vector<int>adj[N];
int visit[1<<16], id, dp[1<<16];
void dfs(int src, int mask){
    col[src][mask] = 1;
    vis[mask] = 1;
    for(int i = 0; i < adj[src].size(); i++){
        int v = adj[src][i];
        int temp = mask | (1<<v);
        if(!col[v][temp]) dfs(v, temp);
    }
}
int call(int mask){
    if(mask == 0) return 0;
    int &res = dp[mask];
    if(visit[mask] == id) return res;
    visit[mask] = id;
    res = 100;
    for(int i = mask; i > 0; i = mask & (i-1)){
        if(!vis[i]) continue;
        res = min(res, call(mask^i) + 1);
    }
    return res;
}
