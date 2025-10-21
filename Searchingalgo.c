#include <stdio.h>

int linearSearch(int arr[], int n, int target, int *steps) {
    for (int i = 0; i < n; i++) {
        (*steps)++;
        if (arr[i] == target)
            return i;
    }
    return -1;
}

int binarySearch(int arr[], int n, int target, int *steps) {
    int left = 0, right = n - 1;
    while (left <= right) {
        (*steps)++;
        int mid = left + (right - left) / 2;
        if (arr[mid] == target)
            return mid;
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return -1;
}

int main() {
    int n, target, choice;
    
    printf("Enter number of elements: ");
    scanf("%d", &n);
    
    int arr[n];
    printf("Enter %d sorted elements:\n", n);
    for(int i = 0; i < n; i++)
        scanf("%d", &arr[i]);
    
    printf("Enter element to search: ");
    scanf("%d", &target);

    printf("\nChoose Search Method:\n");
    printf("1. Linear Search\n");
    printf("2. Binary Search\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    int index = -1, steps = 0;

    if(choice == 1) {
        index = linearSearch(arr, n, target, &steps);
        if(index != -1)
            printf("Element found at index %d using Linear Search.\n", index);
        else
            printf("Element not found using Linear Search.\n");
        printf("Number of steps: %d\n", steps);
    }
    else if(choice == 2) {
        index = binarySearch(arr, n, target, &steps);
        if(index != -1)
            printf("Element found at index %d using Binary Search.\n", index);
        else
            printf("Element not found using Binary Search.\n");
        printf("Number of steps: %d\n", steps);
    }
    else {
        printf("Invalid choice.\n");
    }

    return 0;
}
