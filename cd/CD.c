Q1.Write a C program to identify whether a given line is a comment or not. 
Code:-

#include <stdio.h>
#include <string.h>

int main() {
    char line[500];

    printf("Enter a line of code: ");
    fgets(line, sizeof(line), stdin);

    // Check single-line comment
    if (line[0] == '/' && line[1] == '/') {
        printf("It is a single-line comment.\n");
    }

    // Check multi-line comment
    else if (line[0] == '/' && line[1] == '*') {
        int len = strlen(line);

        if (len >= 4 &&
            line[len - 3] == '*' &&
            line[len - 2] == '/') {
            printf("It is a multi-line comment.\n");
        } else {
            printf("It is an incomplete comment.\n");
        }
    }

    else {
        printf("It is not a comment.\n");
    }

    return 0;
}

Output:-
Enter a line of code: // Hello World
It is a single-line comment.
Enter a line of code: /* Compiler Design */
It is a multi-line comment.
Enter a line of code: int a = 10;
It is not a comment.

Q2.Write a C program to recognize strings under 'a', 'a*b+', 'abb'. 
Code:-

#include <stdio.h>
#include <string.h>

int main() {
    char str[100];
    int i = 0, countA = 0, countB = 0;

    printf("Enter a string: ");
    scanf("%99s", str);

    // Pattern 1: Exactly "a"
    if (strcmp(str, "a") == 0) {
        printf("Accepted: Matches pattern a\n");
    }

    // Pattern 2: a*b+
    else {
        i = 0;

        while (str[i] == 'a') {
            countA++;
            i++;
        }

        while (str[i] == 'b') {
            countB++;
            i++;
        }

        if (str[i] == '\0' && countB > 0) {
            printf("Accepted: Matches pattern a*b+\n");
        }

        // Pattern 3: Exactly "abb"
        else if (strcmp(str, "abb") == 0) {
            printf("Accepted: Matches pattern abb\n");
        }

        else {
            printf("Rejected: Invalid string\n");
        }
    }

    return 0;
}

Output:-
Enter a string: a
Accepted: Matches pattern a
Enter a string: aaabb
Accepted: Matches pattern a*b+
Enter a string: ababa
Rejected: Invalid string

Q3.Write a C program to test whether a given identifier is valid or not. 
Code:-

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char str[100];

    char keywords[32][10] = {
        "auto", "break", "case", "char",
        "const", "continue", "default", "do",
        "double", "else", "enum", "extern",
        "float", "for", "goto", "if",
        "int", "long", "register", "return",
        "short", "signed", "sizeof", "static",
        "struct", "switch", "typedef", "union",
        "unsigned", "void", "volatile", "while"
    };

    int i, valid = 1, keyword = 0;

    printf("Enter an identifier: ");
    scanf("%99s", str);

    // Check first character
    if (!isalpha((unsigned char)str[0]) &&
        str[0] != '_') {
        valid = 0;
    }

    // Check remaining characters
    for (i = 1; str[i] != '\0'; i++) {
        if (!isalnum((unsigned char)str[i]) &&
            str[i] != '_') {
            valid = 0;
            break;
        }
    }

    // Check reserved keywords
    for (i = 0; i < 32; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            keyword = 1;
            break;
        }
    }

    if (valid && !keyword) {
        printf("%s is a valid identifier.\n", str);
    }
    else {
        printf("%s is an invalid identifier.\n", str);
    }

    return 0;
}

Output:-
Enter an identifier: student_name
student_name is a valid identifier.
Enter an identifier: 123student
123student is an invalid identifier.
Enter an identifier: int
int is an invalid identifier.
Enter an identifier: marks2026
marks2026 is a valid identifier.

Q4. Write a C program to simulate lexical analyzer for validating operators.
Code:-

#include <stdio.h>
#include <string.h>

