#include <iostream>
#include <vector>
#include <chrono>
#include <time.h> 
#include <boost/multiprecision/cpp_int.hpp> 
#include <sstream>

using namespace std;
using namespace boost::multiprecision;

bool numb(const string& s)
{
    string::const_iterator itr = s.begin();
    while (itr != s.end() && isdigit(*itr))
        ++itr;
    return !s.empty() && itr == s.end();
}

int modB(int new_ch, int b) {
    while (new_ch < 0)
        new_ch += b;
    return new_ch % b;
}

bool allzeros(vector <int> w) {
    bool x = true;
    for (int i = 0; i < w.size(); i++)
    {
        if (w[i] != 0) {
            x = false;
            break;
        }
    }
    return x;
}

int main()
{
    setlocale(LC_ALL, "rus");
    int j = 0;
    int k = 0;
    int b = 10;
    string w1S = "";
    cout << "Вычитание чисел.\n\n";
    while (true) {
        cout << "Введите первое число: ";
        getline(cin, w1S);
        stringstream myStream(w1S);
        if (numb(w1S))
            break;
        cout << endl << "Ошибка. Введите целое n >= 0" << endl;
    }
    while (w1S[0] == '0') {
        w1S.erase(0, 1);
    }
    string w2S = "";
    while (true) {
        cout << "Введите второе число: ";
        getline(cin, w2S);
        stringstream myStream(w2S);
        if (numb(w2S))
            break;
        cout << endl << "Ошибка. Введите целое n >= 0" << endl;
    }
    while (w2S[0] == 0) {
        w2S.erase(0, 1);
    }
    cpp_int w1boost(w1S);
    cpp_int w2boost(w2S);
    bool flagMesto = false;
    int w1Ssize = size(w1S);
    int w2Ssize = size(w2S);
    vector <int> w1, w2;
    int n = max(w1Ssize, w2Ssize);
    bool flag_rav = false;
    if (w1Ssize == w2Ssize) {
        flag_rav = true;
        w1.resize(n);
        w2.resize(n);
        bool w1Bw2 = false;
        bool stop_if = false;
        for (int i = 0; i < w1Ssize; i++)
        {
            w1[i] = w1S[i] - '0';
            w2[i] = w2S[i] - '0';
            if (!stop_if) {
                if (w1[i] > w2[i]) {
                    w1Bw2 = true;
                    stop_if = true;
                }
                else if (w1[i] < w2[i]) {
                    w1Bw2 = false;
                    stop_if = true;
                }
            }
            if (w1[i] >= b || w2[i] >= b)
            {
                cout << "Ошибка. Система счисления не совпадает с одним из введенных чисел";
                return 0;
            }
        }
        if (!w1Bw2) {
            vector <int> dop_w(n);
            dop_w = w2;
            w2 = w1;
            w1 = dop_w;
        }
    }
    else if (w1Ssize > w2Ssize) {
        w1.resize(n);
        w2.resize(n);
        for (int i = 0; i < w1Ssize; i++)
        {
            w1[i] = w1S[i] - '0';
            if (w1[i] >= b)
            {
                cout << "Ошибка. Система счисления не совпадает с одним из введенных чисел";
                return 0;
            }
        }
        int zeros = n - w2Ssize;
        for (int i = 0; i < zeros; i++)
        {
            w2[i] = 0;
        }
        int i1 = 0;
        for (int i = zeros; i < w1Ssize; i++)
        {
            w2[i] = w2S[i1] - '0';
            i1++;
            if (w2[i] >= b)
            {
                cout << "Ошибка. Система счисления не совпадает с одним из введенных чисел";
                return 0;
            }
        }
    }
    else {
        w2.resize(n);
        w1.resize(n);
        for (int i = 0; i < w2Ssize; i++)
        {
            w1[i] = w2S[i] - '0';
            if (w1[i] >= b)
            {
                cout << "Ошибка. Система счисления не совпадает с одним из введенных чисел";
                return 0;
            }
        }
        int zeros = n - w1Ssize;
        for (int i = 0; i < zeros; i++)
        {
            w2[i] = 0;
        }
        int i1 = 0;
        for (int i = zeros; i < w2Ssize; i++)
        {
            w2[i] = w1S[i1] - '0';
            i1++;
            if (w2[i] >= b)
            {
                cout << "Ошибка. Система счисления не совпадает с одним из введенных чисел";
                return 0;
            }
        }
    }
    vector <int> w(n, 0);
    auto startMy = chrono::high_resolution_clock::now();
    while (j < n)
    {
        int razr = n - 1;
        int new_ch = w1[razr - j] - w2[razr - j] + k;
        w[n - 1 - j] = modB(new_ch, b);
        k = floor((float)new_ch / b);
        j++;
    }
    auto endMy = chrono::high_resolution_clock::now();
    chrono::duration<float> duration = endMy - startMy;
    cout << endl << "Результат: ";
    int w_0 = 0;
    while (w[w_0] == 0) {
        w_0++;
        if (w_0 >= w.size())
            break;
    }
    for (int i = w_0; i < w.size(); i++)
    {
        cout << w[i];
    }
    if (allzeros(w))
        cout << 0;
    if (b == 10) {
        auto startBoost = chrono::high_resolution_clock::now();
        cpp_int wboost = w1boost - w2boost;
        auto endBoost = chrono::high_resolution_clock::now();
        chrono::duration<float> durationBoost = endBoost - startBoost;
        cout << endl << "Время выполнения моей реализации: " << duration.count() << " секунд";
        cout << endl << "Время выполнения реализации boost: " << durationBoost.count() << " секунд";
    }
    else {
        cout << endl << "Время выполнения моей реализации: " << duration.count() << " секунд";
    }
}