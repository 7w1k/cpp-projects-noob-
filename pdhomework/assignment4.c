#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYMBOLS 100
#define MAX_LEN 50

typedef struct {
    char name[MAX_LEN];
    char type[MAX_LEN];
    double value;
    int is_initialized;
} Symbol;

Symbol symbol_table[MAX_SYMBOLS];
int symbol_count = 0;

double parse_expression(const char **expr_ptr);
double parse_term(const char **expr_ptr);
double parse_factor(const char **expr_ptr);

int find_symbol(const char *name) {
    for (int i = 0; i < symbol_count; i++) {
        if (strcmp(symbol_table[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void insert_symbol(const char *name, const char *type, double value, int is_init) {
    int idx = find_symbol(name);
    if (idx != -1) {
        strcpy(symbol_table[idx].type, type);
        symbol_table[idx].value = value;
        symbol_table[idx].is_initialized = is_init;
    } else {
        if (symbol_count < MAX_SYMBOLS) {
            strcpy(symbol_table[symbol_count].name, name);
            strcpy(symbol_table[symbol_count].type, type);
            symbol_table[symbol_count].value = value;
            symbol_table[symbol_count].is_initialized = is_init;
            symbol_count++;
        } else {
            printf("Error: Symbol Table Overflow!\n");
        }
    }
}

double parse_factor(const char **expr_ptr) {
    while (**expr_ptr == ' ') (*expr_ptr)++;
    
    if (**expr_ptr == '(') {
        (*expr_ptr)++;
        double val = parse_expression(expr_ptr);
        if (**expr_ptr == ')') {
            (*expr_ptr)++;
        }
        return val;
    } 
    else if (isalpha(**expr_ptr) || **expr_ptr == '_') {
        char var_name[MAX_LEN];
        int idx = 0;
        while (isalnum(**expr_ptr) || **expr_ptr == '_') {
            var_name[idx++] = *(*expr_ptr)++;
        }
        var_name[idx] = '\0';
        
        int sym_idx = find_symbol(var_name);
        if (sym_idx != -1) {
            if (!symbol_table[sym_idx].is_initialized) {
                printf("Warning: Variable '%s' used uninitialized!\n", var_name);
            }
            return symbol_table[sym_idx].value;
        } else {
            printf("Error: Undeclared variable '%s'!\n", var_name);
            return 0;
        }
    } 
    else {
        char *end_ptr;
        double val = strtod(*expr_ptr, &end_ptr);
        *expr_ptr = end_ptr;
        return val;
    }
}

double parse_term(const char **expr_ptr) {
    double val = parse_factor(expr_ptr);
    while (1) {
        while (**expr_ptr == ' ') (*expr_ptr)++;
        char op = **expr_ptr;
        
        if (op == '*' || op == '/') {
            (*expr_ptr)++;
            double next_val = parse_factor(expr_ptr);
            if (op == '*') val *= next_val;
            else {
                if (next_val == 0) {
                    printf("Error: Division by zero!\n");
                    exit(1);
                }
                val /= next_val;
            }
        } else {
            break;
        }
    }
    return val;
}

double parse_expression(const char **expr_ptr) {
    double val = parse_term(expr_ptr);
    while (1) {
        while (**expr_ptr == ' ') (*expr_ptr)++;
        char op = **expr_ptr;
        
        if (op == '+' || op == '-') {
            (*expr_ptr)++;
            double next_val = parse_term(expr_ptr);
            if (op == '+') val += next_val;
            else val -= next_val;
        } else {
            break;
        }
    }
    return val;
}

void process_statement(char *stmt) {
    stmt[strcspn(stmt, "\r\n")] = 0;
    if (strlen(stmt) == 0) return;

    char type[MAX_LEN] = "";
    char var_name[MAX_LEN] = "";
    double val = 0.0;
    int is_init = 0;

    char temp_stmt[256];
    strcpy(temp_stmt, stmt);
    
    char *token = strtok(temp_stmt, " \t;=");
    if (token != NULL && (strcmp(token, "int") == 0 || strcmp(token, "float") == 0 || strcmp(token, "double") == 0 || strcmp(token, "char") == 0)) {
        strcpy(type, token);
        token = strtok(NULL, " \t;=");
        if (token != NULL) {
            strcpy(var_name, token);
            char *eq_pos = strchr(stmt, '=');
            if (eq_pos != NULL) {
                eq_pos++; 
                const char *expr_ptr = eq_pos;
                val = parse_expression(&expr_ptr);
                is_init = 1;
            }
            insert_symbol(var_name, type, val, is_init);
            return;
        }
    } 
    else {
        char *eq_pos = strchr(stmt, '=');
        if (eq_pos != NULL) {
            *eq_pos = '\0';
            char *v_name = stmt;
            while (*v_name == ' ') v_name++;
            
            int idx = find_symbol(v_name);
            if (idx != -1) {
                eq_pos++;
                const char *expr_ptr = eq_pos;
                val = parse_expression(&expr_ptr);
                symbol_table[idx].value = val;
                symbol_table[idx].is_initialized = 1;
                return;
            } else {
                printf("Error: Assignment to undeclared variable '%s'!\n", v_name);
                return;
            }
        }
    }
    printf("Error: Invalid statement format!\n");
}

void display_symbol_table() {
    printf("\n=========================================\n");
    printf("               SYMBOL TABLE              \n");
    printf("=========================================\n");
    printf("%-15s | %-10s | %-10s\n", "Variable Name", "Data Type", "Value");
    printf("-----------------------------------------\n");
    for (int i = 0; i < symbol_count; i++) {
        if (symbol_table[i].is_initialized) {
            printf("%-15s | %-10s | %.2f\n", symbol_table[i].name, symbol_table[i].type, symbol_table[i].value);
        } else {
            printf("%-15s | %-10s | %-10s\n", symbol_table[i].name, symbol_table[i].type, "Not Init");
        }
    }
    printf("=========================================\n\n");
}

int main() {
    char stmt[256];
    
    printf("=== C Symbol Table & Expression Evaluator ===\n");
    printf("Enter statements one by one. Type 'SHOW' to view the symbol table or 'EXIT' to quit.\n\n");

    while (1) {
        printf("stmt> ");
        if (fgets(stmt, sizeof(stmt), stdin) == NULL) break;
        
        stmt[strcspn(stmt, "\r\n")] = 0;

        if (strcmp(stmt, "EXIT") == 0 || strcmp(stmt, "exit") == 0) {
            break;
        } else if (strcmp(stmt, "SHOW") == 0 || strcmp(stmt, "show") == 0) {
            display_symbol_table();
        } else if (strlen(stmt) > 0) {
            process_statement(stmt);
        }
    }

    return 0;
}