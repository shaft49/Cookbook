int EQ(double d) {
    if ( fabs(d) < EPS ) return 0;
    return d > EPS ? 1 : -1 ;
}
inline double sqr(double x) {
    return x*x;
}
struct point {
    double x,y;
    point() {}
    point(double _x,double _y) : x(_x),y(_y) {};
    point PolarTOCartesian(double R, double theta){
        double mul = PI / 180.0;
        point P;
        P.x = R * cos(theta * mul);
        P.y = R * sin(theta * mul);
        return P;
    }
    bool operator == (point a)const {
        return EQ(a.x-x)==0&&EQ(a.y-y)==0;
    }
    bool operator<(point a)const {
        return EQ(a.x-x)==0?EQ(y-a.y)<0:x<a.x;
    }
    double len() {
        return hypot(x,y);
    }
    double len2() {
        return x*x+y*y;
    }
    /// Eucladian distance
    double distance(point p) {
        return hypot(x-p.x,y-p.y);
    }
    point add(point p) {
        return point(x+p.x,y+p.y);
    }
    point operator+(const point &p) const {
        return point(x+p.x,y+p.y);
    }
    point sub(point p) {
        return point(x-p.x,y-p.y);
    }
    point operator-(const point &p) const {
        return point(x-p.x,y-p.y);
    }
    point mul(double b) {
        return point(x*b,y*b);
    }
    point operator*(double b) const {
        return point(x*b,y*b);
    }
    point div(double b) {
        return point(x/b,y/b);
    }
    point operator/(double b) const {
        return point(x/b,y/b);
    }
    double dot(point p) {
        return x*p.x+y*p.y;
    }
    double cross(point p) {
        return x*p.y-y*p.x;
    }
    double rad(point a,point b) {
        point p=*this;
        return fabs(atan2(fabs(a.sub(p).cross(b.sub(p))),a.sub(p).dot(b.sub(p))));
    }
    //Creates a new point from origin(0,0) of r distance which is co-linear to (0,0) and current point
    point trunc(double r) {
        double l=len();
        if (!EQ(l))return *this;
        r/=l;
        return point(x*r,y*r);
    }
    ///rotate this point counter clockwise on the basis of point p
    point rotate(point p,double angle) {
        point v=this->sub(p);
        double c=cos(angle),s=sin(angle);
        return point(p.x+v.x*c-v.y*s,     p.y+v.x*s+v.y*c);
    }
    point rotleft() {
        return point(-y,x);
    }
    point rotright() {
        return point(y,-x);
    }
    // Point in rectangle or not
    // rectangle : a = leftDown , b = rightTop , c is in the rectangle or not
    // remove = (equal sign) in return condition if strictly in box needed
    bool in_box(point a,point b) {
        point c = *this;
        double lox = min(a.x, b.x), hix = max(a.x, b.x);
        double loy = min(a.y, b.y), hiy = max(a.y, b.y);
        return c.x >= lox && c.x <= hix && c.y >= loy && c.y <= hiy;
    }
};

