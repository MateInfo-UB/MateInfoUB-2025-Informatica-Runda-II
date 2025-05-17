// Author: Theodor Moroianu
// Complexity: O(N) time, O(1) space
// Indented: 100/100

#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

const string WIN = "Radu", LOSE = "Mircea", DRAW = "egalitate";

void Test()
{
    int N;
    cin >> N;

    assert(N <= 1000);

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

    // Suma totala este para, deci va fi mereu remiza.
    if (nr_impare % 2 == 0)
    {
        cout << DRAW << "\n";
        return;
    }

    // dp[i][j][k][l] -> Am paritate i, celalat are paritate j,
    // mai sunt k numere pare si l numere impare.
    vector<vector<vector<vector<int>>>> dp(2, vector<vector<vector<int>>>(2, vector<vector<int>>(nr_pare + 1, vector<int>(nr_impare + 1, 0))));

    dp[1][0][0][0] = 1;

    for (int pare = 0; pare <= nr_pare; pare++)
    {
        for (int impare = 0; impare <= nr_impare; impare++)
        {
            for (int i = 0; i < 2; i++)
            {
                for (int j = 0; j < 2; j++)
                {
                    bool is_win = 0;

                    if (pare && !dp[j][i][pare - 1][impare])
                        is_win = 1;

                    if (impare && !dp[j][i ^ 1][pare][impare - 1])
                        is_win = 1;

                    if (is_win)
                        dp[i][j][pare][impare] = 1;
                }
            }
        }
    }

    // Nu vrea sa ia numarul par, deci nici celalat jucator nu va vrea.
    // Asadar, cine ia ultimul numar va pierde (va fi ala par).
    if (dp[0][0][nr_pare][nr_impare])
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
