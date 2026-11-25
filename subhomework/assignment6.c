#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void trim(char *str) {
    int len = strlen(str);
    while (len > 0 && (str[len-1] == ' ' || str[len-1] == '\t' || str[len-1] == '\n' || str[len-1] == '\r' || str[len-1] == ';')) {
        str[--len] = '\0';
    }
    char *p = str;
    while (*p == ' ' || *p == '\t') p++;
    if (p != str) {
        memmove(str, p, strlen(p) + 1);
    }
}

bool check_integer(const char *str) {
    int i = 0;
    if (str[0] == '+' || str[0] == '-') i++;
    if (str[i] == '\0') return false;
    for (; str[i] != '\0'; i++) {
        if (!isdigit(str[i])) return false;
    }
    return true;
}

bool check_float(const char *str) {
    int i = 0;
    int dot_count = 0;
    if (str[0] == '+' || str[0] == '-') i++;
    if (str[i] == '\0') return false;
    for (; str[i] != '\0'; i++) {
        if (str[i] == '.') {
            dot_count++;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return dot_count == 1;
}

void detect_datatype(char *stmt) {
    char *eq = strchr(stmt, '=');
    if (!eq) {
        printf("Error: Invalid statement format (missing '=')\n");
        return;
    }
    
    *eq = '\0';
    char var_name[50];
    strcpy(var_name, stmt);
    trim(var_name);
    
    char rhs[256];
    strcpy(rhs, eq + 1);
    trim(rhs);
    
    printf("\n-----------------------------------------\n");
    printf("Variable Name : %s\n", var_name);
    printf("RHS Value     : %s\n", rhs);
    
    int len = strlen(rhs);
    if (rhs[0] == '"' && rhs[len-1] == '"') {
        printf("Detected Type : string (char *)\n");
    } 
    else if (rhs[0] == '\'' && rhs[len-1] == '\'' && len == 3) {
        printf("Detected Type : char\n");
    } 
    else if (check_integer(rhs)) {
        printf("Detected Type : int\n");
    } 
    else if (check_float(rhs)) {
        printf("Detected Type : float (or double)\n");
    } 
    else {
        printf("Detected Type : unknown / expression / invalid literal\n");
    }
    printf("-----------------------------------------\n");
}

int main() {
    char input[256];
    
    printf("=== Dynamic Data Type Detector ===\n");
    printf("Enter statements (e.g., a = 3.14; or b = 5;) or type 'exit' to quit.\n\n");
    
    while (1) {
        printf("input> ");
        if (fgets(input, sizeof(input), stdin) == NULL) break;
        
        input[strcspn(input, "\r\n")] = '\0';
        
        // Check for exit (supporting common casings)
        if (strcmp(input, "exit") == 0 || strcmp(input, "EXIT") == 0 || strcmp(input, "Exit") == 0) {
            break;
        }
        if (strlen(input) == 0) continue;
        
        detect_datatype(input);
    }
    
    return 0;
}