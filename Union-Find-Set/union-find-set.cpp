class UnionFindSet {
private:
    int *elem;
    int find(int x) {
        if (x == elem[x]) {
            return x;
        }
        return elem[x] = find(elem[x]);
    }
public:
    UnionFindSet(int n) : elem(new int [n + 5]) {
        for (int i = 0; i <= n; ++i)
            elem[i] = i;
    }
    bool connected(int x, int y) {
        return find(x) == find(y);
    }
    void union(int x, int y) {
        elem[find(x)] = find(y);
    }
};
