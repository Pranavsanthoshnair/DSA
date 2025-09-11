#include <stdio.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

void infixToPostfix(char infix[]) {
    char postfix[MAX];
    int i, k = 0;
    char c;

    for (i = 0; (c = infix[i]) != '\0'; i++) {
        if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || (c >= '0' && c <= '9')) {
            postfix[k++] = c;  // directly append operands
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
            }
            pop(); // remove '('
        }
        else { // treat every operator same (no precedence)
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
            }
            push(c);
        }
    }

    // pop remaining operators
    while (top != -1) {
        postfix[k++] = pop();
    }

    postfix[k] = '\0';

    printf("Infix : %-20s Postfix : %s\n", infix, postfix);
}

int main() {
    char infix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix);

    return 0;
}
