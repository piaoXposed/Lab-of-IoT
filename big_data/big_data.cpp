#include<iostream>
#include<string>
#include<cstdlib>

#define LEN 1004
using namespace std;

//int *stoInverse(string s) {
//    int len = s.length();
//    int static c[LEN];
//    for (int i = 0; i < len; i++) {
//        c[i] = s[len - i - 1] - '0';
//    }
//    return c;
//}

string ctoInverse(int a[], int len) {
    string s;
    for (int i = 0; i < len; i++) {
        s.push_back((char) (a[len - i - 1] + '0'));
    }
    return s;
}

string add(string s1, string s2) {
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
    //if (lb == 0) {
    //    puts("> <");
    //    return;
    //}

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
    while (c[len3] == 0) {
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

int main() {
    string A, B;
    for (int i = 1; i <= 50 + rand() % 10; i++)
        A.push_back((char) (rand() % 10 + '0'));
    for (int i = 1; i <= 50 + rand() % 10; i++)
        B.push_back((char) (rand() % 10 + '0'));
    cout << "A: " << A << endl << "B: " << B << endl;
    if (A.length() < B.length())
        swap(A, B);
    cout << "A+B: " << add(A, B) << endl << "A*B: " << mul(A, B) << endl;
    pair<string, string> div_result = div(A, B);
    cout << "A/B: " << div_result.first << endl << "A%B: " << div_result.second;
    return 0;
}
