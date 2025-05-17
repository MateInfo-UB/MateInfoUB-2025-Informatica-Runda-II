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

    assert(N >= 1 && N <= 100000);
    assert(M == 3);

    vector<tuple<int, int, int>> edges;
    vector<vector<int>> frq(N, vector<int>(M));

    for (int i = 1; i < N; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;

        a--, b--, c--;
        assert(c < M && c >= 0);
        assert(a >= 0 && a < N);
        assert(b >= 0 && b < N);
        edges.push_back({a, b, c});
        frq[a][c]++;
        frq[b][c]++;
    }
    long long answer = 0;

    // Assume that M = 3.
    for (auto [a, b, c] : edges)
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (i != j && i != c && j != c)
                    answer += 1LL * frq[a][i] * frq[b][j];

    cout << answer << '\n';

    return 0;
}