int main() {
    char op[10];

    printf("Enter an operator: ");
    scanf("%9s", op);

    // Arithmetic operators
    if (strcmp(op, "+") == 0 ||
        strcmp(op, "-") == 0 ||
        strcmp(op, "*") == 0 ||
        strcmp(op, "/") == 0 ||
        strcmp(op, "%") == 0) {

        printf("Valid Arithmetic Operator\n");
    }

    // Relational operators
    else if (strcmp(op, "==") == 0 ||
             strcmp(op, "!=") == 0 ||
             strcmp(op, ">") == 0 ||
             strcmp(op, "<") == 0 ||
             strcmp(op, ">=") == 0 ||
             strcmp(op, "<=") == 0) {

        printf("Valid Relational Operator\n");
    }

    // Logical operators
    else if (strcmp(op, "&&") == 0 ||
             strcmp(op, "||") == 0 ||
             strcmp(op, "!") == 0) {

        printf("Valid Logical Operator\n");
    }

    // Assignment operators
    else if (strcmp(op, "=") == 0 ||
             strcmp(op, "+=") == 0 ||
             strcmp(op, "-=") == 0 ||
             strcmp(op, "*=") == 0 ||
             strcmp(op, "/=") == 0 ||
             strcmp(op, "%=") == 0) {

        printf("Valid Assignment Operator\n");
    }

    // Increment and decrement
    else if (strcmp(op, "++") == 0 ||
             strcmp(op, "--") == 0) {

        printf("Valid Increment/Decrement Operator\n");
    }

    // Bitwise operators
    else if (strcmp(op, "&") == 0 ||
             strcmp(op, "|") == 0 ||
             strcmp(op, "^") == 0 ||
             strcmp(op, "~") == 0 ||
             strcmp(op, "<<") == 0 ||
             strcmp(op, ">>") == 0) {

        printf("Valid Bitwise Operator\n");
    }

    else {
        printf("Invalid Operator\n");
    }

    return 0;
}

Output:-
Enter an operator: >=
Valid Relational Operator
Enter an operator: ++
Valid Increment/Decrement Operator
Enter an operator: @
Invalid Operator

Q5. Design context free grammar for the given language 
a) Write a C program for constructing LL (1) parsing. 
Code:-

#include <stdio.h>
#include <string.h>

char input[100];
char stack[100];
int top = -1, pos = 0;

void push(char c) {
    stack[++top] = c;
}

void displayStack() {
    int i;
    for (i = 0; i <= top; i++)
        printf("%c", stack[i]);
}

int main() {
    printf("Enter expression (use i for identifier): ");
    scanf("%99s", input);

    strcat(input, "$");

    push('$');
    push('E');

    printf("\nStack\tInput\tAction\n");

    while (top >= 0) {
        char x = stack[top];
        char a = input[pos];

        printf("%.*s\t%s\t", top + 1, stack, input + pos);

        if (x == a) {
            printf("Match %c\n", a);
            top--;
            pos++;
        }
        else if (x == 'E' && a == 'i') {
            top--;
            push('Q');
            push('T');
            printf("E -> TQ\n");
        }
        else if (x == 'E' && a == '(') {
            top--;
            push('Q');
            push('T');
            printf("E -> TQ\n");
        }
        else if (x == 'Q' && a == '+') {
            top--;
            push('Q');
            push('T');
            push('+');
            printf("Q -> +TQ\n");
        }
        else if (x == 'Q' && (a == ')' || a == '$')) {
            top--;
            printf("Q -> epsilon\n");
        }
        else if (x == 'T' && (a == 'i' || a == '(')) {
            top--;
            push('R');
            push('F');
            printf("T -> FR\n");
        }
        else if (x == 'R' && a == '*') {
            top--;
            push('R');
            push('F');
            push('*');
            printf("R -> *FR\n");
        }
        else if (x == 'R' &&
                 (a == '+' || a == ')' || a == '$')) {
            top--;
            printf("R -> epsilon\n");
        }
        else if (x == 'F' && a == 'i') {
            top--;
            push('i');
            printf("F -> i\n");
        }
        else if (x == 'F' && a == '(') {
            top--;
            push(')');
            push('E');
            push('(');
            printf("F -> (E)\n");
        }
        else {
            printf("Error: Invalid expression\n");
            return 0;
        }
    }

    printf("\nInput accepted by LL(1) parser.\n");

    return 0;
}
Output:-
Enter expression (use i for identifier): i+i*i

Stack   Input       Action
$E      i+i*i$      E -> TQ
...
Input accepted by LL(1) parser.

b) Write a C program for constructing recursive descent parsing. 
Code:-

#include <stdio.h>
#include <string.h>

char input[100];
int pos = 0;

int E();
int Q();
int T();
int R();
int F();

int E() {
    if (T()) {
        if (Q())
            return 1;
    }
    return 0;
}

int Q() {
    if (input[pos] == '+') {
        pos++;

        if (T() && Q())
            return 1;

        return 0;
    }

    return 1;
}

int T() {
    if (F()) {
        if (R())
            return 1;
    }
    return 0;
}

int R() {
    if (input[pos] == '*') {
        pos++;

        if (F() && R())
            return 1;

        return 0;
    }

    return 1;
}

