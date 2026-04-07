#include <stdio.h>
#include <string.h>
#include <ctype.h>

char matrix[5][5];

// generate matrix
void generateMatrix(char key[]) {
    int used[26]={0};
    used['j'-'a']=1; // merge i/j
    char temp[25];
    int k=0;

    // remove duplicates
    for(int i=0;key[i];i++){
        char c=tolower(key[i]);
        if(c=='j') c='i';
        if(!used[c-'a']){
            temp[k++]=c;
            used[c-'a']=1;
        }
    }

    // fill remaining
    for(char c='a';c<='z';c++){
        if(!used[c-'a'])
            temp[k++]=c;
    }

    // fill matrix
    k=0;
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            matrix[i][j]=temp[k++];
}

// display matrix
void displayMatrix(){
    printf("\nPlayfair Matrix:\n");
    for(int i=0;i<5;i++){
        for(int j=0;j<5;j++)
            printf("%c ",matrix[i][j]);
        printf("\n");
    }
}

// find position
void findPos(char c,int *r,int *c2){
    if(c=='j') c='i';
    for(int i=0;i<5;i++)
        for(int j=0;j<5;j++)
            if(matrix[i][j]==c){
                *r=i; *c2=j;
            }
}

// prepare text
void prepare(char str[]){
    int len=strlen(str),k=0;
    char temp[200];

    for(int i=0;i<len;i++){
        if(isalpha(str[i])){
            char c=tolower(str[i]);
            if(c=='j') c='i';
            temp[k++]=c;
        }
    }
    temp[k]='\0';
    strcpy(str,temp);

    // make pairs
    char res[200];
    k=0;
    for(int i=0;i<strlen(str);i++){
        res[k++]=str[i];
        if(str[i]==str[i+1]){
            res[k++]='x';
        }
    }
    if(k%2!=0) res[k++]='x';
    res[k]='\0';

    strcpy(str,res);
}

// encrypt
void encrypt(char str[]){
    for(int i=0;str[i];i+=2){
        int r1,c1,r2,c2;
        findPos(str[i],&r1,&c1);
        findPos(str[i+1],&r2,&c2);

        if(r1==r2){
            str[i]=matrix[r1][(c1+1)%5];
            str[i+1]=matrix[r2][(c2+1)%5];
        }
        else if(c1==c2){
            str[i]=matrix[(r1+1)%5][c1];
            str[i+1]=matrix[(r2+1)%5][c2];
        }
        else{
            str[i]=matrix[r1][c2];
            str[i+1]=matrix[r2][c1];
        }
    }
}

// decrypt
void decrypt(char str[]){
    for(int i=0;str[i];i+=2){
        int r1,c1,r2,c2;
        findPos(str[i],&r1,&c1);
        findPos(str[i+1],&r2,&c2);

        if(r1==r2){
            str[i]=matrix[r1][(c1+4)%5];
            str[i+1]=matrix[r2][(c2+4)%5];
        }
        else if(c1==c2){
            str[i]=matrix[(r1+4)%5][c1];
            str[i+1]=matrix[(r2+4)%5][c2];
        }
        else{
            str[i]=matrix[r1][c2];
            str[i+1]=matrix[r2][c1];
        }
    }
}

int main(){
    char key[]="cryptography";
    char text[200]="Military communication requires secrecy";

    generateMatrix(key);
    displayMatrix();

    prepare(text);
    printf("\nPrepared Text: %s\n",text);

    encrypt(text);
    printf("Encrypted: %s\n",text);

    decrypt(text);
    printf("Decrypted: %s\n",text);

    return 0;
}