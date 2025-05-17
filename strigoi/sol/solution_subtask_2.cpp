#include <iostream>
#include <string>
#include <vector>
#include <assert.h>
using namespace std;

int main()
{
    // Read the degree of the polynomial.
    int N;
    cin >> N;
    assert(N >= 0 && N <= 100);

    const int COEF_MAX = 100;

    vector<vector<int>> idx(COEF_MAX + 1, vector<int>(COEF_MAX + 1));

    vector<string> instructions;

    for (int i = 0; i <= N; i++)
    {
        for (int j = 0; j <= COEF_MAX; j++)
        {
            idx[i][j] = instructions.size();
            instructions.push_back("$A" + to_string(i) + " = " + to_string(j));
        }
    }

    instructions.push_back("$abcd = 10");
    instructions.push_back("$eee = $abcd - 8");
    instructions.push_back("$fff = $eee * 3");
    instructions.push_back("$fff = $fff * $eee");
    instructions.push_back("$runner = $fff - 11");

    for (int i = 0; i <= N; i++)
    {
        instructions.push_back("       $to_add = $runner *      $A" + to_string(i));
        instructions.push_back("   $Y     =     $Y      +     $to_add    ");
        instructions.push_back("$runner=$runner*$X");
    }

    cout << instructions.size() << '\n';
    for (auto &s : instructions)
        cout << s << '\n';
    cout.flush();

    // Read the coefficients.
    vector<int> poly(N + 1);
    for (auto &i : poly)
    {
        cin >> i;
        assert(i >= 0 && i <= 100);
    }

    cout << COEF_MAX * (N + 1) << '\n';
    for (int i = 0; i <= N; i++)
        for (int j = 0; j <= COEF_MAX; j++)
            if (poly[i] != j)
                cout << idx[i][j] << ' ';
    cout << '\n';

    cout.flush();
}