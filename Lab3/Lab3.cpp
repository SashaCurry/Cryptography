#include "iostream"
#include "string"
#include "algorithm"
#include "chrono"
#include "boost/multiprecision/cpp_int.hpp"

using namespace std;
using namespace boost::multiprecision;
string multiplication(string num1, string num2, int mod) {
    reverse(num1.begin(), num1.end());
    reverse(num2.begin(), num2.end());
    int m = num1.length(), n = num2.length();
    string res = "";
    for (int i = 0; i < m + n; i++)
        res = res + "0";

    for (int j = 0; j < n; j++) {
        if (num2[j] == '0') {
            res[j + m] = '0';
            continue;
        }

        int k = 0;
        for (int i = 0; i < m; i++) {
            char u0 = num1[i], v0 = num2[j], w0 = res[i + j];
            int u = (int)u0 - 48, v = (int)v0 - 48, w = (int)w0 - 48;
            
            int t = u * v + w + k;
            res[i + j] = (char)(t % mod + 48);
            k = t / mod;
        }
        res[j + m] = (char)(k + 48);
    }

    reverse(res.begin(), res.end());
    return res;
}


bool isNumIn10(string num) {
    for (int i = 0; i < num.length(); i++)
        if (!isdigit(num[i]))
            return false;
    return true;
}


void numberSystem10(string num1, string num2) {
    cpp_int boostX(num1), boostY(num2);

    auto begin = std::chrono::steady_clock::now();
    string res = multiplication(num1, num2, 10);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    while (res[0] == '0' && res.size() > 1)
        res.erase(0, 1);
    cout << endl << num1 << " * " << num2 << " = " << res << "\nВремя выполнения: " << elapsed_ms.count() << "мc \n";

    begin = std::chrono::steady_clock::now();
    cpp_int boostRes = boostX - boostY;
    end = std::chrono::steady_clock::now();
    elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    cout << "Время выполнения (с помощью встроенной библиотеки): " << elapsed_ms.count() << "мc\n";
}


int main() {
    setlocale(LC_ALL, "ru");
    cout << "\t Умножение неотрицательных целых чисел в 10 системе счисления \nq - выход \n";

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

        numberSystem10(num1, num2);

        cout << endl;
    }
}