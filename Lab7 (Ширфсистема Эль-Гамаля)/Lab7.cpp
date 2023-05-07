#include "LongArithmetic.h"

map <char, string> book { {'0', "11"}, {'1', "12"}, {'2', "13"}, {'3', "14"}, {'4', "15"}, {'5', "16"}, {'6', "17"}, {'7', "18"}, {'8', "19"}, {'9', "21"},
                            {' ', "22"}, {'!', "23"}, {'"', "24"}, {'#', "25"}, {'$', "26"}, {'%', "27"}, {'^', "28"}, {'&', "29"}, {'\'', "31"}, {'(', "32"},
                            {')', "33"}, {'*', "34"}, {'+', "35"}, {',', "36"}, {'-', "37"}, {'.', "38"}, {'/', "39"}, {':', "41"}, {';', "42"}, {'<', "43"},
                            {'=', "44"}, {'>', "45"}, {'?', "46"}, {'@', "47"}, {'[', "48"}, {'\\', "49"}, {']', "51"}, {'_', "52"}, {'`', "53"}, {'{', "54"},
                            {'}', "55"}, {'|', "56"}, {'~', "57"}, {'\n', "58"}, {'а', "59"}, {'б', "61"}, {'в', "62"}, {'г', "63"}, {'д', "64"}, {'е', "65"},
                            {'ё', "66"}, {'ж', "67"}, {'з', "68"}, {'и', "69"}, {'й', "71"}, {'к', "72"}, {'л', "73"}, {'м', "74"}, {'н', "75"}, {'о', "76"},
                            {'п', "77"}, {'р', "78"}, {'с', "79"}, {'т', "81"}, {'у', "82"}, {'ф', "83"}, {'х', "84"}, {'ц', "85"}, {'ч', "86"}, {'ш', "87"},
                            {'щ', "88"}, {'ъ', "89"}, {'ы', "91"}, {'ь', "92"}, {'э', "93"}, {'ю', "94"}, {'я', "95"} };

map <string, char> bookRvs{ {"11", '0'}, {"12", '1'}, {"13", '2'}, {"14", '3'}, {"15", '4'}, {"16", '5'}, {"17", '6'}, {"18", '7'}, {"19", '8'}, {"21", '9'},
                            {"22", ' '}, {"23", '!'}, {"24", '"'}, {"25", '#'}, {"26", '$'}, {"27", '%'}, {"28", '^'}, {"29", '&'}, {"31", '\''}, {"32", '('},
                            {"33", ')'}, {"34", '*'}, {"35", '+'}, {"36", ','}, {"37", '-'}, {"38", '.'}, {"39", '/'}, {"41", ':'}, {"42", ';'}, {"43", '<'},
                            {"44", '='}, {"45", '>'}, {"46", '?'}, {"47", '@'}, {"48", '['}, {"49", '\\'}, {"51", ']'}, {"52", '_'}, {"53", '`'}, {"54", '{'},
                            {"55", '}'}, {"56", '|'}, {"57", '~'}, {"58", '\n'}, {"59", 'а'}, {"61", 'б'}, {"62", 'в'}, {"63", 'г'}, {"64", 'д'}, {"65", 'е'},
                            {"66", 'ё'}, {"67", 'ж'}, {"68", 'з'}, {"69", 'и'}, {"71", 'й'}, {"72", 'к'}, {"73", 'л'}, {"74", 'м'}, {"75", 'н'}, {"76", 'о'},
                            {"77", 'п'}, {"78", 'р'}, {"79", 'с'}, {"81", 'т'}, {"82", 'у'}, {"83", 'ф'}, {"84", 'х'}, {"85", 'ц'}, {"86", 'ч'}, {"87", 'ш'},
                            {"88", 'щ'}, {"89", 'ъ'}, {"91", 'ы'}, {"92", 'ь'}, {"93", 'э'}, {"94", 'ю'}, {"95", 'я'} };

set <char> workSymbs{ '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', ' ', '!', '\"', '#', '$', '%', '^', '&', '\'', '(', ')', '*', '+', ',', '-', '.', '/',
                        ':', ';', '<', '=', '>', '?', '@', '[', '\\', ']', '_', '`', '{', '}', '|', '~', '\n', 'а', 'б', 'в', 'г', 'д', 'е', 'ё', 'ж', 'з',
                        'и', 'й', 'к', 'л', 'м', 'н', 'о', 'п', 'р', 'с', 'т', 'у', 'ф', 'х', 'ц', 'ч', 'ш', 'щ', 'ъ', 'ы', 'ь', 'э', 'ю', 'я' };

