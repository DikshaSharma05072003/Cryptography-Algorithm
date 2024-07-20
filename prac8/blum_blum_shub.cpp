#include <bits/stdc++.h>
#include <fstream>
using namespace std;
void find_random_numbers(int p,int q,int xo,int r_min,int r_max,int m){
    int n = p * q;
    ofstream op("bout.txt");
    vector<int> r(m);
    r[0] = xo;
    for (int i = 1; i < m; i++) {
        int bb = r[i - 1]*r[i-1];
        bb = bb % n;
        r[i] = bb;
    }
    for (int i = 0; i < m; i++){
        r[i] = ((r_max - r_min) * (r[i])) / (n - 1) + r_min;
        op << r[i] << " ";
    }
    op.close();
}
int main(){
    ifstream file;
    string word;
    file.open("binp.txt");
    vector<string> v;
    while (file >> word){
        v.push_back(word);
    }
    file.close();
    int p = stoi(v[0]);
    int q = stoi(v[1]);
    int xo = stoi(v[2]);
    int r_min = stoi(v[3]);
    int r_max = stoi(v[4]);
    int m = stoi(v[5]);
    cout << p << " " << q << " " << xo << " " << r_min << " " << r_max << " " << m << " " << endl;
    find_random_numbers(p, q, xo, r_min, r_max, m);
    return 0;
}