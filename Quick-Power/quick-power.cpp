long long pow_mod(long long b, long long p, long long k) {
    long long ans;
    if(p == 0) {
        return 1 % k;
    }
    ans = pow_mod(b, p / 2, k);
    ans = ans * ans % k;
    if(p % 2 == 1) {
        ans = ans * b % k;
    }
    return ans;
}
