///Sieve of Eratosthenes
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
/// Segmented Sieve
int p, primes[BASE_LEN];
unsigned int base[(BASE_MAX >> 6) + 5], isprime[(MAX >> 6) + 5];

void Sieve(){
    clr(base);
    int i, j, k;

    for (i = 3; i < BASE_SQR; i++, i++){
        if (!chkbit(base, i)){
            k = i << 1;
            for (j = (i * i); j < BASE_MAX; j += k){
                setbit(base, j);
            }
        }
    }

    p = 0;
    for (i = 3; i < BASE_MAX; i++, i++){
        if (!chkbit(base, i)){
            primes[p++] = i;
        }
    }
}

int SegmentedSieve(long long a, long long b){
    long long j, k, x;
    int i, d, counter = 0;

    if (a <= 2 && 2 <= b) counter = 1; /// 2 is counted separately if in range
    if (!(a & 1)) a++;
    if (!(b & 1)) b--;
    if (a > b) return counter;

    clr(isprime);
    for (i = 0; i < p; i++){
        x = primes[i];
        if ((x * x) > b) break;

        k = x << 1;
        j = x * ((a + x - 1) / x);
        if (!(j & 1)) j += x;
        else if (j == x) j += k;

        while (j <= b){
            setbit(isprime, j - a);
            j += k;
        }
    }

    /// Other primes in the range except 2 are added here
    d = (b - a + 1);
    for (i = 0; i < d; i++, i++){
        if (!chkbit(isprime, i) && (a + i) != 1) counter++;
    }

    return counter;
}

/// Bit wise sieve
/*
no storage for even number, memory reduced to half
single bit of 32 bit is used to store state of a number
*/
#define chkbit(ar, i) (((ar[(i) >> 6]) & (1 << (((i) >> 1) & 31))))
#define setbit(ar, i) (((ar[(i) >> 6]) |= (1 << (((i) >> 1) & 31))))
#define isprime(x) (( (x) && ((x)&1) && (!chkbit(ar, (x)))) || ((x) == 2))
#define LEN 1000000
int p, prime[LEN]; //Resize LEN accordingly after calculating the max value of p
unsigned int ar[(N >> 6) + 5] = {0};

void sieve(int n){
    int i, j, k;
    setbit(ar, 0), setbit(ar, 1);
    // i * i might overflow, take care
    for (i = 3; (i * i) <= n; i++, i++){
        if (!chkbit(ar, i)){
            k = i << 1;
            for (j = (i * i); j <= n; j += k) setbit(ar, j);
        }
    }

    p = 0;
    prime[p++] = 2;
    for (i = 3; i <= n; i++, i++){
        if (isprime(i)) prime[p++] = i;
    }
}

///Number of distinct prime factors of a number
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

///Extended Euclidean Algorithm
//Iterative
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
//Recursive
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
/// Modular Inverse
ll mod_inverse(ll a, ll m){
    /// inverse exists if and only if a and m are co-prime
    ll x, y, inv;
    ext_gcd(a, m, x, y);
    inv = (x + m) % m;
    return inv;
}
/// Modular Inverse from 1 to n;
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
