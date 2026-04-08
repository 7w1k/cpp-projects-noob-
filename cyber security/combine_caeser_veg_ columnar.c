#include <stdio.h>
#include <string.h>
#include <ctype.h>

void caesar(char t[], int s, int mode){
    for(int i=0;t[i];i++){
        if(isalpha(t[i])){
            char base='a';
            if(mode==1)
                t[i]=(t[i]-base+s)%26+base;
            else
                t[i]=(t[i]-base-s+26)%26+base;
        }
    }
}

void vigenere(char t[], char k[], int mode){
    int j=0, len=strlen(k);
    for(int i=0;t[i];i++){
        if(isalpha(t[i])){
            if(mode==1)
                t[i]=(t[i]-'a'+(k[j]-'a'))%26+'a';
            else
                t[i]=(t[i]-'a'-(k[j]-'a')+26)%26+'a';
            j=(j+1)%len;
        }
    }
}

void getOrder(char key[], int order[]){
    int len=strlen(key);
    for(int i=0;i<len;i++){
        int pos=0;
        for(int j=0;j<len;j++)
            if(key[j]<key[i]) pos++;
        order[i]=pos;
    }
}

void columnarEncrypt(char text[], char key[], char out[]){
    int len=strlen(text), klen=strlen(key);
    int rows=(len+klen-1)/klen;
    char grid[50][50];
    int order[50], k=0;

    getOrder(key,order);

    for(int i=0;i<rows;i++)
        for(int j=0;j<klen;j++)
            grid[i][j]=(k<len)?text[k++]:'x';

    k=0;
    for(int i=0;i<klen;i++)
        for(int j=0;j<klen;j++)
            if(order[j]==i)
                for(int r=0;r<rows;r++)
                    out[k++]=grid[r][j];
    out[k]='\0';
}

void columnarDecrypt(char cipher[], char key[], char out[]){
    int len=strlen(cipher), klen=strlen(key);
    int rows=(len+klen-1)/klen;
    char grid[50][50];
    int order[50], k=0;

    getOrder(key,order);

    for(int i=0;i<klen;i++)
        for(int j=0;j<klen;j++)
            if(order[j]==i)
                for(int r=0;r<rows;r++)
                    grid[r][j]=cipher[k++];

    k=0;
    for(int i=0;i<rows;i++)
        for(int j=0;j<klen;j++)
            out[k++]=grid[i][j];
    out[k]='\0';
}

void prepare(char t[]){
    char temp[200];
    int k=0;
    for(int i=0;t[i];i++)
        if(isalpha(t[i]))
            temp[k++]=tolower(t[i]);
    temp[k]='\0';
    strcpy(t,temp);
}

int main(){
    char text[200]="Information security depends on confidentiality and integrity";
    char step1[200], step2[200], step3[200];
    char d1[200], d2[200], d3[200];

    prepare(text);
    printf("Original: %s\n",text);

    // Encryption
    strcpy(step1,text);
    caesar(step1,5,1);
    printf("After Caesar: %s\n",step1);

    strcpy(step2,step1);
    vigenere(step2,"cyber",1);
    printf("After Vigenere: %s\n",step2);

    columnarEncrypt(step2,"NETWORK",step3);
    printf("After Columnar: %s\n",step3);

    // Decryption
    columnarDecrypt(step3,"NETWORK",d1);
    printf("After Columnar Dec: %s\n",d1);

    strcpy(d2,d1);
    vigenere(d2,"cyber",0);
    printf("After Vigenere Dec: %s\n",d2);

    strcpy(d3,d2);
    caesar(d3,5,0);
    printf("After Caesar Dec: %s\n",d3);

    // Verification
    if(strcmp(text,d3)==0)
        printf("Verification: PASS\n");
    else
        printf("Verification: FAIL\n");

    return 0;
}
