/**first step
for(int i=1;i<=n;i++)
    if(vis[i]==WHITE)SCC(i);
2nd step:shrink(n);*/
#define WHITE 0
#define GRAY 1
#define BLACK 2
int disc[N], low[N];
vector<int>adj[N],adj_shrink[N], node[N];
int vis[N],head=1;
int globalCnt = 0;
int flagCycle;
vector<int> tarjan;
int cycle[N],color[N];
void init(int n){
    globalCnt=0;
    flagCycle=false;
    head=1;tarjan.clear();
    for(int i=0;i<=n;i++){
        adj[i].clear();adj_shrink[i].clear();
    }
    CLR(vis);CLR(color);
    CLR(low);CLR(disc);CLR(cycle);
}
int SCC ( int s ) {
    vis[s] = GRAY;
    disc[s] = low[s] = globalCnt++;
    tarjan.push_back(s);
    for ( int i = 0; i < adj[s].size(); i++ ) {
        int t = adj[s][i];
        if ( vis[t] == WHITE ) { ///This is tree edge
            SCC ( t );
            low[s] = min ( low[s], low[t] );
        }
        else if ( vis[t] == GRAY ) { ///This is back edge
            ///Cycle detected
            flagCycle = true;
            low[s] = min ( low[s], low[t] );
        }
    }
    if ( disc[s] == low[s] ) {
        while ( 1 ) {
            int lastNode = tarjan.back();
            cycle[lastNode] = head;
            node[head].pb(lastNode);
            tarjan.pop_back();
            vis[lastNode] = BLACK;
            if ( lastNode == s ) break;
        }
        head++;
    }
}
void dfs(int src){
    if(color[src])return;
    color[src]=1;
    for(int i=0;i<adj[src].size();i++){
        if(cycle[src]!=cycle[adj[src][i]]){
            adj_shrink[cycle[src]].pb(cycle[adj[src][i]]);
            dfs(adj[src][i]);
        }
    }
}
void shrink(int n){
    for(int i=1;i<=n;i++){
      if(color[i]==0)dfs(i);
    }
}
