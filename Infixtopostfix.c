#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX 100
char stack[MAX];
int top = -1;
void push(char c) {
    stack[++top] = c;
}
char pop() {
    return stack[top--];
}
int intStack[MAX];
int intTop = -1;
void pushInt(int val) {
    intStack[++intTop] = val;
}
int popInt() {
    return intStack[intTop--];
}
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}
void infixToPostfix(char infix[], char postfix[]) {
    int i, k = 0;
    char c;
    top = -1;  
    for (i = 0; (c = infix[i]) != '\0'; i++) {
        if (isalnum(c)) {
            postfix[k++] = c; 
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
            }
            pop(); 
        }
    else { 
        while (top != -1 && stack[top] != '(' && precedence(stack[top]) >= precedence(c)) {
            postfix[k++] = pop();
        }
        push(c);
    }
    }
    while (top != -1) {
        postfix[k++] = pop();
    }
    postfix[k] = '\0';
    printf("Infix : %-20s Postfix : %s\n", infix, postfix);
}
int evaluatePostfix(char postfix[]) {
    char c;
    int i, op1, op2, result;
    intTop = -1;
    for (i = 0; (c = postfix[i]) != '\0'; i++) {
        if (isdigit(c)) {
            pushInt(c - '0');
        }
        else {
            op2 = popInt();
            op1 = popInt();
            switch (c) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
                default:
                    exit(1);
            }
            pushInt(result);
        }
    }
    return popInt();
}
int main() {
    char infix[MAX];
    char postfix[MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    int result = evaluatePostfix(postfix);
    printf("Evaluation Result: %d\n", result);
    return 0;
}
