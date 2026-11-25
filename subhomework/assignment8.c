#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

bool is_valid_email(const char *email) {
    int len = strlen(email);
    int at_index = -1;
    int dot_index = -1;

    for (int i = 0; i < len; i++) {
        if (email[i] == '@') {
            if (at_index != -1) return false;
            at_index = i;
        } else if (email[i] == '.') {
            dot_index = i;
        }
    }

    if (at_index == -1 || dot_index == -1 || at_index > dot_index || at_index == 0 || dot_index == len - 1) {
        return false;
    }

    if (len < 4 || strcmp(email + len - 4, ".com") != 0) {
        return false;
    }

    for (int i = 0; i < at_index; i++) {
        char c = email[i];
        if (!isalnum(c) && c != '.' && c != '_' && c != '-') {
            return false;
        }
    }

    for (int i = at_index + 1; i < len - 4; i++) {
        char c = email[i];
        if (!isalnum(c) && c != '-' && c != '.') {
            return false;
        }
    }

    return true;
}

int main() {
    char email[256];

    printf("=== Email Address Validator ===\n");
    printf("Required Format: <name>@<domain>.com\n");
    printf("Enter email addresses to test (or type 'exit' to quit):\n\n");

    while (1) {
        printf("email> ");
        if (fgets(email, sizeof(email), stdin) == NULL) break;
        
        email[strcspn(email, "\r\n")] = '\0';

        if (strcmp(email, "exit") == 0 || strcmp(email, "EXIT") == 0 || strcmp(email, "Exit") == 0) {
            break;
        }

        if (is_valid_email(email)) {
            printf("STATUS : Valid Email Address\n\n");
        } else {
            printf("STATUS : Invalid Email Address\n\n");
        }
    }

    return 0;
}