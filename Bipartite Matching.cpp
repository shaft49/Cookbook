/*
Minimum Vertex Cover = Maximum Matching
Minimum Edge Cover = No of vertices – Maximum Matching
Maximum Independent Set = Minimum Edge Cover
Vertex cover is the minimum no of edges need to cover all the vertices
Edge cover is the minimum no vertices need to cover all the edges
Independent set is the set of vertices such that no one has connection with each other
*/
vector<int> adj[N];
int vis[2*N], Left[N], Right[N], counter;
//Nodes get double in vis[] for vertex print
bool tryK (int s){
    if (vis[s] == counter) return false;
    vis[s] = counter;
    for(int i=0;i<adj[s].size();i++){
        int t = adj[s][i];
        if (Right[t] == -1){
            Left[s] = t;
            Right[t] = s;
            return true;
        }
    }
    for (int i = 0; i < adj[s].size(); i++){
        int t = adj[s][i];
        if (tryK(Right[t])){
            Left[s] = t;
            Right[t] = s;
            return true;
        }
    }
    return false;
}

int kuhn (int n){
    int res = 0;
    SET(Left); SET(Right); CLR(vis);
    bool done;
    do{
        done = true; counter += 1;
        for ( int i = 0; i < n; i++ ) {
            if (Left[i] == -1 && tryK (i)) {
                done = false;
            }
        }
    }while(!done);
    for(int i = 0; i < n; i++) res += (Left[i] != -1);
    return res;
}

//Careful. Loop runs from 0 to n-1
//Make sure kuhn(n) has been run
int lcover[N], rcover[N];
void findVertexCover(int n){
    queue<int> q;
    cc++;
    for(int i = 0; i < n; i++){
        if( Left[i] == -1 ) {
            q.push ( i );
            vis[i] = cc;
        }
    };

    while(!q.empty()){
        int s = q.front(); q.pop();
        for(int i = 0; i < adj[s].size(); i++){
            int t = adj[s][i];
            if ( t == Left[s] ) continue;
            int xt = t + n;
            if (vis[xt] == cc) continue;
            vis[xt] = cc;
            xt = right[t];
            if (xt != -1 && vis[xt] != cc){
                vis[xt] = cc;
                q.push ( xt );
            }
        };
    }
    for(int i = 0; i < n; i++){
        if ( vis[i] != cc ) lcover[i] = 1;
        else lcover[i] = 0;
    };
    for(int i = 0; i < n; i++){
        if ( vis[i+n] == cc ) rcover[i] = 1;
        else rcover[i] = 0;
    };
}
