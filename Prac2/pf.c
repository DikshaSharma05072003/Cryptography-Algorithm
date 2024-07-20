#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 30

//ENCRYPTION
int removeSpaces(char* plain, int ps)
{
    int i, count = 0;
    for (i = 0; i < ps; i++){
        if (plain[i] != ' ')
            plain[count++] = plain[i];
    }
    plain[count] = '\0';
    return count;
}
void generateKeyTable(char key[], int ks, char keyT[5][5])
{
    int i, j, k, flag = 0, *dicty;
    dicty = (int*)calloc(26, sizeof(int));
    for (i = 0; i < ks; i++) {
        if (key[i] != 'J')
            dicty[key[i] - 'A'] = 2;
    }
    dicty['J' - 'A'] = 1;
    i = 0;
    j = 0;
    for (k = 0; k < ks; k++) {
        if (dicty[key[k] - 'A'] == 2) {
            dicty[key[k] - 'A'] -= 1;
            keyT[i][j] = key[k];
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
    for (k = 0; k < 26; k++) {
        if (dicty[k] == 0) {
            keyT[i][j] = (char)(k + 'A');
            j++;
            if (j == 5) {
                i++;
                j = 0;
            }
        }
    }
}
void search(char keyT[5][5], char a, char b, int arr[])
{
    if (a == 'j')
        a = 'i';
    else if (b == 'j')
        b = 'i';
    int i,j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (keyT[i][j] == a) {
                arr[0] = i;
                arr[1] = j;
            }
            else if (keyT[i][j] == b) {
                arr[2] = i;
                arr[3] = j;
            }
        }
    }
}
void encrypt(char str[], char o[], char keyT[5][5], int ps)
{
    int i, a[4];
    for (i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);

        if (a[0] == a[2]) {
            o[i] = keyT[a[0]][(a[1] + 1)%5];
            o[i + 1] = keyT[a[0]][(a[3] + 1)%5];
        }
        else if (a[1] == a[3]) {
            o[i] = keyT[(a[0] + 1)%5][a[1]];
            o[i + 1] = keyT[(a[2] + 1)%5][a[1]];
        }
        else {
            o[i] = keyT[a[0]][a[3]];
            o[i + 1] = keyT[a[2]][a[1]];
        }
    }
}
void encryptByPlayfairCipher(char str[],char o[], char key[])
{
    char ps=0, ks=0, keyT[5][5];
    ks = strlen(key);
    ks = removeSpaces(key, ks);
    ps = strlen(str);
    ps = removeSpaces(str, ps);
    int sub = ps;
    for (int i = 0; i < sub; i += 2) {
        if(str[i]==str[i+1]){
            for(int j=sub; j>i+1; j--){
                str[j]=str[j-1];
            }
            str[i+1]='X';
            sub+=1;
        }
    }
    str[sub]='\0';
    if (sub % 2 != 0) {
        str[sub++] = 'Z';
        str[sub] = '\0';
    }
    ps = sub;
    printf("%d\n",ps);
    generateKeyTable(key, ks, keyT);
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            printf("%c ",keyT[i][j]);
        }
        printf("\n");
    }

  //  char o[ps];
    //FILE *op = fopen("playfair_op.txt", "w");
    encrypt(str, o, keyT, ps);
   // printf("Cipher text: %s\n", o);
   // fprintf(op, "Cipher text: %s\n", o);
   // fclose(op);
}

//DECRYPTION
int mod_5(int a)
{
    if (a < 0)
        a += 5;
    return (a % 5);
}
void decrypt(char str[], char o[], char keyT[5][5], int ps)
{
    int i, a[4];
    for (i = 0; i < ps; i += 2) {
        search(keyT, str[i], str[i + 1], a);
        if (a[0] == a[2]) {
            o[i] = keyT[a[0]][mod_5(a[1] - 1)];
            o[i + 1] = keyT[a[0]][mod_5(a[3] - 1)];
        }
        else if (a[1] == a[3]) {
            o[i] = keyT[mod_5(a[0] - 1)][a[1]];
            o[i + 1] = keyT[mod_5(a[2] - 1)][a[1]];
        }
        else {
            o[i] = keyT[a[0]][a[3]];
            o[i + 1] = keyT[a[2]][a[1]];
        }
    }
}
void decryptByPlayfairCipher(char str[],char o[], char key[])
{
    char ps, ks, keyT[5][5];

    ks = strlen(key);
    ps = strlen(str);
    generateKeyTable(key, ks, keyT);
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++){
            printf("%c ",keyT[i][j]);
        }
        printf("\n");
    }
    decrypt(str, o, keyT, ps);

}

int main()
{
    char str[SIZE], key[SIZE], o[SIZE];
    FILE *fp = fopen("playfair_in.txt","r");

    if(fp==NULL){
        printf("File not found");
        return 0;
    }
    int opt;
    printf("1. Encryption 2.Decryption\n");
    scanf("%d",&opt);
            FILE *op = fopen("playfair_op.txt", "w");
    printf("Enter the key: ");
    scanf("%s",&key);
    printf("Key text: %s\n", key);
    if(opt==1){
        while (fgets(str, 100, fp) != NULL) {
            printf("Plain text: %s\n", str);
            encryptByPlayfairCipher(str,o, key);

        printf("Cipher text: %s\n", o);
        fprintf(op, "Cipher text: %s\n", o);


        }
    }else if(opt==2){
        while (fgets(str, 100, fp) != NULL) {
            printf("Plain text: %s\n", str);
            decryptByPlayfairCipher(str,o,key);
    printf("Cipher text: %s\n", o);
    fprintf(op, "Cipher text: %s\n", o);
        }
    }
    fclose(fp);
            fclose(op);
    return 0;
}
