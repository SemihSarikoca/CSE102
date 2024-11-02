#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Book {
    char* isbn;
    char* title;
    char* author;
    int publicationYear;
    int reserved;
    struct Book* next;
} Book;

typedef struct Student {
    char name[100];
    int ID;
    char borrowedBooks[10][100];
    struct Student* next;
} Student;

void addBook(Book** root, char* isbn, char* title, char* author, int publicationYear, int reserved, int method);
void deleteBook(Book** root, char* isbn);
void reverseBookList(Book** root);
void updateBook (Book** root, char* isbn, char* feature, char* value);
void filterAndSortBooks(Book* root, int filterChoice, char* filter, int sortChoice);
void searchBooks(Book* root, int searchChoice, char* searchValue);
void borrowBook(Book* root, Student* student, char* isbn);
void returnBook(Book* root, Student* student, char* isbn);
void printBorrowedBooks(Student* student);

void deallocateStudents(Student* student);
void deallocate(Book** root);
void serialize(Book* root, const char* filename);
void deserialize(Book** root, const char* filename);
void saveStudentToFile(Student* student, const char* filename);
void loadStudentsFromFile(Student** head, const char* filename);

Student* findStudentByID(Student* head, int ID);
Book* sortBooks(Book* root, int sortChoice);
int compareBooks(Book* book1, Book* book2, int sortChoice);
void printLinkedList(Book* root);

int main() {
    Book* root = NULL; //book linkedlist
    deserialize(&root, "books.txt");
    Student* head = NULL; //stundent linkedlist
    loadStudentsFromFile(&head, "students.txt");
    Student* user = NULL; //user

    //new variables that needed for functions
    char isbn[100];
    char title[100];
    char author[100];
    int publicationYear;

    int method, filterChoice, sortChoice, searchChoice, ID;
    char feature[20];
    char newValue[100];
    char filter[100];
    char searchValue[100];

    char choice;
    do { // menu and genaral function calling loop
        printf("\n------- Menu -------\n");
        printf("0. Display borrowed books\n");
        printf("1. Add a book\n");
        printf("2. Delete a book\n");
        printf("3. Reverse book list\n");
        printf("4. Update a book\n");
        printf("5. Filter and sort books\n");
        printf("6. Search for books\n");
        printf("7. Borrow a book\n");
        printf("8. Return a book\n");
        printf("9. Quit\n");
        printf("--------------------\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '0':
                printf("STUDENT ID: ");
                scanf("%d", &ID);
                user = findStudentByID(head, ID);
                printBorrowedBooks(user);
                break;
            case '1':
                printf("ISBN: ");
                scanf("%s", isbn);
                printf("TITLE: ");
                scanf(" %[^\n]", title);
                printf("AUTHOR: ");
                scanf(" %[^\n]", author);
                printf("PUBLICATION YEAR: ");
                scanf("%d", &publicationYear);
                printf("ADDING METHOD FIFO(0)/LIFO(1): ");
                scanf("%d", &method);
                addBook(&root, isbn, title, author, publicationYear, 0, method);
                break;
            case '2':
                printf("ISBN: ");
                scanf("%s", isbn);
                deleteBook(&root, isbn);
                break;
            case '3':
                reverseBookList(&root);
                printLinkedList(root);
                break;
            case '4':
                printf("ISBN: ");
                scanf("%s", isbn);
                printf("FEATURE: ");
                scanf("%s", feature);
                printf("NEW VALUE: ");
                scanf("%s", newValue);
                updateBook(&root, isbn, feature, newValue);
                break;
            case '5':
                printf("FILTER CHOICE AUTHOR(0)/YEAR(1): ");
                scanf("%d", &filterChoice);
                printf("FILTER: ");
                scanf(" %[^\n]", filter);
                printf("SORT CHOICE TITLE(0)/AUTHOR(1)/YEAR(2): ");
                scanf("%d", &sortChoice);
                filterAndSortBooks(root, filterChoice, filter, sortChoice);
                break;
            case '6':
                printf("SEARCH CHOICE ISBN(0)/AUTHOR(1)/TITLE(2): ");
                scanf("%d", &searchChoice);
                printf("SEARCH VALUE: ");
                scanf(" %[^\n]", searchValue);
                searchBooks(root, searchChoice, searchValue);
                break;
            case '7':
                printf("STUDENT ID: ");
                scanf("%d", &ID);
                printf("ISBN: ");
                scanf("%s", isbn);
                user = findStudentByID(head, ID);
                borrowBook(root, user, isbn);
                break;
            case '8':
                printf("STUDENT ID: ");
                scanf("%d", &ID);
                printf("ISBN: ");
                scanf("%s", isbn);
                user = findStudentByID(head, ID);
                returnBook(root, user, isbn);
                break;
            case '9':
                printf("Exiting the program\n");
                break;
            default:
                printf("Invalid choice\n");
        }
    } while (choice != '9');
    // save data to file
    saveStudentToFile(head, "students.txt");
    serialize(root, "books.txt");
    // deallocate books and students
    deallocate(&root);
    deallocateStudents(head);
    return 0;
}

