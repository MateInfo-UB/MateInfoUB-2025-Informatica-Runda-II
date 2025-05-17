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
    assert(M == 2);

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

    for (int i = 0; i < N; i++)
        answer += 1LL * frq[i][0] * frq[i][1];

    cout << answer << '\n';

    return 0;
}
