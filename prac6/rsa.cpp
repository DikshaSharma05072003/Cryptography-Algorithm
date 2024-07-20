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
}void encrypt(int e, int n)
{
    ifstream fin;
    fin.open("input.txt");
    ofstream fout;
    fout.open("output.txt");
    string line;
    map<char,int> m;
    for(int i=1;i<=26;i++)
    {
        char c='A'+i-1;
        m[c]=i;
    }
    
    while (getline(fin, line))
    {
        for (int i = 0; i < line.length(); i++)
        {
            char ch = line[i];
            int val=m[ch] ;
            int ans = power(val, e, n);
           
            char c=ans+65;
            fout<<c;
        }
        fout << endl;
    }
}

void decrypt(int d, int n)
{
    ifstream fin;
    fin.open("input.txt");
    ofstream fout;
    fout.open("output.txt");
    string line;
    map<char,int> m;
    for(int i=1;i<=26;i++)
    {
        char c='A'+i-1;
        m[c]=i;
    }
    while (getline(fin, line))
    {
        for (int i = 0; i < line.length(); i++)
        {
            char ch = line[i];
            int val=line[i]-65 ;
            int ans = power(val, d, n);
            
            char c;
            for(auto it=m.begin();it!=m.end();it++)
            {
                if(it->second==ans)
                {
                    c=it->first;
                }
            }
            fout<<c;
        }
        fout << endl;
    }
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
int calc_e(int e, int On)
{
    if(gcd(e,On)!=1){
        e=2;
        while(e<On){
            int track = gcd(e,On);
            if(track==1)
                break;
            else
                e++;
        }
    }
    return e;
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
    while (file >> word){
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
    e = calc_e(e, On);
    int d = calc_d(e, On);
    if(opt==1){
        encrypt(e, n);
    }else if(opt==2){
        decrypt( d, n);
    }
    return 0;
}
