#include<bits/stdc++.h>
using namespace std;
int calc_d(int e, int On)
{
    int T1=0, T2=1;
    int A = e>On?e:On;
    int B = e>On?On:e;
    int R = A%B;
    int Q= A/B;
    int T = T1-(T2*Q);
    int matrix[7];
//  Q A B R T1 T2 T;
    matrix[0] = Q;
    matrix[1] = A;
    matrix[2] = B;
    matrix[3] = R;
    matrix[4] = T1;
    matrix[5] = T2;
    matrix[6] = T;
    while(matrix[3]!=0){
        matrix[1]=matrix[2];
        matrix[2]=matrix[3];
        matrix[4] = matrix[5];
        matrix[5] = matrix[6];
        matrix[0] = matrix[1]/matrix[2];
        matrix[3] = matrix[1]%matrix[2];
        matrix[6] = matrix[4]-(matrix[5]*matrix[0]);
        cout<<matrix[0]<<" "<<matrix[1]<<" "<<matrix[2]<<" "<<matrix[3]<<" "<<matrix[4]<<" "<<matrix[5]<<" "<<matrix[6]<<endl;
    }
    int d = matrix[5];
    cout<<d<<endl;
    return d;
}
int power(long long x, unsigned int y, int p)
{
    int res = 1;
    x = x % p;
    if (x == 0) return 0;
    while (y > 0) {
        if (y & 1)
            res = (res*x) % p;
        y = y>>1;
        x = (x*x) % p;
    }
    return res;
}
void encrypt(int n, int e)
{
    string s;
    ifstream pt("rsainp.txt");
    ofstream op("rsaop.txt");
    while(getline(pt,s)){
        for(int i=0;i<s.length();i++){
            //char c = s[i];
            int M = s[i];
            //cout<<c<<" "<<M;
            int ciph = power(M, e, n);
            //char ch = ciph;
            cout<<ciph<<endl;
            op<<ciph<<endl;
        }
    }
    pt.close();
    op.close();
}
void decrypt(int n, int d)
{
    string s;
    map<char,int> mp;
    for(int i=0;i<26;i++){
        mp[((char)('A'+i))] =  i;
    }
    ifstream pt("rsainp.txt");
    ofstream op("rsaop.txt");
    while(getline(pt,s)){
        //for(int i=0;i<s.length();i++){
            int M  = stoi(s);
            int ciph = power(M, d, n);
            //char ch = ciph;
            cout<<ciph<<endl;
            op<<ciph<<endl;
        //}
    }
    pt.close();
    op.close();
}
int gcd(int a, int b) {
   int t;
   while(1){
      t= a%b;
      if(t==0)
      return b;
      a = b;
      b= t;
   }
}
int main()
{
    int opt;
    cout<<"1. Encryption  2. Decryption "<<endl;
    cin>>opt;

    fstream file;
    string word;

    file.open("keyinp.txt");
    vector<string> v;
    while (file >> word)
    {
        v.push_back(word);
    }
    file.close();
    int p = stoi(v[0]);
    int q = stoi(v[1]);
    int e = stoi(v[2]);
    cout<<p<<" "<<q<<" "<<e<<endl;
    int n = p*q;
    int On = (p-1)*(q-1);
    cout<<On<<endl;
    while(e<On) {
       int track = gcd(e,On);
       if(track==1)
          break;
       else
          e++;
    }
    int d = calc_d(e, On);
    if(opt==1){
        encrypt(n,e);
    }else if(opt==2){
        decrypt(n, d);
    }
    return 0;
}
