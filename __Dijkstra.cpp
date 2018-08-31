vector<pair<int,int> >adj[N];
int dist[N], done[N];
void dijkstra(int n, int s){
    CLR(done);
    priority_queue<pair<int,int> > pq;
    for ( int i = 0; i < n; i++ ) dist[i] = inf;
    dist[s] = 0
    pq.push( make_pair(-0,s) );
    while (!pq.empty()){
        int s = pq.top().second;
        int cost = pq.top().first * -1;
        pq.pop();
        if (done[s]) continue;
        for ( int i = 0; i < adj[s].size(); i++ ) {
            int t = adj[s][i].first;
            int e = adj[s][i].second;
            if (cost + e < dist[t]) {
                dist[t] = cost + e;
                pq.push (make_pair(-dist[t], t ));
            }
        }
        done[s] = 1;
    }
}
