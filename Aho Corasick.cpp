/** aho :: init()
    aho :: Insert(pattern, i) for all patterns
    aho :: build()
    aho :: match(text)
    for (int i = 0; i < n; i++) cout <<  aho::counter[aho::pos[i]] << endl;
    contains the count of pattern[i] in the text */
#define LET 26
#define PAT 1010
#define MAX 300010
/// Complexity O(N + M) + O(MAX * LET), N = text length, M = sum of pattern length, MAX = Total nodes in trie
namespace aho{
    int id, len, counter[MAX]; /// counter[i] contains the number of times node i is visited in the trie after text traversal
    int Q[MAX], T[MAX], fail[MAX], pos[PAT], lethash[256], trie[MAX][LET]; /// trie[i][j] = next node from node i following character j
    inline int node(){
		CLR(trie[id]);
		fail[id] = 0, counter[id] = 0;
		return id++;
    }
    inline void init(){
        id = 0, len = 0, node();
        for (int i = 'a'; i <= 'z'; i++) lethash[i] = i - 'a'; /// Change here if different character set
    }
    inline void Insert(string str, int i){
        int j, x, cur = 0;
        for (j = 0; j < str.size(); j++){
            x = lethash[str[j]];
            if (!trie[cur][x]) trie[cur][x] = node();
            cur = trie[cur][x];
        }
        pos[i] = cur; /// saving the index of the current pattern
    }
    inline void build(){
        int i, j, x, f = 0, l = 0;
        for (i = 0; i < LET; i++){
            if (trie[0][i]) Q[l++] = trie[0][i];
        }
        while (f < l){
            i = Q[f++];
            for (j = 0; j < LET; j++){
                int &v = trie[i][j];
                if (v == 0) v = trie[fail[i]][j];
                else{
                    fail[v] = trie[fail[i]][j];
                    Q[l++] = v, T[len++] = v;
                }
            }
        }
    }
    inline void match(string str){
        int i, j, x, cur = 0;
        for (j = 0; j < str.size(); j++){
            x = lethash[str[j]];
            cur = trie[cur][x];
            counter[cur]++;
        }
        for (i = len - 1; i >= 0; i--) counter[fail[T[i]]] += counter[T[i]]; /// add to count of fail node also
    }
}
