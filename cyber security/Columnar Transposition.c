#include <stdio.h>
#include <string.h>

void getOrder(char key[], int order[]) {
    int len = strlen(key);
    for(int i=0;i<len;i++){
        int pos=0;
        for(int j=0;j<len;j++)
            if(key[j]<key[i]) pos++;
        order[i]=pos;
    }
}

void encrypt(char text[], char key[]) {
    int len=strlen(text), klen=strlen(key);
    int rows=(len+klen-1)/klen;
    char grid[10][10];
    int order[10], i,j,k=0;

    getOrder(key,order);

    // fill grid
    for(i=0;i<rows;i++)
        for(j=0;j<klen;j++)
            grid[i][j] = (k<len)?text[k++]:'X';

    // read column-wise
    for(i=0;i<klen;i++)
        for(j=0;j<klen;j++)
            if(order[j]==i)
                for(int r=0;r<rows;r++)
                    printf("%c",grid[r][j]);
}

int main(){
    char text[100], temp[100];

    printf("Enter text: ");
    scanf("%s",text);

    printf("After 1st key (DEFENCE): ");
    encrypt(text,"DEFENCE");

    printf("\nAfter 2nd key (SYSTEM): ");
    encrypt(text,"SYSTEM");

    return 0;
}