// Author: Theodor Moroianu
// Complexity: O(N^2) time, O(N) space

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int N;
    cin >> N;

    string s;
    cin >> s;

    assert((int)s.size() == N);

    int x = 0, y = 0;
    int dx = 1, dy = 0;

    int ans = 0;

    for (auto c : s)
    {
        if (c == 'i')
            x += dx, y += dy;
        else if (c == 's')
        {
            dy *= -1;
            swap(dx, dy);
        }
        else if (c == 'd')
        {
            dx *= -1;
            swap(dx, dy);
        }
        else if (c == 'r')
        {
            assert(false);
        }
    }

    ans += abs(x) + abs(y);

    cout << ans << '\n';

    return 0;
}