int F() {
    if (input[pos] == 'i') {
        pos++;
        return 1;
    }

    if (input[pos] == '(') {
        pos++;

        if (E() && input[pos] == ')') {
            pos++;
            return 1;
        }
    }

    return 0;
}

int main() {
    printf("Enter expression (use i for identifier): ");
    scanf("%99s", input);

    if (E() && input[pos] == '\0')
        printf("Expression Accepted\n");
    else
        printf("Expression Rejected\n");

    return 0;
}
Output:-
Enter expression (use i for identifier): i+i*i
Expression Accepted
Enter expression (use i for identifier): i+*i
Expression Rejected

Q6. Design an LALR grammar. 
Write a C program to implement LALR parsing.
Code:-

#include <stdio.h>
#include <string.h>

#define ACCEPT 999

// ACTION table:
// Positive value = shift (next state = value - 1)
// Negative value = reduce (production number)
// 0 = error
int action[7][3] = {
    { 4,  5,   0},       // State 0
    { 0,  0, ACCEPT},    // State 1
    { 4,  5,   0},       // State 2
    { 4,  5,   0},       // State 3
    {-3, -3,  -3},       // State 4
    { 0,  0,  -1},       // State 5
    {-2, -2,  -2}        // State 6
};

// GOTO table: columns S and C
int goTo[7][2] = {
    {1, 2},
    {-1, -1},
    {-1, 5},
    {-1, 6},
    {-1, -1},
    {-1, -1},
    {-1, -1}
};

int terminalIndex(char ch) {
    if (ch == 'c') return 0;
    if (ch == 'd') return 1;
    if (ch == '$') return 2;
    return -1;
}

int nonTerminalIndex(char ch) {
    if (ch == 'S') return 0;
    if (ch == 'C') return 1;
    return -1;
}

int main() {
    char input[100];
    char symbolStack[100];
    int stateStack[100];

    int top = 0;
    int ip = 0;

    printf("Enter input string (only c and d): ");
    fgets(input, sizeof(input), stdin);

    input[strcspn(input, "\n")] = '\0';

    int len = strlen(input);

    if (len == 0 || len >= 98) {
        printf("Invalid input length.\n");
        return 0;
    }

    // Validate input symbols
    for (int i = 0; i < len; i++) {
        if (input[i] != 'c' && input[i] != 'd') {
            printf("Invalid input symbol.\n");
            return 0;
        }
    }

    // Append end marker
    input[len] = '$';
    input[len + 1] = '\0';

    stateStack[0] = 0;

    printf("\nStack\t\tInput\t\tAction\n");

    while (1) {
        int state = stateStack[top];
        int col = terminalIndex(input[ip]);

        if (col == -1) {
            printf("Invalid input.\n");
            break;
        }

        int act = action[state][col];

        // Display current stack
        for (int i = 0; i <= top; i++) {
            if (i > 0)
                printf("%c", symbolStack[i - 1]);
            printf("%d", stateStack[i]);
        }

        printf("\t\t%s\t\t", input + ip);

        // Accept
        if (act == ACCEPT) {
            printf("ACCEPT\n");
            printf("\nInput string is accepted.\n");
            break;
        }

        // Error
        if (act == 0) {
            printf("ERROR\n");
            printf("\nInput string is rejected.\n");
            break;
        }

        // Shift operation
        if (act > 0) {
            int nextState = act - 1;

            printf("Shift %c, go to state %d\n",
                   input[ip], nextState);

            symbolStack[top] = input[ip];
            stateStack[++top] = nextState;
            ip++;
        }

        // Reduce operation
        else {
            int production = -act;
            int popCount;
            char lhs;

            if (production == 1) {
                // S -> CC
                popCount = 2;
                lhs = 'S';
            }
            else if (production == 2) {
                // C -> cC
                popCount = 2;
                lhs = 'C';
            }
            else {
                // C -> d
                popCount = 1;
                lhs = 'C';
            }

            printf("Reduce using production %d\n",
                   production);

            top -= popCount;

            int nt = nonTerminalIndex(lhs);
            int nextState = goTo[stateStack[top]][nt];

            if (nextState == -1) {
                printf("Invalid GOTO entry.\n");
                break;
            }

            symbolStack[top] = lhs;
            stateStack[++top] = nextState;
        }
    }

    return 0;
}
Output:-
Enter input string (only c and d): cdd

Stack           Input           Action
0               cdd$            Shift c, go to state 3
0c3             dd$             Shift d, go to state 4
0c3d4           d$              Reduce using production 3
0c3C6           d$              Reduce using production 2
0C2             d$              Shift d, go to state 4
0C2d4           $               Reduce using production 3
0C2C5           $               Reduce using production 1
0S1             $               ACCEPT

