// Weak Form of CRT, mod value must be pairwise co prime
//Zahin Bhai
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

ll mod_inverse(ll a, ll m){
    /// inverse exists if and only if a and m are co-prime

    ll x, y, inv;
    ext_gcd(a, m, x, y);
    inv = (x + m) % m;
    return inv;
}

ll CRT(int n, ll* ar, ll* mods){
    /// finds the unique solution x modulo M (product of mods) for which x % mods[i] = ar[i]
    /// mods must be pairwise co-prime

    int i, j;
    ll x, y, res = 0, M = 1;

    for (i = 0; i < n; i++) M *= mods[i];
    for (i = 0; i < n; i++){
        x = M / mods[i];
        y = mod_inverse(x, mods[i]);
        res = (res + (((x * ar[i]) % M) * y)) % M;
    }

    return res;
}

// Samiul Bhai
// Strong Form of CRT
/**
    A CRT solver which works even when moduli are not pairwise co prime
    1. Add equations using addEquation() method
    2. Call solve() to get {x, N} pair, where x is the unique solution modulo N.
    Assumptions:
        1. LCM of all mods will fit into long long.
*/
class ChineseRemainderTheorem {
    typedef pair<ll, ll> pll;

    /** CRT Equations stored as pairs of vector. See addEqation()*/
    vector<pll> equations;

public:
    void clear() {
        equations.clear();
    }

    /** Add equation of the form x = r (mod m)*/
    void addEquation( ll r, ll m ) {
        equations.push_back({r, m});
    }
    pll solve() {
        if (equations.size() == 0) return {-1,-1}; /// No equations to solve

        ll a1 = equations[0].first;
        ll m1 = equations[0].second;
        a1 %= m1;
        /** Initially x = a_0 (mod m_0)*/

        /** Merge the solution with remaining equations */
        for ( int i = 1; i < equations.size(); i++ ) {
            ll a2 = equations[i].first;
            ll m2 = equations[i].second;

            ll g = __gcd(m1, m2);
            if ( a1 % g != a2 % g ) return {-1,-1}; /// Conflict in equations

            /** Merge the two equations*/
            ll p, q;
            ext_gcd(m1/g, m2/g, p, q);

            ll mod = m1 / g * m2;
            ll x = ( (__int128)a1 * (m2/g) % mod *q % mod + (__int128)a2 * (m1/g) % mod * p % mod ) % mod;

            /** Merged equation*/
            a1 = x;
            if ( a1 < 0 ) a1 += mod;
            m1 = mod;
        }
        return {a1, m1};
    }
};
