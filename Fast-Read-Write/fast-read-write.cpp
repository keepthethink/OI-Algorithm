int readInt() {
    char c = 0;
    int res = 0, f = 1;

    while(!('0' <= c && c <= '9') && c != '-') {
        c = getchar();
    }
    if(c == '-') {
        f = -1;
    } else {
        res = c - '0';
    }
    while(isDigit(c = getchar())) {
        res = res * 10 + c - '0';
    }
    return f * res;
}

void writeInt(int n) {
    if(n == 0) {
        putchar('0');
    }
    int d[15], num = 0;
    while(n != 0) {
        d[num++] = n % 10;
        n /= 10;
    }
    num--;
    while(num >= 0) {
        putchar(d[num--] + '0');
    }
}

long long readLL() {
    char c = 0;
    long long res = 0, f = 1;

    while(!('0' <= c && c <= '9') && c != '-') {
        c = getchar();
    }
    if(c == '-') {
        f = -1;
    } else {
        res = c - '0';
    }
    while(isDigit(c = getchar())) {
        res = res * 10 + c - '0';
    }
    return f * res;
}

void writeLL(long long n) {
    if(n == 0) {
        putchar('0');
    }
    int d[55], num = 0;
    while(n != 0) {
        d[num++] = n % 10;
        n /= 10;
    }
    num--;
    while(num >= 0) {
        putchar(d[num--] + '0');
    }
}
