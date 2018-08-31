#define RAD(x) ((x*PI)/180)
const double PI=acos(-1.0), EPS = 1e-12;

class PT {
public:
    double x, y;
    PT() {}
    PT(double x, double y) : x(x), y(y) {}
    PT(const PT &p) : x(p.x), y(p.y)    {}
    double Magnitude() {return sqrt(x*x+y*y);}
    PT operator + (const PT &p)  const { return PT(x+p.x, y+p.y); }
    PT operator - (const PT &p)  const { return PT(x-p.x, y-p.y); }
    PT operator * (double c)     const { return PT(x*c,   y*c  ); }
    PT operator / (double c)     const { return PT(x/c,   y/c  ); }
    bool operator < (const PT &p) const {return x == p.x ? y <= p.y : x <= p.x;}
};

double dot(PT p, PT q)     { return p.x*q.x+p.y*q.y; }
double dist2(PT p, PT q)   { return dot(p-q,p-q); }
double dist(PT p, PT q)   { return sqrt(dist2(p,q)); }
double cross(PT p, PT q)   { return p.x*q.y-p.y*q.x; }

// project point c onto line through a and b
// assuming a != b
PT ProjectPointLine(PT a, PT b, PT c) {
    return a + (b-a)*dot(c-a, b-a)/dot(b-a, b-a);
}

double DistancePointSegment(PT a,PT b,PT c) {
    if (b < a) swap(a, b);
    PT on = ProjectPointLine(a, b, c);
    if (a < on && on < b) return dist(c, on);
    else
    {
        double ht = dist(c, on);
        double bs = min(dist(a, on), dist(b, on));
        return sqrt(ht*ht + bs*bs);
    }
}

double mindist(vector <PT> &a, vector <PT> &b)
{
    int i, j, k;
    double minn = inf;

    for (i=1; i<a.size(); i++)
    {
        for (j=1; j<b.size(); j++)
        {
            double atob = min(DistancePointSegment(a[i], a[i-1], b[j]), DistancePointSegment(a[i], a[i-1], b[j-1]));
            double btoa = min(DistancePointSegment(b[j], b[j-1], a[i]), DistancePointSegment(b[j], b[j-1], a[i-1]));
            minn = min(minn, min(atob, btoa));
        }
    }

    return minn;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("C:\\Users\\Dell\\Desktop\\in.txt", "r", stdin);
//    freopen("C:\\Users\\Dell\\Desktop\\in.txt", "w", stdout);
#endif
    ios_base::sync_with_stdio(false);

    int t, cs = 0;
    int n, m, i, j, k, x, y;

    in(t);
    while (t--)
    {
        vector <PT> a, b;

        in(n);
        for (i=0; i<n; i++) in2(x, y), a.pb(PT(x, y));
        in(m);
        for (i=0; i<m; i++) in2(x, y), b.pb(PT(x, y));

        a.pb(a[0]);
        b.pb(b[0]);

        printf("Case %d: %.9f\n", ++cs, mindist(a, b)/2.0);
    }


return 0;
}
