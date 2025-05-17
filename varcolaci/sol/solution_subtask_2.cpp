// Author: Theodor Moroianu
// Complexity: O(N^2) time, O(N^2) space
// Indented: 100/100

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <assert.h>
using namespace std;

const string WIN = "Radu", LOSE = "Mircea", DRAW = "egalitate";

map<tuple<int, int, int, int>, int> memo;

/// 1 if the player wins, 0 if even, -1 if the other player wins.
int MinMax(int parity_player, int parity_other, int left_even, int left_odd)
{
    // Check if we already computed this state.
    auto it = memo.find({parity_player, parity_other, left_even, left_odd});
    if (it != memo.end())
        return it->second;

    // Game over.
    if (left_even == 0 && left_odd == 0)
    {
        if (parity_player == parity_other)
            return 0;
        else
            return (parity_player > parity_other) ? 1 : -1;
    }

    // Try to take a number.
    int score_odd = -1, score_even = -1;
    if (left_odd > 0)
        score_odd = -MinMax(parity_other, parity_player ^ 1, left_even, left_odd - 1);
    if (left_even > 0)
        score_even = -MinMax(parity_other, parity_player, left_even - 1, left_odd);

    int score = max(score_odd, score_even);
    memo[{parity_player, parity_other, left_even, left_odd}] = score;

    return score;
}

void Test()
{
    int N;
    cin >> N;

    assert(N <= 15);

    int nr_pare = 0, nr_impare = 0;

    while (N--)
    {
        int x;
        cin >> x;

        assert(x > 0 && x <= 1000000000);

        if (x % 2 == 0)
            nr_pare++;
        else
            nr_impare++;
    }

    int score = MinMax(0, 0, nr_pare, nr_impare);

    if (score == 0)
    {
        cout << DRAW << "\n";
    }
    else if (score == 1)
        cout << WIN << '\n';
    else
        cout << LOSE << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    assert(T <= 10);

    while (T--)
        Test();
}
