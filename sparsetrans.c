#include <stdio.h>

int rows = 3, cols = 3; // Fixed size matrix
int matrixA[10][10], matrixB[10][10];
int compactA[20][3], compactB[20][3], result[40][3], transposeMat[40][3];
int sizeA, sizeB, sizeR;

void readMatrix(int mat[10][10]) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            scanf("%d", &mat[i][j]);
}

int createCompact(int mat[10][10], int compact[20][3]) {
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

void transpose(int src[40][3], int trans[40][3]) {
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

void display(int mat[40][3], int size) {
    printf("Row Col Val\n");
    for (int i = 0; i <= size; i++)
        printf("%3d %3d %3d\n", mat[i][0], mat[i][1], mat[i][2]);
}

int main() {
    printf("Enter elements of Matrix A (%dx%d):\n", rows, cols);
    readMatrix(matrixA);

    printf("Enter elements of Matrix B (%dx%d):\n", rows, cols);
    readMatrix(matrixB);

    sizeA = createCompact(matrixA, compactA);
    sizeB = createCompact(matrixB, compactB);

    int choice;
    while (1) {
        printf("\n1. Sum A+B\n2. Transpose A\n3. Transpose B\n4. Transpose Result\n5. Exit\nEnter choice: ");
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
                transpose(result, transposeMat);
                printf("Transpose of Result:\n");
                display(transposeMat, result[0][2]);
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }

    return 0;
}
