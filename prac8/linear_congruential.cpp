#include<bits/stdc++.h>
using namespace std;
void find_random_numbers(int a, int c, int m, int xo, int r_min, int r_max, int n){
    ofstream op("lout.txt");
    vector<int> r(n);
    r[0] = xo;
    for(int i=1;i<n;i++){
        int x = (r[i-1]*a)+c;
        x = x%m;
        cout<<x<<" ";
        r[i] =x;
    }    
    for(int i=0;i<n;i++){
        r[i] = ((r_max-r_min)*(r[i]))/(m-1)+r_min;
        cout<<r[i]<<endl;
        op << r[i] << " ";
    }
    op.close();
}
int main(){
    fstream file;
    string word;
    file.open("linp.txt");
    vector<string> v;
    while (file >> word){
        v.push_back(word);
    }
    file.close();
    int a = stoi(v[0]);
    int c = stoi(v[1]);
    int m = stoi(v[2]);
    int xo = stoi(v[3]);
    int r_min = stoi(v[4]);
    int r_max = stoi(v[5]);
    int n = stoi(v[6]);
    cout<<a<<" "<<c<<" "<<m<<" "<<xo<<" "<<r_min<<" "<<r_max<<" "<<n<<" "<<endl;
    find_random_numbers(a,c,m,xo,r_min,r_max,n);
    return 0;
}