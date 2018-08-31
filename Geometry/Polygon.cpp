#define maxp 1000
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


/// Needed for min circle covering polygon
void find(int st,point tri[],circle &c){
    if (!st){
        c=circle(point(0,0),-2);
    }
    if (st==1){
        c=circle(tri[0],0);
    }
    if (st==2){
        c=circle((tri[0] - tri[1])/(2.0),tri[0].distance(tri[1])/2.0);
    }
    if (st==3){
        c = circle(tri[0],tri[1],tri[2]);
    }
}
/// Needed for min circle covering polygon
void solve(polygon P,int cur,int st,point tri[],circle &c){
    find(st,tri,c); // own
    if (st==3)return;
    int i;
    for (i=0; i<cur; i++){
        if(EQ(P.p[i].distance(c.p)-c.r) > 0){
            tri[st]=P.p[i];
            solve(P,i,st+1,tri,c); // own
        }
    }
}
circle mincircle(polygon P) //smallest circle which covers the polygon
{
    random_shuffle(P.p,P.p+P.n);
    point tri[4];
    circle c;
    solve(P,P.n,0,tri,c); // own
    return c;
}

/// Cut polygon by line(a,s)
polygon cutPolygon(polygon &po,point a,point s)
{
    point x,c;
    polygon ans;
    int in=0;
    line now(a,s);
    for(int q=0; q<po.n; q++)
    {
        x=po.p[q];
        c=po.p[(q+1)%po.n];

        /// x is On left
        if(turn(a,s,x)==1 || turn(a,s,x)==0)
        {
            ans.p[in]=x;
            in++;
        }
        /// line(x,c) intersects line(a,s)
        if(now.segmentIntersection(line(x,c)))
        {
            ans.p[in] = line(x,c).crosspoint(now);
            in++;
        }
    }
    ans.n=in;
    return ans;

//    polygon poly;
//    poly.add(point(0,0));
//    poly.add(point(0,h));
//    poly.add(point(w,h));
//    poly.add(point(w,0));
//
//    point fountain(x,y);
//
//    FOR(i,1,n)
//    {
//        point a,b;
//        cin >> a.x >> a.y >> b.x >> b.y;
//
//        if(turn(a, b, fountain) == 1)
//            poly = cutPolygon(poly, a, b);
//        else
//            poly = cutPolygon(poly, b, a);
//        FOR(j,0,poly.n-1) trace(poly.p[j].x, poly.p[j].y);
//    }
}

