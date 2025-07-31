#include <stdio.h>
#define MAX 5

int queue[MAX] = {11, 22, 33};
int front = 0;
int rear = 2;

void enqueue(int value) {
    if (rear == MAX - 1) {
        printf("Queue is full (Overflow)\n");
    } else if (rear == -1) {
        front = 0;
        rear = 0;
        queue[rear] = value;
        printf("%d inserted into the queue\n", value);
    } else {
        rear = rear + 1;
        queue[rear] = value;
        printf("%d inserted into the queue\n", value);
    }
}

void dequeue() {
    if (front == -1) {
        printf("Queue is empty (Underflow)\n");
    } else if (front == rear) {
        printf("Deleted: %d\n", queue[front]);
        front = -1;
        rear = -1;
    } else {
        printf("Deleted: %d\n", queue[front]);
        front++;
    }
}

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

int main() {
    front = -1; rear = -1;
    
    enqueue(11);
    enqueue(22);
    enqueue(33);
    display();

    dequeue();
    display();

    enqueue(44);
    enqueue(55);
    enqueue(66);
    display();

    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();

    enqueue(77);
    display();

    return 0;
}

        queue[rear] = value;
        printf("%d inserted into the queue\n", value);
    } else {
        rear = rear + 1;
        queue[rear] = value;
        printf("%d inserted into the queue\n", value);
    }
}

void dequeue() {
    if (front == -1) {
        printf("Queue is empty (Underflow)\n");
    } else if (front == rear) {
        printf("Deleted: %d\n", queue[front]);
        front = -1;
        rear = -1;
    } else {
        printf("Deleted: %d\n", queue[front]);
        front++;
    }
}

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

int main() {
    front = -1; rear = -1;
    
    enqueue(11);
    enqueue(22);
    enqueue(33);
    display();

    dequeue();
    display();

    enqueue(44);
    enqueue(55);
    enqueue(66);
    display();

    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();

    enqueue(77);
    display();

    return 0;
}