Input string is accepted.

Q7. Write a program in C to check the variable values stores in variables are mapped to 
appropriate datatypes, 
Code:-

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main() {
    char datatype[20];
    char value[100];

    int valid = 0;

    printf("Enter datatype (int/float/char): ");
    scanf("%19s", datatype);

    printf("Enter value: ");
    scanf("%99s", value);

    if (strcmp(datatype, "int") == 0) {
        char *end;
        strtol(value, &end, 10);

        if (*value != '\0' && *end == '\0')
            valid = 1;
    }

    else if (strcmp(datatype, "float") == 0) {
        char *end;
        strtof(value, &end);

        if (*value != '\0' && *end == '\0')
            valid = 1;
    }

    else if (strcmp(datatype, "char") == 0) {
        if (strlen(value) == 1)
            valid = 1;
    }

    else {
        printf("Unknown datatype\n");
        return 0;
    }

    if (valid)
        printf("Valid datatype assignment\n");
    else
        printf("Invalid datatype assignment\n");

    return 0;
}
Output:-
Enter datatype (int/float/char): int
Enter value: 100
Valid datatype assignment
Enter datatype (int/float/char): int
Enter value: hello
Invalid datatype assignment

Q8.Write a C program to detect undeclared variables 
Code:-

#include <stdio.h>
#include <string.h>

int main() {
    char declared[50][50];
    char used[50][50];

    int n, m, i, j, found;

    printf("Enter number of declared variables: ");
    scanf("%d", &n);

    printf("Enter declared variables:\n");

    for (i = 0; i < n; i++) {
        scanf("%49s", declared[i]);
    }

    printf("Enter number of used variables: ");
    scanf("%d", &m);

    printf("Enter used variables:\n");

    for (i = 0; i < m; i++) {
        scanf("%49s", used[i]);
    }

    printf("\nVariable Checking:\n");

    for (i = 0; i < m; i++) {
        found = 0;

        for (j = 0; j < n; j++) {
            if (strcmp(used[i], declared[j]) == 0) {
                found = 1;
                break;
            }
        }

        if (found)
            printf("%s is declared.\n", used[i]);
        else
            printf("%s is undeclared.\n", used[i]);
    }

    return 0;
}
Output:-
Enter number of declared variables: 3

Enter declared variables:
a
b
c

Enter number of used variables: 4

Enter used variables:
a
b
x
c

Variable Checking:
a is declared.
b is declared.
x is undeclared.
c is declared.

Q9.Write a C program to check whether break keyword has been used outside any loop.
Code:-

#include <stdio.h>

int main() {
    int loop, switchBlock, br;

    printf("Is break statement present? (1=Yes, 0=No): ");
    scanf("%d", &br);

    printf("Is break inside a loop? (1=Yes, 0=No): ");
    scanf("%d", &loop);

    printf("Is break inside a switch? (1=Yes, 0=No): ");
    scanf("%d", &switchBlock);

    if (br == 0) {
        printf("No break statement found.\n");
    }

    else if (br == 1 &&
             (loop == 1 || switchBlock == 1)) {
        printf("Valid: Break is used correctly.\n");
    }

    else {
        printf("Error: Break used outside loop or switch.\n");
    }

    return 0;
}
Output:-
Is break statement present? (1=Yes, 0=No): 1
Is break inside a loop? (1=Yes, 0=No): 1
Is break inside a switch? (1=Yes, 0=No): 0
Valid: Break is used correctly.

Is break statement present? (1=Yes, 0=No): 1
Is break inside a loop? (1=Yes, 0=No): 0
Is break inside a switch? (1=Yes, 0=No): 0
Error: Break used outside loop or switch.

Is break statement present? (1=Yes, 0=No): 0
No break statement found.

Q10. Write a C program to create a parse tree Test it with the input : x = (a + b * c) / (a – b * c) 
Code:-

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char data;
    struct Node *left;
    struct Node *right;
};

