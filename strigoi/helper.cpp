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

// To avoid any overflow issues, we compute everything modulo MOD.
const int MOD = 1e9 + 7;
typedef long long i64;

const bool DEBUG = true;

struct InvalidProgram : public runtime_error
{
    InvalidProgram(const string &message) : runtime_error(message) {}
};

std::regex INSTR_TWO_REGISTERS(R"(\s*\$(\w+)\s*=\s*\$(\w+)\s*([\+\-\*])\s*\$(\w+)\s*)"); // $A = $B [+-*] $C
std::regex INSTR_ONE_REGISTER(R"(\s*\$(\w+)\s*=\s*\$(\w+)\s*([\+\-\*])\s*(\d+)\s*)");    // $A = $B [+-*] [numar]
std::regex INSTR_NO_REGISTER(R"(\s*\$(\w+)\s*=\s*(\d+)\s*)");                            // $A = [numar]

class Checker
{
    vector<string> instructions;
    vector<int> polynome;

    i64 PerformOperation(i64 A, i64 B, const string &op)
    {
        if (op == "+")
        {
            return (A + B) % MOD;
        }
        else if (op == "-")
        {
            return (A - B + MOD) % MOD;
        }
        else if (op == "*")
        {
            return (A * B) % MOD;
        }
        else
        {
            throw InvalidProgram("Invalid operation: " + op);
        }
    }

    void RunInstruction(int pc, map<string, i64> &variables)
    {
        if (DEBUG)
        {
            cerr << "Executam operatia #" << pc << ": " << instructions[pc] << endl;
        }
        const string &instruction = instructions[pc];
        std::smatch match;

        if (regex_match(instruction, match, INSTR_TWO_REGISTERS))
        {
            string A = match[1], B = match[2], op = match[3], C = match[4];
            if (variables.find(B) == variables.end())
                throw InvalidProgram("Invalid variable: " + B);

            if (variables.find(C) == variables.end())
                throw InvalidProgram("Invalid variable: " + C);

            i64 result = PerformOperation(variables[B], variables[C], op);
            variables[A] = result;
            if (DEBUG)
                cerr << "Setam " << A << " = " << result << endl;
        }
        else if (regex_match(instruction, match, INSTR_ONE_REGISTER))
        {
            string A = match[1], B = match[2], op = match[3], num = match[4];
            if (variables.find(B) == variables.end())
                throw InvalidProgram("Invalid variable: " + B);
            i64 num_value = 0;

            try
            {
                num_value = atoi(num.c_str());
            }
            catch (...)
            {
                throw InvalidProgram("Invalid number: " + num);
            }

            i64 result = PerformOperation(variables[B], num_value, op);
            variables[A] = result;
            if (DEBUG)
                cerr << "Setam " << A << " = " << result << endl;
        }
        else if (regex_match(instruction, match, INSTR_NO_REGISTER))
        {
            string A = match[1], num = match[2];

            i64 num_value = 0;
            try
            {
                num_value = atoi(num.c_str());
            }
            catch (...)
            {
                throw InvalidProgram("Invalid number: " + num);
            }

            variables[A] = num_value;
            if (DEBUG)
                cerr << "Setam " << A << " = " << num_value << endl;
        }
        else
        {
            throw InvalidProgram("Invalid instruction: " + instruction);
        }
    }

