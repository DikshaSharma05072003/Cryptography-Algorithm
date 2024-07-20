#include<bits/stdc++.h>
#include <fstream>
using namespace std;

string charToBinary(char c) {
    string binary;
    for (int i = 7; i >= 0; i--) {
        binary.push_back((c & (1 << i)) ? '1' : '0');
    }
    return binary;
}
char binaryTochar(string s)
{
    string num = s;
    int dec_value = 0;
    int base = 1;

    int len = num.length();
    for (int i = len - 1; i >= 0; i--) {
        if (num[i] == '1')
            dec_value += base;
        base = base * 2;
    }
    char st= static_cast<char>(dec_value);
    return st;
}

void encrypt(char k1, char k2)
{
    char c1,c2;
    string kk1 = charToBinary(k1);
    string kk2 = charToBinary(k2);
    cout<<kk1<<" "<<kk2<<"\n";

    ifstream in("inp.txt");
    ofstream op("out.txt");

    while(in.get(c1)&& in.get(c2)){
        string s1 = charToBinary(c1);
        string s2 = charToBinary(c2);
        cout<<s1<<" "<<s2<<"\n";
        string l1,r1,l2,r2;
        l1 = s2;
        for(int i=0;i<8;i++){
            r1.push_back(s2[i]^kk1[i]^s1[i]);
        }
        cout<<l1<<" "<<r1<<"\n";
        for(int i=0;i<8;i++){
            r2.push_back(r1[i]^kk2[i]^l1[i]);
        }
        l2 = r1;
        cout<<l2<<" "<<r2<<"\n";
        char nn1 = binaryTochar(l2);
        char nn2 = binaryTochar(r2);
        cout<<nn1<<" "<<nn2<<"\n";
        op<<nn1<<nn2<<" ";
    }
}
void decrypt(char k1, char k2)
{
    char c1,c2;
    string kk1 = charToBinary(k1);
    string kk2 = charToBinary(k2);
    cout<<kk1<<" "<<kk2<<"\n";

    ifstream in("inp.txt");
    ofstream op("out.txt");
    char temp;
    while(in.get(c1)&& in.get(c2)){
        temp = c1;
        c1 = c2;
        c2 = temp;
        string s1 = charToBinary(c1);
        string s2 = charToBinary(c2);
        cout<<s1<<" "<<s2<<"\n";
        string l1,r1,l2,r2;
        l1 = s2;
        for(int i=0;i<8;i++){
            r1.push_back(s2[i]^kk2[i]^s1[i]);
        }
        cout<<l1<<" "<<r1<<"\n";
        for(int i=0;i<8;i++){
            r2.push_back(r1[i]^kk1[i]^l1[i]);
        }
        l2 = r1;
        cout<<l2<<" "<<r2<<"\n";
        char nn1 = binaryTochar(l2);
        char nn2 = binaryTochar(r2);
        temp = nn1;
        nn1 = nn2;
        nn2 = temp;
        cout<<nn1<<" "<<nn2<<"\n";

        op<<nn1<<nn2<<" ";
    }
}
int main()
{
    char k1 = 'A';
    char k2 = 'B';
    int opt;
    cout<<"1. Encryption   2. Decryption"<<endl;
    cin>>opt;
    if(opt==1){
        encrypt(k1,k2);
    }else if(opt==2){
        decrypt(k1,k2);
    }

    return 0;
}
