// Author: Theodor Moroianu

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <unordered_map>
#include <assert.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    vector<vector<pair<int, int>>> edges(N);

    for (int i = 1; i < N; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--, c--;
        assert(c < M && c >= 0);
        assert(a >= 0 && a < N);
        assert(b >= 0 && b < N);
        edges[a].emplace_back(b, c);
        edges[b].emplace_back(a, c);
    }

    vector<int> p;

    function<void(int, int)> Dfs = [&](int node, int parent)
    {
        for (auto [vec, w] : edges[node])
        {
            if (vec == parent)
                continue;
            p.push_back(w);
            Dfs(vec, node);
        }
    };

    for (int i = 0; i < (int)N; i++)
    {
        if ((int)edges[i].size() == 1)
        {
            Dfs(i, -1);
            break;
        }
    }

    for (int i = 0; i < (int)N; i++)
        assert((int)edges[i].size() <= 2);

    vector<int> frq(M);
    int nr_active = 0, answer = 0;
    assert((int)p.size() == N - 1);

    for (int i = 0; i < (int)p.size(); i++)
    {
        cerr << p[i] << ' ';
        // Add the edge.
        frq[p[i]]++;
        if (frq[p[i]] == 1)
            nr_active++;

        if (i == M)
        {
            // Remove the edge.
            frq[p[i - M]]--;
            if (frq[p[i - M]] == 0)
                nr_active--;
        }

        if (nr_active == M)
            answer++;
    }

    cout << answer << '\n';
    return 0;
}
