#include <iostream>
#include <string>

using namespace std;

static const int LEN = 1004;

string str, n10;

string ctoInverse(int a[], int len) {
    string s;
    for (int i = 0; i < len; i++) {
        s.push_back((char) (a[len - i - 1] + '0'));
    }
    return s;
}

string itoStr(int a) {
    int c[LEN], bit = 0;
    string result;
    while (a > 0) {
        c[bit] = a % 10;
        a /= 10;
        bit++;
    }
    result = ctoInverse(c, bit);

    return result;
}

string add(string s1, string s2) {
    if (s1.length() < s2.length())
        swap(s1, s2);
    int len1 = s1.length(), len2 = s2.length();
    int a[LEN], b[LEN], c[LEN];
    for (int i = 0; i < LEN - 1; i++)
        a[i] = b[i] = c[i] = 0;

    for (int i = 0; i < len1; i++)
        a[i] = s1[len1 - i - 1] - '0';
    for (int i = 0; i < len2; i++)
        b[i] = s2[len2 - i - 1] - '0';

    for (int i = 0; i < len1; i++)
        c[i] += a[i] + b[i];

    for (int i = 0; i < len1; i++) {
        if (c[i] >= 10) {
            c[i + 1] += 1;
            c[i] -= 10;
        }
    }

    int len3 = len1 + len2;
    while (c[len3] == 0) {
        len3--;
    }
    len3++;
    string result = ctoInverse(c, len3);
    return result;
}

string mul(string s1, string s2) {
    int len1 = s1.length(), len2 = s2.length();
    int a[LEN], b[LEN], c[LEN];
    for (int i = 0; i < LEN - 1; i++)
        a[i] = b[i] = c[i] = 0;
    for (int i = 0; i < len1; i++)
        a[i] = s1[len1 - i - 1] - '0';
    for (int i = 0; i < len2; i++)
        b[i] = s2[len2 - i - 1] - '0';

    for (int i = 0; i < len1; i++) {
        for (int j = 0; j < len2; j++) {
            c[i + j] += a[i] * b[j];
        }
    }

    for (int i = 0; i < len1 + len2; i++) {
        if (c[i] >= 10) {
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    }

    int len3 = len1 + len2;
    while (c[len3] == 0) {
        len3--;
    }
    len3++;
    string result = ctoInverse(c, len3);
    return result;
}

bool greater_eq(int a[], int b[], int last_dg, int len) {
    if (a[last_dg + len] != 0) return true;
    for (int i = len - 1; i >= 0; --i) {
        if (a[last_dg + i] > b[i]) return true;
        if (a[last_dg + i] < b[i]) return false;
    }
    return true;
}

pair<string, string> div(string s1, string s2) {
    int a[LEN], b[LEN], c[LEN], d[LEN];
    int len1 = s1.length(), len2 = s2.length();
    for (int i = 0; i < LEN - 1; i++)
        a[i] = b[i] = c[i] = d[i] = 0;
    for (int i = 0; i < len1; i++)
        a[i] = s1[len1 - i - 1] - '0';
    for (int i = 0; i < len2; i++)
        b[i] = s2[len2 - i - 1] - '0';

    int la, lb;
    for (la = LEN - 1; la > 0; --la)
        if (a[la - 1] != 0) break;
    for (lb = LEN - 1; lb > 0; --lb)
        if (b[lb - 1] != 0) break;

    for (int i = 0; i < la; ++i) d[i] = a[i];
    for (int i = la - lb; i >= 0; --i) {
        while (greater_eq(d, b, i, lb)) {
            for (int j = 0; j < lb; ++j) {
                d[i + j] -= b[j];
                if (d[i + j] < 0) {
                    d[i + j + 1] -= 1;
                    d[i + j] += 10;
                }
            }
            c[i] += 1;
        }
    }
    int len3 = len1;
    while (c[len3] == 0 && len3 > 0) {
        len3--;
    }
    len3++;
    string result_1 = ctoInverse(c, len3);

    int len4 = len1;
    while (d[len4] == 0 && len4 > 0) {
        len4--;
    }
    len4++;
    string result_2 = ctoInverse(d, len4);
    pair<string, string> result(result_1, result_2);
    return result;
}


int alert(int n1, int n2, int len1) {
    if (!(n1 >= 2 && n1 <= 16 && n2 >= 2 && n2 <= 16)) {
        cout << "error" << endl;
        return 1;
    }

    for (int i = 0; i < len1; i++) {
        if (n1 <= 10) {
            if (!(str[i] >= '0' && str[i] < (char) (n1 + '0'))) {
                cout << "error" << endl;
                return 1;
            }
        } else {
            if (!((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] < (char) (n1 - 10 + 'a')))) {
                cout << "error" << endl;
                return 1;
            }
        }

    }
    return 0;
}

string kpow(string a, int b) {
    string result = "1";
    while (b > 0) {
        if (b & 1) result = mul(result, a);
        a = mul(a, a);
        b >>= 1;
    }
    return result;
}

string converter(string decimal, const string &base) {
    string result = "";
    while (decimal != "0") {
        pair<string, string> tmp1 = div(decimal, base);
        string remainder = tmp1.second;
        if (remainder.size() > 2) {
            remainder = to_string(stoi(remainder) - 10 + 'a');
        }
        result = remainder + result;
        pair<string, string> tmp2 = div(decimal, base);
        decimal = tmp2.first;
    }
    return result;
}

int main() {
    int n1, n2;
    cout << "Source base: ";
    cin >> n1;
    cout << "Input string: ";
    cin >> str;
    cout << "Target base: ";
    cin >> n2;
    int len1 = str.length();

    if (alert(n1, n2, len1)) return 1;

    for (int i = 0; i < len1; i++) {
        if (isalpha(str[i])) {
            n10 = add(n10, mul(kpow(to_string(n1), len1 - i - 1), to_string((int) str[i] - 'a' + 10)));
        } else if (isdigit(str[i])) {
            n10 = add(n10, mul(kpow(to_string(n1), len1 - i - 1), to_string((int) str[i] - '0')));
        }
    }

    cout << "Target String: " << converter(n10, to_string(n2));

    return 0;
}