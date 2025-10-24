#include <stdio.h>

int steps;

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

void bubbleSort(int arr[], int n) {
    steps = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            steps++;
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
    printf("\nSorted array using Bubble Sort: ");
    printArray(arr, n);
}

void insertionSort(int arr[], int n) {
    steps = 0;
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
            steps++;
        }
        arr[j + 1] = key;
        steps++;
    }
    printf("\nSorted array using Insertion Sort: ");
    printArray(arr, n);
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        steps++;
        if (arr[j] < pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1, n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        steps++;
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void copyArray(int src[], int dest[], int n) {
    for (int i = 0; i < n; i++) dest[i] = src[i];
}

int main() {
    int n;
    printf("Enter number of elements: ");
    scanf("%d", &n);

    int arr[n], temp[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) scanf("%d", &arr[i]);

    int bubbleSteps, insertionSteps, quickSteps, mergeSteps;

    copyArray(arr, temp, n);
    bubbleSort(temp, n);
    bubbleSteps = steps;

    copyArray(arr, temp, n);
    insertionSort(temp, n);
    insertionSteps = steps;

    copyArray(arr, temp, n);
    steps = 0;
    quickSort(temp, 0, n - 1);
    quickSteps = steps;
    printf("\nSorted array using Quick Sort: ");
    printArray(temp, n);

    copyArray(arr, temp, n);
    steps = 0;
    mergeSort(temp, 0, n - 1);
    mergeSteps = steps;
    printf("\nSorted array using Merge Sort: ");
    printArray(temp, n);

    printf("\nComparison of Sorting Algorithms:\n");
    printf("Bubble Sort Steps: %d\n", bubbleSteps);
    printf("Insertion Sort Steps: %d\n", insertionSteps);
    printf("Quick Sort Steps: %d\n", quickSteps);
    printf("Merge Sort Steps: %d\n", mergeSteps);

    return 0;
}
