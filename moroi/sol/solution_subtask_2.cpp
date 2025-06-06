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

    int nr_rototol = 0;
    for (auto c : s)
    {
        if (c == 'r')
            nr_rototol++;
    }

    assert(nr_rototol <= 2);

    auto AnsForString = [&](string s)
    {
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
                continue;
            }
        }
        ans += abs(x) + abs(y);
        return ans;
    };

    function<int(int, int, int, int, int)> ComputeBestAnswer = [&](int idx, int x, int y, int dx, int dy) -> int
    {
        if (idx == s.size())
            return abs(x) + abs(y);

        char c = s[idx];
        if (c == 'i')
            return ComputeBestAnswer(idx + 1, x + dx, y + dy, dx, dy);
        else if (c == 's')
            return ComputeBestAnswer(idx + 1, x, y, dy, -dx);
        else if (c == 'd')
            return ComputeBestAnswer(idx + 1, x, y, -dy, dx);
        else if (c == 'r')
        {
            int ans = ComputeBestAnswer(idx + 1, x, y, dx, dy);
            ans = max(ans, ComputeBestAnswer(idx + 1, x, y, dy, -dx));
            ans = max(ans, ComputeBestAnswer(idx + 1, x, y, -dy, dx));
            ans = max(ans, ComputeBestAnswer(idx + 1, x, y, -dx, -dy));
            return ans;
        }
        assert(false);
    };

    int ans = ComputeBestAnswer(0, 0, 0, 1, 0);

    cout << ans << '\n';
    return 0;
}
