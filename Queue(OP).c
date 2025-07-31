#include <stdio.h>
#define MAX 5

int queue[MAX];
int front = -1;
int rear = -1;

void display() {
    if (front == -1) {
        printf("Queue is empty\n");
    } else {
        printf("Queue: ");
        for (int i = front; i <= rear; i++) {
            printf("%d ", queue[i]);
        }
        printf("\n");
    }
}

void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue is full (Overflow)\n");
    } else {
        if (front == -1) {
            front = 0;
        }
        rear++;
        queue[rear] = value;
        printf("%d inserted into the queue\n", value);
    }
    display();
}

void dequeue() {
    if (front == -1) {
        printf("Queue is empty (Underflow)\n");
    } else {
        printf("Deleted: %d\n", queue[front]);
        if (front == rear) {
            front = -1;
            rear = -1;
        } else {
            front++;
        }
    }
    display();
}

int main() {
    int choice, value;

    while (1) {
        printf("\nChoose an operation:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue: ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                printf("Exiting program.\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}

