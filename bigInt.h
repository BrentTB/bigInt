#include <bits/stdc++.h>
using namespace std;

#define print(x) cout<<x<<endl;

class bigInt
{
public:
    // Stores the current size of the number
    int size;

    // Stores whether the current number is negative
    bool negative = false;

    // Stores the individual digits of the number
    vector<int> num;

    // Creates a bigInt object from a long long (defaulted to 0)
    bigInt(long long numL = 0)
    {
        string numS = to_string(numL);

        bigIntHelp(numS);
    }
    // Creates a bigInt object from a string
    bigInt(string numS)
    {
        bigIntHelp(numS);
    }

    // Takes a long long and multiplies it by the bigInt object
    void multiply(long long numL)
    {
        string numS = to_string(numL);
        if (numS.length() <= 16)
        {
            multiplyHelpL(numL);
        }
        else
        {
            multiplyHelpS(numS);
        }
    }
    // Takes a string and multiplies it by the bigInt object
    void multiply(string numS)
    {

        if (numS.length() <= 16) // 9999987678999999
        {
            multiplyHelpL(stoll(numS));
        }
        else
        {
            multiplyHelpS(numS);
        }
    }

    // Takes a long long and divides it by the bigInt object
    void divide(long long numL)
    {
        string numS = to_string(numL);
        if (numS.length() <= 15)
        {
            divideHelpL(numL);
        }
        else
        {
            divideHelpS(numS);
        }
    }
    // Takes a string and divides it by the bigInt object
    void divide(string numS)
    {
        if (numS.length() <= 15)
        {
            divideHelpL(stoll(numS));
        }
        else
        {
            divideHelpS(numS);
        }
    }

    // Takes a long long and adds it to the bigInt object
    void add(long long numL)
    {
        string numS = to_string(numL);
        flip(numS);

        addHelp(numS);
    }
    // Takes a string and adds it to the bigInt object
    void add(string numS)
    {
        flip(numS);

        addHelp(numS);
    }

    // Takes a long long and minuses it from the bigInt object
    void minus(long long numL)
    {
        string numS = to_string(numL);
        flip(numS);

        minusHelp(numS);
    }
    // Takes a string and minuses it from the bigInt object
    void minus(string numS)
    {
        flip(numS);

        minusHelp(numS);
    }

    // Takes a long long and makes the bigInt the remainder when you divide them
    void mod(long long numL)
    {
    }
    // Takes a string and makes the bigInt the remainder when you divide them
    void mod(string numS)
    {
    }

    // Takes a long long and makes the bigInt the result of itself to the power of the input
    void pow(long long numL)
    {
    }
    // Takes a string and makes the bigInt the result of itself to the power of the input
    void pow(string numS)
    {
    }

    // Multiplies the number (n) by (n - 1), (n - 2),... (1)
    void factorial()
    {

        bigInt curNum = bigInt(get());
        while (curNum.get().compare("1") != 0)
        {
            curNum.dec();
            multiply(curNum.get());
        }
    }

    // Decreases the number by 1
    void dec()
    {
        minus(1);
    }
    // Increases the number by 1
    void inc()
    {
        add(1);
    }

    // Returns true if the long long entered is numerically equal to the bigIt object
    bool compare(long long numL)
    {
        string numS = to_string(numL);

        numS = getReady(numS);

        return numS.compare(get()) == 0;
    }
    // Returns true if the string entered is numerically equal to the bigIt object
    bool compare(string numS)
    {

        numS = getReady(numS);

        return numS.compare(get()) == 0;
    }

    // Sets the value of a bigInt object from a long long (defaulted to 0)
    void set(long long numL = 0)
    {
        string numS = to_string(numL);
        size = 0;
        num.clear();
        bigIntHelp(numS);
    }
    // Sets the value of a bigInt object from a string
    void set(string numS)
    {
        size = 0;
        num.clear();
        bigIntHelp(numS);
    }

