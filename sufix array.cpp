// Complexity - O(n*log^2(n))
namespace sa{
    const int MAX =200004;
    struct info{
        int tup[2], indx; ///tup[0] = prev rank, tup[1] = new rank
        bool operator < (const info &a)const{
            return tup[0] != a.tup[0]? tup[0] < a.tup[0] : tup[1] < a.tup[1];
        }
    }suffix[MAX];

    int Rank[18][MAX], LCP[MAX], step;
    void build_sa(string str){
        CLR(Rank);
        int len = str.size(), jump;
        for(int i = 0; i < len; i++){
            Rank[0][i] = str[i] - 'a' + 1; ///rank suffixes according to 1st chsuffix
            CLR(suffix[i].tup);
        }
        for(step = 1, jump = 1; jump <= len; step++, jump <<= 1){
            for(int i = 0; i < len; i++){
                suffix[i].indx = i;
                suffix[i].tup[0] = Rank[step - 1][i]; /// what i was in prev step
                suffix[i].tup[1] = i + jump < len ? Rank[step - 1][i + jump] : -1;
            }
            sort(suffix, suffix + len);
            ///Assign rank to the suffixes
            Rank[step][suffix[0].indx] = 1 /// 0 based creates some problems
            for(int i = 1; i < len; i++){
                if(suffix[i].tup[0] == suffix[i - 1].tup[0] && suffix[i].tup[1] == suffix[i - 1].tup[1]){
                    Rank[step][suffix[i].indx] = Rank[step][suffix[i - 1].indx] ;
                }
                else {
                    ///Relative rank is given, change if continuous rank is required
                    Rank[step][suffix[i].indx] = i + 1;
                }
            }
        }
    }

    void build_lcp(string str){
        CLR(LCP);
        ///LCP[i] is longest common prefix between i & i - 1
        LCP[0] = 0;
        int len = str.size(), i, j, id1, id2;
        ///not necessary id1, id2 has to be adjacent, works for any id1, id2
        for(i = 1; i < len; i++){
            id1 = suffix[i - 1].indx;
            id2 = suffix[i].indx;
            LCP[i] = 0;
            for(j = step - 1; j >= 0; j--) {
                if(Rank[j][id1] == Rank[j][id2]){
                    LCP[i] += (1 << j);
                    id1 += (1 << j);
                    id2 += (1 << j);
                }
            }
        }
    }
}
