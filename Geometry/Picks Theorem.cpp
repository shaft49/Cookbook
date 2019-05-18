// Number of lattice points in polygon
// Picks Theorem :: A = I + B/2 - 1
// A = area of polygon , I =  the number of points (int) lying strictly inside the polygon
// B = number of points on the border( int co ordinate )
ll lattice_points(point a, point b){
    ll x = (ll)(b.x - a.x), y = (ll)(b.y - a.y);
    return llabs(__gcd(x, y)) + 1;
}
ll picksTheorem(polygon P) {
    double A = P.getArea();
    ll B = 0 ;
    int n = P.n;
    for( int i = 0, j = n - 1; i < n; j = i++ ){
        ll ret = lattice_points(P.p[i],P.p[j]);
        B += ret;
    }
    B -= n; // points of polygon will be added twice
    return (2.0 * A - B + 2)/2;
}
