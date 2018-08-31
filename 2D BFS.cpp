char mat[N][N];
int vis[N][N];
void bfs(int row, int col,int sx,int sy){
    vis[sx][sy]=1;
    queue<pii>q;
    q.push({sx,sy});
    while(!q.empty()){
        auto top=q.front();
        q.pop();
        for(int k=0;k<4;k++){
            int tx=top.first+fx[k];
            int ty=top.second+fy[k];
            if(tx>=0 && tx<row && ty>=0 && ty<col){
                if(vis[tx][ty] || mat[tx][ty] == '.')continue;
                vis[tx][ty]=1;
                q.push({tx,ty});
            }
        }
    }
}
