double ternarySearch(double left,double right){
    for(int i = 1; i <= 500; i++){
        double mid1 = left + (right-left) / 3.0, mid2 = left + 2*(right-left)/3;
        if(func(mid1) < func(mid2)) right = mid2;
        else left = mid1;
    }
    return (left + right)/2.0;
    //you might want to check left, right, (left+right)/2 for optimal ans
}

//Ternary search on integers
int lo = -1, hi = n;
while (hi - lo > 1){
    int mid = (hi + lo)>>1;
    if (f(mid) > f(mid + 1))
         hi = mid;
    else
         lo = mid;
}
// lo + 1 is the answer, or you can make the condition hi - lo > 5
// and iterate from lo to hi using for loop, be careful about invalid case in for loop
