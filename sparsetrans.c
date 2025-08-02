#include <stdio.h>

int rows, cols;
int matrixA[6][6], matrixB[6][6];
int compactA[36][3], compactB[36][3], result[72][3], transposeMat[72][3];
int sizeA, sizeB, sizeR;

void initializeMatrix(int mat[6][6]) {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            mat[i][j] = 0;
}

void readMatrixSparse(int mat[6][6], char matrixName) {
    int nonZeroCount;
    printf("Enter number of non-zero elements for Matrix %c: ", matrixName);
    scanf("%d", &nonZeroCount);
    
    printf("Enter non-zero elements (row col value) for Matrix %c:\n", matrixName);
    for (int i = 0; i < nonZeroCount; i++) {
        int row, col, value;
        printf("Element %d: ", i + 1);
        scanf("%d %d %d", &row, &col, &value);
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            mat[row][col] = value;
        } else {
            printf("Invalid position! Skipping element.\n");
            i--; // Retry this element
        }
    }
}

int createCompact(int mat[6][6], int compact[36][3]) {
    int k = 1;
    compact[0][0] = rows;
    compact[0][1] = cols;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (mat[i][j] != 0) {
                compact[k][0] = i;
                compact[k][1] = j;
                compact[k][2] = mat[i][j];
                k++;
            }

    compact[0][2] = k - 1;
    return k - 1;
}

int sumCompact() {
    int i = 1, j = 1, k = 1;
    result[0][0] = rows;
    result[0][1] = cols;

    while (i <= sizeA && j <= sizeB) {
        if (compactA[i][0] < compactB[j][0] ||
           (compactA[i][0] == compactB[j][0] && compactA[i][1] < compactB[j][1])) {
            result[k][0] = compactA[i][0];
            result[k][1] = compactA[i][1];
            result[k][2] = compactA[i][2];
            i++;
        } else if (compactB[j][0] < compactA[i][0] ||
                  (compactB[j][0] == compactA[i][0] && compactB[j][1] < compactA[i][1])) {
            result[k][0] = compactB[j][0];
            result[k][1] = compactB[j][1];
            result[k][2] = compactB[j][2];
            j++;
        } else {
            result[k][0] = compactA[i][0];
            result[k][1] = compactA[i][1];
            result[k][2] = compactA[i][2] + compactB[j][2];
            i++;
            j++;
        }
        k++;
    }

    while (i <= sizeA) {
        result[k][0] = compactA[i][0];
        result[k][1] = compactA[i][1];
        result[k][2] = compactA[i][2];
        i++; k++;
    }

    while (j <= sizeB) {
        result[k][0] = compactB[j][0];
        result[k][1] = compactB[j][1];
        result[k][2] = compactB[j][2];
        j++; k++;
    }

    result[0][2] = k - 1;
    return k - 1;
}

void transpose(int src[72][3], int trans[72][3]) {
    trans[0][0] = src[0][1];
    trans[0][1] = src[0][0];
    trans[0][2] = src[0][2];

    int k = 1;
    for (int i = 0; i < cols; i++)
        for (int j = 1; j <= src[0][2]; j++)
            if (src[j][1] == i) {
                trans[k][0] = src[j][1];
                trans[k][1] = src[j][0];
                trans[k][2] = src[j][2];
                k++;
            }
}

void display(int mat[72][3], int size) {
    printf("Row Col Val\n");
    for (int i = 0; i <= size; i++)
        printf("%3d %3d %3d\n", mat[i][0], mat[i][1], mat[i][2]);
}

void displaySparseMatrix(int mat[6][6]) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%3d ", mat[i][j]);
        }
        printf("\n");
    }
}

void displaySideBySide(int mat[6][6], int compact[36][3], int size, char matrixName) {
    printf("\nMatrix %c\n", matrixName);
    printf("Sparse Matrix Form:\tCompact Array Form:\n");
    
    int maxRows = (rows > size + 1) ? rows : size + 1;
    
    for (int i = 0; i < maxRows; i++) {
        if (i < rows) {
            for (int j = 0; j < cols; j++) {
                printf("%3d ", mat[i][j]);
            }
        } else {
            for (int j = 0; j < cols; j++) {
                printf("    ");
            }
        }
        
        printf("\t\t");
        if (i <= size) {
            printf("[%2d][%2d][%2d]", compact[i][0], compact[i][1], compact[i][2]);
        }
        
        printf("\n");
    }
}

void convertCompactToSparse(int compact[72][3], int mat[6][6]) {
    for (int i = 0; i < 6; i++)
        for (int j = 0; j < 6; j++)
            mat[i][j] = 0;
    
    int size = compact[0][2];
    for (int i = 1; i <= size; i++) {
        int row = compact[i][0];
        int col = compact[i][1];
        int val = compact[i][2];
        mat[row][col] = val;
    }
}

int main() {
    printf("Enter matrix size (3-6): ");
    scanf("%d", &rows);
    cols = rows;

    initializeMatrix(matrixA);
    initializeMatrix(matrixB);

    printf("\n--- Input Matrix A ---\n");
    readMatrixSparse(matrixA, 'A');

    printf("\n--- Input Matrix B ---\n");
    readMatrixSparse(matrixB, 'B');

    sizeA = createCompact(matrixA, compactA);
    sizeB = createCompact(matrixB, compactB);

    int choice;
    while (1) {
        printf("\nMenu:\n");
        printf("1. Sum A + B\n");
        printf("2. Transpose A\n");
        printf("3. Transpose B\n");
        printf("4. Transpose Result\n");
        printf("5. Display Matrix A (Side by Side)\n");
        printf("6. Display Matrix B (Side by Side)\n");
        printf("7. Display Result (Side by Side)\n");
        printf("8. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                sizeR = sumCompact();
                printf("Resultant Matrix (A + B):\n");
                display(result, sizeR);
                break;
            case 2:
                transpose(compactA, transposeMat);
                printf("Transpose of A:\n");
                display(transposeMat, compactA[0][2]);
                break;
            case 3:
                transpose(compactB, transposeMat);
                printf("Transpose of B:\n");
                display(transposeMat, compactB[0][2]);
                break;
            case 4:
                if (sizeR > 0) {
                    transpose(result, transposeMat);
                    printf("Transpose of Result:\n");
                    display(transposeMat, result[0][2]);
                } else {
                    printf("No result matrix to transpose. Please perform sum operation first.\n");
                }
                break;
            case 5:
                displaySideBySide(matrixA, compactA, sizeA, 'A');
                break;
            case 6:
                displaySideBySide(matrixB, compactB, sizeB, 'B');
                break;
            case 7:
                if (sizeR > 0) {
                    int resultSparse[6][6];
                    convertCompactToSparse(result, resultSparse);
                    displaySideBySide(resultSparse, result, sizeR, 'R');
                } else {
                    printf("No result matrix to display. Please perform sum operation first.\n");
                }
                break;
            case 8:
                printf("Exiting Program........................\n");
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