void printLinkedList(Book* root) { // prints book linked list
    for (Book* curr = root; curr != NULL; curr = curr->next) {
        printf("ISBN: %s TITLE: %s AUTHOR: %s PUBLICATION YEAR: %d\n", curr->isbn, curr->title, curr->author, curr->publicationYear);
    }
}
void deallocate(Book** root) { // deallocate the book linked list
    Book* curr = *root;
    while (curr != NULL) {
        Book* prev = curr;
        curr = curr->next;
        free(prev->isbn);
        free(prev->title);
        free(prev->author);
        free(prev);
    }
    *root = NULL;
}

void addBook(Book** root, char* isbn, char* title, char* author, int publicationYear, int reserved, int method) {
    Book* newBook = malloc(sizeof(Book));
    if (newBook ==  NULL) {
        printf("Malloc error!\n");
        exit(1);
    }
    if (method == 0 || method == 1) { // add new values
        newBook->isbn = strdup(isbn);
        newBook->title = strdup(title);
        newBook->author = strdup(author);
        newBook->publicationYear = publicationYear;
        newBook->reserved = reserved;
        newBook->next = NULL;
    }
    if (*root == NULL) {
        *root = newBook;

    } else {
        if (method == 0) { // FIFO
            Book* curr = *root;
            while (curr->next != NULL) {
                curr = curr->next;
            }
            curr->next = newBook;
        } else if (method == 1) { // LIFO
            newBook->next = *root;
            *root = newBook;
        } else {
            printf("Invalid method!\n");
            return;
        }
    }
}

void deleteBook(Book** root, char* isbn) {
    if (*root == NULL) {
        return;
    }
    if (strcmp((*root)->isbn, isbn) == 0) { // delete the root if root is wanted to deleted. and make new root
        Book* deletedBook = *root;
        *root = (*root)->next;
        free(deletedBook->isbn);
        free(deletedBook->title);
        free(deletedBook->author);
        free(deletedBook);
        return;
    }
    for (Book* curr = *root; curr->next != NULL; curr = curr->next) { // delete the wanted book
        if (strcmp(curr->next->isbn, isbn) == 0) {
            Book* deletedBook = curr->next;
            curr->next = curr->next->next;
            free(deletedBook->isbn);
            free(deletedBook->title);
            free(deletedBook->author);
            free(deletedBook);
            return;
        }
    }
}

void reverseBookList(Book** root) {
    Book* prev = NULL;
    Book* curr = *root;
    
    while (curr != NULL) { // reverser logic
        Book* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }

    *root = prev;
}

void updateBook (Book** root, char* isbn, char* feature, char* value) {
    Book* curr = *root;
    while (curr != NULL && strcmp(curr->isbn, isbn) != 0)  {
        curr = curr->next;
    }
    if (curr == NULL) {
        exit(1);
    }
    // update the feaure 
    if (strcmp(feature, "title") == 0) {
        free(curr->title);
        curr->title = strdup(value);
    } else if (strcmp(feature, "author") == 0) {
        free(curr->author);
        curr->author = strdup(value);
    } else if (strcmp(feature, "publicationYear") == 0) {
        curr->publicationYear = atoi(value);
    } else {
        printf("Invalid feature!\n");
        return;
    }

}

void serialize(Book* root, const char* filename) { // save books to the file
    FILE* file= fopen(filename, "w");
    if (file == NULL) {
        printf("File error!\n");
        exit(1);
    }

    for (Book* curr = root; curr != NULL; curr = curr->next) {
        fprintf(file, "%s,%s,%s,%d,%d\n", curr->isbn, curr->title, curr->author, curr->publicationYear, curr->reserved);
    }
    fclose(file);
}
void deserialize(Book** root, const char* filename) { // loads books from file
    FILE* file= fopen(filename, "r");
    if (file == NULL) {
        printf("File error!\n");
        exit(1);
    }
    char isbn[100];
    char title[100];
    char author[100];
    int publicationYear;
    int reserved;
    while (fscanf(file, "%[^,],%[^,],%[^,],%d,%d\n", isbn, title, author, &publicationYear, &reserved) == 5) {
        addBook(root, isbn, title, author, publicationYear, reserved, 0);
    }
    fclose(file);
}

