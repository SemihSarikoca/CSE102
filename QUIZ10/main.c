#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARRAY_SIZE 10000

typedef struct {
    int ID;
    int age;
    float GPA;
} Student;

Student* generateStudentsArray();
int* generateArray(int size);

void part1();
void part2();
void part3();

int main() {
    part1();
    part2();
    part3();
    return 0;
}

int* generateArray(int size) {
    int* array = (int*)malloc(size * sizeof(int));
    printf("Enter the elements of the array: ");
    for (int i = 0; i < size; i++) {
        scanf("%d", &array[i]);
    }
    return array;
}

void part1() {
    printf("\n\nPart - 1\n");
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);
    int* numArray = generateArray(size);

    int minNum = numArray[0];
    for (int i = 1; i < size; i++) {
        if (numArray[i] < minNum) {
            minNum = numArray[i];
        }
    }

    printf("Min of the array elements: %d\n", minNum);
    free(numArray);
}

void part2() {
    printf("\n\nPart - 2\n");
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int *numArray = generateArray(size);

    int *cumSumArray = (int*)calloc(size, sizeof(int));
    cumSumArray[0] = numArray[0];
    for (int i = 1; i < size; i++) {
        cumSumArray[i] = cumSumArray[i - 1] + numArray[i]; // 1 2 3 4 5 -> 1 (1+2) (3+3) (6+4) (10+5)
    }

    printf("First array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", numArray[i]);
    }
    printf("\nSecond array (cumulative sum): ");
    for (int i = 0; i < size; i++) {
        printf("%d ", cumSumArray[i]);
    }
    printf("\n");

    free(numArray);
    free(cumSumArray);
}

Student* generateStudentsArray() {
    Student* students = (Student*)malloc(ARRAY_SIZE * sizeof(Student));
    for (int i = 0; i < ARRAY_SIZE; i++) {
        students[i].ID = rand();
        students[i].age = rand() % 80;
        students[i].GPA = (float)(rand() % 400) / 100.0;
    }
    return students;
}

void part3() {
    srand(time(NULL));
    float overallSumGPA = 0.0, overallAverageGPA;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        Student* students = generateStudentsArray();

        float sumGPA = 0.0;
        float averageGPA;
        for (int j = 0; j < ARRAY_SIZE; j++) {
            sumGPA += students[j].GPA; 
        }
        averageGPA = sumGPA / ARRAY_SIZE;

        overallSumGPA += averageGPA;
        free(students);
    }

    overallAverageGPA = overallSumGPA / ARRAY_SIZE;
    printf("\n\nPart - 3\n");
    printf("Average GPA of 10,000 x 10,000 students: %.2f\n", overallAverageGPA);
}
