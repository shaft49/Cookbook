char mat[N][N];
int dist[N][N], r, c;
bool valid(int x, int y){
    if(x >= 1 && x <= r && y >= 1 && y <= c) return true;
    return false;
}
int bfs01(int sx, int sy){
    deque<pii>dq;
    dq.push_front({sx,sy});
    memset(dist, 63, sizeof(dist));
    dist[sx][sy] = 0;
    while(!dq.empty()){
        pii top = dq.front();
        dq.pop_front();
        for(int i = 0; i < 4; i++){
            int tx = top.ff+fx[i], ty = top.ss+fy[i];
            if(valid(tx,ty)){
                int x = dist[top.ff][top.ss];
                if(mat[tx][ty] != mat[top.ff][top.ss]) x += 1;
                if(x >= dist[tx][ty])continue;
                dist[tx][ty] = x;
                if(mat[tx][ty] == mat[top.ff][top.ss]){
                    dq.push_front({tx,ty});
                }
                else{
                    dq.push_back({tx,ty});
                }
            }
        }
    }
    return dist[r][c];
}
