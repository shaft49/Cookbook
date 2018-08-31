///Hopcroft karp in O(E * sqrt(V))
//Bidirectional edge, if directed then from left to right
// 1 based indexing
#define MAX 500100
namespace hc{
    vector<int> adj[MAX];
    int match[MAX], dist[MAX], n, m, p;
    void init(int nodes){
        n = nodes;
        for(int i = 0; i <= nodes; i++) adj[i].clear();
    }
    void add_edge(int u, int v){
        adj[u].pb(v);
    }
    bool bfs() {
        queue<int> Q;
        for(int i = 1; i <= n; i++){
            if(!match[i]) dist[i] = 0, Q.push(i);
            else dist[i] = inf;
        }
        dist[0] = inf;
        while(!Q.empty()) {
            int u = Q.front(); Q.pop();
            if(u == 0) continue;
            for(int i = 0; i < adj[u].size(); i++){
                int v = adj[u][i];
                if(dist[match[v]] == inf) {
                    dist[match[v]] = dist[u] + 1,
                    Q.push(match[v]);
                }
            }
        }
        return dist[0] != inf;
    }
    bool dfs(int u) {
        if(!u) return 1;
        for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i];
            if(dist[match[v]] == dist[u] + 1) {
                if(dfs(match[v])) {
                    match[u] = v, match[v] = u;
                    return 1;
                }
            }
        }
        dist[u] = inf; return 0;
    }
    int hopcroft_karp(){
        int res = 0;
        CLR(match);
        while(bfs())
            for(int i = 1; i <= n; i++)
                if(!match[i] && dfs(i)) res += 1;
        return res;
    }
}
