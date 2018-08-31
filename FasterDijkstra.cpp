int FasterDijkstra(int sx, int sy){
    queue<pii>qx, qy;
    qx.push({sx,sy});
    memset(dist, 63, sizeof(dist));
    dist[sx][sy] = 0;
    while(!qx.empty() || !qy.empty()){
        pii top;
        if(qx.empty()) top = qy.front(), qy.pop();
        else if(qy.empty()) top = qx.front(), qx.pop();
        else{
            pii u = qx.front(), v = qy.front();
            if(dist[u.ff][u.ss] < dist[v.ff][v.ss])
                top = u, qx.pop();
            else
                top = v, qy.pop();
        }
        for(int i = 0; i < 4; i++){
            int tx = top.ff+fx[i], ty = top.ss+fy[i];
            if(valid(tx,ty)){
                int cost = 0;
                if(mat[tx][ty] != mat[top.ff][top.ss]) cost += 1;
                if(dist[top.ff][top.ss]+cost >= dist[tx][ty])continue;
                dist[tx][ty] = dist[top.ff][top.ss]+cost;
                if(cost == X){
                    qx.push({tx,ty});
                }
                else{
                    qy.push({tx,ty});
                }
            }
        }
    }
    return dist[r][c];
}
