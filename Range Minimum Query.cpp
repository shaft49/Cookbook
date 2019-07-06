///https://www.topcoder.com/community/data-science/data-science-tutorials/range-minimum-query-and-lowest-common-ancestor/
int arr[N];
int table[22][N], height;
void buildTable ( int n ) {
    ///Base Case
    for ( int i = 0; i < n; i++ ) {
        table[0][i] = arr[i];
        debug(arr[i]);
    }
    ///Current power of 2 is cur
    ///power of 2 for previous row is prev
    int cur = 2, prev = 1;
    for ( int i = 1; i < 22; i++ ) {
        if ( cur > n ) {
            height = i;
            break;
        }
        for ( int j = 0; j < n; j++ ) {
            int k = j + prev;
            if ( k >= n ) k = n - 1;
            table[i][j] = min ( table[i-1][j], table[i-1][k]);
        }

        cur *= 2;
        prev *= 2;///power of 2 ghor kore barbe preprocess er somoi
    }
}
int rmq ( int i, int j ) {
    int len = j - i + 1;
    int row = height;
    int two = power ( 2, height );
    while ( two > len ) {
        two /= 2;
        row--;
    }

    int res = min ( table[row][i], table[row][j-two+1] );
    return res;
}
