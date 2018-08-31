//Sieve of Eratosthenes
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

//Number distinct prime factors of a number
int prime_factor(ll n){
    int cnt = 0;
    if(mark[n] == 0) return 1;
    for(ll i = 0; primes[i] * primes[i] <= n; i++){
        if(n % primes[i] == 0){
            cnt++;
            while(n % primes[i] == 0){
                n /= primes[i];
            }
        }
    }
    if(n > 1) cnt += 1;
    return cnt;
}

//Extended Euclidean Algorithm
ll ext_gcd ( ll A, ll B, ll *X, ll *Y ){
    ll x2, y2, x1, y1, x, y, r2, r1, q, r;
    x2 = 1; y2 = 0;
    x1 = 0; y1 = 1;
    for (r2 = A, r1 = B; r1 != 0; r2 = r1, r1 = r, x2 = x1, y2 = y1, x1 = x, y1 = y ) {
        q = r2 / r1;
        r = r2 % r1;
        x = x2 - (q * x1);
        y = y2 - (q * y1);
    }
    *X = x2; *Y = y2;
    return r2;
}

ll ext_gcd(ll a, ll b, ll& x, ll& y){
    /// Bezout's identity, ax + by = gcd(a,b)

    if (!b){
        y = 0, x = 1;
        return a;
    }

    ll g = ext_gcd(b, a % b, y, x);
    y -= ((a / b) * x);
    return g;
}
// Modular Inverse
ll mod_inverse(ll a, ll m){
    /// inverse exists if and only if a and m are co-prime
    ll x, y, inv;
    ext_gcd(a, m, x, y);
    inv = (x + m) % m;
    return inv;
}
// Modular Inverse from 1 to n;
ll fact[N], inv[N];
void Generate(int n){
    int i, x;
    for (fact[0] = 1, i = 1; i <= n; i++) fact[i] = ((ll)i * fact[i - 1]) % MOD;

    /// inv[i] = Inverse modulo of fact[i]
    inv[n] = bigmod(fact[n], MOD - 2);
    for (i = n - 1; i >= 0; i--) inv[i] = ((ll)inv[i + 1] * (i + 1)) % MOD;

    /// Inverse modulo of numbers 1 to MAX in linear time below
    inv[1] = 1;
	for (i = 2; i <= n; i++){
        inv[i] = MOD - ((MOD / i) * (long long)inv[MOD % i]) % MOD;
        if (inv[i] < 0) inv[i] += MOD;
	}
}
