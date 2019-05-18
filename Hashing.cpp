const long long HMOD[] = {2078526727, 2117566807};
const long long BASE[] = {1572872831, 1971536491};

struct stringhash{
    int len;
    vector <long long> P[2], H[2], R[2];

    stringhash(){}
    stringhash(string str){
        int i, j;
        len = str.size();

        for (i = 0; i < 2; i++){
            P[i].resize(len + 1, 0);
            H[i].resize(len + 1, 0), R[i].resize(len + 1, 0);
            for (P[i][0] = 1, j = 1; j <= len; j++) P[i][j] = (P[i][j - 1] * BASE[i]) % HMOD[i];

            H[i][0] = 0;
            for (j = 0; j < len; j++){
                H[i][j] = ((H[i][j] * BASE[i]) + str[j] + 1007) % HMOD[i];
                H[i][j + 1] = H[i][j];
            }

            R[i][len - 1] = 0;
            for (j = len - 1; j >= 0; j--){
                R[i][j] = ((R[i][j] * BASE[i]) + str[j] + 1007) % HMOD[i];
                if (j) R[i][j - 1] = R[i][j];
            }
        }
    }

    inline long long hash(int l, int r){
        long long ar[2];
        ar[0] = H[0][r], ar[1] = H[1][r];
        if (l){
            for (int i = 0; i < 2; i++){
                ar[i] -= ((P[i][r - l + 1] * H[i][l - 1]) % HMOD[i]);
                if (ar[i] < 0) ar[i] += HMOD[i];
            }
        }
        return (ar[0] << 32) ^ ar[1];
    }

    inline long long revhash(int l, int r){
        long long ar[2];
        ar[0] = R[0][l], ar[1] = R[1][l];
        if ((r + 1) < len){
            for (int i = 0; i < 2; i++){
                ar[i] -= ((P[i][r - l + 1] * R[i][r + 1]) % HMOD[i]);
                if (ar[i] < 0) ar[i] += HMOD[i];
            }
        }
        return (ar[0] << 32) ^ ar[1];
    }
};

