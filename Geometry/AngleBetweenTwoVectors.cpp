///Printed
long double angle(point a){
    ///One point will be in the origin
    long double ang = atan2(a.y,a.x);
    if(ang < 0)
        ang += 2*pi;
    return ang*180/pi;
}
long double AngleBetweenVectors(point O, point A, point B){
    point t1, t2;
    t1.x = A.x - O.x; t1.y = A.y - O.y;
    t2.x = B.x - O.x; t2.y = B.y - O.y;
    long double d1 = angle(t1);
    long double d2 = angle(t2);
    long double ang = abs(d2-d1);
    ang = min(ang,360-ang);
    return ang;
}
