#include <bits/stdc++.h>
#include "bigInt.h"
using namespace std;

#define ll long long
#define endl "\n"
#define fo(i, a, b) for (int i = a; i < (int)b; i++)
#define rfo(i, a, b) for (int i = a - 1; i >= b; i--)
#define v(i) vector<i>
#define vll vector<long long>
#define vstr vector<string>
#define pairll pair<long long, long long>
#define vpairll vector<pair<long long, long long>>
#define print(x)       \
    cout << x << "\n"; \
    cout.flush()

#define printt(x) cout << "-> " << x << "\n"

#define printall(x)         \
    for (auto zz : x)       \
    {                       \
        cout << zz << "\n"; \
    }                       \
    cout.flush()

#define pushall(x, n)              \
    x.reserve(n);                  \
    for (int zz = 0; zz < n; zz++) \
    {                              \
        long long tmpV99;          \
        cin >> tmpV99;             \
        x.push_back(tmpV99);       \
    }

#define pushallpair(x, n)              \
    x.reserve(n);                      \
    for (int zz = 0; zz < n; zz++)     \
    {                                  \
        long long tmpV99;              \
        long long tmpV98;              \
        cin >> tmpV99;                 \
        cin >> tmpV98;                 \
        x.push_back({tmpV99, tmpV98}); \
    }

bool AllDig(string var)
{
    fo(i, 0, var.length())
    {

        if ((var[i] < '0' || var[i] > '9') && var[i] != '-')
        {
            return false;
        }
    }
    return true;
}

vstr help;
void PrintHelp()
{

    for (auto line : help)
    {
        print(line);
    }
}

void GetHelpReady()
{

    help.push_back("");
    help.push_back("temp - this line is replaced");

    help.push_back("To start, type \"[variable] = [number or variable]\" to create a variable, or give a different value to an already existing variable");
    help.push_back("Type \"show [variable]\" or simply [variable] to get a variable's value");
    help.push_back("Type \"showall\" to show all the variables");
    help.push_back("To add, type [variable] + [number or variable]");
    help.push_back("You can multiply with *, divide with /, minus with -, and modulus with %");
    help.push_back("You can get factorial with [variable]!");
    help.push_back("You can increment or decrement your number with \"[variable]++\" or \"--\"");
    help.push_back("You can check if two variables are equal with \"[variable] == [variable or number]\"");
    help.push_back("Variable names must start with a letter and may not have the symbols shown above. You cannot have two commands in one sentence");
    help.push_back("As of right now, negative numbers do not work, so don't use them!");
    help.push_back("You can type \"help\" if you want this menu again");
    help.push_back("Type \"del [variable]\" (or delete [variable])if you want to delete a variable");
    help.push_back("To stop, type \"stop\", \"quit\" or \"exit\"");
    help.push_back("As you type commands, you will recieve feedback so you know that something has happened. To toggle these (default is off), type \"comments\" (Error messages will be sent regardless)");
    help.push_back("If you have a variable var1 = 4, to add 5, type \"var1 + 5\" - this is also how to multiply, mod, factorial (doesn't take a second argument), etc");
    help.push_back("Please add instead of minusing a negative number, as that will be taken as a decrement (-1)");

    int maxx = 0;
    fo(i, 2, help.size())
    {

        help[i] = "-> " + help[i];
        maxx = max(maxx, (int)help[i].length());
    }
    fo(i, 2, help.size())
    {
        fo(j, help[i].length(), maxx)
        {

            help[i] += " ";
        }
        help[i] += " |";
    }

    string border = "-";

    fo(i, 0, maxx)
    {
        border += "-";
    }
    border += " ";
    help[1] = border;
    help.push_back(border);
    help.push_back("");
}

