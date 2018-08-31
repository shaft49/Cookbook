int tot;
vector<int>dig;
void calc(ll num) {
    dig.clear();
    while (num) {
        dig.push_back(num % 10);
        num /= 10;
    }
    reverse(dig.begin(),dig.end());
    tot = dig.size();
}
ll dp[82][2][2];
ll call(int pos, int isSmall, int isStart){
    if(pos == tot){
        return something;
    }
    ll &ans = dp[pos][isSmall][isStart];
    if(ans != -1)return ans;
    ans=0;
    int lim = isSmall ? 9 : dig[pos];
    if(!isStart){
        for(int i = 0; i <= lim; i++){
            ans += call(pos+1, isSmall | (i < dig[pos]), isStart);
        }
    }
    else{
        ans += call(pos+1, 1, 1);
        for(int i = 1; i <= lim; i++){
            ans += call(pos+1, isSmall | (i < dig[pos]), 0);
        }
    }
    return ans;
}
void ProcessInput(){
    ll l, r;
    cin >> l >> r ;
    if(l > r) swap(l,r);
    l -= 1;
    ll ansa,ansb;
    if(l < 0)ansa=0;
    else{
        SET(dp);
        calc(l);
        ansa=call(0, 0, 1);
    }
    SET(dp);
    calc(r);
    ansb=call(0, 0, 1);
    cout << ansb - ansa << endl;
}
