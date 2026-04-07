#include <stdio.h>

int modInv(int a){
    for(int i=1;i<26;i++)
        if((a*i)%26==1) return i;
    return -1;
}

int main(){
    int k[2][2], i;
    char t[3];

    printf("Key: ");
    for(i=0;i<2;i++)
        for(int j=0;j<2;j++)
            scanf("%d",&k[i][j]);

    printf("Text(2 letters): ");
    scanf("%s",t);

    int a=t[0]-'a', b=t[1]-'a';

    // encryption
    int e1=(k[0][0]*a+k[0][1]*b)%26;
    int e2=(k[1][0]*a+k[1][1]*b)%26;
    printf("Encrypted: %c%c\n",e1+'a',e2+'a');

    // inverse key
    int det=(k[0][0]*k[1][1]-k[0][1]*k[1][0])%26;
    if(det<0) det+=26;
    int invDet=modInv(det);

    int inv[2][2];
    inv[0][0]=k[1][1]*invDet%26;
    inv[1][1]=k[0][0]*invDet%26;
    inv[0][1]=(-k[0][1]*invDet)%26;
    inv[1][0]=(-k[1][0]*invDet)%26;

    for(i=0;i<2;i++)
        for(int j=0;j<2;j++)
            if(inv[i][j]<0) inv[i][j]+=26;

    // decryption
    int d1=(inv[0][0]*e1+inv[0][1]*e2)%26;
    int d2=(inv[1][0]*e1+inv[1][1]*e2)%26;

    printf("Decrypted: %c%c\n",d1+'a',d2+'a');
}