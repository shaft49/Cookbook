class Node {
public:
    bool endmark;
    int cnt;
    Node* node[10];
    Node(){
        endmark=false;
        cnt = 0;
        for(int i=0;i<10;i++) node[i]=NULL;
    }
};
class Trie {
    Node *root;
public:
    Trie(){
        root = new Node();
    }
    
    void insert(string &str) {
        Node *cur = root;
        for(char ch : str) {
            if (cur -> arr[ch - 'a'] == NULL) cur -> arr[ch - 'a'] = new Node();
            cur = cur -> arr[ch - 'a'];
            cur -> count += 1;
        }
    }
    
    string get_unique_prefix(string &str) {
        string prefix = "";
        Node *cur = root;
        for(char ch : str) {
            cur = cur -> arr[ch - 'a'];
            prefix += ch;
            if(cur -> count == 1) return prefix;
        }
        return prefix;
    }

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
};