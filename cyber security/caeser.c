#include <stdio.h>
#include <ctype.h>
#include <string.h>

void encrypt(char t[], int s){
    for(int i=0;t[i];i++)
        if(isalpha(t[i]))
            t[i]=(t[i]-'a'+s)%26+'a';
}

void decrypt(char t[], int s){
    for(int i=0;t[i];i++)
        if(isalpha(t[i]))
            t[i]=(t[i]-'a'-s+26)%26+'a';
}

void frequency(char t[]){
    int f[26]={0};
    for(int i=0;t[i];i++)
        if(isalpha(t[i]))
            f[t[i]-'a']++;

    for(int i=0;i<26;i++)
        printf("%c:%d\n",'a'+i,f[i]);
}

int main(){
    char text[100];
    int shift;

    printf("Text: "); scanf("%s",text);
    printf("Shift: "); scanf("%d",&shift);

    encrypt(text,shift);
    printf("Encrypted: %s\n",text);

    decrypt(text,shift);
    printf("Decrypted: %s\n",text);

    frequency(text);
}