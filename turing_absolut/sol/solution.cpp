#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int COEF_MAX = 1'000'000'000;

int main()
{
    // Read the degree of the polynomial.
    int N;
    cin >> N;

    cerr << " N =  " << N << endl;

    // We have now to output the coefficients of the polynomial.
    vector<string> instructions;
    auto AddInstruction = [&](string instruction)
    {
        int idx = instructions.size();
        instructions.push_back(instruction);
        return idx;
    };

    // Powers of X.
    auto PowX = [&](int i)
    {
        return "$X" + to_string(i);
    };
    AddInstruction(PowX(0) + " = 1");
    for (int i = 1; i <= N; i++)
        AddInstruction(PowX(i) + " = $X" + to_string(i - 1) + " * " + "$X");

    // For each of the N+1 coefficients, we need the lines adding powers of 2 to a counter.
    // coefs[i][j] -> which line increases the coefficient of X^i by 2^j.
    vector<vector<int>> coeffs(N + 1);
    for (int i = 0; i <= N; i++)
    {
        string Xi = PowX(i);
        string varname = "$COEF_X" + to_string(i);
        AddInstruction(varname + " = 0");

        for (int j = 0; (1 << j) <= COEF_MAX; j++)
        {
            int idx = AddInstruction(varname + " = " + varname + " + " + to_string(1 << j));
            coeffs[i].push_back(idx);
        }

        // We set VAL_Xi = COEF_Xi * X^i, and add it to the answer.
        string combined = "$VAL_X" + to_string(i);
        AddInstruction(combined + " = " + varname + " * " + Xi);
        AddInstruction("$Y = $Y + " + combined);
    }

    // Now print the instructions.
    cout << instructions.size() << '\n';
    for (auto &s : instructions)
        cout << s << '\n';

    cout.flush();

    // Read the coefficients.
    vector<int> poly(N + 1);
    for (auto &i : poly)
        cin >> i;

    cerr << " POLY = ";
    for (auto &i : poly)
        cerr << i << ' ';

    // Lines we will need to comment out.
    vector<int> commented_lines;

    // For each coefficient, we disable the lines which add a power of 2 not present in the coefficient.
    for (int i = 0; i <= N; i++)
        for (int j = 0; (1 << j) <= COEF_MAX; j++)
            if (!(poly[i] & (1 << j)))
                commented_lines.push_back(coeffs[i][j]);

    // Print the lines to comment out.
    cout << commented_lines.size() << '\n';
    cerr << " COMMENTED LINES = ";
    for (auto &i : commented_lines)
        cerr << i << ' ';
    for (auto &i : commented_lines)
        cout << i << '\n';
    cout.flush();
}