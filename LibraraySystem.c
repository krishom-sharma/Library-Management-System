#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TITLE 50
#define MAX_AUTHOR 50

// Define the structure for a book
struct Book {
    int id;
    char title[MAX_TITLE];
    char author[MAX_AUTHOR];
    int isIssued; // 0 for available, 1 for issued
    struct Book* next; // Pointer to the next book
};

int main() {
    struct Book* head = NULL; // Head pointer for the linked list
    struct Book* temp, *current;
    int choice, bookId, found;
    char buffer;

    do {
        printf("\n=== Library Management System ===\n");
        printf("1. Add Book\n");
        printf("2. Display Books\n");
        printf("3. Issue Book\n");
        printf("4. Return Book\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) {
            // Add a new book
            temp = (struct Book*)malloc(sizeof(struct Book));
            if (temp == NULL) {
                printf("Memory allocation failed!\n");
                continue;
            }

            printf("Enter Book ID: ");
            scanf("%d", &temp->id);

            printf("Enter Title: ");
            while ((buffer = getchar()) != '\n' && buffer != EOF); // Clear input buffer
            fgets(temp->title, MAX_TITLE, stdin);
            temp->title[strcspn(temp->title, "\n")] = '\0'; // Remove newline character

            printf("Enter Author: ");
            fgets(temp->author, MAX_AUTHOR, stdin);
            temp->author[strcspn(temp->author, "\n")] = '\0'; // Remove newline character

            temp->isIssued = 0; // Mark as available
            temp->next = head;  // Insert at the beginning of the list
            head = temp;

            printf("Book added successfully!\n");

        } else if (choice == 2) {
            // Display all books
            current = head;
            if (current == NULL) {
                printf("No books in the library.\n");
                continue;
            }

            printf("\nBooks in Library:\n");
            while (current != NULL) {
                printf("ID: %d\nTitle: %s\nAuthor: %s\nStatus: %s\n\n",
                       current->id,
                       current->title,
                       current->author,
                       current->isIssued ? "Issued" : "Available");
                current = current->next;
            }

        } else if (choice == 3) {
            // Issue a book by ID
            if (head == NULL) {
                printf("No books in the library.\n");
                continue;
            }

            printf("Enter Book ID to issue: ");
            scanf("%d", &bookId);

            found = 0;
            current = head;
            while (current != NULL) {
                if (current->id == bookId) {
                    found = 1;
                    if (current->isIssued) {
                        printf("Book is already issued.\n");
                    } else {
                        current->isIssued = 1;
                        printf("Book issued successfully!\n");
                    }
                    break;
                }
                current = current->next;
            }

            if (!found) {
                printf("Book with ID %d not found.\n", bookId);
            }

        } else if (choice == 4) {
            // Return a book by ID
            if (head == NULL) {
                printf("No books in the library.\n");
                continue;
            }

            printf("Enter Book ID to return: ");
            scanf("%d", &bookId);

            found = 0;
            current = head;
            while (current != NULL) {
                if (current->id == bookId) {
                    found = 1;
                    if (!current->isIssued) {
                        printf("Book is not issued.\n");
                    } else {
                        current->isIssued = 0;
                        printf("Book returned successfully!\n");
                    }
                    break;
                }
                current = current->next;
            }

            if (!found) {
                printf("Book with ID %d not found.\n", bookId);
            }

        } else if (choice != 5) {
            // Invalid choice handling
            printf("Invalid choice! Please try again.\n");
        }

    } while (choice != 5);

    // Free allocated memory before exiting
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    printf("Exiting Library Management System. Goodbye!\n");

    return 0;
}
