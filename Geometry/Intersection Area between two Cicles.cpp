/*area of intersection between two circles*/
inline double intersectionArea2C(circle C1,circle C2){
    C2.center.x = Distance(C1.center,C2.center);
    C1.center.x = C1.center.y = C2.center.y = 0;
    if(C1.r < C2.center.x - C2.r + eps)return 0;
    if(-C1.r + eps > C2.center.x - C2.r)return pi*C1.r*C1.r;
    if(C1.r + eps > C2.center.x + C2.r)return pi*C2.r*C2.r;
    double c,CAD,CBD,res;
    c = C2.center.x;
    CAD = 2*acos((C1.r*C1.r+c*c-C2.r*C2.r)/(2*C1.r*c));
    CBD = 2*acos((C2.r*C2.r+c*c-C1.r*C1.r)/(2*C2.r*c));
    res = C1.r*C1.r*(CAD-sin(CAD))+C2.r*C2.r*(CBD-sin(CBD));
    return 0.5*res;
}
