const double eps=1e-11;
const double pi=2*acos(0.0);
#define sz(x) ((int)(x).size())
#define dot(a,b) ((conj(a)*(b)).real())
#define cross(a,b) ((conj(a)*(b)).imag())
#define X real()
#define Y imag()
#define length(a) hypot((a).real(),(a).imag())
#define length2(a) dot(a,a)
#define normalize(a) ((a)/length(a))
#define polar(r,theta) (r)*exp(point(0,theta))
#define vect(p1,p2) ((p2)-(p1))
#define mid(p1,p2)  ((p1)+(p2))/point(2,0)
#define same(a,b) (length2(vect(a,b))<EPS)
#define angle(a) atan2((a).imag(),(a).real())
typedef complex<double> point;
point getP( double m ) {
	return vect( p1, p2 ) * m + p1; ///returns a point in a line segment between point p1,p2
}
///i,j,k are indexes of three points
bool colinear(int i,int j,int k)
{
    ll area=1LL*(arr[i].x-arr[j].x)*(arr[k].y-arr[j].y)-1LL*(arr[k].x-arr[j].x)*(arr[i].y-arr[j].y);
    return area==0;
}
struct point{
    double x,y;
    point(){}
    point(double xx,double yy){
        x=xx;y=yy;
    }
};
struct circle{
    point center;
    double r;
    circle(){}
    circle(point P,double rr)
    {
        center=P;
        r=rr;
    }
};
inline double Distance(point  a,point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
struct vect{
    double x,y,z;
    vect(){}
    vect(double xx,double yy,double zz){
        x=xx;y=yy;z=zz;
    }
};
vect normalize(vect a){
    double nor=sqrt(a.x*a.x+a.y*a.y+a.z*a.z);
    a.x/=nor;a.y/=nor;a.z/=nor;
    return a;
}
double dot_prod(vect a,vect b){
    a.x*=b.x;a.y*=b.y;a.z*=b.z;
    return a.x+a.y+a.z;
}
vect cross_prod(vect a,vect b){
    vect v;
    v.x=a.y*b.z-a.z*b.y;
    v.y=-a.x*b.z+a.z*b.x;
    v.z=a.x*b.y-a.y*b.x;
    return v;
}
///Check two vectors are same or not
bool same_vector(int i,int j){
    ///i,j are position in array
    ll x1y2=arr[i].x*arr[j].y;
    ll x2y1=arr[i].y*arr[j].x;
    ll x2y3=arr[i].y*arr[j].z;
    ll x3y2=arr[i].z*arr[j].y;
    ll x1y3=arr[i].x*arr[j].z;
    ll x3y1=arr[i].z*arr[j].x;
    ///if two vectors are parallel then they are same
    ///if they are parallel then cross product will be 0i+0j+0k
    debug(x1y2,x2y1,x2y3,x3y2,x1y3,x3y1)
    return (x1y2==x2y1 && x2y3==x3y2 && x1y3==x3y1);
}
///ternarySearch()
double ternarySearch(double left,double right)
{
    for(int i=1;i<=500;i++)
    {
        double mid1=left+(right-left)/3.0,mid2=left+2*(right-left)/3;
        if(func(mid1)<func(mid2))
            right=mid2;
        else
            left=mid1;
        //debug(left,right)
    }
    return (left+right)/2.0;
}
bool eq(double a,double b){
    if(abs(a-b)<eps)return true;
    return false;
}

struct line { // Creates a line with equation ax + by + c = 0
	double a, b, c;
	line() {}
	line( point p1,point p2 ) {
		a = p1.y - p2.y;
		b = p2.x - p1.x;
		c = p1.x * p2.y - p2.x * p1.y;
	}
};
struct segment { // Creates a segment with two end points -> A, B
	point A, B;
	segment() {}
	segment( point P1, point P2 ) { A = P1, B = P2; }
};

///intersection : line-line
inline bool intersection( line L1, line L2, point &p ) {
	double det = L1.a * L2.b - L1.b * L2.a;
	if( eq ( det, 0 ) ) return false;
	p.x = ( L1.b * L2.c - L2.b * L1.c ) / det;
	p.y = ( L1.c * L2.a - L2.c * L1.a ) / det;
	return true;
}
///intersection : segment-segment
inline bool intersection( segment L1, segment L2, point &p ) {
	if( !intersection( line( L1.A, L1.B ), line( L2.A, L2.B ), p) ) {
		return false; // can lie on another, just check their equations, and check overlap
	}
	return(eq(Distance(L1.A,p)+Distance(L1.B,p),Distance(L1.A,L1.B)) &&
		eq(Distance(L2.A,p)+Distance(L2.B,p),Distance(L2.A,L2.B)));
}
