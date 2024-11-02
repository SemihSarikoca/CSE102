#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ExamPaper {
    char studentName[100];
    char studentNumber[20];
    int score;
    struct ExamPaper* next;
} ExamPaper;

ExamPaper* createExamPaper(char* studentName, char* studentNumber, int score) {
    ExamPaper* newPaper = (ExamPaper*)malloc(sizeof(ExamPaper));
    strcpy(newPaper->studentName, studentName);
    strcpy(newPaper->studentNumber, studentNumber);
    newPaper->score = score;
    newPaper->next = NULL;
    return newPaper;
}
ExamPaper* push(ExamPaper* stack, char* studentName, char* studentNumber, int score) {
    ExamPaper* newPaper = createExamPaper(studentName, studentNumber, score);
    newPaper->next = stack;
    stack = newPaper;
    return stack;
}
ExamPaper* pop(ExamPaper* stack) {
    if (stack == NULL) {
        printf("Stack is empty.\n");
        return NULL;
    }
    ExamPaper* temp = stack;
    stack = stack->next;
    free(temp);
    return stack;
}
int isEmpty(ExamPaper* stack) {
    if (stack == NULL)
        return 1;
    else
        return 0;
}
void display(ExamPaper* stack) {
    if (stack == NULL) {
        printf("Stack is empty.\n");
        return;
    }
    ExamPaper* temp = stack;
    printf("Exam Papers in the Stack:\n");
    while (temp != NULL) {
        printf("- Student Name: %s, Student Number: %s, Score: %d\n", temp->studentName, temp->studentNumber, temp->score);
        temp = temp->next;
    }
}
void freeStack(ExamPaper* stack) {
    ExamPaper* temp;
    while (stack != NULL) {
        temp = stack;
        stack = stack->next;
        free(temp);
    }
}
int main() {
    ExamPaper* stack = NULL;
    char choice;
    char studentName[100];
    char studentNumber[20];
    int score;
    do {
        printf("1. Add Exam Paper\n");
        printf("2. Remove Exam Paper\n");
        printf("3. Check if Stack is Empty\n");
        printf("4. Display Exam Papers\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        switch (choice) {
            case '1':
                printf("Enter Student Name: ");
                scanf(" %[^\n]s", studentName);
                printf("Enter Student Number: ");
                scanf(" %[^\n]s", studentNumber);
                printf("Enter Score: ");
                scanf("%d", &score);
                stack = push(stack, studentName, studentNumber, score);
                printf("Exam paper added successfully.\n\n");
                display(stack);
                break;
            case '2':
                stack = pop(stack);
                printf("Most recently added exam paper removed successfully.\n\n");
                display(stack);
                break;
            case '3':
                if (isEmpty(stack)) {
                    printf("Stack is empty.\n\n");
                } else {
                    printf("Stack is not empty.\n\n");
                }
                break;
            case '4':
                display(stack);
                break;
            case '5':
                freeStack(stack);
                printf("exiting...\n");
                break;
            default:
                printf("Invalid choice! Please choose again.\n");
                break;
        }
    } while (choice != '5');
    return 0;
}