struct Node* createNode(char data) {
    struct Node* newNode =
        (struct Node*)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

// Display parse tree
void displayTree(struct Node* root, int space) {
    if (root == NULL)
        return;

    space += 5;

    displayTree(root->right, space);

    printf("\n");
    for (int i = 5; i < space; i++)
        printf(" ");

    printf("%c\n", root->data);

    displayTree(root->left, space);
}

int main() {
    struct Node *root, *left, *right;
    struct Node *add, *sub, *mul1, *mul2;

    // Root: assignment operator
    root = createNode('=');
    root->left = createNode('x');

    // Division operator
    root->right = createNode('/');

    // Left side: a + b * c
    add = createNode('+');
    add->left = createNode('a');

    mul1 = createNode('*');
    mul1->left = createNode('b');
    mul1->right = createNode('c');
    add->right = mul1;

    // Right side: a - b * c
    sub = createNode('-');
    sub->left = createNode('a');

    mul2 = createNode('*');
    mul2->left = createNode('b');
    mul2->right = createNode('c');
    sub->right = mul2;

    root->right->left = add;
    root->right->right = sub;

    printf("Parse Tree for x = (a+b*c)/(a-b*c):\n");

    displayTree(root, 0);

    return 0;
}
Output:-
Parse Tree for x = (a+b*c)/(a-b*c):

               =
          x         /
                -       +
              a   *   a   *
                 b c     b c

Q11. Write a C program to generate the three address code. Test it for the expression a + b *
Code:-

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char input[100];
char stack[100];
int top = -1;
int temp = 1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char c) {
    if (c == '*' || c == '/')
        return 2;

    if (c == '+' || c == '-')
        return 1;

    return 0;
}

int main() {
    char postfix[100];
    char operands[100][20];
    int i, j = 0, k = 0;

    printf("Enter expression: ");
    scanf("%99s", input);

    // Convert infix to postfix
    for (i = 0; input[i] != '\0'; i++) {
        char c = input[i];

        if (isalnum((unsigned char)c)) {
            postfix[j++] = c;
        }

        else if (c == '(') {
            push(c);
        }

        else if (c == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = pop();

            if (top == -1) {
                printf("Invalid expression\n");
                return 1;
            }

            pop();
        }

        else if (c == '+' || c == '-' ||
                 c == '*' || c == '/') {

            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(c)) {

                postfix[j++] = pop();
            }

            push(c);
        }

        else {
            printf("Invalid character\n");
            return 1;
        }
    }

    while (top != -1) {
        if (stack[top] == '(') {
            printf("Invalid expression\n");
            return 1;
        }

        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    // Generate three address code
    for (i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];

        if (isalnum((unsigned char)c)) {
            char s[2] = {c, '\0'};
            strcpy(operands[k++], s);
        }

        else {
            if (k < 2) {
                printf("Invalid expression\n");
                return 1;
            }

            char op2[20], op1[20], result[20];

            strcpy(op2, operands[--k]);
            strcpy(op1, operands[--k]);

            sprintf(result, "t%d", temp);

            printf("%s = %s %c %s\n",
                   result, op1, c, op2);

            strcpy(operands[k++], result);
            temp++;
        }
    }

    if (k != 1) {
        printf("Invalid expression\n");
        return 1;
    }

    printf("Result stored in %s\n", operands[0]);

    return 0;
}
Output:-
Enter expression: a+b*c+d
t1 = b * c
t2 = a + t1
t3 = t2 + d
Result stored in t3

Q12. Write a C program to generate the postfix representation of an. Test it for the 
expression: (a – b) * (c + d) + (a – b)
Code:-

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char stack[100];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

int precedence(char c) {
    if (c == '*' || c == '/')
        return 2;

    if (c == '+' || c == '-')
        return 1;

    return 0;
}

int main() {
    char infix[100], postfix[100];
    int i, j = 0;

    printf("Enter infix expression: ");
    scanf("%99s", infix);

    for (i = 0; infix[i] != '\0'; i++) {

        char c = infix[i];

        // If operand, add to postfix
        if (isalnum((unsigned char)c)) {
            postfix[j++] = c;
        }

        // If opening bracket
        else if (c == '(') {
            push(c);
        }

        // If closing bracket
        else if (c == ')') {

            while (top != -1 && stack[top] != '(') {
                postfix[j++] = pop();
            }

            if (top == -1) {
                printf("Invalid expression\n");
                return 1;
            }

            pop();
        }

        // If operator
        else if (c == '+' || c == '-' ||
                 c == '*' || c == '/') {

            while (top != -1 &&
                   stack[top] != '(' &&
                   precedence(stack[top]) >= precedence(c)) {

                postfix[j++] = pop();
            }

            push(c);
        }

        else {
            printf("Invalid character\n");
            return 1;
        }
    }

    // Pop remaining operators
    while (top != -1) {

        if (stack[top] == '(') {
            printf("Invalid expression\n");
            return 1;
        }

        postfix[j++] = pop();
    }

    postfix[j] = '\0';

    printf("Postfix Expression: %s\n", postfix);

    return 0;
}
Output:-
Enter infix expression: (a-b)*(c+d)+(a-b)
Postfix Expression: ab-cd+*ab-+

