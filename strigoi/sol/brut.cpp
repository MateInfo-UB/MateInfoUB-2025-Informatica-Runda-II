#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
    // Read the degree of the polynomial.
    int N;
    cin >> N;

    const int COEF_MAX = 200;

    vector<vector<int>> idx(COEF_MAX + 1, vector<int>(COEF_MAX + 1));

    vector<string> instructions;

    for (int i = 0; i <= COEF_MAX; i++)
    {
        for (int j = 0; j <= COEF_MAX; j++)
        {
            idx[i][j] = instructions.size();
            instructions.push_back("$Y = $X * " + to_string(j));
            instructions.push_back("$Y = $Y + " + to_string(i));
        }
    }

    cout << instructions.size() << '\n';
    for (auto &s : instructions)
        cout << s << '\n';
    cout.flush();

    // Read the coefficients.
    vector<int> poly(N + 1);
    for (auto &i : poly)
        cin >> i;

    if (poly.size() == 1)
        poly.push_back(0);

    cout << instructions.size() - 2 << '\n';
    for (int i = 0; i < (int)instructions.size(); i++)
        if (i != idx[poly[0]][poly[1]] && i != idx[poly[0]][poly[1]] + 1)
            cout << i << '\n';

    cout.flush();
}