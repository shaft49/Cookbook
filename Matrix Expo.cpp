struct MAT{
    ll a[10][10];//Maximum dimension of the matrix
    int row, col;
    MAT(){}
    MAT(int r, int c){
        row = r, col = c, mem();
    }
    void assign ( int r, int c ) {
        row = r, col = c;
    }
    void identity(){
        mem();
        for ( int i = 0; i < row; i++ ) a[i][i] = 1;
    }
    void mem(){
        memset ( a, 0, sizeof a );
    }
    void print() { //For debugging purpose
        printf( "********\n");
        for ( int i = 0; i < row; i++ ){
            for ( int j = 0; j < col; j++ ) printf ( "%llu", a[i][j] );
            printf ( "\n" );
        }
    }
    MAT operator* (const MAT& other) const{
        int i, j, k;
		MAT res(row, other.col);
		long long x, y = mod * mod;
		for(i = 0; i < row; i++){
			for(j = 0; j < other.col; j++){
				for(k = 0, x = 0; k < col; k++){
					x += ((long long)a[i][k] * other.a[k][j]);
					if (x >= y) x -= y;
				}
                res.a[i][j] = x % mod;
			}
		}
		return res;
    }
    MAT operator + ( MAT b ) { //Matrix Summation
        MAT res ( row, b.col );
        for ( int i = 0; i < row; i++ ){
            for ( int j = 0; j < b.col; j++ ){
                    res.a[i][j] = ( a[i][j] + b.a[i][j] ) % mod; //Change here if no mod.
            }
        }
        return res;
    }
    MAT operator ^ ( ll p ) { //Matrix Exponentiation
        MAT res ( row, col ); res.identity();
        MAT x = *this;
        while ( p ){
            if ( p & 1 ) res = res * x;
            x = x * x;
            p >>= 1;
        }
        return res;
    }
};
/*
MAT init(2,1);
init.a[0][0] = 1;
init.a[1][0] = 1;
MAT coef(2,2);
coef.a[0][0] = 1; coef.a[0][1] = 1;
coef.a[1][0] = 1; coef.a[1][1] = 0;
MAT res = (coef^100) * init;
res.print();
*/
