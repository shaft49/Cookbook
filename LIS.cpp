//LDS can be found by simply multiplying the whole array with -1
///v.size() is the length of lis.
int arr[N], L[N], R[N], LISseq[N];
vector<int> v;
void LIS(int n){
    v.clear();
    for(int i = 1; i <= n; i++){
        ///Use lower bound for strictly increasing
        auto it = upper_bound(ALL(v),arr[i]);
        if(it == v.end()){
            v.pb(arr[i]);
            L[i] = v.size();
        }
        else{
            v[it - v.begin()] = arr[i];
            L[i] = it - v.begin() + 1;
        }
    }
}
void LDS(int n){
    v.clear();
    for(int i = n; i >= 1; i--){
        auto it = upper_bound(ALL(v),arr[i]);
        if(it == v.end()){
            v.pb(arr[i]);
            R[i] = v.size();
        }
        else{
            v[it - v.begin()] = arr[i];
            R[i] = it-v.begin()+1;
        }
    }
}
void printLIS(int n){
    int i = 0;
    for(int j = 1; j <= n; j++) if(L[j] > L[i]) i = j;
    int top = L[i]-1;
    int x = top;
    LISseq[top] = arr[i]; top -= 1;
    for(int j = i - 1; j >= 1; j--){
        if(arr[j] < arr[i] && L[j] == L[i] - 1){
            LISseq[top] = arr[j]; top--; i = j;
        }
    }
    for(int i = 0; i <= x; i++) printf("%d\n",LISseq[i]);
}
