#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    FILE *fp = fopen("p1.txt","r");
    if(fp==NULL){
        printf("File not found");
        return 0;
    }
    FILE *op = fopen("ceaser_op.txt", "w");
    int opt,k;
    printf("1. Encryption 2.Decryption\n");
    scanf("%d",&opt);
    char str[100];
    printf("Enter key: ");
    scanf("%d",&k);
    if(opt==1){
        while (fgets(str, 100, fp) != NULL) {
            for(int i=0;i<strlen(str);i++){
                char c = str[i];
                if(c>='a' && c<='z'){
                    c = (c+k-'a')%26+'a';
                }else if(c>='A' && c<='Z'){
                    c = (c+k-'A')%26+'A';
                }
                str[i] =c;
            }
            fprintf(op, "%s\n", str);
            printf("%s", str);
        }

    }else if(opt==2){

    while (fgets(str, 100, fp) != NULL) {

    for(int i=0;i<strlen(str);i++){
        char c = str[i];
        if(c>='a' && c<='z'){
            c = (c-k-'a'+26)%26+'a';
        }else if(c>='A' && c<='Z'){
            c = (c-k-'A'+26)%26+'A';
        }
        str[i] =c;
    }
    fprintf(op, "%s\n", str);
    printf("%s", str);
        }
    }
    fclose(fp);
    return 0;
}
