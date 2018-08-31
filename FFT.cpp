FFT
#define MAX 262148 // 2 * Smallest power of 2 greater than MAXN, 2^18 when MAXN = 10^5
typedef complex <double> complx; // Replace double with long double if more precision is required
complx dp[MAX >> 1], P1[MAX], P2[MAX];
void FFT(complx *ar, int n, int inv){
    int i, j, l, len, len2;
    const double p = 4.0 * inv * acos(0.0);
    for (i = 1, j = 0; i < n; i++){
        for (l = n >> 1; j >= l; l >>= 1) j -= l;
        j += l;
        if (i < j) swap(ar[i], ar[j]);
    }
    for (len = 2; len <= n; len <<= 1){
        len2 = len >> 1;
        double theta = p / len;
        complx mul(cos(theta), sin(theta));
        dp[0] = complx(1, 0);
        for (i = 1; i < len2; i++) dp[i] = (dp[i - 1] * mul);
        for (i = 0; i < n; i += len){
            complx t, *pu = ar + i, *pv = ar + i + len2, *pend = ar + i + len2, *pw = dp;
            for (; pu != pend; pu++, pv++, pw++){
                t = (*pv) * (*pw);
                *pv = *pu - t;
                *pu += t;
            }
        }
    }
    if (inv == -1){
        for (i = 0; i < n; i++) ar[i] /= n;
    }
}
int multiply(int a, complx* A, int b, complx* B){
    int i, n, m = 1;
    n = a + b - 1;
    //m = 1 << (64 - __builtin_clz(n) - (__builtin_popcount(n) == 1));
    while(m < a*2 || m < b*2) m <<= 1;
    for (i = a; i < m; i++) A[i] = 0;
    for (i = b; i < m; i++) B[i] = 0;
    FFT(A, m, 1), FFT(B, m, 1);
    for (i = 0; i < m; i++) A[i] = A[i] * B[i];
    FFT(A, m, -1);
    return m;
}
// Multiplies two polynomials A and B and return the coefficients of their product in A
// Function returns degree of the polynomial A * B
int multiply(int a, ll* A, int b, ll* B){
    for (int i = 0; i < a; i++) P1[i] = complx(A[i], 0);
    for (int i = 0; i < b; i++) P2[i] = complx(B[i], 0);
    int degree = multiply(a, P1, b, P2);
    for (int i = 0; i < degree; i++) A[i] = floor(P1[i].real() + 0.5);
    return degree;
}
