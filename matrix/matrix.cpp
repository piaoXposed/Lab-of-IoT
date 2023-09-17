#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
using namespace std;
#define MAX 150

int matrix1[MAX][MAX], matrix2[MAX][MAX], m1, n1, m2, n2;
clock_t start1,end1,start2,end2;
void read() {
    cout << "Matrix1 m, n: ";
    cin >> m1 >> n1;
    cout << "Matrix2 m, n: ";
    cin >> m2 >> n2;
    cout << "Matrix 1 (m*n): " << endl;
    for (int i = 0; i < m1; i++)
        for (int j = 0; j < n1; j++)
            cin >> matrix1[i][j];
    cout << "Matrix 2 (m*n): " << endl;
    for (int i = 0; i < m2; i++)
        for (int j = 0; j < n2; j++)
            cin >> matrix2[i][j];
}

void print(int a[][MAX], int column, int line) {
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < line; j++) {
            cout << a[i][j] << " ";
        }
        cout << endl;
    }
}

void clear(int a[][MAX]) {
    for (int i = 0; i < MAX; i++)
        for (int j = 0; j < MAX; j++)
            a[i][j] = 0;
}

int alert(string s, int column1, int line1, int column2, int line2) {
    if (s == "add") {
        if (column1 != column2 || line1 != column2) {
            return 1;
        }
    } else if (s == "mul") {
        if (line1 != column2) {
            return 1;
        }
    } else if(s == "square"){
        if(column1!=line1 || column2!=line2 || column1!=column2){
            return 1;
        }
    }
    return 0;
}

int trans(int a[][MAX], int column, int line) {
    int result[MAX][MAX];
    clear(result);
    swap(column, line);
    for (int i = 0; i < column; i++)
        for (int j = 0; j < line; j++)
            result[i][j] = a[j][i];
    cout << "Transition of matrix1: " << endl;
    print(result, column, line);
}

int add(int a[][MAX], int b[][MAX], int column1, int line1, int column2, int line2) {
    if (alert("add", column1, line1, column2, line2)) {
        cout << "error";
        return 1;
    }
    int result[MAX][MAX];
    clear(result);
    for (int i = 0; i < column1; i++)
        for (int j = 0; j < line1; j++)
            result[i][j] = a[i][j] + b[i][j];
    cout << "Adding matrix1 with matrix2: " << endl;
    print(result, column1, line1);
}

int mul1(int a[][MAX], int b[][MAX], int column1, int line1, int column2, int line2) {
    start1=clock();

    if (alert("mul", column1, line1, column2, line2)) {
        cout << "error";
        return 1;
    }
    int result[MAX][MAX];
    clear(result);
    //for(int i=1000000;i>0;i--)
    //    i--;
    for (int i = 0; i < column1; i++) {
        for (int j = 0; j < line2; j++) {
            for (int k = 0; k < line1; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    cout << "Multiplication of matrix1 and matrix2 in O(n3): " << endl;
    print(result, column1, line2);
    end1 = clock();
    return 0;
}
void submul(int a[][MAX], int b[][MAX], int column, int result[][MAX]) {//square
    clear(result);
    for (int i = 0; i < column; i++) {
        for (int j = 0; j < column; j++) {
            for (int k = 0; k < column; k++) {
                result[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
void subadd(int a[][MAX], int b[][MAX], int column, int result[][MAX]) {//square
    clear(result);
    for (int i = 0; i < column; i++)
        for (int j = 0; j < column; j++)
            result[i][j] = a[i][j] + b[i][j];
}
int mul2(int a[][MAX], int b[][MAX], int column1, int line1, int column2, int line2){
    start2 =clock();

    if (alert("square", column1, line1, column2, line2)) {
        cout << "error: not square";
        return 1;
    }
    bool flag=false;
    if(column1%2==1){
        column1++;
        flag=true;
    }
    int result[MAX][MAX];
    clear(result);
    int half=column1/2;
    int ma[MAX][MAX],mb[MAX][MAX],mc[MAX][MAX],md[MAX][MAX],me[MAX][MAX],mf[MAX][MAX],mg[MAX][MAX],mh[MAX][MAX];
    //clear(ma);clear(mb);clear(mc);clear(md);clear(me);clear(mf);clear(mg);clear(mh);
    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++)
            ma[i][j]=a[i][j];
    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++)
            mb[i][j]=a[i][half+j];
    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++)
            mc[i][j]=a[half+i][j];
    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++)
            md[i][j]=a[half+i][half+j];

    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++)
            me[i][j]=b[i][j];
    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++)
            mf[i][j]=b[i][half+j];
    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++)
            mg[i][j]=b[half+i][j];
    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++)
            mh[i][j]=b[half+i][half+j];

    int mae[MAX][MAX],mbg[MAX][MAX],maf[MAX][MAX],mbh[MAX][MAX],mce[MAX][MAX],mdg[MAX][MAX],mcf[MAX][MAX],mdh[MAX][MAX];
    submul(ma,me,half,mae);submul(mb,mg,half,mbg);
    submul(ma,mf,half,maf);submul(mb,mh,half,mbh);
    submul(mc,me,half,mce);submul(md,mg,half,mdg);
    submul(mc,mf,half,mcf);submul(md,mh,half,mdh);
    int c11[MAX][MAX],c12[MAX][MAX],c21[MAX][MAX],c22[MAX][MAX];
    subadd(mae, mbg,half, c11);
    subadd(maf, mbh,half, c12);
    subadd(mce, mdg,half, c21);
    subadd(mcf, mdh,half,c22);

    for(int i=0;i<half;i++)
        for(int j=0;j<half;j++)
            result[i][j]=c11[i][j];
    for(int i=0;i<half;i++)
        for(int j=half;j<column1;j++)
            result[i][j]=c12[i][j-half];
    for(int i=half;i<column1;i++)
        for(int j=0;j<half;j++)
            result[i][j]=c21[i-half][j];
    for(int i=half;i<column1;i++)
        for(int j=half;j<column1;j++)
            result[i][j]=c22[i-half][j-half];
    if(flag)
        column1--;

    cout<<"Multiplication of matrix1 and matrix2 using Strassen:"<<endl;
    print(result,column1,column1);

    end2 = clock();
    return 0;
}
void generate_matrix(){
    m1=n1=m2=n2=100;
    for(int i=0;i<m1;i++){
        for(int j=0;j<n1;j++){
            matrix1[i][j]=rand()%10;
            matrix2[i][j]=rand()%10;
        }
    }
    cout<<"Matrix1 :"<<endl;
    print(matrix1,m1,n1);
    cout<<"Matrix2 :"<<endl;
    print(matrix2,m2,n2);
}
int main() {
    //read();
    generate_matrix();
    trans(matrix1, m1, n1);
    add(matrix1, matrix2, m1, n1, m2, n2);

    mul1(matrix1, matrix2, m1, n1, m2, n2);
    mul2(matrix1, matrix2, m1, n1, m2, n2);//square only

    cout<<"Time in O(n3): "<<double(end1-start1)/CLOCKS_PER_SEC<<"s"<<endl;
    cout<<"Time using Strassen: "<<double(end2-start2)/CLOCKS_PER_SEC<<"s"<<endl;
    return 0;
}