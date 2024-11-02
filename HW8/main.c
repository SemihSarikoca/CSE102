#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define BOARD_SIZE 3
#define FILENAME "puzzle_state.txt"
#define SCORE_FILE "best_score.txt"

typedef struct {
    int board[BOARD_SIZE][BOARD_SIZE];
} PuzzleBoard;

bool isSolvable(int* arr, int size);
bool isPuzzleSolved(const PuzzleBoard *puzzle);
void shuffleArray(int *array, int size);
void swapCells(int *a, int *b);
void initializeBoard(PuzzleBoard *puzzle);
void printBoard(const PuzzleBoard *puzzle);
void saveBoardToFile(const PuzzleBoard *puzzle);
void performMove(PuzzleBoard *puzzle, int number, char direction);
void playGameAsUser();
void finishGameWithPC();
void showBestScore();
int main() { // Menu
    char choice;
    while (true) {
        printf("Menu:\n");
        printf("1. Play game as a user\n");
        printf("2. Finish the game with PC\n");
        printf("3. Show the best score\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        switch (choice) {
            case '1':
                playGameAsUser();
                break;
            case '2':
                finishGameWithPC();
                break;
            case '3':
                showBestScore();
                break;
            case '4':
                printf("Terminating the program...\n");
                return 0;
            default:
                printf("Invalid choice! Please enter a valid choice.\n");
                break;
        }

    }
    return 0;
}
void swapCells(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
bool isSolvable(int* arr, int size) {
    int inversions = 0;
    // Using iversions logic to chech if puzzle solvable or not. (return 1 or 0).
    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            if (arr[i] > arr[j])
                inversions++;
        }
    }
    return (inversions % 2 == 0);
}
void shuffleArray(int *array, int size) {
    srand(time(NULL));
    // Shuffels integer array using rand()
    for (int i = size - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swapCells(&array[i], &array[j]);
    }
}
void initializeBoard(PuzzleBoard *puzzle) {
    int numbers[BOARD_SIZE * BOARD_SIZE - 1];
    // Create number array starting from 0 to 8
    for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++) {
        numbers[i] = i;
    }
    srand(time(NULL));
    do {
        shuffleArray(numbers, BOARD_SIZE * BOARD_SIZE); // Shuffle the array
        int index = 0;
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                puzzle->board[i][j] = numbers[index++]; // Transfer the 1D number array to 2D puzzle->board array
            }
        }
    } while (!isSolvable(numbers, BOARD_SIZE * BOARD_SIZE - 1)); // Do until created puzzle is solvable
}
void printBoard(const PuzzleBoard *puzzle) {
    printf("Puzzle Board:\n");
    // Prints board to the terminal
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (puzzle->board[i][j] == 0) {
                printf("  ");
            } else {
                printf("%d ", puzzle->board[i][j]);
            }
        }
        printf("\n");
    }
}
void saveBoardToFile(const PuzzleBoard *puzzle) {
    FILE *file = fopen(FILENAME, "a");
    if (file == NULL) {
        printf("Error opening file for saving puzzle state.\n");
        return;
    }
    // Prints puzzle board to the file, write "_" for 0. So its look like empty cell
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (puzzle->board[i][j] == 0) {
                fprintf(file, "_ ");
            } else {
                fprintf(file, "%d ", puzzle->board[i][j]);
            }
        }
        fprintf(file, "\n");
    }
    fprintf(file, "\n");
    fclose(file);
}
bool isPuzzleSolved(const PuzzleBoard *puzzle) {
    int count = 1;
    /* Checks if the puzzle format is like this:
        1   2   3
        4   5   6
        7   8
        checks until board[2][2] which means dont checks last cell bcoz its clear that 0 in there.
        if puzzle solved then return true, else return false.
    */
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (puzzle->board[i][j] != count && !(i == BOARD_SIZE - 1 && j == BOARD_SIZE - 1)) {
                return false;
            }
            count++;
        }
    }
    return true;
}
// Option 1
void performMove(PuzzleBoard *puzzle, int number, char direction) {
    int emptyRow, emptyCol;
    int numberRow, numberCol;
    // Find the position of the empty cell and the given number
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (puzzle->board[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
            } else if (puzzle->board[i][j] == number) {
                numberRow = i;
                numberCol = j;
            }
        }
    }
    // Perform the move based on the given direction
    switch (direction) {
        case 'U': //up
            if (numberRow - 1 == emptyRow && numberCol == emptyCol) { 
                swapCells(&puzzle->board[emptyRow][emptyCol], &puzzle->board[numberRow][numberCol]);
            } else {
                printf("Invalid move! Cannot move number %d up.\n", number);
            }
            break;
        case 'D': //down
            if (numberRow + 1 == emptyRow && numberCol == emptyCol) {
                swapCells(&puzzle->board[emptyRow][emptyCol], &puzzle->board[numberRow][numberCol]);
            } else {
                printf("Invalid move! Cannot move number %d down.\n", number);
            }
            break;
        case 'L': //left
            if (numberRow == emptyRow && numberCol - 1 == emptyCol) {
                swapCells(&puzzle->board[emptyRow][emptyCol], &puzzle->board[numberRow][numberCol]);
            } else {
                printf("Invalid move! Cannot move number %d left.\n", number);
            }
            break;
        case 'R': //right
            if (numberRow == emptyRow && numberCol + 1 == emptyCol) {
                swapCells(&puzzle->board[emptyRow][emptyCol], &puzzle->board[numberRow][numberCol]);
            } else {
                printf("Invalid move! Cannot move number %d right.\n", number);
            }
            break;
        default:
            printf("Invalid direction! Please enter a valid direction (U, D, L, R).\n");
    }
}
void playGameAsUser() {
    PuzzleBoard puzzle;
    initializeBoard(&puzzle);
    saveBoardToFile(&puzzle);
    int moveCount = 0;
    int number;
    char direction;
    int score;
    while (true) {
        printBoard(&puzzle);
        printf("Enter number and direction (U/D/L/R) for the move: ");
        scanf("%d-%c", &number, &direction); // Taking user input

        performMove(&puzzle, number, direction);
        saveBoardToFile(&puzzle);
        moveCount++;

        if (isPuzzleSolved(&puzzle)) { // if puzzle is solved, calculate the score and print with the move count
            score = 1000 - (10 * moveCount);
            printf("\nCongratulations! You solved the puzzle in %d moves.\n", moveCount);
            printf("Your score is: %d\n", score);
            break;
        }
    }
    // Checks if the new score bigger than the score in the file. if bigger then writes new score to the file.
    FILE *s_file = fopen(SCORE_FILE, "r+"); // Open in read & write format
    if (s_file == NULL) {
        printf("Error opening score file.\n");
        exit(1);
    }
    int best_score;
    int flag = fscanf(s_file, "%d", &best_score);
    if (flag != 1) {
        printf("Error reading best score from file.\n");
        fclose(s_file);
        exit(1);
    }
    if (score > best_score) {
        printf("\nCongratulations! You break the record.\nOld record: %d\n", best_score);
        best_score = score;
    }
    rewind(s_file);
    fprintf(s_file, "%d", best_score);
    fclose(s_file);
}
// Option 2
void autoFinish(PuzzleBoard *puzzle, int *moveCount) {
    int emptyRow, emptyCol, numberRow, numberCol;
    // Find the empty cells location
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (puzzle->board[i][j] == 0) {
                emptyRow = i;
                emptyCol = j;
            }
        }
    }
    // Generate a random move {0, 1, 2, 3}
    int move = rand() % 4;
    // Determine the new position based on the move
    switch (move) {
        case 0:  // Up
            numberRow = emptyRow - 1;
            numberCol = emptyCol;
            if (numberRow >= 0 && numberRow < BOARD_SIZE && numberCol >= 0 && numberCol < BOARD_SIZE) {
                // Swap the cells between empty and number cells
                printf("Computer Move: %d-U\n", puzzle->board[numberRow][numberCol]);
                swapCells(&puzzle->board[emptyRow][emptyCol], &puzzle->board[numberRow][numberCol]);
                (*moveCount)++;
                printBoard(puzzle);  // Print the board after each move
                saveBoardToFile(puzzle);
            }        
            break;
        case 1:  // Down
            numberRow = emptyRow + 1;
            numberCol = emptyCol;
            if (numberRow >= 0 && numberRow < BOARD_SIZE && numberCol >= 0 && numberCol < BOARD_SIZE) {
                // Swap the cells between empty and number cells
                printf("Computer Move: %d-D\n", puzzle->board[numberRow][numberCol]);
                swapCells(&puzzle->board[emptyRow][emptyCol], &puzzle->board[numberRow][numberCol]);
                (*moveCount)++;
                printBoard(puzzle);  // Print the board after each move
                saveBoardToFile(puzzle);            
            }           
            break;
        case 2:  // Left
            numberRow = emptyRow;
            numberCol = emptyCol - 1;
            if (numberRow >= 0 && numberRow < BOARD_SIZE && numberCol >= 0 && numberCol < BOARD_SIZE) {
                printf("Computer Move: %d-L\n", puzzle->board[numberRow][numberCol]);
                // Swap the cells between empty and number cells
                swapCells(&puzzle->board[emptyRow][emptyCol], &puzzle->board[numberRow][numberCol]);
                (*moveCount)++;
                printBoard(puzzle);  // Print the board after each move
                saveBoardToFile(puzzle);
            }            
            break;
        case 3:  // Right
            numberRow = emptyRow;
            numberCol = emptyCol + 1;
            if (numberRow >= 0 && numberRow < BOARD_SIZE && numberCol >= 0 && numberCol < BOARD_SIZE) {
                printf("Computer Move: %d-R\n", puzzle->board[numberRow][numberCol]);
                // Swap the cells between empty and number cells
                swapCells(&puzzle->board[emptyRow][emptyCol], &puzzle->board[numberRow][numberCol]);
                (*moveCount)++;
                printBoard(puzzle);  // Print the board after each move
                saveBoardToFile(puzzle);
            }
            break;
    }
    if (!isPuzzleSolved(puzzle)) {
        autoFinish(puzzle, moveCount); // Call itself
    }
}
void finishGameWithPC() {
    PuzzleBoard puzzle;
    int moveCount = 0;
    initializeBoard(&puzzle);
    saveBoardToFile(&puzzle);
    
    autoFinish(&puzzle, &moveCount);

    int score = 1000 - (10 * moveCount);
    printf("\nPuzzle solved by the pc it takes %d moves.\n", moveCount);
}
// Option 3
void showBestScore() {
    FILE *s_file = fopen(SCORE_FILE, "r+");
    if (s_file == NULL) {
        printf("Error opening score file.\n");
        exit(1);
    }
    int best_score;
    int flag = fscanf(s_file, "%d", &best_score); //Read the score
    if (flag != 1) {
        printf("Error reading best score from file.\n");
        fclose(s_file);
        exit(1);
    }
    printf("Best score: %d\n", best_score); // Print score to terminal
    fclose(s_file);
}
