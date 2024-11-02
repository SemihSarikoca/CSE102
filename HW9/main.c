#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 10 // Board size (only create n x n (n is pozitive integer) size table)


typedef struct { // Block
    char type;
    int value;
} Block;
typedef struct { // 2D board made out of "Block"s
    Block** board;
} Board;

typedef struct { //body loacation of the snake row,colum
    int row;
    int col;
} Point;
typedef struct { //snake
    Point* body;
    int length;
} Snake;

Board* init_board();
void draw_board(Board* gameBoard, Snake* snake);
void play(Board* gameBoard);
void update(Board* gameBoard, Snake* snake, int* moveCounter, Point oldhead);
int check_status(Board* gameBoard, Snake* snake);
Point move(Snake* snake, int* moveCounter);

int main() {
    Board* gameBoard = init_board(); // create the gameboard
    play(gameBoard); // play

    // free
    for (int i = 0; i < BOARD_SIZE; i++) {
        free(gameBoard->board[i]);
    }
    free(gameBoard->board);
    free(gameBoard);

    return 0;
}

Board* init_board() {
    // allocate board and blocks inside of it
    Board* gameBoard = (Board*)malloc(sizeof(Board));
    gameBoard->board = (Block**)malloc(BOARD_SIZE * sizeof(Block*));
    for (int i = 0; i < BOARD_SIZE; i++) {
        gameBoard->board[i] = (Block*)malloc(BOARD_SIZE * sizeof(Block));
        for (int j = 0; j < BOARD_SIZE; j++) { // fill the board with empty space
            gameBoard->board[i][j].type = 'e';
            gameBoard->board[i][j].value = 0;
        }
    }
    srand(time(NULL));
    int obstacle_row, obstacle_col;
    int bait_row, bait_col;
    do { // create random obtacle and bait coordinates
        obstacle_row = rand() % BOARD_SIZE;
        obstacle_col = rand() % BOARD_SIZE;
        bait_row = rand() % BOARD_SIZE;
        bait_col = rand() % BOARD_SIZE;
    } while ((obstacle_row == 0 && obstacle_col == 0) || (obstacle_row == bait_row && obstacle_col == bait_col) || (bait_row == 0 && bait_col == 0)); // start a loop if obstacle or bait in the left corner of the board or if they have exact same location
    // write the type and value of the obstacle block
    gameBoard->board[obstacle_row][obstacle_col].type = 'o';
    gameBoard->board[obstacle_row][obstacle_col].value = 1; 
    // write the type and the value of the bait block (block already has the 0 value but doing one more time cause no harm)
    gameBoard->board[bait_row][bait_col].type = 'b';
    gameBoard->board[bait_row][bait_col].value = 0;
    return gameBoard; // retun the board
}
void draw_board(Board* gameBoard, Snake* snake) {
    for (int i = 0; i <= BOARD_SIZE+1; i++) { // draws top border
        if (i == 0 || i == BOARD_SIZE+1)
            printf("+");
        else
            printf("-");
    }
    printf("\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("|"); // draws left border
        for (int j = 0; j < BOARD_SIZE; j++) {
            int snakeFlag = 0;
            for (int k = 0; k < snake->length; k++) { //checks if any part of the snake in the loacation. if true make flag from 0 to 1
                if (snake->body[k].row == i && snake->body[k].col == j) {
                    snakeFlag = 1;
                    break;
                }
            }
            if (snakeFlag) { // print the snake body (head and tail)
                if (i == snake->body[0].row && j == snake->body[0].col) {
                    printf("O"); // head
                } else {
                    printf("X"); // tail
                }
            } else if (gameBoard->board[i][j].type == 'e') { // print " " for empty blocks
                printf(" ");
            } else if (gameBoard->board[i][j].type == 'o') { // print value of the obstacle block for obstacle
                printf("%d", gameBoard->board[i][j].value);
            } else if (gameBoard->board[i][j].type == 'b') { // print "." for bait
                printf(".");
            }
        }
        printf("|\n"); // print right border
    }
    for (int i = 0; i <= BOARD_SIZE+1; i++) { // print bottom border
        if (i == 0 || i == BOARD_SIZE+1)
            printf("+");
        else
            printf("-");
    }
    printf("\n");
}
void play(Board* gameBoard) {
    Snake* snake = (Snake*)malloc(sizeof(Snake)); // allocate snake
    Point oldhead; 
    snake->body = (Point*)malloc((BOARD_SIZE*BOARD_SIZE) * sizeof(Point)); // allocat body of the snake 
    snake->length = 1; // make snake lengt 1 (just head)
    snake->body[0].row = 0;
    snake->body[0].col = 0;
    int moveCounter = 0, isGameEnded;
    while (1) { // main playing part
        system("clear");
        
        draw_board(gameBoard, snake);
        printf("\nmove:%d\n\n", moveCounter);

        oldhead = move(snake, &moveCounter);
        if (check_status(gameBoard, snake)) { 
            printf("Game over!\n");
            break;
        }
        update(gameBoard, snake, &moveCounter, oldhead);
    }
    //free
    free(snake->body); 
    free(snake);
}
void update(Board* gameBoard, Snake* snake, int* moveCounter, Point oldhead) {
    for (int i = snake->length; i > 1; i--) { // update the tail of the snake
        snake->body[i] = snake->body[i - 1];
    }
    snake->body[1] = oldhead; // move body[1] (snake tail that just before the head) to the old location of the head 
    Point head = snake->body[0]; // i use this because its become more readeble this way and convenience
    srand(time(NULL));
    if (gameBoard->board[head.row][head.col].type == 'b') { // if head on top of the bait
        snake->length++; // increase snake length
        gameBoard->board[head.row][head.col].type = 'e'; // make empty block type
        int bait_row, bait_col, flag;
        do {
            flag = 0;
            bait_row = rand() % BOARD_SIZE;
            bait_col = rand() % BOARD_SIZE;
            for (int i = 0; i <= snake->length; i++) { // check if new created location on the snake body
                if (snake->body[i].row == bait_row && snake->body[i].col == bait_col) {
                    flag = 1;
                    break;
                }
            }
        } while (gameBoard->board[bait_row][bait_col].type != 'e' || flag == 1); // create random loacation bait that on the empty block (and not on the snake body)
        gameBoard->board[bait_row][bait_col].type = 'b'; // make block type bait
    }
    if (gameBoard->board[head.row][head.col].value > 0 && gameBoard->board[head.row][head.col].value <= snake->length) { // if snake head on top of the obstacle that not bigger than himself destroy the obstacle 
        gameBoard->board[head.row][head.col].type = 'e';
        gameBoard->board[head.row][head.col].value = 0;
    }
    if ((*moveCounter) % 5 == 0) { // every 5 legit move create new obstacles
        for (int i = 0; i < BOARD_SIZE; i++) {
            for (int j = 0; j < BOARD_SIZE; j++) {
                if (gameBoard->board[i][j].type == 'o') { // first make all obstacles empty block 
                    gameBoard->board[i][j].type = 'e';
                    gameBoard->board[i][j].value = 0;
                }
            }
        }
        int num_obstacles = rand() % 3 + 1; // number of obstacles (1-3)
        for (int k = 0; k < num_obstacles; k++) { // run number of the obstacles time
            int obstacle_row, obstacle_col, flag = 0;
            do {
                flag = 0;
                obstacle_row = rand() % BOARD_SIZE;
                obstacle_col = rand() % BOARD_SIZE;
                for (int i = 0; i <= snake->length; i++) { // check if new created location on the snake body
                    if (snake->body[i].row == obstacle_row && snake->body[i].col == obstacle_col) {
                        flag = 1;
                    }
                }
            } while (gameBoard->board[obstacle_row][obstacle_col].type != 'e' || flag == 1); // if obstacle location on the block that not empty or on the snake body. enter loop and create new one until conditions are met
            int obstacle_height = rand() % 9 + 1; // randomly create obstacle height (1-9)
            gameBoard->board[obstacle_row][obstacle_col].type = 'o'; // change the block type to obstacle
            gameBoard->board[obstacle_row][obstacle_col].value = obstacle_height; // change the value(height) of the block
        }
    }
}
int check_status(Board* gameBoard, Snake* snake) {
    Point head = snake->body[0]; // assign head of the snake to the "head" variable for convenience
    if (head.row < 0 || head.row > BOARD_SIZE - 1 || head.col < 0 || head.col > BOARD_SIZE - 1) {
        return 1;  // Game over (hit the one of the border)
    }
    if (gameBoard->board[head.row][head.col].type == 'o' && gameBoard->board[head.row][head.col].value > snake->length) {
        return 1;  // Game over (hit the obstacle longer than snake)
    }
    for (int i = 1; i < snake->length; i++) {
        if (head.row == snake->body[i].row && head.col == snake->body[i].col) {
            return 1;  // Game over (hit the body of the snake)
        }
    }
    if (snake->length == BOARD_SIZE*(BOARD_SIZE - 1)) {
        return 1; // Game over (there is so little space for playing)
    }
    return 0; // Game continues
}
Point move(Snake* snake, int* moveCounter) {
    Point head = snake->body[0]; // assign head of the snake to the "head" variable for convenience
    Point newhead; // loacation that head moves
    Point oldhead; // old loacation of the head
    char direction;
    int ignoreFlag;
    do {
        ignoreFlag = 0;
        printf("Enter your next move (w/a/s/d): ");
        scanf(" %c", &direction); // input from user
        switch (direction) { // make moves
            case 'w': // up
                newhead.row = head.row-1;
                newhead.col = head.col;
                break;
            case 'a': // left
                newhead.row = head.row;
                newhead.col = head.col-1;
                break;
            case 's': // down
                newhead.row = head.row+1;
                newhead.col = head.col;
                break;
            case 'd': // right
                newhead.row = head.row;
                newhead.col = head.col+1;
                break;
            default:
                ignoreFlag = 1; // ignore anything other than w,a,s,d
                break;
        }
        if (newhead.row == snake->body[1].row && newhead.col == snake->body[1].col) { // if player want to move head to directly body ignore the move
            ignoreFlag = 1;
        }
    } while (ignoreFlag); // loop until it's legal move
    (*moveCounter)++; // increase the move counter for creating obstacle every 5 move
    oldhead = snake->body[0]; // assign loaciton of the current head to the oldhead variable
    snake->body[0] = newhead; // assign new loacation of the head 
    return oldhead; // return the old loacation of the head so that, code be able to update the tail of the snake in the update function (without this snake->body[1] will not be updated)
}
