#include <stdio.h>

int rows, cols, matrixA[10][10], matrixB[10][10];
int compactA[100][3], compactB[100][3], result[200][3], transposeMat[200][3];
int sizeA, sizeB, sizeR;

void readMatrixSparse(int mat[10][10], char name) {
    int count, row, col, value;
    printf("How many non-zero elements for Matrix %c: ", name);
    scanf("%d", &count);
    printf("Enter %d non-zero elements (row col value):\n", count);
    for (int i = 0; i < count; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d %d %d", &row, &col, &value);
        if (row >= 0 && row < rows && col >= 0 && col < cols)
            mat[row][col] = value;
    }
    // Fill remaining positions with 0 (already initialized)
}

int createCompact(int mat[10][10], int compact[100][3]) {
    int k = 1;
    compact[0][0] = rows; compact[0][1] = cols;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (mat[i][j] != 0) {
                compact[k][0] = i; compact[k][1] = j; compact[k][2] = mat[i][j];
                k++;
            }
    compact[0][2] = k - 1;
    return k - 1;
}

int sumCompact() {
    int i = 1, j = 1, k = 1;
    result[0][0] = rows; result[0][1] = cols;
    while (i <= sizeA && j <= sizeB) {
        if (compactA[i][0] < compactB[j][0] || (compactA[i][0] == compactB[j][0] && compactA[i][1] < compactB[j][1])) {
            result[k][0] = compactA[i][0]; result[k][1] = compactA[i][1]; result[k][2] = compactA[i][2];
            i++;
        } else if (compactB[j][0] < compactA[i][0] || (compactB[j][0] == compactA[i][0] && compactB[j][1] < compactA[i][1])) {
            result[k][0] = compactB[j][0]; result[k][1] = compactB[j][1]; result[k][2] = compactB[j][2];
            j++;
        } else {
            result[k][0] = compactA[i][0]; result[k][1] = compactA[i][1]; result[k][2] = compactA[i][2] + compactB[j][2];
            i++; j++;
        }
        k++;
    }
    while (i <= sizeA) {
        result[k][0] = compactA[i][0]; result[k][1] = compactA[i][1]; result[k][2] = compactA[i][2];
        i++; k++;
    }
    while (j <= sizeB) {
        result[k][0] = compactB[j][0]; result[k][1] = compactB[j][1]; result[k][2] = compactB[j][2];
        j++; k++;
    }
    result[0][2] = k - 1;
    return k - 1;
}

void transpose(int src[200][3], int trans[200][3]) {
    trans[0][0] = src[0][1]; trans[0][1] = src[0][0]; trans[0][2] = src[0][2];
    int k = 1;
    for (int i = 0; i < cols; i++)
        for (int j = 1; j <= src[0][2]; j++)
            if (src[j][1] == i) {
                trans[k][0] = src[j][1]; trans[k][1] = src[j][0]; trans[k][2] = src[j][2];
                k++;
            }
}

void display(int mat[200][3], int size) {
    printf("Row Col Val\n");
    for (int i = 0; i <= size; i++)
        printf("%3d %3d %3d\n", mat[i][0], mat[i][1], mat[i][2]);
}

void displayMatrix(int mat[10][10], int compact[100][3], int size, char name) {
    printf("\nMatrix %c - Sparse Form:\t\tCompact Form:\n", name);
    int maxRows = (rows > size + 1) ? rows : size + 1;
    for (int i = 0; i < maxRows; i++) {
        if (i < rows) {
            for (int j = 0; j < cols; j++) printf("%3d ", mat[i][j]);
        } else {
            for (int j = 0; j < cols; j++) printf("    ");
        }
        printf("\t\t");
        if (i <= size) printf("[%2d][%2d][%2d]", compact[i][0], compact[i][1], compact[i][2]);
        printf("\n");
    }
}

void convertToSparse(int compact[200][3], int mat[10][10]) {
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            mat[i][j] = 0;
    int size = compact[0][2];
    for (int i = 1; i <= size; i++)
        mat[compact[i][0]][compact[i][1]] = compact[i][2];
}

int main() {
    printf("Enter matrix size (1-10): ");
    scanf("%d", &rows);
    cols = rows;
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            matrixA[i][j] = matrixB[i][j] = 0;
    readMatrixSparse(matrixA, 'A');
    readMatrixSparse(matrixB, 'B');
    sizeA = createCompact(matrixA, compactA);
    sizeB = createCompact(matrixB, compactB);
    int choice;
    while (1) {
        printf("\n1.Sum 2.Transpose 3.Show A 4.Show B 5.Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 1) {
            sizeR = sumCompact();
            printf("Sum Result (Sparse Matrix Form):\n");
            // Convert result compact form back to sparse matrix and print it
            int sumSparse[10][10] = {0};
            convertToSparse(result, sumSparse);
            // Display sumSparse matrix (sparse matrix form)
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++)
                    printf("%3d ", sumSparse[i][j]);
                printf("\n");
            }
        }
        else if (choice == 2) {
            if (sizeR > 0) {
                transpose(result, transposeMat);
                printf("Transpose of Result:\n");
                display(transposeMat, result[0][2]);
            } else printf("No result to transpose.\n");
        }
        else if (choice == 3) displayMatrix(matrixA, compactA, sizeA, 'A');
        else if (choice == 4) displayMatrix(matrixB, compactB, sizeB, 'B');
        else if (choice == 5) {
            printf("Exiting...\n");
            return 0;
        }
        else {
            printf("Invalid choice!\n");
        }
    }
}