int main()
{

    vstr commands;
    commands.push_back("help");
    commands.push_back("stop");
    commands.push_back("quit");
    commands.push_back("exit");
    commands.push_back("show");
    commands.push_back("showall");
    commands.push_back("comments");
    commands.push_back("del");
    commands.push_back("delete");

    string input;

    bool comments = false;

    GetHelpReady();
    PrintHelp();

    unordered_map<string, ll> getvariable; // this connects a variable name to a number
    v(bigInt) variables;
    int variableCount = 0;

    variables.push_back(bigInt(0)); // this is because getVariable returns 0 on no match

mainLoop:
    while (true)
    {

        getline(cin, input);

        string tmp;
        char action = 's';
        string var;
        string val;
        int place, place2;
        int ind = 0;
        bool isVar = true;

        // Get the type of query, and remove spaces
        bool special = false;
        int cNorm = 0;

        string spec1 = "*/%!^";
        string spec2 = "+-=";
        string spec2chnge = "idc";

        for (auto ltr : input)
        {
            if (ltr != ' ')
            {
                tmp.push_back(tolower(ltr));
            }
        }

        input = tmp;

        fo(ltr, 0, input.length())
        {

            for (auto it : spec1)
            {
                if (input[ltr] == it)
                {
                    if (special)
                    {
                        printt("There were too many special characters in that string, please try again");
                        goto mainLoop;
                    }
                    ind = ltr;
                    special = true;
                    action = it;
                    continue;
                }
            }

            fo(i, 0, spec2.length())
            {
                if (input[ltr] == spec2[i])
                {
                    if (action == spec2[i])
                    {
                        action = spec2chnge[i];
                    }
                    else
                    {
                        if (special && input[ltr] != '-') //allow for negative numbers
                        {
                            printt("There were too many special characters in that string, please try again");
                            goto mainLoop;
                        }
                        if (!special)
                        {
                            ind = ltr;
                            special = true;
                            action = spec2[i];
                        }
                    }
                    continue;
                }
            }
        }

        if (input.length() == 0)
        {
            continue;
        }
        if (AllDig(input))
        {

            printt("Please enter a variable, not just a number");
            continue;
        }

        var = input.substr(0, ind);

        if (ind == 0) // there are no special commands
        {

            // print(input);
            if (input.compare("stop") == 0 || input.compare("quit") == 0 || input.compare("exit") == 0)
            {
                break;
            }
            if (input.compare("help") == 0)
            {
                PrintHelp();
                continue;
            }
            
            if (input.compare("comments") == 0)
            {
                comments = !comments;

                if (comments)
                    printt("Comments are now on");
                continue;
            }
            
            if (input.compare("showall") == 0)
            {
                for (auto it : getvariable)
                {
                    printt(it.first << ": " << variables[it.second].get());
                }

                continue;
            }
            
            if (input.substr(0, 3).compare("del") == 0)
            {

                if (input.substr(0, 6).compare("delete") == 0)
                {
                    var = input.substr(6, input.length() - 1);
                }
                else
                {
                    var = input.substr(3, input.length() - 1);
                }
                if (AllDig(var))
                {
                    printt("You cannot delete a number");
                    continue;
                }

                place = getvariable[var];

                if (place == 0)
                {
                    printt("There is no variable named " << var);
                    getvariable.erase(var);
                }
                else
                {
                    if (comments)
                        printt(var << " has been deleted");
                    getvariable.erase(var);
                }
                continue;
            }

            if (input.substr(0, 4).compare("show") == 0 || action == 's')
            {
                if (input.substr(0, 4).compare("show") == 0)
                {
                    var = input.substr(4, input.length() - 1);
                }
                else
                {
                    var = input;
                    // print(input);
                }

                if (AllDig(var))
                {

                    printt("Variables cannot have only digits in them");
                    continue;
                }

                place = getvariable[var];

                if (place == 0)
                {
                    printt("I'm sorry, there is no variable named " << var);
                    getvariable.erase(var);
                }
                else
                {
                    printt(var << ": " << variables[place].get());
                }
                continue;
            }

            printt("Please enter a variable");
            continue;
        }
        else
        {

            for (auto str : commands)
            {

                if (input.find(str) != string::npos)
                {
                    printt("You cannot have a variable with the name " << str << " in it");
                    goto mainLoop;
                }
            }
        }

        val = input.substr(ind + 1, input.length() - 1);
        print(val);

        if (AllDig(var))
        {

            isVar = false;

            printt("Not here yet, but I want to just display the result of this eqution (like is 15 * var1 : var1 = 4 : display -> 60)");
            continue;
        }

        switch (action)
        {
        case 'c':

            if (val.length() == 0)
            {
                printt("Please enter both values / variables");
                break;
            }

            val = val.substr(1, val.length() - 1);

            place = getvariable[var];

            place2 = -1;

            if (!AllDig(val))
            {
                place2 = getvariable[val];
            }

            if (place2 == 0 || place == 0)
            {
                if (place == 0)
                {
                    printt("I'm sorry, there is no variable named " << var);
                    getvariable.erase(var);
                }
                if (place2 == 0)
                {

                    printt("I'm sorry, there is no variable named " << val);
                    getvariable.erase(val);
                }
            }
            else
            {

                if (place2 == -1)
                {
                    bool comp = variables[place].compare(val);
                    string tmp = (comp) ? "the same " : "different";

                    printt("The values are " + tmp);
                }
                else
                {
                    bool comp = variables[place].compare(variables[place2].get());

                    string tmp = (comp) ? "the same " : "different";

                    printt("The values are " + tmp);
                }
            }

            break;
        case 'i':

            place = getvariable[var];

            if (place == 0)
            {
                printt("I'm sorry, there is no variable named " << var);
                getvariable.erase(var);
            }
            else
            {
                variables[place].inc();
                if (comments)
                    printt("The variable " << var << " has been incremented");
            }

            break;
        case 'd':

            place = getvariable[var];

            if (place == 0)
            {
                printt("I'm sorry, there is no variable named " << var);
                getvariable.erase(var);
            }
            else
            {
                variables[place].dec();
                if (comments)
                    printt("The variable " << var << " has been deceremented");
            }

            break;
        case '*':

            if (val.length() == 0)
            {
                printt("Please enter both values / variables");
                break;
            }

            place = getvariable[var];

            place2 = -1;

            if (!AllDig(val))
            {
                place2 = getvariable[val];
            }

            if (place2 == 0 || place == 0)
            {
                if (place == 0)
                {
                    printt("I'm sorry, there is no variable named " << var);
                    getvariable.erase(var);
                }
                if (place2 == 0)
                {

                    printt("I'm sorry, there is no variable named " << val);
                    getvariable.erase(val);
                }
            }
            else
            {

                if (place2 == -1)
                {
                    variables[place].multiply(val);

                    if (comments)
                        printt("The value of variable " << var << " has been added");
                }
                else
                {
                    variables[place].multiply(variables[place2].get());

                    if (comments)
                        printt("The value of variable " << var << " has been added with " << val);
                }
            }

            break;
        case '/':

            if (val.length() == 0)
            {
                printt("Please enter both values / variables");
                break;
            }

            place = getvariable[var];

            place2 = -1;

            if (!AllDig(val))
            {
                place2 = getvariable[val];
            }

            if (place2 == 0 || place == 0)
            {
                if (place == 0)
                {
                    printt("I'm sorry, there is no variable named " << var);
                    getvariable.erase(var);
                }
                if (place2 == 0)
                {

                    printt("I'm sorry, there is no variable named " << val);
                    getvariable.erase(val);
                }
            }
            else
            {

                if (place2 == -1)
                {
                    variables[place].divide(val);

                    if (comments)
                        printt("The value of variable " << var << " has been added");
                }
                else
                {
                    variables[place].divide(variables[place2].get());

                    if (comments)
                        printt("The value of variable " << var << " has been added with " << val);
                }
            }

            break;
        case '+':

            if (val.length() == 0)
            {
                printt("Please enter both values / variables");
                break;
            }

            place = getvariable[var];

            place2 = -1;

            if (!AllDig(val))
            {
                place2 = getvariable[val];
            }

            if (place2 == 0 || place == 0)
            {
                if (place == 0)
                {
                    printt("I'm sorry, there is no variable named " << var);
                    getvariable.erase(var);
                }
                if (place2 == 0)
                {

                    printt("I'm sorry, there is no variable named " << val);
                    getvariable.erase(val);
                }
            }
            else
            {

                if (place2 == -1)
                {
                    variables[place].add(val);

                    if (comments)
                        printt("The value of variable " << var << " has been added");
                }
                else
                {
                    variables[place].add(variables[place2].get());

                    if (comments)
                        printt("The value of variable " << var << " has been added with " << val);
                }
            }

            break;
        case '-':

            if (val.length() == 0)
            {
                printt("Please enter both values / variables");
                break;
            }

            place = getvariable[var];

            place2 = -1;

            if (!AllDig(val))
            {
                place2 = getvariable[val];
            }

            if (place2 == 0 || place == 0)
            {
                if (place == 0)
                {
                    printt("I'm sorry, there is no variable named " << var);
                    getvariable.erase(var);
                }
                if (place2 == 0)
                {

                    printt("I'm sorry, there is no variable named " << val);
                    getvariable.erase(val);
                }
            }
            else
            {

                if (place2 == -1)
                {
                    variables[place].minus(val);

                    if (comments)
                        printt("The value of variable " << var << " has been subtracted");
                }
                else
                {
                    variables[place].minus(variables[place2].get());

                    if (comments)
                        printt("The value of variable " << var << " has been subtracted with " << val);
                }
            }

            break;
        case '%':

            if (val.length() == 0)
            {
                printt("Please enter both values / variables");
                break;
            }

            place = getvariable[var];

            place2 = -1;

            if (!AllDig(val))
            {
                place2 = getvariable[val];
            }

            if (place2 == 0 || place == 0)
            {
                if (place == 0)
                {
                    printt("I'm sorry, there is no variable named " << var);
                    getvariable.erase(var);
                }
                if (place2 == 0)
                {

                    printt("I'm sorry, there is no variable named " << val);
                    getvariable.erase(val);
                }
            }
            else
            {

                if (place2 == -1)
                {
                    variables[place].mod(val);

                    if (comments)
                        printt("The value of variable " << var << " has been modded");
                }
                else
                {
                    variables[place].mod(variables[place2].get());

                    if (comments)
                        printt("The value of variable " << var << " has been modded by " << val);
                }
            }

        case '^':

            if (val.length() == 0)
            {
                printt("Please enter both values / variables");
                break;
            }

            place = getvariable[var];

            place2 = -1;

            if (!AllDig(val))
            {
                place2 = getvariable[val];
            }

            if (place2 == 0 || place == 0)
            {
                if (place == 0)
                {
                    printt("I'm sorry, there is no variable named " << var);
                    getvariable.erase(var);
                }
                if (place2 == 0)
                {

                    printt("I'm sorry, there is no variable named " << val);
                    getvariable.erase(val);
                }
            }
            else
            {

                if (place2 == -1)
                {
                    variables[place].pow(val);

                    if (comments)
                        printt("The value of variable " << var << " has been exponentiated");
                }
                else
                {
                    variables[place].pow(variables[place2].get());

                    if (comments)
                        printt("The value of variable " << var << " has been exponentiated with " << val);
                }
            }

            break;
        case '=':

            if (val.length() == 0)
            {
                printt("Please enter both values / variables");
                break;
            }

            if (AllDig(var))
            {
                printt("You can not assign a value to a number - math has already done that");
                break;
            }

            place = getvariable[var];

            place2 = -1;

            if (!AllDig(val))
            {
                place2 = getvariable[val];
            }

            if (place2 == 0)
            {
                printt("I'm sorry, there is no variable named " << val);
                getvariable.erase(val);

                if (place == 0)
                {
                    getvariable.erase(var);
                }
            }
            else
            {

                if (place == 0)
                {
                    if (place2 == -1)
                    {
                        variables.push_back(bigInt(val));
                        getvariable[var] = ++variableCount;

                        if (comments)
                            printt("A new variable " << var << " has been created");
                    }
                    else
                    {
                        variables.push_back(variables[place2]);
                        getvariable[var] = ++variableCount;

                        if (comments)
                            printt("A new variable " << var << " has been created with the value of variable " << val);
                    }
                }
                else
                {
                    if (place2 == -1)
                    {
                        variables[place].set(val);

                        if (comments)
                            printt("The value of variable " << var << " has been replaced");
                    }
                    else
                    {
                        variables[place].set(variables[place2].get());

                        if (comments)
                            printt("The value of variable " << var << " has been replaced with the value of variable " << val);
                    }
                }
            }

            break;
        case '!':

            // ind = input.find("!");

            // var = input.substr(0, ind);

            // if (var.length() == 0)
            // {
            //     printt("Please enter the variable");
            //     break;
            // }

            place = getvariable[var];

            if (place == 0)
            {
                printt("I'm sorry, there is no variable named " << var);
                getvariable.erase(var);
            }
            else
            {
                variables[place].factorial();
                if (comments)
                    printt("The variable " << var << " has been factorialed");
            }

            break;

        default:

            printt("I'm sorry, something went wrong and I didn't understand your request");
            break;
        }
    }
    /*
    possible action values and its meaning:

    s - show number     - Done
    c - compare         - Done
    i - increment       - Done
    d - decrement       - Done (needs minus to work)
    * - multiply        - Done
    / - divide          - Done
    + - plus            - Done
    - - minus           - Done
    % - mod             - Done
    = - assign value    - Done
    ! = factorial       - Done

    Other commands:

    stop / quit / exit - stops the program          - Done
    show - shows the number                         - Done
    help - show the help menu                       - Done
    showall - shows all variables                   - Done
    comments - toggles whether comments are shown   - Done
    del / delete - deletes a variable               - Done

    */
}

/*


TODO:

get all the current function working, 

factorial will only work when minus does


must not let you create variables with only numbers

allow you to say 4 * 8, and return the output (if the first number is not a variable)

allow them to use ; to put multiple statements on 1 line 

something like 5- -4 will probably break it

make help text much neater and better


*/

