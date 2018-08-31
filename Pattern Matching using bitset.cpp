#include <bits/stdc++.h>
using namespace std;
const int N = (int)1e5+10;
bitset<N>bs[26], ans, one;
string text, pat;
void PreProcess(){
    int len = text.size();
    one.set();
    for(int i = 0; i < len; i++)bs[text[i]-'a'][i+1] = 1;
}
void update(int pos, char ch){
    char prev = text[pos-1];
    bs[prev-'a'][pos] = 0, bs[ch-'a'][pos] = 1;
    text[pos-1] = ch;
}
int query(int l, int r){
    ans = one;
    int len = pat.size();
    if(r-l+1 < len) return 0;
    for(int i = 0; i < len; i++){
        ans &= (bs[pat[i]-'a'] >> (i+1));
    }
    //If a bit is set in ans then a pattern will match starting at that position
    //Position of bitset is in reverse order
    int lft = (ans >> (l-1)).count();
    int rght = (ans >> (r-len+1)).count();
    return lft-rght;
}
int main(){
    /*1.update a single character.
      2.Find number of substring in the range [l,r] matches with pat*/
    cin >> text;
    for(int i = 0; i < text.size(); i++)one[i] = 1;
    text = text;
    PreProcess();
    int q;
    cin >> q;
    while(q--){
        int op, l, r;
        cin >> op >> l ;
        if(op == 1){
            char ch; cin >> ch;
            update(l, ch);
        }
        else{
            cin >> r >> pat;
            int res = query(l,r);
            cout << res << endl;
        }
    }
    return 0;
}
/*
012345678
ababababa
3
2 1 7 aba
1 5 c
2 1 7 aba
ans-> 3 1
*/

