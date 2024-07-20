#include<bits/stdc++.h>
using namespace std;
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
bool isPrimitiveRoot(int a, int p) {
    vector<bool> visited(p, false);
    int x = 1;
    for (int i = 0; i < p - 1; i++) {
        x = (x * a) % p;
        if (visited[x]) return false;
        visited[x] = true;
    }
    return true;
}
int calc_alpha(int p) {
    vector<int> factors;
    int phi = p - 1;
    int n = phi;
    for (int i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0)
                n /= i;
        }
    }
    if (n > 1)
        factors.push_back(n);
    for (int res = 2; res <= p; res++) {
        bool ok = true;
        for (int factor : factors) {
            if (pow(res, phi / factor) == 1) {
                ok = false;
                break;
            }
        }
        if (ok && isPrimitiveRoot(res, p))
            return res;
    }
    return -1; 
}
void find_key(int Xa, int Xb, int q)
{
    int alpha = calc_alpha(q);
    cout << "Alpha: " << alpha <<endl;
    long long int Ya =  power(alpha, Xa, q);
    long long int Yb = power(alpha, Xb, q);
    cout<<"Ya: "<<Ya<<"\nYb: "<<Yb<<endl;
    long long int k1 = power(Yb, Xa, q);
    long long int k2 = power(Ya, Xb, q);
    cout<<"K1: "<<k1<<"\n"<<"K2: "<<k2<<endl;
}
int main()
{
    fstream file;
    string word;

    file.open("keyinp.txt");
    vector<string> v;
    while (file >> word)
    {
        v.push_back(word);
    }
    file.close();
    int Xa = stoi(v[0]);
    int Xb = stoi(v[1]);
    int q = stoi(v[2]);
    cout<<Xa<<" "<<Xb<<" "<<q<<endl;
    find_key(Xa,Xb,q);
    return 0;
}