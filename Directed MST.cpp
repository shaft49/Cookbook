// Directed minimum spanning tree in O(n * m)
// Constructs a rooted tree of minimum total weight from the root node
// Returns -1 if no solution from root
struct edge{
    int u, v, w;
    edge(){}
    edge(int u, int v, int w) : u(u), v(v), w(w){}
};
edge E[N];
int cost[N], parent[N], label[N], comp[N];
int DMST(int n, int len, int root){
    int i, j, idx , l, x, y, res = 0;
    while(1){
        for (i = 0; i < n; i++){
            cost[i] = inf; label[i] = comp[i] = -1;
        }
        for (int i = 0; i < len; i++){
            edge e = E[i];
            if (e.u != e.v && cost[e.v] > e.w){
                cost[e.v] = e.w;
                parent[e.v] = e.u;
            }
        }
        cost[root] = 0;
        for (i = 0; i < n; i++){
            if(cost[i] == inf) return -1; // No Solution for the current root
            res += cost[i];
        }
        idx = 0;
        // cycle detection
        for (i = 0; i < n; i++){
            for (x = i; x != root && comp[x] == -1; x = parent[x]) comp[x] = i;
            if (x != root && comp[x] == i){
                for (idx++; label[x] == -1; x = parent[x]) label[x] = idx - 1;
            }
        }
        if (idx == 0) break;
        for (i = 0; i < n; i++){
            if (label[i] == -1) label[i] = idx++; // yet not find any group
        }
        for (int i = 0; i < len; i++){
            edge &e = E[i];
            x = label[e.u], y = label[e.v];
            if (x != y) e.w -= cost[e.v];
            e.u = x, e.v = y;
        }
        root = label[root], n = idx;
    }
    return res;
}
