#include <stdio.h>

int deque[100];  // Maximum possible size
int front = -1, rear = -1, MAX;

int isFull() {
    return ((front == 0 && rear == MAX - 1) || (front == rear + 1));
}

int isEmpty() {
    return (front == -1);
}

void insertFront(int val) {
    if (isFull()) {
        printf("Deque Full!\n");
        return;
    }
    if (front == -1) {  // First element
        front = rear = 0;
    } else if (front == 0) {
        front = MAX - 1;
    } else {
        front--;
    }
    deque[front] = val;
}

void insertRear(int val) {
    if (isFull()) {
        printf("Deque Full!\n");
        return;
    }
    if (rear == -1) {  // First element
        front = rear = 0;
    } else if (rear == MAX - 1) {
        rear = 0;
    } else {
        rear++;
    }
    deque[rear] = val;
}

void deleteFront() {
    if (isEmpty()) {
        printf("Deque Empty!\n");
        return;
    }
    int deletedVal = deque[front];
    printf("Deleted %d from Front\n", deletedVal);

    if (front == rear) {
        front = rear = -1;
    } else if (front == MAX - 1) {
        front = 0;
    } else {
        front++;
    }
}

void deleteRear() {
    if (isEmpty()) {
        printf("Deque Empty!\n");
        return;
    }
    int deletedVal = deque[rear];
    printf("Deleted %d from Rear\n", deletedVal);

    if (front == rear) {
        front = rear = -1;
    } else if (rear == 0) {
        rear = MAX - 1;
    } else {
        rear--;
    }
}

void display() {
    if (isEmpty()) {
        printf("Deque Empty!\n");
        return;
    }
    int i = front;
    printf("Deque: ");
    while (1) {
        printf("%d ", deque[i]);
        if (i == rear) break;
        i = (i + 1) % MAX;
    }
    printf("\n");
}

int main() {
    int choice, val;
    printf("Enter size of deque (max 100): ");
    scanf("%d", &MAX);

    while (1) {
        printf("\n1.Insert Front  2.Insert Rear  3.Delete Front  4.Delete Rear  5.Display  6.Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                insertFront(val);
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &val);
                insertRear(val);
                break;
            case 3:
                deleteFront();
                break;
            case 4:
                deleteRear();
                break;
            case 5:
                display();
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
