#include <stdio.h>
#include <stdlib.h>
struct Term {
    int coeff;
    int expo;
    struct Term* next;
};
struct Term* insertNode(struct Term* poly, int coeff, int expo) {
    struct Term* newNode = malloc(sizeof(struct Term));
    newNode->coeff = coeff;
    newNode->expo = expo;
    newNode->next = NULL;
    if (poly == NULL || expo > poly->expo) {
        newNode->next = poly;
        poly = newNode;
    } 
    else {
        struct Term* current = poly;
        while (current->next != NULL && current->next->expo >= expo) {
            current = current->next;
        }
        newNode->next = current->next;
        current->next = newNode;
    }
    return poly;
}
struct Term* createPoly(struct Term* poly) {
    int n, coeff, expo;
    printf("Enter number of terms: ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) {
        printf("Enter coefficient of term %d: ", i + 1);
        scanf("%d", &coeff);
        printf("Enter exponent of term %d: ", i + 1);
        scanf("%d", &expo);

        poly = insertNode(poly, coeff, expo);
    }
    return poly;
}
void printPoly(struct Term* poly) {
    if (poly == NULL) {
        printf("No polynomial\n");
        return;
    }
    struct Term* current = poly;
    while (current != NULL) {
        printf("%dX^%d", current->coeff, current->expo);
        if (current->next != NULL) printf(" + ");
        current = current->next;
    }
    printf("\n");
}
struct Term* addPoly(struct Term* poly1, struct Term* poly2) {
    struct Term* result = NULL;
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->expo == poly2->expo) {
            int sumCoeff = poly1->coeff + poly2->coeff;
            if (sumCoeff != 0) {  
                result = insertNode(result, sumCoeff, poly1->expo);
            }
            poly1 = poly1->next;
            poly2 = poly2->next;
        }
        else if (poly1->expo > poly2->expo) {
            result = insertNode(result, poly1->coeff, poly1->expo);
            poly1 = poly1->next;
        }
        else { 
            result = insertNode(result, poly2->coeff, poly2->expo);
            poly2 = poly2->next;
        }
    }
    while (poly1 != NULL) {
        result = insertNode(result, poly1->coeff, poly1->expo);
        poly1 = poly1->next;
    }
    while (poly2 != NULL) {
        result = insertNode(result, poly2->coeff, poly2->expo);
        poly2 = poly2->next;
    }
    return result;
}
int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;
    struct Term* result = NULL;
    printf("Enter first polynomial:\n");
    poly1 = createPoly(poly1);
    printf("Enter second polynomial:\n");
    poly2 = createPoly(poly2);
    result = addPoly(poly1, poly2);
    printf("Polynomial 1: ");
    printPoly(poly1);
    printf("Polynomial 2: ");
    printPoly(poly2);
    printf("Result : ");
    printPoly(result);
    return 0;
}
