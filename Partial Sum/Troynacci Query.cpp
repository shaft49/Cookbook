///Simulate to Understand the logic
#include<bits/stdc++.h>
using namespace std;
#define ll long long int
const int N = (int)1e5+10;
const ll mod = (ll)1e9+7;
ll F[N],A,B;
ll arr[N],P[N];
void precalc(){
    for(int i = 3; i < N; i++)
        F[i] = (A*F[i-2] + B*F[i-1])%mod;
}
void update(int l, int r){
    P[l] += F[1]; P[l] %= mod;
    P[l+1] += F[2]-B*F[1];
    P[l+1] = (P[l+1]%mod+mod) % mod;

    P[r+1] -= F[r-l+2];
    P[r+1] = (P[r+1]%mod+mod) % mod;
    P[r+2] -= A*F[r-l+1];
    P[r+2] = (P[r+2]%mod+mod) % mod;
}
int main(){
    int n, q;
    scanf("%d %d", &n, &q);
    scanf("%lld %lld %lld %lld",&F[1],&F[2],&A,&B);
    for(int i = 1; i <= n; i++)
        scanf("%lld",&arr[i]);
    precalc();
    while(q--){
        int l, r;
        scanf("%d %d",&l,&r);
        update(l,r);

    }
    for(int i = 1; i <= n; i++){
        P[i] += A*P[i-2] + B*P[i-1];
        P[i] %= mod;
        printf("%lld ",(arr[i]+P[i])%mod);
    }
    return 0;
}
