﻿#include "iostream"
#include "string"
#include "algorithm"
#include "chrono"
#include "boost/multiprecision/cpp_int.hpp"

using namespace std;
using namespace boost::multiprecision;
int pow(int x, int n) {
    int res = 1;
    for (int i = 0; i < n; i++)
        res *= x;
    return res;
}


bool isNumIn10(string num) {
    for (int i = 0; i < num.length(); i++)
        if (!isdigit(num[i]))
            return false;
    return true;
}


string cleaning(string num) {
    while (num[0] == '0' && num.size() > 1)
        num.erase(0, 1);
    return num;
}


bool isFstMoreSnd(string num1, string num2) {
    num1 = cleaning(num1);
    num2 = cleaning(num2);

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

string subtraction(string num1, string num2, int mod) {
    num1 = cleaning(num1);
    num2 = cleaning(num2);

    string res = "";
    int n = num1.length(), k = 0;

    while (num1.length() > num2.length())
        num2 = "0" + num2;

    for (int j = n - 1; j >= 0; j--) {
        char u0 = num1[j], v0 = num2[j];
        int u = (int)u0 - 48, v = (int)v0 - 48;
        res = to_string((u - v + k + mod) % mod) + res;
        k = (u - v + k - mod + 1) / mod;
    }

    while (res[0] == '0' && res.length() > 1)
        res.erase(0, 1);
    return res;
}

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
    while (res[0] == '0' && res.length() > 1)
        res.erase(0, 1);
    return res;
}


pair<string, string> simpleDiv(string num1, string num2) {
    int x = num2[0] - 48;

    int tmp = 0;
    string q = "";
    for (int i = 0; i < num1.length(); i++) {
        tmp = tmp * 10 + int(num1[i]) - 48;
        q = q + to_string(tmp / x);
        tmp = tmp - x * (q.back() - 48);
    }

    while (q[0] == '0' && q.length() > 1)
        q.erase(0, 1);
    return make_pair(q, to_string(tmp));
}


pair<string, string> division(string num1, string num2, int b) {
    if (num2.length() == 1)
        return simpleDiv(num1, num2);
    else if (!isFstMoreSnd(num1, num2) && num1 != num2)
        return make_pair("0", num1);

    string num1copy = num1, num2copy = num2;
    int mn = num1.length(), n = num2.length();
    string q = "";

    int m = mn - n;

    int d = b / ((int)num2[0] - 48 + 1);
    num1 = multiplication(num1, to_string(d), 10);
    num2 = multiplication(num2, to_string(d), 10);
    if (num1.length() == mn)
        num1 = "0" + num1;

    for (int j = m; j >= 0; j--) {
        mn = num1.length(), n = num2.length();
        while (mn - (j + n) - 1 < 0) {
            num1 = "0" + num1;
            mn++;
        }

        int n1 = num1[mn - (j + n) - 1] - 48;
        int n2 = num1[mn - (j + n - 1) - 1] - 48;
        int n3 = num2[n - (n - 1) - 1] - 48;
        int q_ = (n1 * b + n2) / n3;
        int r_ = (n1 * b + n2) % n3;

        n1 = num2[n - (n - 2) - 1] - 48;
        n2 = num1[mn - (j + n - 2) - 1] - 48;
        if (q_ == b || q_ * n1 > b * r_ + n2) {
            q_ = q_ - 1;
            r_ = r_ + n3;
            if (r_ < b)
                if (q_ == b || q_ * n1 > b * r_ + n2) {
                    q_ = q_ - 1;
                    r_ = r_ + n3;
                }
        }

        string help = multiplication(to_string(q_), num2, 10);
        string substr = num1.substr(mn - (j + n) - 1, n + 1);
        if (isFstMoreSnd(help, substr)) {
            substr = subtraction(to_string(pow(b, n + 1)), subtraction(help, substr, 10), 10);
            num1 = num1.substr(0, mn - (j + n) - 1) + substr + num1.substr(mn - j);
            q = q + to_string(q_);

            q.back() = (int)q.back() - 1;
            substr = num1.substr(mn - (j + n) - 1, n + 1);
            num1 = addition(substr, "0" + num2, 10) + num1.substr(mn - j);
        }
        else {
            substr = subtraction(substr, help, 10);
            num1 = num1.substr(0, mn - (j + n) - 1) + substr + num1.substr(mn - j);
            q = q + to_string(q_);
        }
    }

    q = cleaning(q);
    string r = subtraction(num1copy, multiplication(num2copy, q, 10), 10);
    return make_pair(q, r);
}


int main() {
    setlocale(LC_ALL, "ru");
    cout << "\t Деление неотрицательных целых чисел в 10 системе счисления \nq - выход \n";

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

        num1 = cleaning(num1);
        num2 = cleaning(num2);

        if (num2 == "0") {
            cout << "Деление на 0 невозможно!\n";
            continue;
        }

        auto begin = std::chrono::steady_clock::now();
        pair<string, string> res = division(num1, num2, 10);
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        cout << endl << num1 << " / " << num2 << " = " << res.first << "\nОстаток: " << res.second << "\nВремя выполнения : " << elapsed_ms.count() << "мc \n";

        cpp_int boostX(num1), boostY(num2);
        begin = std::chrono::steady_clock::now();
        cpp_int boostRes = boostX / boostY;
        end = std::chrono::steady_clock::now();
        elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        cout << "Время выполнения (с помощью встроенной библиотеки): " << elapsed_ms.count() << "мc\n";

        cout << endl;
    }
}