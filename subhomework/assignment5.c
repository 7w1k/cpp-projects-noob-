#include <stdio.h>
#include <string.h>
#include <ctype.h>

void findFirst(char c);
void addToResult(char val);

int count;
char production[10][10];
char result[20];
int resultIndex = 0;

int main() {
    int i;
    char choice;
    char c;
    
    printf("=== FIRST Set Calculator ===\n");
    printf("Enter the number of productions: ");
    scanf("%d", &count);
    
    printf("Enter the productions in format A=B (e.g., S=Ab, A=e):\n");
    for(i = 0; i < count; i++) {
        scanf("%s", production[i]);
    }
    
    do {
        resultIndex = 0;
        memset(result, 0, sizeof(result));
        
        printf("\nEnter the non-terminal to find FIRST for: ");
        scanf(" %c", &c);
        
        findFirst(c);
        
        printf("FIRST(%c) = { ", c);
        for(i = 0; i < resultIndex; i++) {
            printf("%c ", result[i]);
        }
        printf("}\n");
        
        printf("\nDo you want to find FIRST for another non-terminal? (y/n): ");
        scanf(" %c", &choice);
    } while(choice == 'y' || choice == 'Y');
    
    return 0;
}

void findFirst(char c) {
    int i, j, foundEpsilon;
    
    if(!isupper(c)) {
        addToResult(c);
        return;
    }
    
    for(i = 0; i < count; i++) {
        if(production[i][0] == c) {
            if(production[i][2] == 'e') {
                addToResult('e');
            } else {
                j = 2; 
                while(production[i][j] != '\0') {
                    foundEpsilon = 0;
                    char currentSymbol = production[i][j];
                    
                    int prevResultCount = resultIndex;
                    findFirst(currentSymbol);
                    
                    for(int k = prevResultCount; k < resultIndex; k++) {
                        if(result[k] == 'e') {
                            foundEpsilon = 1;
                            break;
                        }
                    }
                    
                    if(foundEpsilon) {
                        if(production[i][j+1] == '\0') {
                            break;
                        } else {
                            for(int k = 0; k < resultIndex; k++) {
                                if(result[k] == 'e') {
                                    for(int m = k; m < resultIndex - 1; m++) {
                                        result[m] = result[m+1];
                                    }
                                    resultIndex--;
                                    result[resultIndex] = '\0';
                                    break;
                                }
                            }
                            j++;
                        }
                    } else {
                        break; 
                    }
                }
            }
        }
    }
}

void addToResult(char val) {
    for(int i = 0; i < resultIndex; i++) {
        if(result[i] == val) return;
    }
    result[resultIndex++] = val;
    result[resultIndex] = '\0';
}