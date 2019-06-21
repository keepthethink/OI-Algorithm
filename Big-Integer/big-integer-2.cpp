struct BigInteger {
    static const int BASE = 100000000;
    static const int WIDTH = 8;
    bool sign;
    size_t length;
    std::vector<int> num;
    BigInteger(long long x = 0) { *this = x; }
    BigInteger(const std::string &x) { *this = x; }
    BigInteger(const BigInteger &x) { *this = x; }
    void cutLeadingZero() {
        while (num.back() == 0 && num.size() != 1) { num.pop_back(); }
    }
    void setLength() {
        cutLeadingZero();
        int tmp = num.back();
        if (tmp == 0) { length = 1; }
        else {
            length = (num.size() - 1) * WIDTH;
            while (tmp > 0) {
                ++length;
                tmp /= 10;
            }
        }
    }
    BigInteger &operator=(long long x) {
        num.clear();
        if (x >= 0) sign = true;
        else {
            sign = false;
            x = -x;
        }
        do {
            num.push_back(x % BASE);
            x /= BASE;
        } while (x > 0);
        setLength();
        return *this;
    }
    BigInteger &operator=(const std::string &str) {
        num.clear();
        sign = (str[0] != '-');
        int x, len = (str.size() - 1 - (!sign)) / WIDTH + 1;
        for (int i = 0; i < len; i++) {
            int End = str.length() - i * WIDTH;
            int start = std::max((int) (!sign), End - WIDTH);//防止越界
            sscanf(str.substr(start, End - start).c_str(), "%d", &x);
            num.push_back(x);
        }
        setLength();
        return *this;
    }
    BigInteger &operator=(const BigInteger &tmp) {
        num = tmp.num;
        sign = tmp.sign;
        length = tmp.length;
        return *this;
    }
    size_t size() const { return length; }
    BigInteger e(size_t n) const {
        int tmp = n % WIDTH;
        BigInteger ans;
        ans.length = n + 1;
        n /= WIDTH;
        while (ans.num.size() <= n) ans.num.push_back(0);
        ans.num[n] = 1;
        while (tmp--) ans.num[n] *= 10;
        return ans * (*this);
    }
    BigInteger abs() const {
        BigInteger ans(*this);
        ans.sign = true;
        return ans;
    }
    const BigInteger &operator+() const { return *this; }
    BigInteger operator+(const BigInteger &b) const {
        if (!b.sign) { return *this - (-b); }
        if (!sign) { return b - (-*this); }
        BigInteger ans;
        ans.num.clear();
        for (int i = 0, g = 0;; i++) {
            if (g == 0 && i >= num.size() && i >= b.num.size()) break;
            int x = g;
            if (i < num.size()) x += num[i];
            if (i < b.num.size()) x += b.num[i];
            ans.num.push_back(x % BASE);
            g = x / BASE;
        }
        ans.setLength();
        return ans;
    }
    BigInteger operator-() const {
        BigInteger ans(*this);
        if (ans != 0) ans.sign = !ans.sign;
        return ans;
    }
    BigInteger operator-(const BigInteger &b) const {
        if (!b.sign) { return *this + (-b); }
        if (!sign) { return -((-*this) + b); }
        if (*this < b) { return -(b - *this); }
        BigInteger ans;
        ans.num.clear();
        for (int i = 0, g = 0;; i++) {
            if (g == 0 && i >= num.size() && i >= b.num.size()) break;
            int x = g;
            g = 0;
            if (i < num.size()) x += num[i];
            if (i < b.num.size()) x -= b.num[i];
            if (x < 0) {
                x += BASE;
                g = -1;
            }
            ans.num.push_back(x);
        }
        ans.setLength();
        return ans;
    }
    BigInteger operator*(const BigInteger &b) const {
        int lena = num.size(), lenb = b.num.size();
        std::vector<long long> ansLL;
        for (int i = 0; i < lena + lenb; i++) ansLL.push_back(0);
        for (int i = 0; i < lena; i++) {
            for (int j = 0; j < lenb; j++) {
                ansLL[i + j] += (long long) num[i] * (long long) b.num[j];
            }
        }
        while (ansLL.back() == 0 && ansLL.size() != 1) ansLL.pop_back();
        int len = ansLL.size();
        long long g = 0, tmp;
        BigInteger ans;
        ans.sign = (ansLL.size() == 1 && ansLL[0] == 0) || (sign == b.sign);
        ans.num.clear();
        for (int i = 0; i < len; i++) {
            tmp = ansLL[i];
            ans.num.push_back((tmp + g) % BASE);
            g = (tmp + g) / BASE;
        }
        if (g > 0) ans.num.push_back(g);
        ans.setLength();
        return ans;
    }
    BigInteger operator/(const long long &b) const {
        BigInteger c;
        c.num.clear();
        for (int i = 0; i < num.size(); i++) {
            c.num.push_back(0);
        }
        long long g = 0;
        for (int i = num.size() - 1; i >= 0; i--) {
            c.num[i] = int((num[i] + g * BASE) / b);
            g = num[i] + g * BASE - c.num[i] * b;
        }
        for (int i = num.size() - 1; c.num[i] == 0; i--) {
            c.num.pop_back();
        }
        return c;
    }
    BigInteger operator/(const BigInteger &b) const {
        BigInteger aa((*this).abs());
        BigInteger bb(b.abs());
        if (aa < bb) return 0;
        char *str = new char[aa.size() + 1];
        memset(str, 0, sizeof(char) * (aa.size() + 1));
        BigInteger tmp;
        int lena = aa.length, lenb = bb.length;
        for (int i = 0; i <= lena - lenb; i++) {
            tmp = bb.e(lena - lenb - i);
            while (aa >= tmp) {
                ++str[i];
                aa = aa - tmp;
            }
            str[i] += '0';
        }
        BigInteger ans(str);
        delete[]str;
        ans.sign = (ans == 0 || sign == b.sign);
        return ans;
    }
    BigInteger operator%(const long long &b) const {
        long long ans = 0;
        for (int i = num.size() - 1; i >= 0; i--)
            ans = (ans * BASE + num[i]) % b;
        return ans;
    }
    BigInteger operator%(const BigInteger &b) const {
        return *this - *this / b * b;
    }
    BigInteger &operator++() {
        *this = *this + 1;
        return *this;
    }
    BigInteger &operator--() {
        *this = *this - 1;
        return *this;
    }
    BigInteger &operator+=(const BigInteger &b) {
        *this = *this + b;
        return *this;
    }
    BigInteger &operator-=(const BigInteger &b) {
        *this = *this - b;
        return *this;
    }
    BigInteger &operator*=(const BigInteger &b) {
        *this = *this * b;
        return *this;
    }
    BigInteger &operator/=(const long long &b) {
        *this = *this / b;
        return *this;
    }
    BigInteger &operator/=(const BigInteger &b) {
        *this = *this / b;
        return *this;
    }
    BigInteger &operator%=(const long long &b) {
        *this = *this % b;
        return *this;
    }
    BigInteger &operator%=(const BigInteger &b) {
        *this = *this % b;
        return *this;
    }
    bool operator<(const BigInteger &b) const {
        if (sign && !b.sign) { return false; }
        else if (!sign && b.sign) { return true; }
        else if (!sign && !b.sign) { return -b < -*this; }
        if (num.size() != b.num.size()) return num.size() < b.num.size();
        for (int i = num.size() - 1; i >= 0; i--)
            if (num[i] != b.num[i]) return num[i] < b.num[i];
        return false;
    }

    bool operator>(const BigInteger &b) const { return b < *this; }
    bool operator<=(const BigInteger &b) const { return !(b < *this); } 
    bool operator>=(const BigInteger &b) const { return !(*this < b); }
    bool operator!=(const BigInteger &b) const { return b < *this || *this < b; }
    bool operator==(const BigInteger &b) const { return !(b < *this) && !(*this < b); }
    bool operator||(const BigInteger &b) const { return *this != 0 || b != 0; }
    bool operator&&(const BigInteger &b) const { return *this != 0 && b != 0; }
    bool operator!() { return (bool) (*this == 0); }
    friend std::ostream &operator<<(std::ostream &out, const BigInteger &x) {
        if (!x.sign) out << '-';
        out << x.num.back();
        for (int i = x.num.size() - 2; i >= 0; i--) {
            char buf[10];
            //如WIDTH和BASR有变化,此处要修改为%0(WIDTH)d
            sprintf(buf, "%08d", x.num[i]);
            for (int j = 0; j < strlen(buf); j++) out << buf[j];
        }
        return out;
    }
    friend std::istream &operator>>(std::istream &in, BigInteger &x) {
        std::string str;
        in >> str;
        size_t len = str.size();
        int start = 0;
        if (str[0] == '-') start = 1;
        if (str[start] == '\0') return in;
        for (int i = start; i < len; i++) {
            if (str[i] < '0' || str[i] > '9') return in;
        }
        x.sign = !start;
        x = str.c_str();
        return in;
    }
};
