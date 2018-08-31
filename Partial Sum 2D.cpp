void update(int xl, int yl, int xr, int yr, int val){
    //xl <= xr, yl <= yr;
    ++yr, ++xr;
    table[xl][yl] += val;
    table[xr][yl] -= val;
    table[xl][yr] -= val;
    table[xr][yr] += val;
}
void query(){
    //n = row + 1, m = col + 1;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            table[i][j + 1] += table[i][j];
    for(int j = 0; j < m; j++)
        for(int i = 0; i < n; i++)
            table[i + 1][j] += table[i][j];
}
