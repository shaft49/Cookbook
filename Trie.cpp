class data{
public:
    bool endmark;
    int cnt;
    data *node[10];
    data(){
        endmark=false;
        cnt = 0;
        for(int i=0;i<10;i++)node[i]=NULL;
    }
};
data *root;
void Insert(string s){
    int len = s.size();
    data *now = root;
    for(int i = 0;i < len; i++){
        if(now -> node[s[i]-'0'] == NULL) now->node[s[i]-'0'] = new data();
        now=now -> node[s[i]-'0'];
        now -> cnt += 1;
    }
}
ll query_min(string s){
    data *now=root;
    int len = s.size(), pw_id = len - 1;
    ll ans=0LL;
    for(int i = 0; i < len; i++){
        int val = s[i];
        if(now->node[val] != NULL && now -> node[val] -> cnt > 0){
            now = now -> node[val];
        }
        else{
            ans += pw[pw_id]; val ^= 1;
            now = now->node[val];
        }
       /// now->cnt -= 1;///Use this if you need to delete
        pw_id -= 1;
    }
    return ans;
}
ll query_max(string s){
    data *now=root;
    int len = s.size(), pw_id = len - 1;
    ll ans=0LL;
    for(int i=0;i<len;i++){
        int val=s[i]^1;
        if(now->node[val]!=NULL && now->node[val]->cnt > 0){
            now = now->node[val];
        }
        else{
            ans += pw[pw_id];
            val ^= 1;
            now = now->node[val];
        }
        now->cnt -= 1; pw_id -= 1;
    }
    return ans;
}
root=new data();///decalre this in main function;
