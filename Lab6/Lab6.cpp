#include "iostream"
#include "string"
#include "algorithm"

using namespace std;
string decForm(string x) {
    long long res = 0, deg = 1;
    if (x.back() == '1')
        res += 1;
    for (int i = 1; i < x.length(); i++) {
        deg = deg * 2;
        if (x[x.length() - i - 1] == '1')
            res += deg;
    }
    return to_string(res);
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


string addition(string num1, string num2, int b = 10) {
    num1 = cleaning(num1);
    num2 = cleaning(num2);
    if (num1.length() < num2.length())
        while (num1.length() < num2.length())
            num1 = '0' + num1;
    else
        while (num2.length() < num1.length())
            num2 = '0' + num2;

    string res = "";
    int n = num1.length(), k = 0;

    for (int j = n - 1; j >= 0; j--) {
        char u0 = num1[j], v0 = num2[j];
        int u = (int)u0 - 48, v = (int)v0 - 48;
        res = to_string((u + v + k) % b) + res;
        k = (u + v + k) / b;
    }
    if (k == 1)
        res = '1' + res;

    res = cleaning(res);
    return res;
}


string subtraction(string num1, string num2, int b = 10) {
    num1 = cleaning(num1);
    num2 = cleaning(num2);

    while (num1.length() > num2.length())
        num2 = "0" + num2;

    string res = "";
    int n = num1.length(), k = 0;

    for (int j = n - 1; j >= 0; j--) {
        char u0 = num1[j], v0 = num2[j];
        int u = (int)u0 - 48, v = (int)v0 - 48;
        res = to_string((u - v + k + b) % b) + res;
        k = (u - v + k - b + 1) / b;
    }

    res = cleaning(res);
    return res;
}


string multiplication(string num1, string num2, int b = 10) {
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
            res[i + j] = (char)(t % b + 48);
            k = t / b;
        }
        res[j + m] = (char)(k + 48);
    }

    reverse(res.begin(), res.end());
    res = cleaning(res);
    return res;
}


string pow(int x, int n) {
    string res = "1";
    for (int i = 0; i < n; i++)
        res = multiplication(res, to_string(x));
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

    q = cleaning(q);
    return make_pair(q, to_string(tmp));
}


pair<string, string> division(string num1, string num2, int b = 10) {
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
        int substrSize = substr.length();
        if (isFstMoreSnd(help, substr)) {
            substr = subtraction(pow(b, n + 1), subtraction(help, substr, 10), 10);
            while (substr.length() < substrSize)
                substr = "0" + substr;
            num1 = num1.substr(0, mn - (j + n) - 1) + substr + num1.substr(mn - j);
            q = q + to_string(q_);

            q.back() = (int)q.back() - 1;
            substr = num1.substr(mn - (j + n) - 1, n + 1);
            num1 = addition(substr, "0" + num2, 10) + num1.substr(mn - j);
        }
        else {
            substr = subtraction(substr, help, 10);
            while (substr.length() < substrSize)
                substr = "0" + substr;
            num1 = num1.substr(0, mn - (j + n) - 1) + substr + num1.substr(mn - j);
            q = q + to_string(q_);
        }
    }

    q = cleaning(q);
    string r = subtraction(num1copy, multiplication(num2copy, q, 10), 10);
    return make_pair(q, r);
}


string exponentiation(string num, string deg, string mod) {
    num = cleaning(num);
    deg = cleaning(deg);
    mod = cleaning(mod);
    if (mod == "0")
        return "Hеопределённость!";
    else if (mod == "1")
        return "0";
    else if (deg == "0")
        return "1";

    string N = deg, Y = "1", Z = num;
    for (;;) {
        string prevN = N;
        N = simpleDiv(N, "2").first;
        if ((prevN.back() - 48) % 2 != 0) {
            Y = division(multiplication(Z, Y, 10), mod, 10).second;
            if (N == "0")
                return Y;
        }
        Z = division(multiplication(Z, Z, 10), mod, 10).second;
    }
}


bool miller_rabin(string n, int k = 10) {
    if (n == "0" || n == "1")
        return false;

    string d = subtraction(n, "1");
    int s = 0;
    while (division(d, "2").second == "0") {
        s++;
        d = division(d, "2").first;
    }

    string nDec = subtraction(n, "1");
    for (int i = 0; i < k; i++) {
        string a = division(to_string(rand()), nDec).second;
        if (a == "0" || a == "1")
            a = addition(a, "2");

        string x = exponentiation(a, d, n);
        if (x == "1" || x == nDec)
            continue;

        bool flag = false;
        for (int j = 0; j < s; j++) {
            x = division(multiplication(x, x), n).second;
            if (x == nDec) {
                flag = true;
                break;
            }
        }
        if (!flag)
            return false;
    }

    return true;
}


string generateG(string q) {
    string s, p = "2", pDec;
    while (!miller_rabin(p)) {
        string sBin = "";
        int sBinSize = rand() % 50 + 1;
        for (int i = 0; i < sBinSize; i++)
            sBin = sBin + to_string(rand() % 2);
        s = decForm(sBin);

        p = addition(multiplication(q, s), "1");
        pDec = subtraction(p, "1");
    }

    string a = "2";
    while (isFstMoreSnd(pDec, a)) {
        string g = exponentiation(a, division(pDec, q).first, p);
        if (g == "1") {
            a = addition(a, "1");
            continue;
        }

        cout << "\ns = " << s << "\np = " << p << "\ng = " << g << "\ng ^ q (mod p) = " << exponentiation(g, q, p) << endl;
        return g;
    }
}

int main() {
    srand(time(0));
    setlocale(LC_ALL, "ru");
    cout << "\t Нахождение элемента g из Zp порядка q \nq - выход \n";

    for (;;) {
        string q;

        while (true) {
            cout << "\nЧисло q: ";
            cin >> q;
            if (q == "q")
                return 0;
            if (isNumIn10(q))
                break;
            cout << "Данное число не принадлежит положительной 10-й СС!";
        }

        if (!miller_rabin(q))
            cout << endl << q << " - составное число!\n";
        else
            generateG(q);
    }
    
    return 0;
}