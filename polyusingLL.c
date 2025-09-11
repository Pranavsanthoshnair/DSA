#include <stdio.h>
#include <stdlib.h>

// Node for each polynomial term
struct Term {
    int coeff;
    int expo;
    struct Term* next;
};

// Insert a new term in sorted order (by exponent)
struct Term* insertNode(struct Term* poly, int coeff, int expo) {
    struct Term* newNode = malloc(sizeof(struct Term));
    newNode->coeff = coeff;
    newNode->expo = expo;
    newNode->next = NULL;

    // Insert at head if empty or higher exponent
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

// Create a polynomial by taking input
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

// Print polynomial
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

// Add two polynomials (stub for now)
struct Term* addPoly(struct Term* poly1, struct Term* poly2) {
    // Not implemented in your code, leaving blank
    return NULL;
}

int main() {
    struct Term* poly1 = NULL;
    struct Term* poly2 = NULL;
    struct Term* result = NULL;

    printf("Enter first polynomial:\n");
    poly1 = createPoly(poly1);

    printf("Enter second polynomial:\n");
    poly2 = createPoly(poly2);

    // addPoly still incomplete
    result = addPoly(poly1, poly2);

    printf("Polynomial 1: ");
    printPoly(poly1);

    printf("Polynomial 2: ");
    printPoly(poly2);

    printf("Result (not implemented): ");
    printPoly(result);

    return 0;
}
