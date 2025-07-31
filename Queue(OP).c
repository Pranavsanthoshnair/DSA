#include <stdio.h>
#define MAX 5

int queue[MAX] = {11, 22, 33};
int front = 0;   
int rear = 2;    

void display() {
    if (front == -1) {
        printf("");
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
    display();

    enqueue(44);
    enqueue(55);
    enqueue(66);  

    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();
    dequeue();   

    enqueue(77);

    return 0;
}
