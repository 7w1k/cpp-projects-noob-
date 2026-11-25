#include <stdio.h>
#include <string.h>
#include <ctype.h>

const char *keywords[] = {
    "int", "float", "double", "char", "long", "short", "unsigned", "signed",
    "for", "while", "do", "if", "else", "switch", "case", "break", "continue", "return", "void"
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
    printf("\n%-15s | %-15s\n", "TOKEN", "TYPE");
    printf("---------------------------------\n");

    while (expr[i] != '\0' && expr[i] != '\n') {
        if (isspace(expr[i])) {
            i++;
            continue;
        }

        if (isalpha(expr[i]) || expr[i] == '_') {
            char buffer[100];
            int idx = 0;
            while (isalnum(expr[i]) || expr[i] == '_') {
                buffer[idx++] = expr[i++];
            }
            buffer[idx] = '\0';

            if (is_keyword(buffer)) {
                printf("%-15s | %-15s\n", buffer, "Keyword");
            } else {
                printf("%-15s | %-15s\n", buffer, "Identifier");
            }
        }
        else if (isdigit(expr[i])) {
            char buffer[100];
            int idx = 0;
            while (isdigit(expr[i]) || expr[i] == '.') {
                buffer[idx++] = expr[i++];
            }
            buffer[idx] = '\0';
            printf("%-15s | %-15s\n", buffer, "Constant");
        }
        else {
            char c = expr[i];
            
            if ((c == '=' && expr[i+1] == '=') ||
                (c == '+' && expr[i+1] == '+') ||
                (c == '-' && expr[i+1] == '-') ||
                (c == '<' && expr[i+1] == '=') ||
                (c == '>' && expr[i+1] == '=')) {
                char op[3] = { c, expr[i+1], '\0' };
                printf("%-15s | %-15s\n", op, "Operator");
                i += 2;
            } 
            else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '=' || c == '<' || c == '>' || c == '!') {
                char op[2] = { c, '\0' };
                printf("%-15s | %-15s\n", op, "Operator");
                i++;
            } 
            else if (c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}' || c == '[' || c == ']') {
                char sep[2] = { c, '\0' };
                printf("%-15s | %-15s\n", sep, "Separator");
                i++;
            } 
            else {
                printf("%c               | %-15s\n", c, "Unknown");
                i++;
            }
        }
    }
}

int main() {
    char decl_stmt[256];
    char loop_stmt[512];

    printf("=== PART (A): Declaration Statement Tokenizer ===\n");
    printf("Enter declaration statement (e.g., float radius = 5.5;): ");
    fgets(decl_stmt, sizeof(decl_stmt), stdin);
    tokenize(decl_stmt);

    printf("\n=== PART (B): Loop Statement Tokenizer ===\n");
    printf("Enter loop statement (e.g., for(int i=0; i<10; i++) { sum += i; }): ");
    fgets(loop_stmt, sizeof(loop_stmt), stdin);
    tokenize(loop_stmt);

    return 0;
}