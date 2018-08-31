int expo(long long x, int n, int m){
    long long res = 1;
    while (n){
        if (n & 1) res = (res * x) % m;
        x = (x * x) % m;
        n >>= 1;
    }
    return (res % m);
}

int extended_gcd(int a, int b, int& x, int& y){
    // Bezout's identity, ax + by = gcd(a,b)
    if (!b){
        y = 0, x = 1;
        return a;
    }
    int g = extended_gcd(b, a % b, y, x);
    y -= ((a / b) * x);
    return g;
}

int inverse_modulo(int a, int m){
    // inverse exists if and only if a and m are co-prime
    int x, y, inv;
    extended_gcd(a, m, x, y);
    inv = (x + m) % m;
    return inv;
}

int discrete_log(int g, int h, int p){
    /*
     * returns smallest x such that (g^x) % p = h % p, -1 if none exists
     * p must be a PRIME
     * function returns x, the discrete log of h with respect to g modulo p
     */
    g %= p, h %= p;
    if (g == 0){
        if(h == 0) return 1;
        if (h == 1) return 0;
        else return -1;
    }
    unordered_map <int, int> mp;
    int i, q, r, m = ceil(sqrt(p)); // sqrtl for large number
    long long d = 1, inv = expo(inverse_modulo(g, p), m, p);

    for (i = 0; i <= m; i++){
        if (!mp[d]) mp[d] = i + 1;
        d *= g;
        if (d >= p) d %= p;
    }

    d = h;
    for (q = 0; q <= m; q++){
        r = mp[d];
        if (r) return ((m * q) + (--r));
        d *= inv;
        if (d >= p) d %= p;
    }
    return -1;
}
