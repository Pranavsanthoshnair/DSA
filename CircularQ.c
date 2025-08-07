#include <stdio.h>

int FRONT = 0, REAR = -1, size = 0, capacity;

void enqueue(int CircularQ[], int value) {
    if (size == capacity) {
        printf("Queue Overflow!\n");
        return;
    }
    REAR = (REAR + 1) % capacity;
    CircularQ[REAR] = value;
    size++;
}

void dequeue() {
    if (size == 0) {
        printf("Queue Empty!\n");
        return;
    }
    FRONT = (FRONT + 1) % capacity;
    size--;
    if (size == 0) {
        FRONT = 0;
        REAR = -1;
    }
}

void display(int CircularQ[]) {
    printf("Circular Queue: ");
    if (size == 0) {
        printf("Empty\n");
        return;
    }
    for (int i = 0; i < size; i++) {
        int index = (FRONT + i) % capacity;
        printf("%d\t", CircularQ[index]);
    }
    printf("\n");
}

int main() {
    printf("Enter the size of Circular Queue: ");
    scanf("%d", &capacity);

    int CircularQ[capacity];

    while (1) {
        int choice, value;
        printf("\n1. Enqueue\t2. Dequeue\t3. Exit\nChoice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element: ");
                scanf("%d", &value);
                enqueue(CircularQ, value);
                display(CircularQ);
                break;

            case 2:
                dequeue();
                display(CircularQ);
                break;

            case 3:
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
