#include <signal.h>

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <stdexcept>
#include <regex>
#include <iostream>
#include <set>

using namespace std;

int main(int argc, char **argv)
{
    signal(SIGPIPE, SIG_IGN);

    ifstream sample_in("input.txt");
    ofstream fifo_out(argv[2]);
    ifstream fifo_in(argv[1]);

    try
    {
        for (int i = 0; i < 5; i++)
        {
            string word;
            sample_in >> word;
            fifo_out << word << endl;

            // Read the reply.
            string reply;
            fifo_in >> reply;

            if (reply != word)
            {
                cout << "0.0" << endl;
                cerr << "Error: Expected " << word << ", got " << reply << endl;
                return 0;
            }
        }
    }
    catch (const exception &e)
    {
        cout << "0.0" << endl;
        cerr << "Error: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "0.0" << endl;
        cerr << "Unknown error" << endl;
    }

    cout << "1.0" << endl;
    cerr << "Valid program" << endl;
}
