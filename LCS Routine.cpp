vector<string>v;
string a, b, ans;
int n, dp[N][N], alen, blen, res; //res = lcs length
int LCS(int i, int j){
    if(i >= alen || j >= blen) return 0;
    int &ans = dp[i][j];
    if(ans != -1) return ans;
    if(a[i] == b[j]) ans = 1 + LCS(i+1, j+1);
    else ans = max(LCS(i+1,j), LCS(i,j+1));
    return ans;
}
void printLCS(int i, int j){
    if(i >= alen || j >= blen){
        if(ans.size() == res) v.pb(ans);
        return;
    }
    if(a[i]==b[j]){
        ans+=a[i];
        printLCS(i+1,j+1); //for all lcs
        ans.erase(ans.end()-1); //to find all lcs last character is deleted
    }else{
        if(dp[i+1][j] > dp[i][j+1]) printLCS(i+1,j);
        else if(dp[i+1][j] < dp[i][j+1]) printLCS(i,j+1);
        else{
            printLCS(i+1,j); printLCS(i,j+1);
        }
    }
}
/// Lexicographically smallest LCS
#define Pii pair<int,string>
Pii dp[N][N];
bool color[101][101];
Pii add(Pii a, Pii b){
    Pii d;
    d.ff = a.ff + b.ff;
    d.ss = a.ss + b.ss;
    return d;
}
Pii minimum(Pii a, Pii b){
    if(a.ff > b.ff) return a;
    else{
        if(a.ff == b.ff){
            if(a.ss < b.ss) return a;
            else return b;
        } else return b;
    }
}
Pii LCS(int i, int j){
    if(i >= alen || j >= blen) return Pii(0,"");
    Pii &ans = dp[i][j];
    if(color[i][j])return ans;
    color[i][j] = 1;
    if(a[i] == b[j]){
        string str = ""; str += a[i];
        ans = add(Pii(1,str),LCS(i+1,j+1));
    }else{
        Pii pp = LCS(i+1,j);
        Pii pq = LCS(i,j+1);
        ans = minimum(pp,pq);
    } return ans;
}