void filterAndSortBooks(Book* root, int filterChoice, char* filter, int sortChoice) {
    Book* filteredBooks = NULL;
    Book* curr = root;

    while (curr != NULL) {
        if (filterChoice == 0) {
            // Filter by author
            if (strcmp(curr->author, filter) == 0) {
                // Book matches the filter criteria, add it to the filtered list
                addBook(&filteredBooks, curr->isbn, curr->title, curr->author, curr->publicationYear, curr->reserved, 0);
            }
        } else if (filterChoice == 1) {
            int filterYear = atoi(filter);
            if (curr->publicationYear == filterYear) {
                // Book matches the filter criteria, add it to the filtered list
                addBook(&filteredBooks, curr->isbn, curr->title, curr->author, curr->publicationYear, curr->reserved, 0);
            }
        } else {
            printf("Invalid filter choice.\n");
            return;
        }
        curr = curr->next;
    }
    if (filteredBooks == NULL) {
        return;
    }
    filteredBooks = sortBooks(filteredBooks, sortChoice); // sorting
    printLinkedList(filteredBooks); // printing
    deallocate(&filteredBooks); //deallocate
}
Book* sortBooks(Book* root, int sortChoice) {
    if (root == NULL || root->next == NULL) {
        return root;
    }
    Book* sortedList = NULL;
    Book* curr = root;
    while (curr != NULL) {
        Book* nextBook = curr->next;
        curr->next = NULL; // disconnect the current node from the list
        if (sortedList == NULL || compareBooks(curr, sortedList, sortChoice) < 0) {
            // insert at the beginning of the sorted list
            curr->next = sortedList;
            sortedList = curr;
        } else {
            // find the appropriate position to insert the current node
            Book* temp = sortedList;
            while (temp->next != NULL && compareBooks(curr, temp->next, sortChoice) >= 0) {
                temp = temp->next;
            }
            // insert after temp
            curr->next = temp->next;
            temp->next = curr;
        }
        curr = nextBook;
    }
    return sortedList;
}
int compareBooks(Book* book1, Book* book2, int sortChoice) {
    // compare books based on the sortChoice criteria
    if (sortChoice == 0) {
        // sort by title
        return strcmp(book1->title, book2->title);
    } else if (sortChoice == 1) {
        // sort by author
        return strcmp(book1->author, book2->author);
    } else if (sortChoice == 2) {
        // sort by publication year
        return book1->publicationYear - book2->publicationYear;
    } else {
        return 0; // invalid sort choice
    }
}
void searchBooks(Book* root, int searchChoice, char* searchValue) {
    Book* curr = root;
    int found = 0;
    while (curr != NULL) {
        if (searchChoice == 0) {
            // search by ISBN number
            if (strcmp(curr->isbn, searchValue) == 0) {
                printf("ISBN: %s TITLE: %s AUTHOR: %s PUBLICATION YEAR: %d\n", curr->isbn, curr->title, curr->author, curr->publicationYear);
                found = 1;
            }
        } else if (searchChoice == 1) {
            // search by author
            if (strcmp(curr->author, searchValue) == 0) {
                printf("ISBN: %s TITLE: %s AUTHOR: %s PUBLICATION YEAR: %d\n", curr->isbn, curr->title, curr->author, curr->publicationYear);
                found = 1;
            }
        } else if (searchChoice == 2) {
            // search by title
            if (strcmp(curr->title, searchValue) == 0) {
                printf("ISBN: %s TITLE: %s AUTHOR: %s PUBLICATION YEAR: %d\n", curr->isbn, curr->title, curr->author, curr->publicationYear);
                found = 1;
            }
        } else {
            printf("Invalid search choice.\n");
            return;
        }
        curr = curr->next;
    }
    if (!found) {
        printf("Book not found.\n");
    }
}

