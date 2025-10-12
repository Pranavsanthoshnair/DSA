#include <stdio.h>

#define SIZE 10

int main() {
    int hashTable[SIZE];
    int i, n, value;

    for (i = 0; i < SIZE; i++) {
        hashTable[i] = -1;
    }

    printf("Enter the number of elements to insert: ");
    scanf("%d", &n);

    printf("Enter %d integers:\n", n);
    for (i = 0; i < n; i++) {
        scanf("%d", &value);
        int index = value % SIZE;
        hashTable[index] = value;
    }

    printf("\nHash Table (index : value)\n");
    for (i = 0; i < SIZE; i++) {
        if (hashTable[i] != -1)
            printf("%d : %d\n", i, hashTable[i]);
        else
            printf("%d : ---\n", i);
    }

    return 0;
}
