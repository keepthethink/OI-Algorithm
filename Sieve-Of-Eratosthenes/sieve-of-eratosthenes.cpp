const int MAXN = 10000000 + 5;

bool noprime[MAXN];

void sieve(int n) {
    noprime[1] = true;
    for(int i = 2; i * i <= n; i++) {
        if(!noprime[i]) {
            for(int j = i * 2; j <= n; j += i) {
                noprime[j] = true;
            }
        }
    }
}
