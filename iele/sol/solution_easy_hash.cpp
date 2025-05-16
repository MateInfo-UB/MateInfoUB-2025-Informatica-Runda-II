// Author: Theodor Moroianu
// Complexity: O(N * log^2) time, O(1) space
// Indented: 100/100

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <unordered_map>
#include <assert.h>

using namespace std;

typedef unsigned long long int u64;

struct PermHash
{
    vector<u64> h;
    u64 expected_sum;

    PermHash(int N) : h(N), expected_sum(0)
    {
        mt19937_64 rnd(42);
        for (int i = 0; i < N; i++)
        {
            h[i] = rnd();
            expected_sum += h[i];
        }
    }
};

struct Centroid
{
    vector<vector<pair<int, int>>> edges;
    vector<int> dead, size;
    PermHash hash;
    int N, M;

    Centroid(int N, int M) : edges(N), dead(N), size(N), hash(M), N(N), M(M) {}

    int ComputeSize(int node, int parent)
    {
        size[node] = 1;
        for (auto [vec, _] : edges[node])
        {
            if (vec == parent || dead[vec])
                continue;
            size[node] += ComputeSize(vec, node);
        }
        return size[node];
    }

    int FindCentroid(int node, int parent, int size_root)
    {
        for (auto [vec, _] : edges[node])
        {
            if (vec == parent || dead[vec])
                continue;
            if (2 * size[vec] > size_root)
                return FindCentroid(vec, node, size_root);
        }
        return node;
    }

    u64 AddBranch(int node, u64 h_cnt, int parent, unordered_map<u64, int> &count_by_h)
    {
        // Something cool about counting permutations is that we don't need to check if we are overlapping with our own path:
        // If we add an edge twice, then it would not be a permutation anymore.

        u64 ans = 0;

        // We first try to close the path right now.
        u64 other_sum = hash.expected_sum - h_cnt;

        if (count_by_h.count(other_sum))
            ans += count_by_h[other_sum];

        // Now we add ourselves and search for the other depth.
        count_by_h[h_cnt]++;

        for (auto [vec, w] : edges[node])
            if (!dead[vec] && vec != parent)
                ans += AddBranch(vec, h_cnt + hash.h[w], node, count_by_h);

        return ans;
    }

    u64 Solve(int node)
    {
        // Find centroid.
        ComputeSize(node, -1);
        node = FindCentroid(node, -1, size[node]);

        // Kill the node for avoiding future visits.
        dead[node] = 1;

        unordered_map<u64, int> count_by_h;
        // Add the root itself.
        count_by_h[0] = 1;

        u64 ans = 0;

        // Add all neighbours to the count_by_h.
        for (auto [vec, w] : edges[node])
            if (!dead[vec])
                ans += AddBranch(vec, hash.h[w], node, count_by_h);

        // Recursively solve the problem for each neighbour.
        for (auto [vec, _] : edges[node])
            if (!dead[vec])
                ans += Solve(vec);

        return ans;
    }
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N, M;
    cin >> N >> M;

    Centroid centroid(N, M);

    for (int i = 1; i < N; i++)
    {
        int a, b, c;
        cin >> a >> b >> c;
        centroid.edges[a - 1].emplace_back(b - 1, c - 1);
        centroid.edges[b - 1].emplace_back(a - 1, c - 1);
    }

    u64 ans = centroid.Solve(0);
    cout << ans << '\n';

    assert(ans > 0);

    return 0;
}
