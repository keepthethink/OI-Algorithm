class TreeArray {
private:
    int lowBit(int n) {
        return n & (-n);
    }
    
    int sum(int n) {
        int ans = 0;
        while(n > 0) {
            ans += c[n];
            n -= lowBit(n);
        }
        return ans;
    }
    
public:
    static const int MAXN = 500000 + 5;

    int c[MAXN];
    int n;

    TreeArray() {
        memset(c, 0, sizeof(c));
    }

    TreeArray(int n) {
        memset(c, 0, sizeof(c));
        this -> n = n;
    }

    void clear(int n = 0) {
        memset(c, 0, sizeof(c));
        if(n != 0) {
            this -> n = n;
        }
    }

    void update(int space , int v) {
        while(space <= n) {
            c[space] += v;
            space += lowBit(space);
        }
    }

    int sum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};