/// -1 -> Right Turn
///  1 -> Left Turn
///  0 -> Straight Line / Co-linear
int turn( point O , point A , point B) { //
    double res = (A.x - O.x) * (B.y - O.y) - (A.y - O.y) * (B.x - O.x);
    if( res < 0 ) return -1 ; // O->A->B is a right turn
    if( res > 0 ) return  1 ; // O->A->B is a left turn
    return 0; // O->A->B is a straight line / co-linear
}
//Find if C is between A and B or B and A
bool pointBetween ( point a, point b, point c ) {
    if ( min(a.x,b.x) <= c.x && c.x <= max(a.x,b.x) && min(a.y,b.y) <= c.y && c.y <= max(a.y,b.y) ) return true;
    else return false;
}
struct line {
    point a,b;
    line() {}
    line(point _a,point _b) {
        a=_a;
        b=_b;
    }
    bool operator==(line v) {
        return (a==v.a)&&(b==v.b);
    }
    ///inclination angle
    /// The angle between the line and x-axis,
    line(point p,double angle) {
        a=p;
        if (EQ(angle-PI/2)==0) {
            b=a.add(point(0,1));
        } else {
            b=a.add(point(1,tan(angle)));
        }
    }
    /// ax+by+c=0
    line(double _a,double _b,double _c) {
        if (EQ(_a)==0) {
            a=point(0,-_c/_b);
            b=point(1,-_c/_b);
        } else if (EQ(_b)==0) {
            a=point(-_c/_a,0);
            b=point(-_c/_a,1);
        } else {
            a=point(0,-_c/_b);
            b=point(1,(-_c-_a)/_b);
        }
    }
    void adjust() {
        if (b<a)swap(a,b);
    }
    double length() {
        return a.distance(b);
    }
    //point D creates a ration of m : n in AB line, AD : DB = m : n
    point section(point A, point B, double m, double n){
        point D;
        D.x = (B.x * m+ A.x * n) / (m + n);
        D.y = (B.y * m + A.y * n) / (m + n);
        return D;
    }
    /// Straight tilt(inclination angle) angle 0 <= angle <180
    double angle() {
        double k=atan2(b.y-a.y,b.x-a.x);
        if (EQ(k)<0)k+=PI;
        if (EQ(k-PI)==0)k-=PI;
        return k;
    }
    /** Points and line segments between
         1 Counter clockwise
         2 in a clockwise
         3 parallel
    **/
    int relation(point p) {
        int c=EQ(p.sub(a).cross(b.sub(a)));
        if (c<0)return 1;
        if (c>0)return 2;
        return 3;
    }
    bool pointonseg(point p) {
        return EQ(p.sub(a).cross(b.sub(a)))==0&&EQ(p.sub(a).dot(p.sub(b)))<=0;
    }
    bool parallel(line v) {
        return EQ(b.sub(a).cross(v.b.sub(v.a)))==0;
    }
    /*
     2 norms intersect
     1 non-standard intersection
     0 disjoint / not intersect
    */
    /// If the point is int / ll use the below one, in the last of this page
    /// P1, p2 makes first segment, p3, p4 makes the second segment
    bool segmentIntersection ( line l ) {
        point c = l.a;
        point d = l.b;
        ll s1 = turn( a, b, c );
        ll s2 = turn( a, b, d );
        ll s3 = turn( c, d, a );
        ll s4 = turn( c, d, b );

        if(s1 != s2 && s3 != s4) return true;
        if ( s1 == 0 && pointBetween ( a, b, c ) ) return true;
        else if ( s2 == 0 && pointBetween ( a, b, d ) ) return true;
        else if ( s3 == 0 && pointBetween ( c, d, a ) ) return true;
        else if ( s4 == 0 && pointBetween ( c, d, b ) ) return true;

        return false;
    }
    int linecrossseg(line v) { //*this seg,  v line
        int d1=EQ(b.sub(a).cross(v.a.sub(a)));
        int d2=EQ(b.sub(a).cross(v.b.sub(a)));
        if ((d1^d2)==-2)return 2;
        return (d1==0||d2==0);
    }
    /**
        0 Parallel
        1 coincides
        2 intersect
    **/
    int linecrossline(line v) {
        if ((*this).parallel(v)) {
            return v.relation(a)==3;
        }
        return 2;
    }

