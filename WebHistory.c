#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    char url[100];
    struct Node *prev, *next;
};

struct Node *current = NULL;

void visit(char *url) {
    struct Node *newPage = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newPage->url, url);
    newPage->prev = current;
    newPage->next = NULL;

    if (current) {
        // Clear forward history before linking
        struct Node *temp = current->next;
        while (temp) { 
            struct Node *del = temp;
            temp = temp->next;
            free(del);
        }
        current->next = newPage;
    }
    current = newPage;
    printf("Visited: %s\n", url);
}

void back() {
    if (current && current->prev) {
        current = current->prev;
        printf("Back to: %s\n", current->url);
    } else printf("No previous page.\n");
}

void forward() {
    if (current && current->next) {
        current = current->next;
        printf("Forward to: %s\n", current->url);
    } else printf("Nothing to move forward.\n");
}

void currentPage() {
    if (current) printf("Current page: %s\n", current->url);
    else printf("No page open.\n");
}

int main() {
    int choice;
    char url[100];

    while (1) {
        printf("\n1. Visit new page\n2. Back\n3. Forward\n4. Current Page\n5. Exit\nEnter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: printf("Enter URL: "); scanf("%s", url); visit(url); break;
            case 2: back(); break;
            case 3: forward(); break;
            case 4: currentPage(); break;
            case 5: exit(0);
            default: printf("Invalid choice\n");
        }
    }
    return 0;
}
