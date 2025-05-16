#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <map>
#include <algorithm>
#include <random>
#include <functional>
using namespace std;

int NByTest(int test)
{
    if (test <= 1)
        return 1000;
    return 100000;
}

int MByTest(int test)
{
    if (test == 1)
        return 10;

    if (test & 1)
        return 10;

    return NByTest(test) / 10;
}

double ProbabilityOfMutationByTest(int test)
{
    int M = MByTest(test);
    return 0.1 / M;
}

enum Strategy
{
    Random,
    Chain,
    Dense,
    TwoLevels,
    ThreeLevels,
};

Strategy StrategyByTest(int test)
{

    if (test == 2 || test == 3)
        return ThreeLevels;

    if (test == 4 || test == 5)
        return TwoLevels;

    if (test == 6 || test == 7)
        return Chain;

    if (test & 1)
        return Dense;
    return Random;
}

int main(int argc, char *argv[])
{
    assert(argc == 2);
    int TEST = atoi(argv[1]);

    int N = NByTest(TEST);
    int M = MByTest(TEST);
    Strategy strategy = StrategyByTest(TEST);
    double probability_of_mutation = ProbabilityOfMutationByTest(TEST);

    mt19937 rnd(TEST);
    uniform_real_distribution<double> dist_01(0, 1);
    vector<int> perm_nodes(N);
    iota(perm_nodes.begin(), perm_nodes.end(), 1);
    shuffle(perm_nodes.begin(), perm_nodes.end(), rnd);

    bool weights_are_set = false;
    vector<vector<pair<int, int>>> edges(N);

    if (strategy == Chain)
    {
        for (int i = 0; i < N - 1; i++)
        {
            edges[i].push_back({(i + 1) % N, 0});
            edges[(i + 1) % N].push_back({i, 0});
        }
    }
    else if (strategy == Dense)
    {
        for (int i = 1; i < N; i++)
        {
            int parent = rnd() % i;
            edges[i].push_back({parent, 0});
            edges[parent].push_back({i, 0});
        }
    }
    else if (strategy == Random)
    {
        for (int i = 1; i < N; i++)
        {
            int parent = max(0, i - 3);
            if (dist_01(rnd) < probability_of_mutation)
                parent = rnd() % i;
            edges[i].push_back({parent, 0});
            edges[parent].push_back({i, 0});
        }
    }
    else if (strategy == TwoLevels)
    {
        M = 2;
        weights_are_set = true;
        for (int i = 1; i < N; i++)
        {
            int parent = 0;
            int weight = rnd() % M;
            edges[i].push_back({parent, weight});
            edges[parent].push_back({i, weight});
        }
    }
    else if (strategy == ThreeLevels)
    {
        M = 3;
        weights_are_set = true;
        int lvl_2 = 10;

        for (int i = 1; i < N; i++)
        {
            int parent = 0;
            int weight = rnd() % M;

            if (i > lvl_2)
                parent = rnd() % (lvl_2 + 1);

            edges[i].push_back({parent, weight});
            edges[parent].push_back({i, weight});
        }
    }
    else
        assert(false);

    // Add the weights.
    map<pair<int, int>, int> weights;
    function<void(int, int, int)> Dfs = [&](int node, int parent, int w_cnt)
    {
        for (auto &[vec, weight] : edges[node])
        {
            if (weights.count({node, vec}))
            {
                weight = weights[{node, vec}];
                continue;
            }

            if (vec == parent)
                continue;

            weight = (w_cnt + 1) % M;

            if (dist_01(rnd) < probability_of_mutation)
                weight = rnd() % M;

            weights[{node, vec}] = weight;
            weights[{vec, node}] = weight;

            Dfs(vec, node, weight);
        }
    };

    if (!weights_are_set)
        Dfs(0, -1, 0);

    vector<int> perm_weights(M);
    iota(perm_weights.begin(), perm_weights.end(), 1);
    shuffle(perm_weights.begin(), perm_weights.end(), rnd);

    cout << N << ' ' << M << '\n';
    for (int i = 0; i < N; i++)
        for (auto [vec, weight] : edges[i])
            if (i < vec)
                cout << perm_nodes[i] << ' ' << perm_nodes[vec] << ' ' << perm_weights[weight] << '\n';
}