    // Returns the string representation of the number
    string get()
    {

        string Snum = negative? "-":"";
        for (int i = size - 1; i >= 0; i--)
        {
            Snum += to_string(num[i]);
        }
        return Snum;
    }

private:
    // Flips a string, ie: the last and first digits swap, the second and second last...
    void flip(string &num)
    {

        int l = 0, r = num.length() - 1;

        while (r > l)
        {

            char tmp = num[l];
            num[l++] = num[r];
            num[r--] = tmp;
        }
    }

    // Takes a string, flips it, and pushes the digits back to an int array
    void bigIntHelp(string numS)
    {


        if (numS[0] == '-')
        {
            negative = true;
            numS = numS.substr(1, numS.length());
        }
        else
        {
            negative = false;
        }

        numS = getReady(numS);

        size = numS.length();

        num.reserve(size);
        for (int i = size - 1; i >= 0; i--)
        {
            num.push_back((numS[i] - '0'));
        }
    }

    // To help multiply when the number fits in a long long (this runs faster than the string method)
    void multiplyHelpL(long long numL)
    {

        long long carry = 0;
        for (int i = 0; i < size; i++)
        {

            long long numtmp = numL * num[i] + carry;

            num[i] = numtmp % 10;
            carry = floor(numtmp / 10);
        }
        while (carry != 0)
        {
            num.push_back(carry % 10);
            size++;
            carry = floor(carry / 10);
        }

        set(getReady(get()));
    }

    // To help multiply when the number does not fit in a long long
    void multiplyHelpS(string numS)
    {

        string carry = "";
        for (int i = 0; i < size; i++)
        {
            bigInt numtmp = bigInt(numS);
            numtmp.multiply(num[i]);
            numtmp.add(carry);

            string get = numtmp.get();

            num[i] = get[get.length() - 1] - '0';

            carry = get.substr(0, get.length() - 1);
        }
        while (carry.compare("") != 0)
        {
            num.push_back(carry[carry.length() - 1] - '0');
            size++;
            carry = carry.substr(0, carry.length() - 1);
        }

        set(getReady(get()));
    }

    // To help divide when the number fits in a long long (this runs faster than the string method)
    void divideHelpL(long long numL)
    {
    }
    //not sure if ill need booth of these or not
    // To help divide when the number does not fit in a long long
    void divideHelpS(string numS)
    {
    }

    // To help add to the bigInt
    void addHelp(string numS)
    {

        int sizeT = numS.length();

        for (int i = sizeT; i < size; i++)
        {
            numS += "0";
        }
        for (int i = size; i < sizeT; i++)
        {
            num.push_back(0);
            size++;
        }

        long long carry = 0;
        for (int i = 0; i < size; i++)
        {
            long long numtmp = (numS[i] - '0') + num[i] + carry;

            num[i] = numtmp % 10;
            carry = floor(numtmp / 10);
        }

        if (carry != 0)
        {
            num.push_back(carry);
            size++;
        }

        set(getReady(get()));
    }

    // To help minus from the bigInt
    void minusHelp(string numS)
    {
    }

    // To help mod the bigInt
    void modHelp(string numS) {

    }

    // To help bring the bigInt to a power
    void powHelp(string numS) {

    }

    // Removes preceding zero's from the number
    string getReady(string numS)
    {

        // int on = negative ? 1 : 0;
        int on = 0;
        while (on < numS.length() - 1 && numS[on] == '0')
        {
            on++;
        }
        if (on > 0)
            numS = numS.substr(on, numS.length() - on);

        return numS;
    }
};

/*
TODO: 
exponent
modulus
get things like minus working
allow negative numbers
decimal places?
greater than, smaller than

allow it to use any base (Number entered could be 23AF3) - even if just bases less than 10 (like 2 for binary)

if i have greater than, then i can do say 4 - 500 by saying 500 is bigger, so make the negative true (or !negative) and then do 500 - 4


*/