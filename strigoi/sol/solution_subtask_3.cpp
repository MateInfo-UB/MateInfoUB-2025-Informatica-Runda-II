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
    assert(N == 0);

    const int COEF_MAX = 1000000000;
    const int RAD = 33000;

    vector<int> poz_rad, poz_1;

    vector<string> instructions;

    for (int i = 0; i < RAD; i++)
    {
        poz_rad.push_back(instructions.size());
        instructions.push_back("$Y = $Y + " + to_string(RAD));
        poz_1.push_back(instructions.size());
        instructions.push_back("$Y = $Y + 1");
    }

    cout << instructions.size() << '\n';
    for (auto &s : instructions)
        cout << s << '\n';
    cout.flush();

    int nr;
    cin >> nr;

    assert(nr >= 0 && nr <= 1000000000);

    int nr_rad = nr / RAD;
    int nr_1 = nr % RAD;

    cout << RAD - nr_rad + RAD - nr_1 << '\n';
    for (int i = 0; i < RAD - nr_rad; i++)
        cout << poz_rad[i] << ' ';
    for (int i = 0; i < RAD - nr_1; i++)
        cout << poz_1[i] << ' ';
    cout << '\n';

    cout.flush();
}