#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <random>
#include <assert.h>

using namespace std;

typedef long long i64;

string sum(string a, string b)
{
    string result;
    int carry = 0;
    int i = 0;
    while (i < a.size() || i < b.size() || carry)
    {
        if (i < a.size())
            carry += a[i] - '0';
        if (i < b.size())
            carry += b[i] - '0';
        result.push_back(carry % 10 + '0');
        carry /= 10;
        i++;
    }
    return result;
}

int main()
{
    string a, b;
    cin >> a >> b;

    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    auto result = sum(a, b);

    while (result.size() > 1 && result.back() == '0')
        result.pop_back();

    reverse(result.begin(), result.end());

    cout << result << endl;
}