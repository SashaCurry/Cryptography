#include "iostream"
#include "string"
#include "chrono"
#include "boost/multiprecision/cpp_int.hpp"

using namespace std;
using namespace boost::multiprecision;
string subtraction(string num1, string num2, int mod) {
    string res = "";
    int n = num1.length(), k = 0;

    for (int j = n - 1; j >= 0; j--) {
        char u0 = num1[j], v0 = num2[j];
        int u = (int)u0 - 48, v = (int)v0 - 48;
        res = to_string((u - v + k + mod) % mod) + res;
        k = (u - v + k - mod + 1) / mod;
    }
    return res;
}


bool isNumIn10(string num) {
    for (int i = 0; i < num.length(); i++)
        if (!isdigit(num[i]))
            return false;
    return true;
}


bool isFstMoreSnd(string num1, string num2) {
    if (num1.length() > num2.length())
        return true;
    else if (num1.length() < num2.length())
        return false;
    for (int i = 0; i < num1.length(); i++) {
        char u0 = num1[i], v0 = num2[i];
        int u = (int)u0 - 48, v = (int)v0 - 48;
        if (u > v)
            return true;
        else if (u < v)
            return false;
    }
    return false;
}


void numberSystem10(string num1, string num2) {
    cpp_int boostX(num1), boostY(num2);
    string num1slave = num1, num2slave = num2;

    if (num1slave.length() < num2slave.length())
        while (num1slave.length() < num2slave.length())
            num1slave = '0' + num1slave;
    else
        while (num2slave.length() < num1slave.length())
            num2slave = '0' + num2slave;

    auto begin = std::chrono::steady_clock::now();
    string res = subtraction(num1slave, num2slave, 10);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    while (res[0] == '0' && res.size() > 1)
        res.erase(0, 1);
    cout << endl << num1 << " - " << num2 << " = " << res << "\nВремя выполнения: " << elapsed_ms.count() << "мc\n";

    begin = std::chrono::steady_clock::now();
    cpp_int boostRes = boostX - boostY;
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "\nВремя выполнения (с помощью встроенной библиотеки): " << elapsed_ms.count() << "мc\n";
}


int main() {
    setlocale(LC_ALL, "ru");
    cout << "\t Вычитание неотрицательных целых чисел в 10 системе счисления\n";
    cout << " q - выход \n";

    for (;;) {
        string num1, num2;
        
        while (true) {
            cout << "\n1-е число: ";
            cin >> num1;
            if (num1 == "q")
                return 0;
            if (isNumIn10(num1))
                break;
            cout << "Данное число не принадлежит положительной 10-й СС!";
        }
        while (true) {
            cout << "2-е число: ";
            cin >> num2;
            if (num2 == "q")
                return 0;
            if (isNumIn10(num2))
                break;
            cout << "Данное число не принадлежит положительной 10-й СС!\n";
        }

        while (num1[0] == '0' && num1.size() > 1)
            num1.erase(0, 1);
        while (num2[0] == '0' && num2.size() > 1)
            num2.erase(0, 1);

        if (isFstMoreSnd(num1, num2))
            numberSystem10(num1, num2);
        else
            numberSystem10(num2, num1);
        
        cout << endl;
    }
}