#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 100

char stack[MAX];
int top = -1;

void push(char c) {
    stack[++top] = c;
}


char pop() {
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


void infixToPostfix(char infix[], char postfix[]) {
    int i = 0, k = 0;
    char c;
    top = -1;

    while ((c = infix[i]) != '\0') {
        if (isdigit(c) || c == '.') {
            while (isdigit(infix[i]) || infix[i] == '.') {
                postfix[k++] = infix[i++];
            }
            postfix[k++] = ' '; 
            continue;
        }
        else if (c == '(') {
            push(c);
        }
        else if (c == ')') {
            while (top != -1 && stack[top] != '(') {
                postfix[k++] = pop();
                postfix[k++] = ' ';
            }
            pop(); 
        }
        else {
            while (top != -1 && stack[top] != '(') {
                char topOp = stack[top];
                int precTop = precedence(topOp);
                int precCurr = precedence(c);
                if (precTop > precCurr || (precTop == precCurr && !isRightAssociative(c))) {
                    postfix[k++] = pop();
                    postfix[k++] = ' ';
                } else {
                    break;
                }
            }
            push(c);
        }
        i++;
    }
    while (top != -1) {
        postfix[k++] = pop();
        postfix[k++] = ' ';
    }
    postfix[k] = '\0';
    printf("Infix  : %s\n", infix);
    printf("Postfix: %s\n", postfix);
}
float evaluatePostfix(char postfix[]) {
    float stackf[MAX];
    int topf = -1;

    char *token = strtok(postfix, " ");
    while (token != NULL) {
        if (isdigit(token[0]) || (token[0] == '.' && isdigit(token[1]))) {
            stackf[++topf] = atof(token);
        } else {
          
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
                case '^': stackf[++topf] = powf(op1, op2); break;
                default:
                    printf("Unknown operator %c\n", token[0]);
                    exit(1);
            }
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
    char infix[MAX], postfix[3 * MAX];
    printf("Enter infix expression: ");
    scanf("%s", infix);
    infixToPostfix(infix, postfix);
    float result = evaluatePostfix(postfix);
    printf("Evaluation Result: %.6f\n", result);
    return 0;
}
