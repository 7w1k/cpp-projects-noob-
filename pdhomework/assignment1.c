#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

const char *input_ptr;

double parse_expression();
double parse_term();
double parse_factor();

double parse_factor() {
    while (*input_ptr == ' ') input_ptr++;
    
    if (*input_ptr == '(') {
        input_ptr++; 
        double val = parse_expression();
        if (*input_ptr == ')') {
            input_ptr++; 
        }
        return val;
    } else {
        char *end_ptr;
        double val = strtod(input_ptr, &end_ptr);
        input_ptr = end_ptr;
        return val;
    }
}

double parse_term() {
    double val = parse_factor();
    while (1) {
        while (*input_ptr == ' ') input_ptr++;
        char op = *input_ptr;
        
        if (op == '*' || op == '/') {
            input_ptr++; 
            double next_val = parse_factor();
            if (op == '*') {
                val *= next_val;
            } else {
                if (next_val == 0) {
                    printf("Error: Division by zero!\n");
                    return 0; // Prevent program crash on division by zero
                }
                val /= next_val;
            }
        } else {
            break;
        }
    }
    return val;
}

double parse_expression() {
    double val = parse_term();
    while (1) {
        while (*input_ptr == ' ') input_ptr++;
        char op = *input_ptr;
        
        if (op == '+' || op == '-') {
            input_ptr++; 
            double next_val = parse_term();
            if (op == '+') {
                val += next_val;
            } else {
                val -= next_val;
            }
        } else {
            break;
        }
    }
    return val;
}

int main() {
    char expression[256];
    
    printf("=== BODMAS Expression Evaluator ===\n");
    printf("Enter expressions (e.g., 3+2*4/2), or type 'exit' to quit.\n\n");
    
    while (1) {
        printf("INPUT  : ");
        if (fgets(expression, sizeof(expression), stdin) == NULL) break;
        
        // Remove trailing newline and carriage return
        expression[strcspn(expression, "\r\n")] = '\0';
        
        // Check for exit command
        if (strcmp(expression, "exit") == 0 || strcmp(expression, "EXIT") == 0) {
            break;
        }
        
        if (strlen(expression) == 0) continue;
        
        input_ptr = expression;
        double result = parse_expression();
        
        if (result == (int)result) {
            printf("OUTPUT : %d\n\n", (int)result);
        } else {
            printf("OUTPUT : %.2f\n\n", result);
        }
    }
    
    return 0;
}