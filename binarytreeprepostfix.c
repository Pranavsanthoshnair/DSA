#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
struct Node {
    char value[50];
    struct Node *left, *right;
};
struct Node *stack[100];
int top = -1;
void push(struct Node *n){ stack[++top] = n; }
struct Node* pop(){ return stack[top--]; }
struct Node* peek(){ return stack[top]; }
struct Node* createNode(char *val){
    struct Node* n = malloc(sizeof(struct Node));
    strcpy(n->value, val);
    n->left = n->right = NULL;
    return n;
}
int precedence(char op){
    if (op=='+'||op=='-') return 1;
    if (op=='*'||op=='/') return 2;
    if (op=='^') return 3;
    return 0;
}
void buildTree(char expr[]){
    struct Node *opStack[100]; int opTop=-1;
    for (int i=0;i<strlen(expr);i++){
        if (isspace(expr[i])) continue;
        if (isalnum(expr[i])){
            char token[50]; int j=0;
            while (i<strlen(expr) && isalnum(expr[i])) token[j++]=expr[i++];
            token[j]='\0'; i--;
            push(createNode(token));
        }
        else if (expr[i]=='(') opStack[++opTop]=createNode("(");
        else if (expr[i]==')'){
            while (opTop>=0 && strcmp(opStack[opTop]->value,"(")!=0){
                struct Node* op=opStack[opTop--];
                op->right=pop(); op->left=pop(); push(op);
            }
            opTop--;
        }
        else {
            while (opTop>=0 && precedence(opStack[opTop]->value[0])>=precedence(expr[i])){
                struct Node* op=opStack[opTop--];
                op->right=pop(); op->left=pop(); push(op);
            }
            char token[2]={expr[i],'\0'};
            opStack[++opTop]=createNode(token);
        }
    }
    while (opTop>=0){
        struct Node* op=opStack[opTop--];
        op->right=pop(); op->left=pop(); push(op);
    }
}
void printPrefix(struct Node *r){
    if (!r) return;
    printf("%s ",r->value);
    printPrefix(r->left);
    printPrefix(r->right);
}
void printPostfix(struct Node *r){
    if (!r) return;
    printPostfix(r->left);
    printPostfix(r->right);
    printf("%s ",r->value);
}
int main(){
    char expr[100]; int choice;
    printf("Enter infix expression: ");
    fgets(expr,sizeof(expr),stdin);
    expr[strcspn(expr,"\n")]=0;
    buildTree(expr);
    while (1){
        printf("\n1. Prefix\n2. Postfix\n3. Exit\nChoice: ");
        scanf("%d",&choice);
        if (choice==1){ printf("\nPrefix: "); printPrefix(peek()); printf("\n"); }
        else if (choice==2){ printf("\nPostfix: "); printPostfix(peek()); printf("\n"); }
        else if (choice==3){ printf("Exiting...\n"); break; }
        else printf("Invalid choice!\n");
    }
    return 0;
}
