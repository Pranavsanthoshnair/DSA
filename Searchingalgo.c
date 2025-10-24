#include <stdio.h>

int binarySearch(int arr[], int n, int target) {
    int left = 0, right = n - 1;
    int steps = 0;

    while (left <= right) {
        steps++;
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            printf("Element found at index %d\n", mid);
            printf("Number of steps: %d\n", steps);
            return mid;
        }
        else if (arr[mid] < target)
            left = mid + 1;
        else
            right = mid - 1;
    }

    printf("Element not found.\n");
    printf("Number of steps: %d\n", steps);
    return -1;
}

int main() {
    int n, target;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d sorted elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter element to search: ");
    scanf("%d", &target);

    binarySearch(arr, n, target);

    printf("\nTime Complexity:\n");
    printf("Best Case: O(1)\n");
    printf("Worst Case: O(log n)\n");

    printf("\nSpace Complexity:\n");
    printf("O(1)\n");

    return 0;
}