    point crosspoint(line v) {
        double a1=v.b.sub(v.a).cross(a.sub(v.a));
        double a2=v.b.sub(v.a).cross(b.sub(v.a));
        return point((a.x*a2-b.x*a1)/(a2-a1),(a.y*a2-b.y*a1)/(a2-a1));
    }
    double dispointtoline(point p) {
        return fabs(p.sub(a).cross(b.sub(a)))/length();
    }
    /// To get only the minimum distance
    double dispointtoseg(point p) {
        if (EQ(p.sub(b).dot(a.sub(b)))<0||EQ(p.sub(a).dot(b.sub(a)))<0) {
            return min(p.distance(a),p.distance(b));
        }
        return dispointtoline(p);
    }
    /// To get the minimum distance & point call it
    double dispointtoseg(point p, point &res) {
        if (EQ(p.sub(b).dot(a.sub(b)))<0||EQ(p.sub(a).dot(b.sub(a)))<0) {
            double pa = p.distance(a);
            double pb = p.distance(b);
            if(pa+EPS < pb)
            {
                res = a;
                return pa;
            }
            else
            {
                res = b;
                return pb;
            }
        }
        res = lineprog(p);
        return dispointtoline(p);
    }
    /// Intersection point between Perpendicular line from p and this line
    /// Have to check before if there is any intersection or not
    point lineprog(point p) {
        return a.add(b.sub(a).mul(b.sub(a).dot(p.sub(a))/b.sub(a).len2()));
    }
    point symmetrypoint(point p) {
        point q=lineprog(p);
        return point(2*q.x-p.x,2*q.y-p.y);
    }
};
struct circle {
    point p;
    double r;
    circle() {}
    circle(point _p,double _r):
        p(_p),r(_r) {};
    circle(double x,double y,double _r):
        p(point(x,y)),r(_r) {};
    circle(point a,point b,point c) { //Circumcircle of triangle
        p=line(a.add(b).div(2),a.add(b).div(2).add(b.sub(a).rotleft())).crosspoint(line(c.add(b).div(2),c.add(b).div(2).add(b.sub(c).rotleft())));
        r=p.distance(a);
    }
    circle(point a,point b,point c,bool t) { //Triangle inscribed circle
        line u,v;
        double m=atan2(b.y-a.y,b.x-a.x),n=atan2(c.y-a.y,c.x-a.x);
        u.a=a;
        u.b=u.a.add(point(cos((n+m)/2),sin((n+m)/2)));
        v.a=b;
        m=atan2(a.y-b.y,a.x-b.x),n=atan2(c.y-b.y,c.x-b.x);
        v.b=v.a.add(point(cos((n+m)/2),sin((n+m)/2)));
        p=u.crosspoint(v);
        r=line(a,b).dispointtoseg(p);
    }
    bool operator==(circle v) {
        return ((p==v.p)&&EQ(r-v.r)==0);
    }
    bool operator<(circle v)const {
        return ((p<v.p)||(p==v.p)&&EQ(r-v.r)<0);
    }
    double area() {
        return PI*sqr(r);
    }
    double circumference() {
        return 2*PI*r;
    }
    /// 0 outside the circle
    /// 1 on the circle
    /// 2 inside the circle
    int relation(point b) {
        double dst=b.distance(p);
        if (EQ(dst-r)<0)return 2;
        if (EQ(dst-r)==0)return 1;
        return 0;
    }
    int relationseg(line v) {
        double dst=v.dispointtoseg(p);
        if (EQ(dst-r)<0)return 2;
        if (EQ(dst-r)==0)return 1;
        return 0;
    }
    int relationline(line v) {
        double dst=v.dispointtoline(p);
        if (EQ(dst-r)<0)return 2;
        if (EQ(dst-r)==0)return 1;
        return 0;
    }
    /// Relation between 2 circles
    // 5 way off / are away from
    // 4 circumscribed /outer cutting
    // 3 intersect
    // 2-cut inside/inscribed
    // 1 contains / includes
    int relationcircle(circle v) {
        double d=p.distance(v.p);
        if (EQ(d-r-v.r)>0)return 5;
        if (EQ(d-r-v.r)==0)return 4;
        double l=fabs(r-v.r);
        if (EQ(d-r-v.r)<0&&EQ(d-l)>0)return 3;
        if (EQ(d-l)==0)return 2;
        if (EQ(d-l)<0)return 1;
    }

