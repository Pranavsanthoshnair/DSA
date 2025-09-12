#include <stdio.h>
#include <ctype.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}

char pop() {
    return stack[top--];
}

void infixToPostfix(char infix[], char postfix[]) {
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

// 🔥 NEW: Postfix Evaluation
int evaluatePostfix(char postfix[]) {
    int valStack[MAX], vtop = -1;
    int values[256] = {0};

    // ask user values for operands
    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isalnum(c) && values[(int)c] == 0) {
            printf("Enter value for %c: ", c);
            scanf("%d", &values[(int)c]);
        }
    }

    for (int i = 0; postfix[i] != '\0'; i++) {
        char c = postfix[i];
        if (isalnum(c)) {
            valStack[++vtop] = values[(int)c];
        } else {
            int b = valStack[vtop--];
            int a = valStack[vtop--];
            int res;
            switch (c) {
                case '+': res = a + b; break;
                case '-': res = a - b; break;
                case '*': res = a * b; break;
                case '/': res = a / b; break;
                default: res = 0;
            }
            valStack[++vtop] = res;
        }
    }
    return valStack[vtop];
}

int main() {
    char infix[MAX], postfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);

    int result = evaluatePostfix(postfix);
    printf("Evaluated Result = %d\n", result);

    return 0;
}
