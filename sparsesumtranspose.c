#include <stdio.h>
typedef struct { int row, col, val; } Triplet;
int rows, cols, A[10][10] = {0}, B[10][10] = {0};
Triplet cA[100], cB[100], result[200], transposeR[200];
int sizeA, sizeB, sizeR;

void inputMatrix(int M[10][10], char name) {
    int n, r, c, v;
    printf("How many non-zero elements for Matrix %c: ", name);
    scanf("%d", &n);
    printf("Enter %d non-zero elements (row col value):\n", n);
    for (int i = 0; i < n; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d %d %d", &r, &c, &v);
        if (r >= 0 && r < rows && c >= 0 && c < cols) M[r][c] = v;
    }
}

int toCompact(int M[10][10], Triplet C[100]) {
    int k = 1;
    C[0] = (Triplet){rows, cols, 0};
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (M[i][j]) C[k++] = (Triplet){i, j, M[i][j]};
    return C[0].val = k - 1;
}

int addCompact() {
    int i = 1, j = 1, k = 1;
    result[0] = (Triplet){rows, cols, 0};
    while (i <= sizeA && j <= sizeB) {
        if (cA[i].row < cB[j].row || (cA[i].row == cB[j].row && cA[i].col < cB[j].col)) result[k++] = cA[i++];
        else if (cB[j].row < cA[i].row || (cB[j].row == cA[i].row && cB[j].col < cA[i].col)) result[k++] = cB[j++];
        else result[k++] = (Triplet){cA[i].row, cA[i].col, cA[i++].val + cB[j++].val};
    }
    while (i <= sizeA) result[k++] = cA[i++];
    while (j <= sizeB) result[k++] = cB[j++];
    return result[0].val = k - 1;
}

void toSparse(Triplet C[200], int M[10][10]) {
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++) M[i][j] = 0;
    for (int i = 1; i <= C[0].val; i++) M[C[i].row][C[i].col] = C[i].val;
}

void transpose(Triplet S[200], Triplet T[200]) {
    T[0] = (Triplet){S[0].col, S[0].row, S[0].val};
    int k = 1;
    for (int i = 0; i < cols; i++)
        for (int j = 1; j <= S[0].val; j++)
            if (S[j].col == i) T[k++] = (Triplet){S[j].col, S[j].row, S[j].val};
}

void showCompact(Triplet C[200], int size) {
    printf("Row Col Val\n");
    for (int i = 0; i <= size; i++) printf("%3d %3d %3d\n", C[i].row, C[i].col, C[i].val);
}

void showMatrix(int M[10][10], Triplet C[100], int size, char name) {
    printf("\nMatrix %c - Sparse Form:\t\tCompact Form:\n", name);
    for (int i = 0; i < (rows > size + 1 ? rows : size + 1); i++) {
        if (i < rows) for (int j = 0; j < cols; j++) printf("%3d ", M[i][j]);
        else for (int j = 0; j < cols; j++) printf("    ");
        printf("\t\t");
        if (i <= size) printf("[%2d][%2d][%2d]", C[i].row, C[i].col, C[i].val);
        printf("\n");
    }
}

int main() {
    printf("Enter matrix size (1-10): "); scanf("%d", &rows); cols = rows;
    inputMatrix(A, 'A'); inputMatrix(B, 'B');
    sizeA = toCompact(A, cA); sizeB = toCompact(B, cB);
    int choice;
    while (1) {
        printf("\n1.Sum 2.Transpose 3.Show A 4.Show B 5.Exit\nChoice: "); scanf("%d", &choice);
        if (choice == 1) {
            sizeR = addCompact(); int sum[10][10]; toSparse(result, sum);
            printf("Sum Result (Sparse Matrix Form):\n");
            for (int i = 0; i < rows; i++) {
                for (int j = 0; j < cols; j++) printf("%3d ", sum[i][j]);
                printf("\n");
            }
        } else if (choice == 2) {
            if (result[0].val > 0) { transpose(result, transposeR); printf("Transpose of Result:\n"); showCompact(transposeR, transposeR[0].val); }
            else printf("No result to transpose.\n");
        } else if (choice == 3) showMatrix(A, cA, sizeA, 'A');
        else if (choice == 4) showMatrix(B, cB, sizeB, 'B');
        else if (choice == 5) { printf("Exiting...\n"); return 0; }
        else printf("Invalid choice!\n");
    }
}
