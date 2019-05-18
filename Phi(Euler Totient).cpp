//Use one of these, run time is almost same
int phi[N];
void Totient(int n){
    CLR(phi);
    int i, j, x;
    for (i = 1; i <= n; i++){
        phi[i] += i;
        for (j = (i << 1); j <= n; j += i){
            phi[j] -= phi[i];
        }
    }
}

void Totient(int n){
    CLR(phi);
    int i, j, x;
    phi[1] = 1;
    for (i = 2; i <= n; i++){
        if (!phi[i]){
            phi[i] = i - 1;
            for (j = (i << 1); j <= n; j += i){
                x = phi[j];
                if (!x) x = j;
                x = (x / i) * (i - 1);
                phi[j] = x;
            }
        }
    }
}


int phi[N];
short P[N] = {0};

void Generate(int n){
    int i, j, k, d, x;
    P[0] = P[1] = 1;
    for (i = 4; i <= n; i++, i++) P[i] = 2;

    for (i = 3; i * i <= n;){
        d = i << 1;
        for (j = (i * i); j <= n; j += d) P[j] = i;
        do{
            i++;
        } while (P[++i]);
    }

    phi[1] = 1;
    for (i = 2; i <= n; i++){
        if (!P[i]) phi[i] = i - 1;
        else{
            k = i / P[i];
            if (!(k % P[i])) phi[i] = phi[k] * P[i];
            else phi[i] = phi[k] * (P[i] - 1);
        }
    }
}
