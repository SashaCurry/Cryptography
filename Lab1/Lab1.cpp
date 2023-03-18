#include "iostream"
#include "string"
#include "chrono"
#include "boost/multiprecision/cpp_int.hpp"

using namespace std;
using namespace boost::multiprecision;
string addition(string num1, string num2, int mod) {
    string res = "";
    int n = num1.length(), k = 0;

    for (int j = n - 1; j >= 0; j--) {
        char u0 = num1[j], v0 = num2[j];
        int u = (int)u0 - 48, v = (int)v0 - 48;
        res = to_string((u + v + k) % mod) + res;
        k = (u + v + k) / mod;
    }
    if (k == 1)
        res = '1' + res;

    return res;
}


bool isNumIn10(string num) {
    for (int i = 0; i < num.length(); i++)
        //if (num[i] != '0' && num[i] != '1' && num[i] != '2' && num[i] != '3' && num[i] != '4' &&
            //num[i] != '5' && num[i] != '6' && num[i] != '7' && num[i] != '8' && num[i] != '9')
        if (!isdigit(num[i]))
            return false;
    return true;
}


void numberSystem10(string num1, string num2) {
    cpp_int boostX(num1), boostY(num2);

    if (num1.length() < num2.length())
        while (num1.length() < num2.length())
            num1 = '0' + num1;
    else
        while (num2.length() < num1.length())
            num2 = '0' + num2;

    auto begin = std::chrono::steady_clock::now();
    string res = addition(num1, num2, 10);
    while (res[0] == '0' && res.size() > 1)
        res.erase(0, 1);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "\nСумма: " << res << "\nВремя выполнения: " << elapsed_ms.count() << "мc\n";

    begin = std::chrono::steady_clock::now();
    cpp_int boostRes = boostX + boostY;
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "\nСумма (с помощью встроенной библиотеки): " << boostRes << "\nВремя выполнения (с помощью встроенной библиотеки): ";
    cout << elapsed_ms.count() << "мc\n";
}


int main() {
    setlocale(LC_ALL, "ru");
    cout << "\t Сложение неотрицательных целых чисел в 10 системе счисления\n";
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
            cout << "Данное число не принадлежит 10-й СС!";
        }
        while (true) {
            cout << "2-е число: ";
            cin >> num2;
            if (num2 == "q")
                return 0;
            if (isNumIn10(num2))
                break;
            cout << "Данное число не принадлежит 10-й СС!\n";
        }

        numberSystem10(num1, num2);
        cout << endl;
    }
}