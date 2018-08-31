char mark[N];
vector<ll>primes;
void sieve(int n){
    mark[0] = 1, mark[1] = 1;
    for(int i = 4; i <= n; i += 2) mark[i] = 1;
    primes.pb(2);
    for(ll i = 3; i <= n; i += 2){
        if(mark[i] == 0){
        for(ll j = i*i; j <= n; j += 2*i){
            mark[j]=1;
        }
        primes.push_back(i);
        }
    }
}