set <char> upSymbs{ 'А', 'Б', 'В', 'Г', 'Д', 'Е', 'Ё', 'Ж', 'З', 'И', 'Й', 'К', 'Л', 'М', 'Н', 'О', 'П',
                    'Р', 'С', 'Т', 'У', 'Ф', 'Ч', 'Ц', 'Ч', 'Ш', 'Щ', 'Ъ', 'Ы', 'Ь', 'Э', 'Ю', 'Я' };


/////////////////////////////////////////////////////////////////////РЕЖИМ ГЕНЕРАЦИИ КЛЮЧЕЙ///////////////////////////////////////////////////////////////////
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


set <string> fact(string n) {
    set <string> res;

    while (division(n, "2").second == "0") {
        n = division(n, "2").first;
        res.insert("2");
    }

    string del = "3";
    while (n != "1") {
        if (division(n, del).second == "0") {
            n = division(n, del).first;
            res.insert(del);
        }
        else
            del = addition(del, "1");
    }

    return res;
}


string genericG(set <string> mults, string p) {
    string g, pDec = subtraction(p, "1");
    urbanShaurma:while (true) {
        string gBin = "";
        int gBinSize = rand() % 50 + 1;
        for (int i = 0; i < gBinSize; i++)
            gBin = gBin + to_string(rand() % 2);
        g = division(decForm(gBin), p).second;
        if (g == "0" || g == "1")
            continue;

        for (auto it : mults)
            if (exponentiation(g, division(pDec, it).first, p) == "1")
                goto urbanShaurma;
        return g;
    }
}


void genericKeys() {
    string p;
    while (true) {
        cout << "\np = ";
        cin >> p;
        if (p == "q")
            return;
        else if (miller_rabin(p))
            break;
        else
            cout << p << " - не простое число!\n";
    }

    string pDec = subtraction(p, "1");
    set <string> multsPdec = fact(pDec);
    string  g = genericG(multsPdec, p);
    cout << "g = " << g << endl;

    string xBin = "";
    int xBinSize = rand() % 50;
    for (int i = 0; i < xBinSize; i++)
        xBin = xBin + to_string(rand() % 2);
    string x = division(decForm(xBin + "11"), pDec).second;
    cout << "x = " << x << endl;

    string y = exponentiation(g, x, p);
    cout << "y = " << y << endl;

    ofstream fout;
    fout.open("keys.txt");
    fout << "p = " << p << "\ng = " << g << "\nx = " << x << "\ny = " << y;
    fout.close();
    cout << "Ключи успешно записаны в файл \"keys.txt\"\n";
}


//////////////////////////////////////////////////////////////////////РЕЖИМ ШИФРОВАНИЯ///////////////////////////////////////////////////////////////////////
vector <string> getKeys() {
    vector <string> keys;
    ifstream fin;
    while (true) {
        string fileKeys;
        cout << "\nФайл с ключами (по умолчанию keys.txt): ";
        getline(cin, fileKeys);
        if (fileKeys == "")
            fileKeys = "keys.txt";

        fin.open(fileKeys);
        if (fin.is_open())
            break;
        else
            cout << "Файл " << fileKeys << " не найден! \n";
    }

    string str;
    while (getline(fin, str))
        keys.push_back(str.substr(4));

    return keys;
}


string clearText() {
    ifstream fin;
    string fileText;
    while (true) {
        cout << "\nФайл с текстом (по умолчанию default.txt): ";
        getline(cin, fileText);
        if (fileText == "")
            fileText = "default.txt";

        fin.open(fileText);
        if (fin.is_open())
            break;
        else
            cout << "Файл " << fileText << " не найден! \n";
    }

    cout << "Была произведена очистка текста от неизвестных символов и приведение к нижнему регистру. Получившийся текст: \n";
    ofstream fout("clear_" + fileText);
    char el;
    string codeSymbs = "";
    while (fin.get(el)) {
        if (upSymbs.find(el) != upSymbs.end()) {
            cout << char(el + 32);
            fout << char(el + 32);
            codeSymbs += book[char(el + 32)];
        }
        else if (workSymbs.find(el) == workSymbs.end())
            continue;
        else {
            cout << el;
            fout << el;
            codeSymbs += book[el];
        }
    }

    fin.close();
    fout.close();
    return codeSymbs;
}


