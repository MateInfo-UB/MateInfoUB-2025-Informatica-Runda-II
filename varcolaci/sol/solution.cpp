// Author: Theodor Moroianu
// Complexity: O(N) time, O(1) space
// Indented: 100/100

#include <iostream>
#include <string>
using namespace std;

const string WIN = "Radu", LOSE = "Mircea", DRAW = "egalitate";

void Test()
{
    int N;
    cin >> N;

    int nr_pare = 0, nr_impare = 0;

    while (N--)
    {
        int x;
        cin >> x;

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

    // Doua pare se anuleaza unul pe altul, deci putem sa le eliminam.
    nr_pare %= 2;

    // Cate numere ia primul jucator.
    int num_luate = (nr_pare + nr_impare + 1) / 2;

    // Nu are nicio alegere.
    if (nr_pare == 0)
    {
        if (num_luate % 2 == 0)
            cout << LOSE << '\n';
        else
            cout << WIN << '\n';
        return;
    }

    // Ia numarul par, si dupa castiga.
    if (num_luate % 2 == 0)
    {
        cout << WIN << '\n';
        return;
    }

    // Nu vrea sa ia numarul par, deci nici celalat jucator nu va vrea.
    // Asadar, cine ia ultimul numar va pierde (va fi ala par).
    if (nr_impare % 2 == 0)
        cout << LOSE << '\n';
    else
        cout << WIN << '\n';
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int T;
    cin >> T;

    while (T--)
        Test();
}
