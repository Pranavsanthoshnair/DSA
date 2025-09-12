#include <stdio.h>
int deque[100];
int front = -1, rear = -1, MAX;

int isFull() {
    return (front == (rear + 1) % MAX);
}
int isEmpty() {
    return (front == -1);
}
void insertFront(int val) {
    if (isFull()) {
        printf("Deque Full!\n");
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } else if (front == 0) {
        front = MAX - 1;
    } else {
        front--;
    }
    deque[front] = val;
    printf("Inserted %d at Front\n", val);
}
void insertRear(int val) {
    if (isFull()) {
        printf("Deque Full!\n");
        return;
    }
    if (isEmpty()) {
        front = rear = 0;
    } else if (rear == MAX - 1) {
        rear = 0;
    } else {
        rear++;
    }
    deque[rear] = val;
    printf("Inserted %d at Rear\n", val);
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
void printDeque() {
    if (isEmpty()) {
        printf("Deque is Empty.\n");
        return;
    }
    int i = front;
    printf("Current Deque: ");
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
    if (MAX <= 0 || MAX > 100) {
        printf("Invalid deque size. Must be between 1 and 100.\n");
        return 1;
    }
    while (1) {
        printf("\n1.Insert Front  2.Insert Rear  3.Delete Front  4.Delete Rear  5.Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &val);
                insertFront(val);
                printDeque();
                break;
            case 2:
                printf("Enter value: ");
                scanf("%d", &val);
                insertRear(val);
                printDeque();
                break;
            case 3:
                deleteFront();
                printDeque();
                break;
            case 4:
                deleteRear();
                printDeque();
                break;
            case 5:
                return 0;
            default:
                printf("Invalid choice!\n");
        }
    }
}
