#include <stdio.h>

#define MAX 100

// Each non-zero matrix element is stored with its row, column, and value
struct Element {
    int row, col, value;
};

// This function prints all non-zero elements of a sparse matrix
void display(struct Element mat[], int count) {
    printf("Row Col Value\n");
    for (int i = 0; i < count; i++) {
        printf(" %d   %d    %d\n", mat[i].row, mat[i].col, mat[i].value);
    }
}

// This function reads user input to fill a sparse matrix
int readSparseMatrix(struct Element mat[]) {
    int n;
    printf("Enter number of non-zero elements: ");
    scanf("%d", &n);

    // Ask user to enter each element's row, column and value
    for (int i = 0; i < n; i++) {
        printf("Enter row, column and value for term %d: ", i + 1);
        scanf("%d %d %d", &mat[i].row, &mat[i].col, &mat[i].value);
    }

    return n;  // Return total number of non-zero elements
}

// This function calculates the transpose of a sparse matrix
int transpose(struct Element mat[], struct Element result[], int count) {
    for (int i = 0; i < count; i++) {
        result[i].row = mat[i].col;   // Flip row and column
        result[i].col = mat[i].row;
        result[i].value = mat[i].value;
    }
    return count;  // Same number of non-zero elements after transpose
}

// This function adds two sparse matrices and stores result in 'result' array
int addSparse(struct Element a[], int n1, struct Element b[], int n2, struct Element result[]) {
    int i = 0, j = 0, k = 0;

    // Traverse both matrices like merging two sorted lists
    while (i < n1 && j < n2) {
        // If A[i] comes before B[j] in matrix order, add A[i] to result
        if (a[i].row < b[j].row || (a[i].row == b[j].row && a[i].col < b[j].col)) {
            result[k++] = a[i++];
        }
        // If B[j] comes before A[i], add B[j] to result
        else if (b[j].row < a[i].row || (a[i].row == b[j].row && b[j].col < a[i].col)) {
            result[k++] = b[j++];
        }
        // If both positions match, add their values
        else {
            result[k] = a[i];
            result[k].value = a[i].value + b[j].value;
            i++; j++; k++;
        }
    }

    // If elements are left in A, add them
    while (i < n1) result[k++] = a[i++];

    // If elements are left in B, add them
    while (j < n2) result[k++] = b[j++];

    return k;  // Return total non-zero elements in result
}

int main() {
    struct Element A[MAX], B[MAX], sum[MAX], transA[MAX];
    int n1, n2, nSum, nTrans;

    // Read matrix A from user
    printf("Enter Sparse Matrix A:\n");
    n1 = readSparseMatrix(A);

    // Read matrix B from user
    printf("\nEnter Sparse Matrix B:\n");
    n2 = readSparseMatrix(B);

    // Display entered matrices
    printf("\nMatrix A:\n");
    display(A, n1);

    printf("\nMatrix B:\n");
    display(B, n2);

    // Add A and B
    nSum = addSparse(A, n1, B, n2, sum);
    printf("\nSum of A and B:\n");
    display(sum, nSum);

    // Transpose of A
    nTrans = transpose(A, transA, n1);
    printf("\nTranspose of A:\n");
    display(transA, nTrans);

    return 0;
}
