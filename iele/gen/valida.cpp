#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <fstream>
#include <map>
#include <random>
using namespace std;

struct UF
{
    vector<int> parent, g;

    UF(int N) : parent(N), g(N, 1)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int Find(int x)
    {
        if (parent[parent[x]] != parent[x])
            parent[x] = Find(parent[x]);
        return parent[x];
    }

    bool Unite(int a, int b)
    {
        a = Find(a);
        b = Find(b);

        if (a == b)
            return false;

        if (g[a] < g[b])
            swap(a, b);

        parent[b] = a;
        g[a] += g[b];
        return true;
    }
};

int main(int argc, char *argv[])
{
    ifstream in(argv[1]);

    int N, M;
    in >> N >> M;

    cerr << "N = " << N << ", M = " << M << endl;
    assert(N >= 1);
    assert(M >= 1);

    UF uf(N + 1);

    for (int i = 1; i < N; i++)
    {
        int a, b, c;
        in >> a >> b >> c;
        assert(a >= 1 && a <= N);
        assert(b >= 1 && b <= N);
        assert(c >= 1 && c <= M);
        assert(uf.Unite(a, b));
    }
}