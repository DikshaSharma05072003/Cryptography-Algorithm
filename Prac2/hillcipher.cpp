#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

//ENCRYPTION
int removeSpaces(string plain, int ps)
{
    int i, count = 0;
    for (i = 0; i < ps; i++){
        if (plain[i] != ' ')
            plain[count++] = plain[i];
    }
    plain[count] = '\0';
    return count;
}
string HillCipher(string str, string key, string ct)
{
    int pt = str.length();
    pt = removeSpaces(str,pt);
    int keyMatrix[pt][pt];
    int k = 0;
    for (int i = 0; i < pt; i++){
        for (int j = 0; j < pt; j++){
            keyMatrix[i][j] = (key[k]-'A') ;
            k++;
        }
    }

    int strVector[pt][1];
    for (int i = 0; i < pt; i++){
        strVector[i][0] = (str[i]-'A');
    }
    int cipherMatrix[pt][1];

    int x, i, j;
    for (i = 0; i < pt; i++){
        cipherMatrix[i][0] = 0;
        for (x = 0; x < pt; x++){
            cipherMatrix[i][0] += keyMatrix[i][x] * strVector[x][0];
        }
        cipherMatrix[i][0] = cipherMatrix[i][0] % 26;
    }
    for (int i = 0; i < pt; i++){
        ct += cipherMatrix[i][0] + 65;
    }
    return ct;
}

//DECRYPTION
int modInverse(int a, int m){
    a=a%m;
    for(int x=-m;x<m;x++)
       if((a*x)%m==1)
          return x;
}
void getCofactor(vector<vector<int> > &a, vector<vector<int> > &temp, int p, int q, int n){
    int i=0,j=0;
    for(int row=0;row<n;row++){
        for(int col=0;col<n;col++){
            if(row!=p&&col!=q){
                temp[i][j++] = a[row][col];
                if (j==n-1){
                    j=0;
                    i++;
                }
            }
        }
    }
}
int determinant(vector<vector<int> > &a, int n, int N){
    int D = 0;
    if(n==1)
        return a[0][0];
    vector<vector<int> > temp(N, vector<int>(N));
    int sign = 1;
    for(int f=0;f<n;f++){
        getCofactor(a, temp, 0, f, n);
        D += sign * a[0][f] * determinant(temp, n - 1, N);
        sign = -sign;
    }
    return D;
}
void adjoint(vector<vector<int> > &a,vector<vector<int> > &adj,int N){
    if(N == 1){
        adj[0][0] = 1;
        return;
    }
    int sign = 1;
    vector<vector<int> > temp(N, vector<int>(N));
    for(int i=0;i<N;i++){
        for(int j=0;j<N;j++){
            getCofactor(a, temp, i, j, N);
            sign = ((i+j)%2==0)? 1: -1;
            adj[j][i] = (sign)*(determinant(temp, N-1 , N));
        }
    }
}
bool inverse(vector<vector<int> > &a, vector<vector<int> > &inv, int N){
    int det = determinant(a, N, N);
    if(det == 0){
        cout << "Inverse does not exist";
        return false;
    }
    int invDet = modInverse(det,26);
    vector<vector<int> > adj(N, vector<int>(N));
    adjoint(a, adj, N);
    for(int i=0;i<N;i++)
        for(int j=0;j<N;j++)
            inv[i][j] = (adj[i][j]*invDet)%26;
    return true;
}
string hilldecryption(string s, string key, string ct)
{
    int x,y,i,j,k,n;
    n = s.length();
    k = 0;
    vector<vector<int> > a(n, vector<int>(n));
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            a[i][j] = (key[k]-'A');
            k++;
        }
    }
    vector<vector<int> > adj(n, vector<int>(n));
    vector<vector<int> > inv(n, vector<int>(n));

    if(inverse(a,inv,n)){
        cout<<"Inverse exist\n";
    }

    k=0;
    while(k<s.size()){
        for(i=0;i<n;i++){
            int sum = 0;
            int temp = k;
            for(j=0;j<n;j++){
                sum += ((inv[i][j] + 26)%26*(s[temp++]-'A')%26)%26;
                sum = sum%26;
            }
            ct+=(sum+'A');
        }
        k+=n;
    }
    int f=ct.size()-1;
    while(ct[f]=='X'){
        f--;
    }
    for(i=0;i<=f;i++){
        cout<<ct[i];
    }
    cout<<'\n';
return ct;
}

int main()
{
    string key = "GYBNQKURP";
    string str;
    ifstream in("hillcipher_ip.txt");
    ofstream oo("hillcipher_op.txt");
    ofstream f("hillcipher_op.txt");
    int opt;
    cout<<"1. Encryption    2. Decryption\n";
    cout<<"Enter your choice: ";
    cin>>opt;
    while(getline(in, str)){
        string ct;
        if(opt==1){

            ct = HillCipher(str, key, ct);
            f <<"Cipher text: "<< ct << endl;

        }else{
            ct = hilldecryption(str,key,ct);
            oo <<"Cipher text: "<< ct << endl;
        }
    }
    in.close();
      f.close();
        oo.close();
    return 0;
}