    /// if circle are intersect
    int pointcrosscircle(circle v,point &p1,point &p2) {
        int rel=relationcircle(v);
        if (rel==1||rel==5)return 0;
        double d=p.distance(v.p);
        double l=(d+(sqr(r)-sqr(v.r))/d)/2;
        double h=sqrt(sqr(r)-sqr(l));
        p1=p.add(v.p.sub(p).trunc(l).add(v.p.sub(p).rotleft().trunc(h)));
        p2=p.add(v.p.sub(p).trunc(l).add(v.p.sub(p).rotright().trunc(h)));
        if (rel==2||rel==4) {
            return 1;
        }
        return 2;
    }
    // Too little to do tangent to the circle (point and circle first crossermine the relationship)
    int tangentline(point q,line &u,line &v) {
        int x=relation(q);
        if (x==2)return 0;
        if (x==1) {
            u=line(q,q.add(q.sub(p).rotleft()));
            v=u;
            return 1;
        }
        double d=p.distance(q);
        double l=sqr(r)/d;
        double h=sqrt(sqr(r)-sqr(l));
        u=line(q,p.add(q.sub(p).trunc(l).add(q.sub(p).rotleft().trunc(h))));
        v=line(q,p.add(q.sub(p).trunc(l).add(q.sub(p).rotright().trunc(h))));
        return 2;
    }
    /// circle circle intersection area
    double areacircle(circle v) {
        int rel=relationcircle(v);
        if (rel>=4)return 0.0;
        if (rel<=2)return min(area(),v.area());
        double d=p.distance(v.p);
        double hf=(r+v.r+d)/2.0;
        double ss=2*sqrt(hf*(hf-r)*(hf-v.r)*(hf-d));
        double a1=acos((r*r+d*d-v.r*v.r)/(2.0*r*d));
        a1=a1*r*r;
        double a2=acos((v.r*v.r+d*d-r*r)/(2.0*v.r*d));
        a2=a2*v.r*v.r;
        return a1+a2-ss;
    }
    /// Circle Intersection Area
    /*
    This code assumes the circle center and radius to be integer.
    Change this when necessary.
    */
    inline double commonArea(const circle &b) {
        int dsq = p.distance(b.p);
        double d = sqrt((double)dsq);
        if(sqr(r + b.r) <= dsq) return 0;
        if(r >= b.r && sqr(r-b.r) >= dsq) return PI * b.r * b.r;
        if(r <= b.r && sqr(b.r-r) >= dsq) return PI * r * r;
        double angleA = 2.0 * acos((r * r + dsq - b.r * b.r) / (2.0 * r * d));
        double angleB = 2.0 * acos((b.r * b.r + dsq - r * r) / (2.0 * b.r * d));
        return 0.5 * (r * r * (angleA - sin(angleA)) + b.r * b.r * (angleB - sin(angleB)));
    }

    /// needed for polygon
    int pointcrossline(line v,point &p1,point &p2)
    {
        if (!(*this).relationline(v))return 0;
        point a=v.lineprog(p);
        double d=v.dispointtoline(p);
        d=sqrt(r*r-d*d);
        if (EQ(d)==0)
        {
            p1=a;
            p2=a;
            return 1;
        }
        p1=a.sub(v.b.sub(v.a).trunc(d));
        p2=a.add(v.b.sub(v.a).trunc(d));
        return 2;
    }
    double areatriangle(point a,point b){
        if (EQ(p.sub(a).cross(p.sub(b))==0))return 0.0;
        point q[5];
        int len=0;
        q[len++]=a;
        line l(a,b);
        point p1,p2;
        if (pointcrossline(l,q[1],q[2])==2)
        {
            if (EQ(a.sub(q[1]).dot(b.sub(q[1])))<0)q[len++]=q[1];
            if (EQ(a.sub(q[2]).dot(b.sub(q[2])))<0)q[len++]=q[2];
        }
        q[len++]=b;
        if (len==4&&(EQ(q[0].sub(q[1]).dot(q[2].sub(q[1])))>0))swap(q[1],q[2]);
        double res=0;
        int i;
        for (i=0;i<len-1;i++){
            if (relation(q[i])==0||relation(q[i+1])==0){
                double arg=p.rad(q[i],q[i+1]);
                res+=r*r*arg/2.0;
            }
            else{
                res+=fabs(q[i].sub(p).cross(q[i+1].sub(p))/2.0);
            }
        }
        return res;
    }
};

#define maxp 200010
//If size is large declare array as global
struct polygon{
    int n;
    point p[maxp];
    line l[maxp];
    polygon(){
        n = 0;
    }
    void add(point q){
        p[n++] = q;
    }
    void getline(){
        for (int i = 0; i < n; i++){
            l[i] = line( p[i] , p[(i+1)%n] );
        }
    }

