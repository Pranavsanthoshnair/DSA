#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top >= MAX - 1) {
        printf("Error: Stack overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Error: Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int isRightAssociative(char op) {
    return op == '^';
}

int isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^';
}

int isVariable(char c) {
    return isalpha(c);
}

void infixToPostfix(const char *infix, char *postfix) {
    int i = 0, k = 0;
    top = -1;

    while (infix[i] != '\0') {
        char c = infix[i];

        if (isspace(c)) {
            i++;
            continue;
        }

        if (isdigit(c) || c == '.') {
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' ';
        }
        else if (isVariable(c)) {
            postfix[k++] = c;
            postfix[k++] = ' ';
            i++;
        }
        else if (c == '(') {
            push(c);
            i++;
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            if (top == -1) {
                printf("Error: Mismatched parentheses\n");
                exit(1);
            }
            pop();
            i++;
        }
        else if (isOperator(c)) {
            if (c == '-') {
                if (i == 0 || infix[i-1] == '(' || isOperator(infix[i-1])) {
                    postfix[k++] = '0';
                    postfix[k++] = ' ';
                    push('-');
                    i++;
                    continue;
                }
            }
            while (top != -1 && stack[top] != '(') {
                char topOp = stack[top];
                int precTop = precedence(topOp);
                int precCurr = precedence(c);
                if (precTop > precCurr || (precTop == precCurr && !isRightAssociative(c))) {
                    postfix[k++] = pop();
                    postfix[k++] = ' ';
                }
                else {
                    break;
                }
            }
            push(c);
            i++;
        }
        else {
            printf("Error: Invalid character '%c' in expression\n", c);
            exit(1);
        }
    }
    while (top != -1) {
        if (stack[top] == '(' || stack[top] == ')') {
            printf("Error: Mismatched parentheses\n");
            exit(1);
        }
        postfix[k++] = pop();
        postfix[k++] = ' ';
    }
    postfix[k] = '\0';
}

float power(float base, int exp) {
    float result = 1.0f;
    int absExp = exp < 0 ? -exp : exp;
    for (int i = 0; i < absExp; i++) {
        result *= base;
    }
    if (exp < 0) {
        return 1.0f / result;
    }
    return result;
}

int containsVariable(const char *expr) {
    for (int i = 0; expr[i]; i++) {
        if (isVariable(expr[i])) return 1;
    }
    return 0;
}

float evaluatePostfix(const char *postfix) {
    float stackf[MAX];
    int topf = -1;

    char exprCopy[3 * MAX];
    strcpy(exprCopy, postfix);

    char *token = strtok(exprCopy, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '.' && isdigit(token[1])) ||
            (token[0] == '-' && (isdigit(token[1]) || token[1] == '.'))) {
            stackf[++topf] = atof(token);
        }
        else if (strlen(token) == 1 && isOperator(token[0])) {
            if (topf < 1) {
                printf("Error: insufficient operands\n");
                exit(1);
            }
            float op2 = stackf[topf--];
            float op1 = stackf[topf--];
            switch (token[0]) {
                case '+': stackf[++topf] = op1 + op2; break;
                case '-': stackf[++topf] = op1 - op2; break;
                case '*': stackf[++topf] = op1 * op2; break;
                case '/':
                    if (op2 == 0) {
                        printf("Error: division by zero\n");
                        exit(1);
                    }
                    stackf[++topf] = op1 / op2;
                    break;
                case '^':
                    if ((int)op2 == op2) {
                        stackf[++topf] = power(op1, (int)op2);
                    } else {
                        printf("Error: non-integer exponent not supported\n");
                        exit(1);
                    }
                    break;
                default:
                    printf("Unknown operator %c\n", token[0]);
                    exit(1);
            }
        }
        else {
            printf("Error: Invalid token '%s'\n", token);
            exit(1);
        }
        token = strtok(NULL, " ");
    }
    if (topf != 0) {
        printf("Error: invalid expression\n");
        exit(1);
    }
    return stackf[topf];
}

int main() {
    char infix[3 * MAX], postfix[3 * MAX];

    printf("Enter infix expression: ");
    if (!fgets(infix, sizeof(infix), stdin)) {
        printf("Error reading input\n");
        return 1;
    }
    size_t len = strlen(infix);
    if (len > 0 && infix[len - 1] == '\n') {
        infix[len - 1] = '\0';
    }

    infixToPostfix(infix, postfix);

    printf("Infix  : %s\n", infix);
    printf("Postfix: %s\n", postfix);

    if (containsVariable(infix)) {
        printf("Expression contains variables, evaluation skipped.\n");
    } else {
        float result = evaluatePostfix(postfix);
        printf("Evaluation Result: %.6f\n", result);
    }

    return 0;
}
