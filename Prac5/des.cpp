#include<bits/stdc++.h>
#include<fstream>
using namespace std;

void removeSpaces(string ssss)
{
    for(int i=0;i<ssss.length();i++){
        if(ssss[i]==' '){
            for(int j=i;i<ssss.length();j++){
                ssss[i]=ssss[i+1];
            }
        }
    }
}
string charToBinary(char c)
{
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
    if(dec_value>127){
        dec_value = dec_value%128;
    }
    char st= static_cast<char>(dec_value);
    return st;
}
string keyop(string kk)
{
    string kl1,kr1;
    for(int i=1;i<28;i++){
        kl1+=kk[i];
    }
    kl1+="0";
    //kl1+='\0';
    cout<<"KL1: "<<kl1<<endl;
    for(int i=29;i<56;i++){
        kr1+=kk[i];
    }
    kr1+="0";
    //kr1+='\0';
    cout<<"KR1: "<<kr1<<endl;
    string kkk="";
    for(int i=0;i<kl1.length();i++){
        kkk+=kl1[i];
    }
    for(int i=0;i<kr1.length();i++){
        kkk+=kr1[i];
    }
    cout<<kkk<<endl;
    return kkk;
}
string intial_permutation(string s)
{
    vector< vector<char>> v( 8 , vector<char> (8));
    int k=0;
    for(int i=7;i>=0;i--){
        int t=k+1;
        for(int j=4;j<8;j++){
            v[j][i] = s[k];
            k+=2;
        }
        for(int j=0;j<4;j++){
            v[j][i] = s[t];
            t+=2;
        }
    }
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            cout<<v[i][j]<<" ";
        }
        cout<<endl;
    }
    string str1;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            str1+=v[i][j];
        }
    }
    return str1;
}
string expansion_permutation(string r)
{
    int e_box[48] = {
        32,1,2,3,4,5,
        4,5,6,7,8,9,
        8,9,10,11,12,13,
        12,13,14,15,16,17,
        16,17,18,19,20,21,
        20,21,22,23,24,25,
        24,25,26,27,28,29,
        28,29,30,31,32,1
    };
    string ebx;
    for(int i=0;i<48;i++){
        int num = e_box[i];
        ebx+=(r[num-1]);
        cout<<num<<endl;
    }
    cout<<"E-box: "<<ebx<<endl;
    return ebx;
}
string dectobin(int n)
{
    string binary;
    while(n != 0) {
		binary = (n % 2 == 0 ? "0" : "1") + binary;
		n = n/2;
	}
	while(binary.length() < 4){
		binary = "0" + binary;
	}
    return binary;
}
string sbox(string s)
{
    int s_box[4][16] = {
        {14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7},
        {0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8},
        {4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0},
        {15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13}
    };
    string sbx;
    for(int i=0;i<48;i+=6){
        cout<<s[i]<<s[i+1]<<s[i+2]<<s[i+3]<<s[i+4]<<s[i+5]<<endl;
        int row = (s[i]-48)*2+(s[i+5]-48);
        int col = ((s[i+1]-48)*8)+((s[i+2]-48)*4)+((s[i+3]-48)*2)+(s[i+4]-48);
        int num = s_box[row][col];
        cout<<row<<" "<<col<<" "<<num<<endl;
        sbx+=(dectobin(num));
    }
    cout<<"S-Box: "<<sbx<<endl;
    return sbx;
}
string pbox(string s)
{
    string pp;
	int permutation_tab[32] = {
        16,7,20,21,29,12,28,17,
        1,15,23,26,5,18,31,10,
        2,8,24,14,32,27,3,9,
        19,13,30,6,22,11,4,25
    };
    for(int i=0;i<32;i++){
        int num = permutation_tab[i];
        pp+=(s[num-1]);
    }
    cout<<"P-Box: "<<pp<<endl;
    return pp;
}
string inv_ip(string l)
{
    int iip[64] = {
        40,8,48,16,56,24,64,32,
        39,7,47,15,55,23,63,31,
        38,6,46,14,54,22,62,30,
        37,5,45,13,53,21,61,29,
        36,4,44,12,52,20,60,28,
        35,3,43,11,51,19,59,27,
        34,2,42,10,50,18,58,26,
        33,1,41,9,49,17,57,25,
    };
    string iips="";
    for(int i=0;i<64;i++){
        int num = iip[i]-1;
        iips+=l[num];
    }
    cout<<"IIP: "<<" "<<iips<<endl;
    return iips;
}
int getdecimal(string text)
{
    int sum = 0;
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == '1')
        {
            sum += pow(2, text.size() - 1 - i);
        }
    }
    return sum;
}
void encrypt(string key)
{
    string ss;

    ifstream inp("inp.txt");
    ofstream out("op.txt");
    while(getline(inp, ss)){
        removeSpaces(ss);
        if(ss.length()%8!=0){
            int t = ss.length()%8;
            for(int k=0;k<t;k++){
                ss=ss+'X';
            }
        }
        string s,l1,r1;
        string kk;
        for(int i=0;i<key.length();i++){
            kk+=charToBinary(key[i]);
        }
        for(int i=0;i<ss.length();i+=8){
            for(int j=0;j<8;j++){
                s = s + charToBinary(ss[j]);
            }
            cout<<s<<endl;
            string is = intial_permutation(s);
            string kkk =keyop(kk);
            string key, xx, sbx;
            for(int i=0;i<48;i++){
                key+=kkk[i];
            }
            cout<<"KEY-48: "<<key<<endl;
            l1 = is.substr(0,32);
            r1 = is.substr(32,64);
            cout<<"L1: "<<l1<<endl;
            cout<<"R1: "<<r1<<endl;
            string es = expansion_permutation(r1);
            for(int i=0;i<48;i++){
                if(es[i]==key[i]){
                    xx+="0";
                }else{
                    xx+="1";
                }
            }
            cout<<"XOR"<<xx<<endl;
            string s_box = sbox(xx);
            string p_box = pbox(s_box);
            string l2,r2;
            for(int i=0;i<32;i++){
                if(l1[i]==p_box[i]){
                    r2+="0";
                }else{
                    r2+="1";
                }
            }
            l2=r1;
            cout<<"L2: "<<l2<<endl;
            cout<<"r2: "<<r2<<endl;

            //ROUND 2---------------------------------
            string kk1 =keyop(kkk);
            string key1, xx1, sbx1;
            for(int i=0;i<48;i++){
                key1+=kk1[i];
            }
            cout<<"KEY-48: "<<key1<<endl;
            string es1 = expansion_permutation(r2);

            for(int i=0;i<48;i++){
                if(es1[i]==key1[i]){
                    xx1+="0";
                }else{
                    xx1+="1";
                }
            }
            cout<<"XOR"<<xx1<<endl;
            string s_box1 = sbox(xx1);
            string p_box1 = pbox(s_box1);
            string l3,r3;
            l3 = r2;
            for(int i=0;i<32;i++){
               if(l2[i]==p_box1[i]){
                    r3+="0";
                }else{
                    r3+="1";
                }
            }
            cout<<"L3: "<<l3<<endl;
            cout<<"r3: "<<r3<<endl;
            r3 = r3+l3;
            string text = inv_ip(r3);
            cout<<"CipherText: "<<text<<endl;
            string result;
        for(int k=0;k<16;k++)
        {
            int x=getdecimal(text.substr(k*4,4));
            char ch;
            if(x<10)
            {
                ch=char(x+'0');
            }
            else{
                switch(x)
                {
                    case 10:ch='A';break;
                    case 11:ch='B';break;
                    case 12:ch='C';break;
                    case 13:ch='D';break;
                    case 14:ch='E';break;
                    case 15:ch='F';break;
                    default:break;
                }
            }
            result.append(1,ch);
        }

        out<<result<<"\n"<<endl;
        }
    }
    inp.close();
    out.close();
}
char getchars_from_binary(string s)
{
    int sum=0;
    for(int i=0;i<8;i++){
        if(s[i]=='1'){
            sum+=pow(2,7-i);
        }
    }
    char ch=char(sum);
    return ch;
}
void decrypt(string key)
{
    string ss;

    ifstream inp("inp.txt");
    ofstream out("op.txt");
    while(getline(inp, ss)){
        string s,l1,r1;
        string kk;
        for(int i=0;i<key.length();i++){
            kk+=charToBinary(key[i]);
        }
        string kk1 =keyop(kk);
        string kk2 =keyop(kk1);
        string text;
 //converting hexa to binary
        map<char,string> m;
        m['0']="0000";
        m['1']="0001";
        m['2']="0010";
        m['3']="0011";
        m['4']="0100";
        m['5']="0101";
        m['6']="0110";
        m['7']="0111";
        m['8']="1000";
        m['9']="1001";
        m['A']="1010";
        m['B']="1011";
        m['C']="1100";
        m['D']="1101";
        m['E']="1110";
        m['F']="1111";
        for(int k=0;k<16;k++){
        string pppps=m[ss[k]];
        text=text+pppps;
        }
        cout<<text<<endl;
        for(int i=0;i<text.length();i+=64){
            string is = intial_permutation(text);
            string key, xx, sbx;
            key = kk2.substr(0,48);
            cout<<"KEY-48: "<<key<<endl;
            l1 = is.substr(0,32);
            r1 = is.substr(32,64);
            cout<<"L1: "<<l1<<endl;
            cout<<"R1: "<<r1<<endl;
            string es = expansion_permutation(r1);
            for(int i=0;i<48;i++){
                if(es[i]==key[i]){
                    xx+="0";
                }else{
                    xx+="1";
                }
            }
            cout<<"XOR"<<xx<<endl;
            string s_box = sbox(xx);
            string p_box = pbox(s_box);
            string l2,r2;
            for(int i=0;i<32;i++){
                if(l1[i]==p_box[i]){
                    r2+="0";
                }else{
                    r2+="1";
                }
            }
            l2=r1;
            cout<<"L2: "<<l2<<endl;
            cout<<"r2: "<<r2<<endl;
            //ROUND 2---------------------------------
            string key1, xx1, sbx1;
            key1 = kk1.substr(0,48);
            cout<<"KEY-48: "<<key1<<endl;
            string es1 = expansion_permutation(r2);

            for(int i=0;i<48;i++){
                if(es1[i]==key1[i]){
                    xx1+="0";
                }else{
                    xx1+="1";
                }
            }
            cout<<"XOR"<<xx1<<endl;
            string s_box1 = sbox(xx1);
            string p_box1 = pbox(s_box1);
            string l3,r3;
            l3 = r2;
            for(int i=0;i<32;i++){
               if(l2[i]==p_box1[i]){
                    r3+="0";
                }else{
                    r3+="1";
                }
            }
            cout<<"L3: "<<l3<<endl;
            cout<<"r3: "<<r3<<endl;
            string cipher = inv_ip(r3);
            string result;
            for(int k=0;k<8;k++){
            result=result.append(1,getchars_from_binary(text.substr(8*k,8)));
            }
            cout<<"CipherText: "<<result<<endl;
            out<<result<<"\n"<<endl;
        }

    }
    inp.close();
    out.close();
}

int main()
{
    string k = "aaaaaaa";
    int opt;
    cout<<"1.Encryption 2.Decryption";
    cin>>opt;
    if(opt==1){
        encrypt(k);
    }else if(opt==2){
        decrypt(k);
    }
    return 0;
}
