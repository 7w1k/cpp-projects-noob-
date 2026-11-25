#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {
    "printf", "scanf", "if", "else", "switch", "case", "default", "break",
    "int", "float", "double", "char", "return", "void", "default"
};
int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

int is_keyword(const char *str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

void tokenize(const char *expr) {
    int i = 0;
    printf("\n%-20s | %-15s\n", "TOKEN", "TYPE");
    printf("-----------------------------------------\n");

    while (expr[i] != '\0' && expr[i] != '\n') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (expr[i] == '"') {
            char buffer[256];
            int idx = 0;
            buffer[idx++] = expr[i++]; 
            while (expr[i] != '\0' && expr[i] != '"') {
                buffer[idx++] = expr[i++];
            }
            if (expr[i] == '"') {
                buffer[idx++] = expr[i++]; 
            }
            buffer[idx] = '\0';
            printf("%-20s | %-15s\n", buffer, "String Literal");
        }
        else if (isalpha(expr[i]) || expr[i] == '_') {
            char buffer[100];
            int idx = 0;
            while (isalnum(expr[i]) || expr[i] == '_') {
                buffer[idx++] = expr[i++];
            }
            buffer[idx] = '\0';

            if (is_keyword(buffer)) {
                printf("%-20s | %-15s\n", buffer, "Keyword");
            } else {
                printf("%-20s | %-15s\n", buffer, "Identifier");
            }
        }
        else if (isdigit(expr[i])) {
            char buffer[100];
            int idx = 0;
            while (isdigit(expr[i]) || expr[i] == '.') {
                buffer[idx++] = expr[i++];
            }
            buffer[idx] = '\0';
            printf("%-20s | %-15s\n", buffer, "Constant");
        }
        else {
            char c = expr[i];
            
            if ((c == '=' && expr[i+1] == '=') ||
                (c == '!' && expr[i+1] == '=') ||
                (c == '<' && expr[i+1] == '=') ||
                (c == '>' && expr[i+1] == '=') ||
                (c == '&' && expr[i+1] == '&') ||
                (c == '|' && expr[i+1] == '|')) {
                char op[3] = { c, expr[i+1], '\0' };
                printf("%-20s | %-15s\n", op, "Operator");
                i += 2;
            } 
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' || c == '!' || c == '&') {
                char op[2] = { c, '\0' };
                printf("%-20s | %-15s\n", op, "Operator");
                i++;
            } 
            else if (c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}' || c == ':' || c == '"') {
                char sep[2] = { c, '\0' };
                printf("%-20s | %-15s\n", sep, "Separator");
                i++;
            } 
            else {
                printf("%-20c | %-15s\n", c, "Unknown");
                i++;
            }
        }
    }
}

int main() {
    char io_stmt[256];
    char cond_stmt[512];

    printf("=== PART (A): I/O Statement Tokenizer ===\n");
    printf("Enter I/O statement (e.g., printf(\"Sum = %%d\", sum);): ");
    fgets(io_stmt, sizeof(io_stmt), stdin);
    tokenize(io_stmt);

    printf("\n=== PART (B): If-Else and Switch Case Tokenizer ===\n");
    printf("Enter conditional statement (e.g., if(x > 10) { switch(opt) { case 1: break; } }): ");
    fgets(cond_stmt, sizeof(cond_stmt), stdin);
    tokenize(cond_stmt);

    return 0;
}