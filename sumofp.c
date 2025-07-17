#include <stdio.h>

struct Term {
    int coeff;
    int expo;
};

void addPolynomials(struct Term poly1[], int n1, struct Term poly2[], int n2, struct Term polyResult[], int *nResult) {
    int i = 0, j = 0, k = 0;

    while (i < n1 && j < n2) {
        if (poly1[i].expo == poly2[j].expo) {
            polyResult[k].coeff = poly1[i].coeff + poly2[j].coeff;
            polyResult[k].expo = poly1[i].expo;
            i++;
            j++;
            k++;
        }
        else if (poly1[i].expo > poly2[j].expo) {
            polyResult[k] = poly1[i];
            i++;
            k++;
        }
        else {
            polyResult[k] = poly2[j];
            j++;
            k++;
        }
    }

    while (i < n1) {
        polyResult[k] = poly1[i];
        i++;
        k++;
    }

    while (j < n2) {
        polyResult[k] = poly2[j];
        j++;
        k++;
    }

    *nResult = k; 
}

void displayPolynomial(struct Term poly[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%dx^%d", poly[i].coeff, poly[i].expo);
        if (i != n - 1) {
            printf(" + ");
        }
    }
    printf("\n");
}

void readPolynomial(struct Term poly[], int *n) {
    printf("Enter the number of terms in the polynomial: ");
    scanf("%d", n);

    for (int i = 0; i < *n; i++) {
        printf("Enter coefficient and exponent for term %d: ", i + 1);
        scanf("%d %d", &poly[i].coeff, &poly[i].expo);
    }
}

int main() {
    struct Term poly1[20], poly2[20], polyResult[40];
    int n1, n2, nResult;
    
    printf("Enter the first polynomial:\n");
    readPolynomial(poly1, &n1);
    
    printf("Enter the second polynomial:\n");
    readPolynomial(poly2, &n2);
    
    printf("First Polynomial: ");
    displayPolynomial(poly1, n1);
    
    printf("Second Polynomial: ");
    displayPolynomial(poly2, n2);
    
    addPolynomials(poly1, n1, poly2, n2, polyResult, &nResult);
    
    printf("Sum of Polynomials: ");
    displayPolynomial(polyResult, nResult);

    return 0;
}
