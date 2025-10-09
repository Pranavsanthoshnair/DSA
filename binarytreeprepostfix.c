#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TreeNode {
    char data;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

int getPrecedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    if (op == '^') return 3;
    return -1;
}

void infixToPostfix(char* infix, char* postfix) {
    char opStack[100];
    int top = -1, k = 0;

    for (int i = 0; infix[i]; i++) {
        if (isalnum(infix[i])) postfix[k++] = infix[i];
        else if (infix[i] == '(') opStack[++top] = infix[i];
        else if (infix[i] == ')') {
            while (top != -1 && opStack[top] != '(') postfix[k++] = opStack[top--];
            top--;
        } else {
            while (top != -1 && getPrecedence(infix[i]) <= getPrecedence(opStack[top]))
                postfix[k++] = opStack[top--];
            opStack[++top] = infix[i];
        }
    }

    while (top != -1) postfix[k++] = opStack[top--];
    postfix[k] = '\0';
}

TreeNode* createNode(char data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

TreeNode* buildExpressionTree(char* postfix) {
    TreeNode* nodeStack[100];
    int top = -1;
    TreeNode *node, *rightChild, *leftChild;

    for (int i = 0; postfix[i]; i++) {
        if (isalnum(postfix[i])) {
            node = createNode(postfix[i]);
            nodeStack[++top] = node;
        } else {
            node = createNode(postfix[i]);
            rightChild = nodeStack[top--];
            leftChild = nodeStack[top--];
            node->left = leftChild;
            node->right = rightChild;
            nodeStack[++top] = node;
        }
    }
    return nodeStack[top];
}

void preOrderTraversal(TreeNode* root) {
    if (root) {
        printf("%c ", root->data);
        preOrderTraversal(root->left);
        preOrderTraversal(root->right);
    }
}

void postOrderTraversal(TreeNode* root) {
    if (root) {
        postOrderTraversal(root->left);
        postOrderTraversal(root->right);
        printf("%c ", root->data);
    }
}

void printLevelOrder(TreeNode* root) {
    if (!root) return;
    TreeNode* queue[100];
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        int nodeCount = rear - front;
        for (int i = 0; i < nodeCount; i++) {
            TreeNode* current = queue[front++];
            printf("%c ", current->data);
            if (current->left) queue[rear++] = current->left;
            if (current->right) queue[rear++] = current->right;
        }
        printf("\n");
    }
}

int main() {
    char infix[100], postfix[100];
    printf("Enter an infix expression: ");
    fgets(infix, sizeof(infix), stdin);
    infix[strcspn(infix, "\n")] = 0;

    infixToPostfix(infix, postfix);
    TreeNode* root = buildExpressionTree(postfix);

    printf("\nPrefix Equivalent:   ");
    preOrderTraversal(root);
    printf("\nPostfix Equivalent:  ");
    postOrderTraversal(root);
    printf("\nLevel Order (Tree):\n");
    printLevelOrder(root);
    return 0;
}
