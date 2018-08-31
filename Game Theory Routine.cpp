                    //MinMax
bool dp[N];
int p, q, r, vis[N];
bool valid(int x){
    return x >= 0; //check whether it is a possible move or not
}
bool MinMax(int n){
    if(vis[n]) return dp[n];
    vis[n]=1;
    if(valid(n - 1) && !MinMax(n - 1)) return dp[n] = true;// n theke jesob valid move
    if(valid(n - p) && !MinMax(n - p)) return dp[n] = true;// deoa jai segular jkono ekta
    if(valid(n - q) && !MinMax(n - q)) return dp[n] = true;// false holei true return korbe
    return dp[n] = false; //otherwise false
}

                     //Grundy
int dp[N];
int grundy(int x){
    if(x <= 0) return 0;
    int &ret = dp[x];
    if(ret != -1) return ret;
    set<int> st;
    for(int i = 0; i < x; i++){
        st.insert(grundy(i - 2) ^ grundy(x - i - 3));
        //possible moves from current state
    }
    int cur = 0;
    while(st.find(cur) != st.end()) cur += 1;
    return ret = cur;
}
                //Green Hackenbush
//value of dfs() > 0 then win
int dfs(int s, int p){
    int g = 0;
    for(int i = 0; i < adj[s].size(); i++){
        int t = adj[s][i];
        if(t == p) continue;
        int x = dfs(t, s);
        g ^= (x + 1);
    }
    return g;
}
                 //Red Blue Hackenbush
//res > 0 -> even win
//res < 0 -> odd win
//res == 0 don't play
// for multiple stalks add the value normally
ll ar[N];
ll hackenbush(int n){
    ll V = 1LL << 50, lst = -1, res = 0;
    int flag = 0;
    for(int i = 0; i < n; i++){
        ll cur = ar[i];
        if(lst == -1) lst = cur;
        if(cur % 2LL != lst % 2LL) flag = 1;
        if(flag) V /= 2;
        if(cur % 2LL) res -= V;
        else res += V;
        lst = cur;
    }
    return res;
}
