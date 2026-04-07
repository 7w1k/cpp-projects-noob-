#include <stdio.h>
#include <string.h>

void encrypt(char t[], char k[]){
    int i,j=0;
    for(i=0;t[i];i++){
        t[i]=(t[i]-'a'+k[j]-'a')%26+'a';
        j=(j+1)%strlen(k);
    }
}

void decrypt(char t[], char k[]){
    int i,j=0;
    for(i=0;t[i];i++){
        t[i]=(t[i]-'a'-(k[j]-'a')+26)%26+'a';
        j=(j+1)%strlen(k);
    }
}

int main(){
    char text[100],key[100];

    printf("Text: "); scanf("%s",text);
    printf("Key: "); scanf("%s",key);

    encrypt(text,key);
    printf("Encrypted: %s\n",text);

    decrypt(text,key);
    printf("Decrypted: %s\n",text);
}