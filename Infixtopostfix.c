#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    if (top >= MAX - 1) exit(1);
    stack[++top] = c;
}

char pop() {
    if (top == -1) exit(1);
    return stack[top--];
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return 0;
}

int isRightAssociative(char op) { return op == '^'; }
int isOperator(char c) { return c == '+' || c == '-' || c == '*' || c == '/' || c == '^'; }
int isVariable(char c) { return isalpha(c); }

void infixToPostfix(const char *infix, char *postfix) {
    int i = 0, k = 0;
    top = -1;

    while (infix[i]) {
        char c = infix[i];
        if (isspace(c)) { i++; continue; }

        if (isdigit(c) || c == '.') {
            while (isdigit(infix[i]) || infix[i] == '.') postfix[k++] = infix[i++];
            postfix[k++] = ' ';
        } else if (isVariable(c)) {
            postfix[k++] = c; postfix[k++] = ' '; i++;
        } else if (c == '(') {
            push(c); i++;
        } else if (c == ')') {
            while (top != -1 && stack[top] != '(') postfix[k++] = pop(), postfix[k++] = ' ';
            if (top == -1) exit(1);
            pop(); i++;
        } else if (isOperator(c)) {
            if (c == '-' && (i == 0 || infix[i-1] == '(' || isOperator(infix[i-1]))) {
                postfix[k++] = '0'; postfix[k++] = ' ';
                push('-'); i++; continue;
            }
            while (top != -1 && stack[top] != '(') {
                char topOp = stack[top];
                int pTop = precedence(topOp), pCurr = precedence(c);
                if (pTop > pCurr || (pTop == pCurr && !isRightAssociative(c))) {
                    postfix[k++] = pop(); postfix[k++] = ' ';
                } else break;
            }
            push(c); i++;
        } else exit(1);
    }
    while (top != -1) {
        if (stack[top] == '(') exit(1);
        postfix[k++] = pop(); postfix[k++] = ' ';
    }
    postfix[k] = 0;
}

float power(float base, int exp) {
    float res = 1;
    int e = exp < 0 ? -exp : exp;
    for (int i = 0; i < e; i++) res *= base;
    return exp < 0 ? 1.0f / res : res;
}

int containsVariable(const char *expr) {
    while (*expr) if (isVariable(*expr++)) return 1;
    return 0;
}

float evaluatePostfix(const char *postfix) {
    float stackf[MAX]; int topf = -1;
    char buf[32];
    int i = 0, j = 0;
    while (postfix[i]) {
        if (isspace(postfix[i])) { i++; continue; }

        if (isdigit(postfix[i]) || postfix[i] == '.' || 
           (postfix[i] == '-' && (isdigit(postfix[i+1]) || postfix[i+1] == '.'))) {
            j = 0;
            if (postfix[i] == '-') buf[j++] = postfix[i++];
            while (isdigit(postfix[i]) || postfix[i] == '.') buf[j++] = postfix[i++];
            buf[j] = 0;
            stackf[++topf] = atof(buf);
        } else if (isOperator(postfix[i])) {
            if (topf < 1) exit(1);
            float b = stackf[topf--], a = stackf[topf--];
            switch(postfix[i]) {
                case '+': stackf[++topf] = a + b; break;
                case '-': stackf[++topf] = a - b; break;
                case '*': stackf[++topf] = a * b; break;
                case '/': if (b == 0) exit(1); stackf[++topf] = a / b; break;
                case '^': {
                    int eb = (int)b;
                    if (b == eb) stackf[++topf] = power(a, eb);
                    else exit(1);
                    break;
                }
            }
            i++;
        } else exit(1);
    }
    if (topf != 0) exit(1);
    return stackf[topf];
}

int main() {
    char infix[3 * MAX], postfix[3 * MAX];

    printf("Enter infix expression: ");
    if (!fgets(infix, sizeof(infix), stdin)) return 1;
    size_t len = strlen(infix);
    if (len && infix[len - 1] == '\n') infix[len - 1] = 0;

    infixToPostfix(infix, postfix);

    printf("Infix  : %s\n", infix);
    printf("Postfix: %s\n", postfix);

    if (containsVariable(infix))
        printf("Expression contains variables, evaluation skipped.\n");
    else {
        float res = evaluatePostfix(postfix);
        printf("Evaluation Result: %.6f\n", res);
    }
    return 0;
}
