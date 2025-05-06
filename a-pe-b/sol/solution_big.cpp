#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <complex>
#include <assert.h>

using namespace std;

typedef long long i64;

vector<int> ReadNr()
{
    string s;
    cin >> s;
    vector<int> v;
    for (int i = 0; i < s.size(); i++)
        v.push_back(s[i] - '0');
    reverse(v.begin(), v.end());
    return v;
}

void PrintNr(vector<int> v)
{
    while (!v.empty() && v.back() == 0)
        v.pop_back();
    reverse(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
        cout << v[i];
    cout << endl;
}

void DFT(vector<complex<double>> &a, bool rev)
{
    int n = a.size();
    auto b = a;
    for (int step = n / 2; step; step /= 2)
    {
        for (int i = 0; i < n / 2; i += step)
        {
            auto wn = polar(1.0, 2.0 * M_PI * (rev ? -i : i) / n);
            for (int j = 0; j < step; ++j)
            {
                auto u = a[i * 2 + j], v = wn * a[i * 2 + j + step];
                b[i + j] = u + v;
                b[i + n / 2 + j] = u - v;
            }
        }
        swap(a, b);
    }
    if (rev)
        for (auto &x : a)
            x /= n;
}

vector<int> FFT(vector<int> a, vector<int> b)
{
    int n = 1;
    while (n < a.size() + b.size())
        n *= 2;
    vector<complex<double>> fa(n), fb(n);
    for (int i = 0; i < a.size(); i++)
        fa[i] = a[i];
    for (int i = 0; i < b.size(); i++)
        fb[i] = b[i];
    DFT(fa, false);
    DFT(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] *= fb[i];
    DFT(fa, true);
    vector<int> c(n);
    for (int i = 0; i < n; i++)
        c[i] = round(fa[i].real());

    return c;
}

vector<int> FixVector(vector<int> a)
{

    int carry = 0;
    for (int i = 0; i < a.size(); i++)
    {
        a[i] += carry;
        carry = a[i] / 10;
        a[i] %= 10;
    }
    while (carry)
    {
        a.push_back(carry % 10);
        carry /= 10;
    }

    while (a.size() > 1 && a.back() == 0)
        a.pop_back();

    return a;
}

bool operator<(vector<int> a, vector<int> b)
{
    a = FixVector(a);
    b = FixVector(b);

    if (a.size() != b.size())
        return a.size() < b.size();
    for (int i = a.size() - 1; i >= 0; i--)
        if (a[i] != b[i])
            return a[i] < b[i];
    return false;
}

int main()
{
    vector<int> a = ReadNr();
    vector<int> b = ReadNr();

    vector<int> c = vector<int>(50);

    for (int i = 49; i >= 0; i--)
    {
        while (c[i] != 9)
        {
            c[i]++;
            if (a < FFT(b, c))
            {
                c[i]--;
                break;
            }
        }
    }

    PrintNr(c);
    return 0;
}