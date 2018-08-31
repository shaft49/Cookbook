// Heavy Light Decomposition on Trees, 0 based indexing
// With RMQ support for nodes
// Define the operation, default is +
// x * NIL = x, NIL = 0 for addition/subtraction, 1 for multiplication,
// INF/-INF for min/max, etc
// RMQ to add values on nodes, if required to set/replace values modify appropriately
#define NIL 0
namespace hld{
    int r, n, id;
    vector <int> adj[N];
    int nodeval[N], lazy[4 * N], tree[4 * N]; /// RMQ
    int parent[N], subtree[N], depth[N], head[N], chain[N], tail[N], num[N]; /// HLD

    // head[i] = -1 if the edge from i to parent[i] is not heavy,
    // otherwise head[i] = unique id of the heavy edge
    // tail[i] = -1 if there is no heavy edge from i to it's children,
    // otherwise down[i] = node number of the heavy child of i
    // chain[i] = i, if i is root, otherwise up[i] = node number of parent
    // of i following only heavy up edges and one last light edge

    void init(int nodes, int* arr){
        n = nodes;
        SET(head); SET(tail);
        for (int i = 0; i <= nodes; i++) adj[i].clear();
        for (int i = 0; i < n; i++) nodeval[i] = arr[i];
    }

    void add_edge(int a, int b){
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    void dfs(int i, int par){
        parent[i] = par, subtree[i] = 1;
        if (i != par) depth[i] = depth[par] + 1;
        int j, x, len = adj[i].size();
        for (j = 0; j < len; j++){
            x = adj[i][j];
            if (x != par){
                dfs(x, i);
                subtree[i] += subtree[x];
            }
        }
    }
    // build heavy light decomposition
    void build(int i, int par){
        chain[i] = i;
        if (head[i] != -1) chain[i] = chain[par];
        int j, x, heavy = -1, len = adj[i].size();
        for (j = 0; j < len; j++){
            x = adj[i][j];
            if ((x != par) && ((subtree[x] << 1) >= subtree[i])){
                heavy = x, head[x] = i, tail[i] = x;
            }
        }
        if (heavy != -1){
            num[heavy] = ++id;
            build(heavy, i);
        }
        for (j = 0; j < len; j++){
            x = adj[i][j];
            if ((x != par) && (x != heavy)) build(x, i);
        }
    }
    // RMQ update defined for build
    void update_rmq(int node, int b, int e, int l, int r, int x);
    void build(int root){
        r = root, id = 0, depth[r] = 0;
        dfs(r, r);
        build(r, r);
        for (int i = 0; i < n; i++){
            if (chain[i] == i) chain[i] = parent[i];
        }
        // Builds RMQ
        CLR(lazy);
        for (int i = 0; i < (N << 2); i++) tree[i] = NIL;
        for (int i = 0; i < n; i++){
            if (head[i] != -1) update_rmq(1, 1, id, num[i], num[i], nodeval[i]);
        }
    }
    void build(){
        build(0); /// Root set to 0 by default!
    }

    int lca(int a, int b){
        while (chain[a] != chain[b]){
            if (depth[chain[a]] > depth[chain[b]]) a = chain[a];
            else b = chain[b];
        }
        if (a == b) return a;
        if (head[a] != -1 && head[b] != -1){
            if (depth[a] < depth[b]) return a;
            else return b;
        }
        return chain[a];
    }
    /************** RMQ functions **************/


    // Change lazy propagation accordingly
    // Note lazy and updates set for adding values in node,
    // update if set/replace operation
    int call(int a, int b){
        return a + b;
    }
    inline void push(int node, int b, int e){
        int L = node << 1, R = L | 1;
    // Consider the special case when lazy[] becomes zero because of update
    // operation then need to handle it and change the value of tree accordingly
        if (lazy[node]){
            // Change lazy according to operation
            tree[node] += (lazy[node] * (e - b + 1));
            // Change lazy according to operation
            if (b != e) lazy[L] += lazy[node], lazy[R] += lazy[node];
            lazy[node] = 0;
        }
    }
    // Change query accordingly
    int query_rmq(int node, int b, int e, int l, int r){
        int mid = (b + e) >> 1, L = node << 1, R = L | 1;
        push(node, b, e);
        if (b == l && e == r) return tree[node];
        else if (r <= mid) return query_rmq(L, b, mid, l, r);
        else if (l > mid) return query_rmq(R, mid+1, e, l, r);
        else{
            int p1 = query_rmq(L, b, mid, l, mid);
            int p2 = query_rmq(R, mid+1, e, mid+1, r);
            return call(p1, p2);
        }
    }

    // Change update accordingly
    void update_rmq(int node, int b, int e, int l, int r, int val){
        int L = (node << 1), R = L + 1, mid = (b + e) >> 1;
        // Change lazy according to operation, change here if set
        if (b == l && e == r) lazy[node] += val;
        push(node, b, e);
        if (b == l && e == r) return;
        if (r <= mid){
            push(R, mid+1, e);
            update_rmq(L, b, mid, l, r, val);
        }
        else if (l > mid){
            push(L, b, mid);
            update_rmq(R, mid+1, e, l, r, val);
        }
        else{
            update_rmq(L, b, mid, l, mid, val);
            update_rmq(R, mid+1, e, mid+1, r, val);
        }
        tree[node] = call(tree[L], tree[R]);
    }

    /************** HLD + RMQ **************/
    // Sum of all nodes in the path from u to l, l must be an ancestor of u
    int query_tree(int u, int l){
        int res = 0;
        while (depth[u] > depth[l]){
            if (head[u] != -1){
                int v = tail[chain[u]];
                if (depth[v] <= depth[l]) v = tail[l];
                res = call(res, query_rmq(1, 1, id, num[v], num[u]));
                u = parent[v];
            }
            else res = call(nodeval[u], res), u = parent[u];
        }
        return res;
    }

    // Sum of all nodes in the path from u to v
    int query(int u, int v){
        int l = lca(u, v), res = 0;
        res = call(res, query_tree(u, l));
        res = call(res, query_tree(v, l));
        if (head[l] == -1) res = call(nodeval[l], res);
        else res = call(query_rmq(1, 1, id, num[l], num[l]), res);
        return res;
    }

    // Add w to all nodes in the path from u to l, l must be an ancestor of u
    void update_tree(int u, int l, int w){
        while (depth[u] > depth[l]){
            if (head[u] != -1){
                int v = tail[chain[u]];
                if (depth[v] <= depth[l]) v = tail[l];
                update_rmq(1, 1, id, num[v], num[u], w);
                u = parent[v];
            }
            // Change here if set instead of add
            else nodeval[u] = call(nodeval[u], w), u = parent[u];
        }
    }

    // Add w to all nodes in the path from u to v
    void update(int u, int v, int w){
        int l = lca(u, v);
        update_tree(u, l, w);
        update_tree(v, l, w);
        // Change here if set instead of add
        if (head[l] == -1) nodeval[l] = call(nodeval[l], w);
        else update_rmq(1, 1, id, num[l], num[l], w);
    }
}
