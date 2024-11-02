#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#define ALPHABET_SIZE 26
//part2 colors 
typedef enum { //colors
    RED,
    GREEN,
    BLUE,
    YELLOW,
    ORANGE
} Color;
double color_vector[5][3] = { //rgb values for colors
    {1,0,0},
    {0,1,0},
    {0,0,1},
    {0.5,0.5,0},
    {0.5,0.4,0.2}
};
//part1 declerations
void part1();
char make_lowercase(char c);
int check_alpahbet(char c);
//part2 declerations
void part2();
Color colorMixer(Color c1, Color c2, Color(*func)(Color, Color));
Color mixFunc(Color c1, Color c2);
double ecludian_distance(double v1[3], double v2[3]);
//part3 declerations
void part3();
void print_board(char board[3][3]);
bool is_legal_move(char board[3][3], int row, int col);
bool is_gameover(char board[3][3], char turn);
bool is_board_full(char board[3][3]);
//main
int main() {
    part1();
    part2();
    part3();
    return 0;
}
//part1 functions
void part1() {
    char filename[50];
    printf("Enter the file name: ");
    scanf(" %s", filename); //take the file name from user
    FILE *fp;
    fp = fopen(filename, "r");
    if (fp == NULL) { //terminate if there is no such file
        printf("There is no such a file!\n");
        exit(1);
    }
    int counter[ALPHABET_SIZE] = {0}, i; //make a counter that size of a alphabet and each block will be start from 0 to count
    char c;
    while ((c = fgetc(fp)) != EOF) { // get char until there is no char to take(EOF)
        if (check_alpahbet(c)){ //count only if readed char is part of the alphabet
            counter[make_lowercase(c) - 'a']++; //start from a = first element of the alphabet and add each letter readed
        }
    }
    printf("Part1 - Letter Frequency\n\n");
    for (i = 0; i < ALPHABET_SIZE; i++) {
        printf(" %c: %d\n", 'A'+i, counter[i]); //with %c print alphabet uppercase and %d print the counter of each letter
    }
    fclose(fp);
    printf("\n--------------------------------------------------------\n");
}
char make_lowercase(char c) { //add every chat 'a' - 'A' (32). If the char is in the alphabet that means make the A to lowercase a. So counting mak no problem
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    } 
    else {
        return c;
    }
}
int check_alpahbet(char c) { //check that if the readed char is part of the alphabet by ASCII equvilant
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
        return 1; 
    }
    else {
        return 0;
    }
}
//part2 functions
void part2() {
    char user_input1, user_input2;
    Color c1, c2;
    printf("Part2 - Color Mixer\n\n");
    printf("Enter color 1 (r,g,b,y,o): ");
    scanf(" %c", &user_input1); //user input
    printf("Enter color 2 (r,g,b,y,o): ");
    scanf(" %c", &user_input2); //user input
    switch (user_input1) { //user input ----> equevilant color
        case 'r':
            c1 = RED;
            break;
        case 'g':
            c1 = GREEN;
            break;
        case 'b':
            c1 = BLUE;
            break;
        case 'y':
            c1 = YELLOW;
            break;
        case 'o':
            c1 = ORANGE;
            break;
    }
    switch (user_input2) { //user input ----> equevilant color
        case 'r':
            c2 = RED;
            break;
        case 'g':
            c2 = GREEN;
            break;
        case 'b':
            c2 = BLUE;
            break;
        case 'y':
            c2 = YELLOW;
            break;
        case 'o':
            c2 = ORANGE;
            break;
    }
    colorMixer(c1, c2, mixFunc); //call function
    printf("\n--------------------------------------------------------\n");
}
double ecludian_distance(double v1[3], double v2[3]) {
    return sqrt((v2[0]-v1[0])*(v2[0]-v1[0]) + (v2[1]-v1[1])*(v2[1]-v1[1]) + (v2[2]-v1[2])*(v2[2]-v1[2])); //ecludian distance formula (3d)
}
Color colorMixer(Color c1, Color c2, Color(*func)(Color, Color)) { // takes two 'Color' enumeration values and a function pointer as arguments. Return new color
    return func(c1, c2);
}
Color mixFunc(Color c1, Color c2) {
    double c1_vector[3], c2_vector[3];
    switch (c1) { //set the rgb values for c1
        case RED:
            c1_vector[0] = color_vector[RED][0];
            c1_vector[1] = color_vector[RED][1];
            c1_vector[2] = color_vector[RED][2];
            break;
        case GREEN:
            c1_vector[0] = color_vector[GREEN][0];
            c1_vector[1] = color_vector[GREEN][1];
            c1_vector[2] = color_vector[GREEN][2];
            break;
        case BLUE:
            c1_vector[0] = color_vector[BLUE][0];
            c1_vector[1] = color_vector[BLUE][1];
            c1_vector[2] = color_vector[BLUE][2];
            break;
        case YELLOW:
            c1_vector[0] = color_vector[YELLOW][0];
            c1_vector[1] = color_vector[YELLOW][1];
            c1_vector[2] = color_vector[YELLOW][2];
            break;
        case ORANGE:
            c1_vector[0] = color_vector[ORANGE][0];
            c1_vector[1] = color_vector[ORANGE][1];
            c1_vector[2] = color_vector[ORANGE][2];
            break;
    }
    switch (c2) { //set the rgb values for c2
        case RED:
            c2_vector[0] = color_vector[RED][0];
            c2_vector[1] = color_vector[RED][1];
            c2_vector[2] = color_vector[RED][2];
            break;
        case GREEN:
            c2_vector[0] = color_vector[GREEN][0];
            c2_vector[1] = color_vector[GREEN][1];
            c2_vector[2] = color_vector[GREEN][2];
            break;
        case BLUE:
            c2_vector[0] = color_vector[BLUE][0];
            c2_vector[1] = color_vector[BLUE][1];
            c2_vector[2] = color_vector[BLUE][2];
            break;
        case YELLOW:
            c2_vector[0] = color_vector[YELLOW][0];
            c2_vector[1] = color_vector[YELLOW][1];
            c2_vector[2] = color_vector[YELLOW][2];
            break;
        case ORANGE:
            c2_vector[0] = color_vector[ORANGE][0];
            c2_vector[1] = color_vector[ORANGE][1];
            c2_vector[2] = color_vector[ORANGE][2];
            break;
    }
    double mixed_vector[3] = {((c1_vector[0]+c2_vector[0])/2.0), ((c1_vector[1]+c2_vector[1])/2.0), ((c1_vector[2]+c2_vector[2])/2.0)}; //calculating vector value of mix of c1 and c2
    Color i, mixedColor;
    double minDistance = 50; //make first distance very large so it run firts if no matter what 
    for (i = RED; i <= ORANGE; i++) {
        double distance = ecludian_distance(mixed_vector, color_vector[i]); //calculate distance from mixed vector to every color vector 
        if (distance < minDistance) { //if the new calculated distance smaller than the previous one
            minDistance = distance; //make new distance minimum distance
            mixedColor = i; //and make new distance equevilent color, new color(mixedColor)
        }
    }
    printf("Mixed Color: ");
    switch (mixedColor) { //print mixed color
        case RED:
            printf("RED ");
            break;
        case GREEN:
            printf("GREEN ");
            break;
        case BLUE:
            printf("BLUE ");
            break;
        case YELLOW:
            printf("YELLOW ");
            break;
        case ORANGE:
            printf("ORANGE ");
            break;
    }
    printf("[%0.1f, %0.1f, %0.1f]", mixed_vector[0], mixed_vector[1], mixed_vector[2]); //print mixed vector
    return 0;
}
//part3 functions
void part3() {
    char board[3][3];
    int row, col;
    char player_turn = 'X'; //game start with X
    for (row = 0; row < 3; row++) { //fill array with '_'
        for (col = 0; col < 3; col++) {
            board[row][col] = '_';
        }
    }
    printf("Part3 - Tic Tac Toe\n");
    while (1) {
        if (player_turn == 'X') {
            printf("\nPlayer 1 (X), enter your move (row, col): ");
            scanf("%d %d", &row, &col); //take coordinates
            if (is_legal_move(board, row, col)) { //if player enter legal move
                board[row][col] = 'X'; //fill that coordinate with X
                print_board(board); //then print the board
                if (is_gameover(board, player_turn)) { //if game is over with that move, break from the while loop
                    break;
                }
                player_turn = 'O'; //change turn
            }
            else {
                printf("Enter legal move!\n"); //if player enters illegal move such 3 3 or 2 4, warn user and continue
                continue;
            }
        }
        else if (player_turn == 'O') {
            printf("\nPlayer 2 (O), enter your move (row, col): ");
            scanf("%d %d", &row, &col); //take coordinates
            if (is_legal_move(board, row, col)) { //if player enter legal move
                board[row][col] = 'O'; //fill that coordinate with O
                print_board(board); //then print the board
                if (is_gameover(board, player_turn)) { //if game is over with that move, break from the while loop
                    break;
                }
                player_turn = 'X'; //change turn
            }
            else {
                printf("\nEnter legal move!"); //if player enters illegal move such 3 3 or 2 4, warn user and continue
                continue;
            }
        }
    }
    char playAgain;
    printf("\nDo you want to play again (y/n)? ");
    scanf(" %c", &playAgain); // ask user want to play
    printf("--------------------------------------------------------\n");
    if (playAgain == 'y') {
        part3(); //if player wants to play again recall the function
    }
}
void print_board(char board[3][3]) { //prints the game board
    for(int row = 0; row < 3; row++) {
        for(int col = 0; col < 3; col++) {
            printf("%c ",board[row][col]); 
        }
        printf("\n");
    }
}
bool is_legal_move(char board[3][3], int row, int col) {
    if (board[row][col] != '_') { //if there is a something else from '_' in the coordinates, retun false
        return false;
    }
    return true; //if place is empty retun true
}
bool is_gameover(char board[3][3], char turn) {
    int i;
    for(i = 0; i < 3; i++) { //horizontal check
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) {
            if (board[1][i] != '_') {
                printf("\nPlayer %c wins!", turn);
                return true;
            }
        }
    }
    for(i = 0; i < 3; i++) { //vertical check
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][1] != '_') {
                printf("\nPlayer %c wins!", turn);
                return true;
            }
        }
    }
    if ((board[0][0] == board[1][1] && board[1][1] == board[2][2]) ||
        (board[0][2] == board[1][1] && board[1][1] == board[2][0])) { //diagonal check
        if (board[1][1] != '_') {
            printf("\nPlayer %c wins!", turn);
            return true;
        }
    }
    else if (is_board_full(board)) { //if there is no empty space in the board print and contidions from above not happened, print tie 
        printf("\nTie!");
        return true;
    }
    return false;
}
bool is_board_full(char board[3][3]) { //check the array if there is 9 non '_' character, return true (board is full). else false (there is space left)
    int flag = 0, i, j;
    for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++){
            if (board[i][j] != '_') {
                flag++;
            }
        }
    }
    if (flag == 9) {
        return true;
    }
    return false;
}