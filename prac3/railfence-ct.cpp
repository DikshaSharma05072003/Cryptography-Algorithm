#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void encrypt(int key)
{
    ifstream fin;
    ofstream fout;
    fin.open("in.txt");
    fout.open("op.txt");

    string line;

    while (getline(fin, line)){
        int rows = 0, n = 0;
        for (int i = 0; i < line.length(); i++){
            if (line[i] != ' '){
                n++;
            }
        }
        if (n % key == 0){
            rows = n / key;
        }else{
            rows = n / key + 1;
        }
        vector<vector<char> > text(rows, vector<char>(key, '*'));
        int i = 0;
        for (int j = 0; j < rows; j++){
            for (int l = 0; l < key; l++){
                if (i < line.length() && line[i] == ' '){
                    i++;
                }
                if (i < line.length()){
                    text[j][l] = line[i];
                    i++;
                }else{
                    break;
                }
            }
        }
        for (int j = 0; j < rows; j++){
            for (int l = 0; l < key; l++){
                cout << text[j][l] << " ";
            }
            cout << endl;
        }
        string out;
        for (int j = 0; j < key; j++){
            for (int l = 0; l < rows; l++){
                if (text[l][j] == '*'){
                    continue;
                }
                out.append(1, text[l][j]);
            }
        }
        fout <<"\n"<< out;
    }
    fin.close();
    fout.close();
}

void decrypt(int key)
{
    ifstream fin;
    ofstream fout;
    fin.open("in.txt");
    fout.open("op.txt");
    string line;

    while (getline(fin, line)){
        int rows = 0;
        int n = 0;
        for(int i = 0; i < line.length(); i++){
            if (line[i] != ' '){
                n++;
            }
        }
        if (n % key == 0){
            rows = n / key;
        }else{
            rows = n / key + 1;
        }
        vector<vector<char> > text(rows, vector<char>(key, '*'));
        int i = 0;
        int rem = line.length() % key;
        int count = 0;
        int y = rows;
        for (int j = 0; j < key; j++){
            for (int l = 0; l < y; l++){
                if (i < line.length()){
                    text[l][j] = line[i];
                    i++;
                }else{
                    break;
                }
            }
            count++;
            if (count == rem){
                y=y-1;
            }
        }
        string out;
        for (int j = 0; j < rows; j++){
            for (int l = 0; l < key; l++){
                if (text[j][l] == '*'){
                    continue;
                }
            out.append(1, text[j][l]);
            }
        }
        fout <<"\n"<< out;
    }
    fin.close();
    fout.close();
}

int main()
{
    int key;
    cout << "Enter the key : ";
    cin >> key;
    int opt;
    cout<<"1. Encryption  2. Decryption ";
    cin>>opt;
    if(opt==1){
        encrypt(key);
    }else if(opt==2){
        decrypt(key);
    }

}