    /**
                    বিন্দুটা পলিগন এর কোথায় আছে তা return করে
                    3 পলিগনের একটা বিন্দু
                    2 পলিগন এর লাইন এর উপর অবস্থিত
                    1 পলিগন এর ভিতরে অবস্থিত
                    0 পলিগন এর বাইরে অবস্থিত
    **/
    int relationpoint(point q){
        int i,j;
        for (i=0; i<n; i++){
            if (p[i]==q)return 3;
        }
        getline();
        for (i=0; i<n; i++){
            if (l[i].pointonseg(q))return 2;
        }
        int cnt=0;
        for (i=0; i<n; i++){
            j=(i+1)%n;
            point a = q - p[j];
            point b = p[i] - p[j];
            int k=EQ(a.cross(b));
            int u=EQ(p[i].y-q.y);
            int v=EQ(p[j].y-q.y);
            if (k>0&&u<0&&v>=0)cnt++;
            if (k<0&&v<0&&u>=0)cnt--;
        }
        return cnt!=0;
    }

    /// convex or concave
    bool isconvex(){
        bool s[3];
        memset(s,0,sizeof(s));
        int i,j,k;
        for (i = 0; i < n ; i++){
            j = (i+1)%n;
            k = (j+1)%n;
            point a = p[j] - p[i];
            point b = p[k] - p[i];
            s[ EQ ( a.cross(b) ) + 1 ] = 1;
            if ( s[0] && s[2] )return 0;
        }
        return 1;
    }
    ///Return Circumference of polygon
    double getcircumference(){
        double sum=0;
        for (int i=0; i<n; i++){
            sum += p[i].distance(p[(i+1)%n]);
        }
        return sum;
    }
    ///Return area of Polygon
    double getArea(){
        double sum=0;
        int i;
        for (i=0; i<n; i++){
            sum += p[i].cross(p[(i+1)%n]);
        }
        return fabs(sum)/2;
    }
    ///পলিগন এর বিন্দুগুলা clock wise order(1) না anti clock wise order(0) এ আছে তা return করে
    bool getDirection(){
        double sum=0;
        int i;
        for (i=0; i<n; i++){
            sum += p[i].cross(p[(i+1)%n]);
        }
        if (EQ(sum)>0)return 1;
        return 0;
    }
    ///return intersection area of polygon and circle
    double areacircle(circle c){
        int i,j,k,l,m;
        double ans=0;
        for (i=0; i<n; i++){
            int j=(i+1)%n;
            point a = p[j] - c.p;
            point b = p[i] - c.p;
            if (EQ(a.cross(b))>=0){
                ans+= c.areatriangle(p[i],p[j]);
            }
            else{
                ans-= c.areatriangle(p[i],p[j]);
            }
        }
        return fabs(ans);
    }
    /// returns center of polygon / convex
    point centerPoly(){
        double area = getArea();
        double factor = 1.0 / (6 * area);
        double cx = 0, cy = 0;
        int i,sz = n;
        for( i = 0 ; i < sz ; i++){
            point cur = p[i] , next = p[(i + 1) % sz];
            cx += (cur.x + next.x) * (cur.x * next.y - cur.y * next.x);
            cy += (cur.y + next.y) * (cur.x * next.y - cur.y * next.x);
        }
        cx *= factor;
        cy *= factor;
        return point(cx, cy);
    }
    /// strictly should be true if p needs to be strictly contained on the polygon
    /// not on the edges
    bool containsInPoly(point P, bool strictly){
        int mid, low = 1, high = n-1, idx = 1;
        while(low <= high){
            mid = (low + high) >> 1;
            if(turn(p[0], P, p[mid]) > 0) low = mid + 1;
            else idx = mid, high = mid - 1;
        }
        if(!strictly && line(p[0], p[n-1]).pointonseg(P)) return true;
        if(!strictly && line(p[idx], p[idx-1]).pointonseg(P)) return true;
        if(idx == 1 || turn(p[0], P, p[n-1]) == 0) return false;
        return (turn(p[idx], P, p[idx-1]) < 0);
    }
    /// If a line intersects polygon or not
    bool intersects(line li){
        getline();
        for(int i = 0; i < n; i++){
            if(li.segmentIntersection(l[i]))
                return true;
        }
        for(int i = 0; i < n; i++){
            if(l[i].pointonseg(li.a) || l[i].pointonseg(li.b))
                return true;
        }
        if(relationpoint(li.a)==1 || relationpoint(li.b)==1)
            return true;
        return false;
    }
};
