// Author: Theodor Moroianu
// Complexity: O(N^2) time, O(N) space

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

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
        edges[a - 1].emplace_back(b - 1, c - 1);
        edges[b - 1].emplace_back(a - 1, c - 1);
    }

    int ans = 0;
    vector<int> used(M);

    function<void(int, int)> Dfs = [&](int node, int nr_edges_used)
    {
        if (nr_edges_used == M)
        {
            ans++;
            return;
        }

        for (auto [neigh, weight] : edges[node])
        {
            if (used[weight] == 0)
            {
                used[weight]++;
                Dfs(neigh, nr_edges_used + 1);
                used[weight]--;
            }
        }
    };

    for (int i = 0; i < N; i++)
        Dfs(i, 0);

    assert(ans % 2 == 0);
    ans /= 2;

    cout << ans << '\n';
    return 0;
}
