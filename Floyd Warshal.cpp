void FloydWarshal(int n){
    for(int k=1; k <= n; k++){
        for(int i=1; i <= n; i++){
            for(int j=1; j <= n; j++){
                if(mat[i][j] > mat[i][k] + mat[k][j])
                    mat[i][j] = mat[i][k] + mat[k][j];
            }
        }
    }
}