    bool EvaluatePolynome(i64 X)
    {
        map<string, i64> variables;
        variables["X"] = X;
        variables["Y"] = 0;

        for (int pc = 0; pc < (int)instructions.size(); pc++)
            RunInstruction(pc, variables);

        // If not present, we assume that Y is 0.
        i64 Y = variables["Y"];

        // Evaluate what the real Y is.
        i64 real_Y = 0;
        for (int i = (int)polynome.size() - 1; i >= 0; i--)
            real_Y = (real_Y * X + polynome[i]) % MOD;

        if (DEBUG && Y != real_Y)
        {
            cerr << "Invalid program (modulo " << MOD << "): " << endl;
            cerr << "X: " << X << ", Y: " << Y << ", Real Y: " << real_Y << endl;
        }

        cerr << "X: " << X << ", Y: " << Y << ", Real Y: " << real_Y << endl;

        return Y == real_Y;
    }

public:
    Checker(const vector<string> &instructions, vector<int> commented_lines, const vector<int> &polynome)
    {
        // Make sure that the commented lines are unique.
        sort(commented_lines.begin(), commented_lines.end());
        if (unique(commented_lines.begin(), commented_lines.end()) != commented_lines.end())
        {
            throw InvalidProgram("Duplicate commented lines");
        }

        // Make sure that the commentend lines are in the range of the instructions.
        if (!commented_lines.empty() && (commented_lines[0] < 0 || commented_lines.back() >= (int)instructions.size()))
        {
            throw InvalidProgram("Commented lines out of range");
        }

        // Initialize our member variables.
        set<int> all_commented_lines(commented_lines.begin(), commented_lines.end());
        for (int i = 0; i < (int)instructions.size(); i++)
        {
            if (all_commented_lines.find(i) == all_commented_lines.end())
            {
                this->instructions.push_back(instructions[i]);
            }
        }

        this->polynome = polynome;
    }

    /// @brief  Checks if the program is valid, i.e. that the execution of the program
    ///         yields a correct evaluation of the polynomial.
    /// @return True if the program is valid, false otherwise.
    /// @throw  If an error is encountered evaluating the program, an InvalidProgram exception is thrown.
    bool CheckProgramIsValid()
    {
        // Pick a few values for X.
        vector<i64> Xs = {0, 1, 2, 3, 13, 23, 51};

        // Check if the program is valid for all values of X.
        for (i64 X : Xs)
        {
            if (DEBUG)
            {
                cerr << "Checking X = " << X << endl;
            }
            if (!EvaluatePolynome(X))
            {
                return false;
            }
        }
        return true;
    }
};

const int MAX_INSTRUCTIONS = 200'000;

int main()
{
    try
    {
        // Print the polynomial's degree.
        cout << "Introduceti gradul polinomului: ";
        int N;
        cin >> N;

        // Read the instructions.
        cout << "Introduceti numarul de instructiuni: ";
        int NR_INSTRUCTIONS;
        cin >> NR_INSTRUCTIONS;

        if (NR_INSTRUCTIONS < 0)
            throw InvalidProgram("Numar de instructiuni invalid: " + to_string(NR_INSTRUCTIONS));

        if (NR_INSTRUCTIONS > MAX_INSTRUCTIONS)
            throw InvalidProgram("Prea multe instructiuni: " + to_string(NR_INSTRUCTIONS));

        cout << "Introduceti instructiunile: ";
        vector<string> instructions(NR_INSTRUCTIONS);
        cin.ignore();
        for (int i = 0; i < NR_INSTRUCTIONS; i++)
            getline(cin, instructions[i]);

        // Print the coefficients of the polynomial.
        cout << "Introduceti coeficientii polinomului: ";
        vector<int> polynome(N + 1);
        for (auto &coef : polynome)
            cin >> coef;

        // Read the lines to comment out.
        cout << "Introduceti numarul de linii comentate: ";
        int NR_COMMENTED_LINES;
        cin >> NR_COMMENTED_LINES;
        vector<int> commented_lines(NR_COMMENTED_LINES);
        cout << "Introduceti liniile comentate: ";
        for (auto &i : commented_lines)
            cin >> i;

        // Check if the program is valid.
        Checker checker(instructions, commented_lines, polynome);

        if (checker.CheckProgramIsValid())
            cout << "Raspunsul este corect!" << endl;
        else
            cout << "Raspunsul NU calculeaza polinomul corect!" << endl;
    }
    catch (const InvalidProgram &e)
    {
        cout << "Programul NU a putut fi parsat: " << e.what() << endl;
    }
    catch (const exception &e)
    {
        cout << "A aparut o eroare: " << e.what() << endl;
    }
    catch (...)
    {
        cout << "A aparut o eroare. Programul NU este corect" << endl;
    }
}