string nod(string x, string y) {
    string r = division(y, x).second;
    if (r == "0")
        return x;
    else
        return nod(r, x);
}


void encryption() {
    vector <string> keysPGXY = getKeys();
    string p = keysPGXY[0], g = keysPGXY[1], x = keysPGXY[2], y = keysPGXY[3];
    cout << "p = " << p << "\ng = " << g << "\nx = " << x << "\ny = " << y << endl;
    string codeSymbs = clearText();
    cout << "\n\nТекст, представленный в виде кодов его символов: " << codeSymbs;

    cout << "\n\nШифртекст (сохранён в файл encrypted.txt): ";
    ofstream fout("encrypted.txt");
    int offset = p.size();
    for (int i = 0; i < codeSymbs.length(); i += offset) {
        string M = codeSymbs.substr(i, offset);
        if (division(M, p).first != "0") {
            M.pop_back();
            i--;
        }

        string k = "2", pDec = subtraction(p, "1");
        int offset = pDec.length();
        while (nod(k, pDec) != "1") {
            string kBin = "";
            int kBinSize = rand() % offset;
            for (int i = 0; i < kBinSize; i++)
                kBin = kBin + to_string(rand() % 2);
            k = division(decForm(kBin + "1"), p).second;
        }

        string a = exponentiation(g, k, p), b = division(multiplication(exponentiation(y, k, p), M), p).second;
        cout << "(" << a << "," << b << ") ";
        fout << "(" << a << "," << b << ") ";
    }
    cout << endl;
}


/////////////////////////////////////////////////////////////////////РЕЖИМ РАСШИФРОВАНИЯ//////////////////////////////////////////////////////////////////////
void decryption() {
    vector <string> keysPGXY = getKeys();
    string p = keysPGXY[0], g = keysPGXY[1], x = keysPGXY[2], y = keysPGXY[3];
    cout << "p = " << p << "\ng = " << g << "\nx = " << x << "\ny = " << y << endl;

    ifstream fin;
    string fileText;
    while (true) {
        cout << "\nФайл с шифртекстом (по умолчанию encrypted.txt): ";
        getline(cin, fileText);
        if (fileText == "")
            fileText = "encrypted.txt";

        fin.open(fileText);
        if (fin.is_open())
            break;
        else
            cout << "Файл " << fileText << " не найден! \n";
    }

    string codeSymbs = "";
    cout << "Шифртекст: \n";
    string str = "", a = "", b = "", pDec = subtraction(p, "1");
    char el;
    while (fin.get(el)) {
        cout << el;
        if (el == '(') {
            a = "";
            b = "";
        }
        else if (el == ',') {
            a = str;
            str = "";
        }
        else if (el == ')') {
            b = str;
            str = "";
            codeSymbs += division(multiplication(b, exponentiation(a, subtraction(pDec, x), p)), p).second; //b * a^(p-1-x) mod p
        }
        else if (isdigit(el))
            str += el;
    }

    cout << "\n\nТекст, представленный в виде кодов его символов: " << codeSymbs << endl;

    cout << "\nРасшифрованный текст (сохранён в файле decrypter.txt): \n";
    ofstream fout("decrypter.txt");
    for (int i = 0; i < codeSymbs.length(); i += 2) {
        string M = codeSymbs.substr(i, 2);
        if (bookRvs.find(M) == bookRvs.end())
            continue;
        cout << bookRvs[M];
        fout << bookRvs[M];
    }
    cout << endl;

    fin.close();
    fout.close();
}


int main() {
    srand(time(0));
    setlocale(LC_ALL, "ru");
    cout << "\t Шифрсистема Эль-Гамаля (с использование реализованного текста Миллера-Рабина) \nq - выход \n";

    for (;;) {
        string mode;
        cout << "\nРежим работы: 1) Генерация ключей; 2) Шифрование; 3) Дешифрование;\n";

        while (true) {
            getline(cin, mode);
            if (mode == "")
                continue;
            if (mode == "q")
                return 0;
            if (mode == "1" || mode == "2" || mode == "3")
                break;
            cout << "Выбранного режима работы не существует!\n";
        }

        if (mode == "1")
            genericKeys();
        else if (mode == "2")
            encryption();
        else if (mode == "3")
            decryption();
    }

    return 0;
}
