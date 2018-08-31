struct edge{
    int a,b,c;
    edge(){}
    edge(int a, int b, int c):a(a),b(b),c(c){}
    bool operator < (const edge &p)const{
        return c<p.c;
    }
};
vector<edge>adj;
int par[N];
int find(int n){
    if(par[n]==n)return n;
    return par[n]=find(par[n]);
   /*int tmp = n;
     while(par[tmp] != tmp)
          tmp = par[tmp];
     while(par[n] != tmp){
          int tmp_x = par[n];
          par[n] = tmp;
          n = tmp_x;
     }
     return tmp;*/
}
int mst(int n){
    sort(ALL(adj));
    for(int i=1;i<=n;i++) par[i]=i;
    int cnt=0,res=0;
    for(int i=0;i<adj.size();i++){
        int x=find(adj[i].a);
        int y=find(adj[i].b);
        if(x!=y){
            par[x]=y;
            cnt++;
            res+=adj[i].c;
            if(cnt==n-1)break;
        }
    }
    return res;
}
