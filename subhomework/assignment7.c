#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

const char *keywords[] = {
    "int", "float", "double", "char", "if", "else", "while", "for", 
    "do", "return", "void", "switch", "case", "break", "continue"
};
int num_keywords = sizeof(keywords) / sizeof(keywords[0]);

bool is_keyword(const char *str) {
    for (int i = 0; i < num_keywords; i++) {
        if (strcmp(str, keywords[i]) == 0) return true;
    }
    return false;
}

bool is_valid_identifier(const char *str) {
    if (str[0] == '\0' || is_keyword(str)) return false;
    if (!isalpha(str[0]) && str[0] != '_') return false;
    
    for (int i = 1; str[i] != '\0'; i++) {
        if (!isalnum(str[i]) && str[i] != '_') return false;
    }
    return true;
}

bool is_operator(const char *str) {
    const char *operators[] = {
        "+", "-", "*", "/", "=", "==", "!=", "<", ">", "<=", ">=", 
        "&&", "||", "!", "++", "--", "+=", "-=", "*=", "/=", "%"
    };
    int num_ops = sizeof(operators) / sizeof(operators[0]);
    
    for (int i = 0; i < num_ops; i++) {
        if (strcmp(str, operators[i]) == 0) return true;
    }
    return false;
}

void simulate_lexical_analyzer(const char *input) {
    int i = 0;
    printf("\n%-20s | %-25s\n", "TOKEN", "CLASSIFICATION");
    printf("--------------------------------------------------\n");

    while (input[i] != '\0' && input[i] != '\n') {
        if (isspace(input[i])) {
            i++;
            continue;
        }

        if (isalpha(input[i]) || input[i] == '_') {
            char buffer[100];
            int idx = 0;
            while (isalnum(input[i]) || input[i] == '_') {
                buffer[idx++] = input[i++];
            }
            buffer[idx] = '\0';

            if (is_keyword(buffer)) {
                printf("%-20s | %-25s\n", buffer, "Keyword");
            } else if (is_valid_identifier(buffer)) {
                printf("%-20s | %-25s\n", buffer, "Valid Identifier");
            } else {
                printf("%-20s | %-25s\n", buffer, "Invalid Identifier");
            }
        }
        else if (isdigit(input[i])) {
            char buffer[100];
            int idx = 0;
            while (isdigit(input[i]) || input[i] == '.') {
                buffer[idx++] = input[i++];
            }
            buffer[idx] = '\0';
            printf("%-20s | %-25s\n", buffer, "Constant / Number");
        }
        else {
            char c = input[i];
            char next_c = input[i+1];
            char op_buffer[3] = { c, '\0', '\0' };
            
            if ((c == '=' && next_c == '=') ||
                (c == '!' && next_c == '=') ||
                (c == '<' && next_c == '=') ||
                (c == '>' && next_c == '=') ||
                (c == '&' && next_c == '&') ||
                (c == '|' && next_c == '|') ||
                (c == '+' && next_c == '+') ||
                (c == '-' && next_c == '-') ||
                (c == '+' && next_c == '=') ||
                (c == '-' && next_c == '=') ||
                (c == '*' && next_c == '=') ||
                (c == '/' && next_c == '=')) {
                op_buffer[1] = next_c;
                i += 2;
            } else {
                i++;
            }

            if (is_operator(op_buffer)) {
                printf("%-20s | %-25s\n", op_buffer, "Valid Operator");
            } else if (c == ';' || c == ',' || c == '(' || c == ')' || c == '{' || c == '}') {
                char sep_buffer[2] = { c, '\0' };
                printf("%-20s | %-25s\n", sep_buffer, "Separator / Punctuator");
            } else {
                printf("%-20s | %-25s\n", op_buffer, "Unknown / Invalid Token");
            }
        }
    }
    printf("\n");
}

int main() {
    char input_expr[256];

    printf("=== Lexical Analyzer: Identifier & Operator Validator ===\n");
    printf("Enter statements, or type 'exit' to quit.\n\n");
    
    while (1) {
        printf("input> ");
        if (fgets(input_expr, sizeof(input_expr), stdin) == NULL) break;
        
        // Remove trailing newline
        input_expr[strcspn(input_expr, "\r\n")] = '\0';

        // Check for exit command
        if (strcmp(input_expr, "exit") == 0 || strcmp(input_expr, "EXIT") == 0) {
            break;
        }
        
        if (strlen(input_expr) == 0) continue;

        simulate_lexical_analyzer(input_expr);
    }

    return 0;
}