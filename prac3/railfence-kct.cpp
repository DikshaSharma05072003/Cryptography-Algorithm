#include <bits/stdc++.h>
#include <fstream>
using namespace std;

//ENCRYPTION
string railenc(string str, string key, string sss)
{
    int r, pr, ps=0, ks;
    for(int i=0;i<str.length();i++){
        if(str[i]!=' '){
            ps++;
        }
    }
    ks = key.length();
    pr = ps%ks;
    if(pr==0){
        r = ps/ks;
    }else{
        r = (ps/ks)+1;
    }
    int k=0;
    cout<<str<<"\n";
    vector<vector<char> > matrix(r, vector<char>(ks));
    for(int i=0;i<r;i++){
        if(i==r-1){
            for(int j=0;j<pr;j++){
                if(str[k]!=' '){
                    matrix[i][j] = str[k];
                    k++;
                }else{
                    k++;
                    j--;
                }
            }
        }else{
            for(int j=0;j<ks;j++){
                if(str[k]!=' '){
                    matrix[i][j] = str[k];
                    k++;
                }else{
                    k++;
                    j--;
                }
            }
        }
    }
    string s=key;
    sort(s.begin(),s.end());
    for(int i=0;i<key.length();i++){
        int ff =  key.find(s[i]);
        key[ff]='*';
        if(ff<pr){
            for(int j=0;j<r;j++){
                if(matrix[j][ff]=='*'){
                    continue;
                }
                sss.append(1,matrix[j][ff]);
            }
        }else{
            for(int j=0;j<r-1;j++){
                if(matrix[j][ff]=='*'){
                    continue;
                }
                sss.append(1,matrix[j][ff]);
            }
        }

    }
    for(int i=0;i<r;i++){
        for(int j=0;j<ks;j++){
            cout<<matrix[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<sss;
    return sss;
}

//DECRYPTION
string raildec(string line, string key, string sss)
{
    string s=key;
    sort(s.begin(),s.end());

    int col = key.size();
    int rows = 0;
    if (line.size()%col==0){
        rows=line.size()/col;
    }else{
        rows=line.size()/col+1;
    }
    int rem=line.length()%col;
    int count=0;

    vector<vector<char> > text(rows,vector<char>(col,'*'));
    int n=rows;
    int i=0;

    for(int j=0;j<key.size();j++){
        int num=key.find(s[j]);
        cout<<num<<endl;
        key[num]='*';
        for(int r=0;r<n;r++){
            text[r][num]=line[i];
            i++;
            count++;
        }
        if(count>=rem && n!=rows-1){
            n=n-1;
        }
    }
    for(int r=0;r<rows;r++){
        for(int j=0;j<col;j++){
            if(text[r][j]=='*'){
                break;
            }
            sss.append(1,text[r][j]);
        }
    }
    for(int i=0;i<rows;i++){
        for(int j=0;j<col;j++){
            cout<<text[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<sss;
    return sss;
}

int main()
{
    string str, key;
    cout<<"Enter the key: ";
    cin>>key;

    int opt;
    cout<<"1. Encryption    2. Decryption\n";
    cout<<"Enter your choice: ";
    cin>>opt;

    ifstream in("railfence-kct_inp.txt");
    ofstream f("railfence-kct_out.txt");


    while(getline(in, str)){
        string sss, ss;
        if(opt==1){
            ss = railenc(str,key, sss);
            f <<"Cipher text: "<< ss << endl;
        }else{
            ss = raildec(str,key,sss);
            f <<"Cipher text: "<< ss << endl;
        }
    }
    in.close();
    f.close();
    return 0;
}
