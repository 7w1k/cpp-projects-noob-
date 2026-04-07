#include <stdio.h>

int main(){
    char text[100], key[27], rev[26], res[100];
    int i;

    printf("Text: "); scanf("%s",text);
    printf("Key: "); scanf("%s",key);

    // reverse key for decryption
    for(i=0;i<26;i++)
        rev[key[i]-'a']='a'+i;

    // encrypt
    for(i=0;text[i];i++)
        res[i]=key[text[i]-'a'];
    res[i]='\0';
    printf("Encrypted: %s\n",res);

    // decrypt
    for(i=0;res[i];i++)
        res[i]=rev[res[i]-'a'];
    printf("Decrypted: %s\n",res);
}