void borrowBook(Book* root, Student* student, char* isbn) {
    if (student == NULL) {
        printf("There are no student with that ID.\n");
        return;
    }
    Book* curr = root;
    while (curr != NULL) {
        if (strcmp(curr->isbn, isbn) == 0) { // isbn match
            if (curr->reserved == 0) { // borrow
                int i = 0;
                while (i < 10 && student->borrowedBooks[i][0] != '\0') { // go to the end of the borrowedBooks list
                    i++;
                }
                if (i < 10) {
                    curr->reserved = 1;
                    strcpy(student->borrowedBooks[i], isbn);
                    printf("Book with ISBN %s has been successfully borrowed.\n", isbn);
                } else {
                    printf("Student has already borrowed the maximum number of books.\n"); // has borrow limit
                }
            } else { // already borrowed
                printf("Book with ISBN %s is already reserved.\n", isbn);
            }
            return;
        }
        curr = curr->next;
    }
    printf("Book with ISBN %s does not exist.\n", isbn); //invalid isbn
}
void returnBook(Book* root, Student* student, char* isbn) {
    if (student == NULL) {
        printf("There are no student with that ID.\n");
        return;
    }

    Book* currBook = root;
    while (currBook != NULL) {
        if (strcmp(currBook->isbn, isbn) == 0) { // isbn match
            if (currBook->reserved == 1) { // return
                int i = 0;
                while (i < 10 && strcmp(student->borrowedBooks[i], isbn) != 0) {
                    i++;
                }
                if (i < 10) {
                    currBook->reserved = 0;
                    // remove the returned book and shift the remaining books
                    for (int j = i; j < 9; j++) {
                        strcpy(student->borrowedBooks[j], student->borrowedBooks[j + 1]);
                    }
                    student->borrowedBooks[9][0] = '\0';
                    printf("Book with ISBN %s has been successfully returned.\n", isbn); 
                } else {
                    printf("Book with ISBN %s is not borrowed by the student.\n", isbn);
                }
            } else { // not borrowed 
                printf("Book with ISBN %s is already available.\n", isbn);
            }
            return;
        }
        currBook = currBook->next;
    }
    printf("Book with ISBN %s does not exist.\n", isbn); // no book with this isbn in the linked list
}

void loadStudentsFromFile(Student** head, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }


    deallocateStudents(*head);
    *head = NULL;

    char line[400];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0';

        Student* newStudent = malloc(sizeof(Student));
        if (newStudent == NULL) {
            printf("Memory allocation failed for new student.\n");
            fclose(file);
            return;
        }

        int parsedFields = sscanf(line, "%d,%[^,],", &(newStudent->ID), newStudent->name);
        if (parsedFields != 2) {
            printf("Error parsing line: %s\n", line);
            free(newStudent);
            continue;  // Skip to next line
        }

        for (int i = 0; i < 10; i++) {
            newStudent->borrowedBooks[i][0] = '\0';
        }

        char* token = strtok(line, ",");
        int i = 0;
        while (token != NULL) {
            token = strtok(NULL, ",");
            if (token != NULL && i < 10) {
                strcpy(newStudent->borrowedBooks[i], token);
                i++;
            }
        }

        newStudent->next = NULL;
        if (*head == NULL) {
            *head = newStudent;
        } else {
            Student* current = *head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = newStudent;
        }
    }
    fclose(file);
}
void saveStudentToFile(Student* student, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file: %s\n", filename);
        return;
    }

    Student* curr = student;
    while (curr != NULL) {
        fprintf(file, "%d,%s", curr->ID, curr->name);
        int i = 1;
        while (i < 10 && curr->borrowedBooks[i][0] != '\0') { // save linked list to file 
            fprintf(file, ",%s", curr->borrowedBooks[i]);
            i++;
        }
        fprintf(file, "\n");
        curr = curr->next;
    }

    fclose(file);
}
void printBorrowedBooks(Student* student) {
    if (student == NULL) {
        printf("There are no student with that ID.\n");
        return;
    }
    printf("Borrowed Books by Student %s:\n", student->name);
    int i = 1;
    while (i < 10 && student->borrowedBooks[i][0] != '\0') { // print the borrowed books by user
        printf("ISBN: %s\n", student->borrowedBooks[i]);
        i++;
    }
    if (i == 1) { // tell user if not borrowed any
        printf("ID: %d STUDENT: %s do not borrowed any book.\n", student->ID, student->name);
    }
}
void deallocateStudents(Student* student) {
    while (student != NULL) { // deallocate the student linked list
        Student* temp = student;
        student = student->next;
        free(temp);
    }
}
Student* findStudentByID(Student* head, int ID) { // fint student by using id from user
    Student* curr = head;
    while (curr != NULL) {
        if (curr->ID == ID) {
            return curr;  // found the student with the ID
        }
        curr = curr->next;
    }
    return NULL;  // student with the ID not found
}
