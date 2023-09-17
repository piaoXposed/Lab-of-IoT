#include<iostream>

using namespace std;

int queen[10];
int king[10][10], n, ans;

bool check1(int a[], int row) {
    for (int i = 1; i < row; i++)
        if ((abs(a[row] - a[i]) == row - i) || (a[i] == a[row]))
            return false;
    return true;
}

void print_1(int a[]) {
    for (int i = 1; i <= 8; i++)
        cout << a[i];
    cout << endl;
}

void dfs_1(int row) {
    if (row > n) {
        ans++;
        print_1(queen);
    } else {
        for (int i = 1; i <= n; i++) {
            queen[row] = i;
            if (check1(queen, row))
                dfs_1(row + 1);
        }
    }
}

/*bool check_1(int x, int y){
    for(int i=1;i<=n;i++)
        if(king[x][i] || king[i][y])
            return false;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(abs(x-i)==abs(y-j) && king[i][j])
                return false;
    return true;
}
void print_1(){
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++)
            cout<<king[i][j]<<" ";
        cout<<endl;
    }
    cout<<endl;
}

string king_to_str(int a[][10]){
    string str="";
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(a[i][j])
                str.push_back((char)(j+'0'));
    return str;
}
string ans_king[102];
bool not_same(){
    string str=king_to_str(king);
    for(int i=1;i<100;i++)
        if(ans_king[i]==str)
            return false;
    return true;
}

void dfs_1(int k, int row){
    if(k>n){
        if(not_same()){
            ans++;
            ans_king[ans]=king_to_str(king);
            print_1();
        }
    }else{
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++){
                if(check_1(i,j)){
                    king[i][j]=1;
                    dfs_1(k+1, row+1);
                    king[i][j]=0;
                }
            }
    }
}*/
bool check_2(int x, int y) {
    if (king[x][y] || king[x - 1][y] || king[x + 1][y] || king[x][y - 1] || king[x][y + 1] || king[x - 1][y - 1] ||
        king[x - 1][y + 1] || king[x + 1][y - 1] || king[x + 1][y + 1])
        return false;
    return true;
}

void print_2(int a[][10]) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++)
            cout << king[i][j] << " ";
        cout << endl;
    }
    cout << endl;
}

string str_ans_2[2010];

bool store_ans(int a[][10]) {
    string str = "";
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            str.push_back((char) (a[i][j]));

    bool flag = true;
    for (int i = 0; i < 2000; i++)
        if (str_ans_2[i] == str)
            flag = false;

    if (flag) {
        str_ans_2[ans++] = str;
        return true;
    } else
        return false;
}

void dfs_2(int k) {
    if (k > n) {
        if (store_ans(king)) {
            print_2(king);
        }
    } else {
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++) {
                if (check_2(i, j)) {
                    king[i][j] = 1;
                    dfs_2(k + 1);
                    king[i][j] = 0;
                }
            }
    }
}

int main() {
    /*n = 8;
    dfs_1(1);
    cout << "8 Queens Answer: " << ans;*/

    n = 4, ans = 0;
    dfs_2(1);
    cout << "4 Kings Answer: " << ans;
    return 0;
}