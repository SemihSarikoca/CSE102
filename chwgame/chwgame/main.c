#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BOARD_SIZE 16
#define BOARD_SPACE BOARD_SIZE * BOARD_SIZE
#define FIRST_GRADE_ECTS_REQUIRED 32
#define SECOND_GRADE_ECTS_REQUIRED 24
#define COURSE_ECTS 8

char board[BOARD_SPACE];
int player_pos = (BOARD_SPACE / 2) + ((BOARD_SIZE % 2 == 0) ? (BOARD_SIZE / 2) : 0);
int first_year_ects = 0;
int second_year_ects = 0;
int total_moves = 0;

void initialize_game(void);
void print_board(void);
void move_player(char direction);


int main(void) {


	initialize_game();
	print_board();

	char direction;
	while (1) {
		printf("Enter direction (w/a/s/d): ");
		scanf(" %c", &direction);
		move_player(direction);
		print_board();

		if (player_pos == BOARD_SPACE - 1) {
			printf("Congratulations! You reached the X.\n");
			printf("Total ECTS: %d\n", first_year_ects + second_year_ects);
			printf("Total moves: %d\n", total_moves);
			break;
		}
	}

	return 0;
}

int grade_border(int i) {

	// Calculate distance between current position and player
	int row_distance = abs(i / BOARD_SIZE - BOARD_SIZE / 2);
	int col_distance = abs(i % BOARD_SIZE - BOARD_SIZE / 2);

	if ((row_distance == 2 && col_distance <= 2) || (row_distance <= 2 && col_distance == 2)) {
		return 1;
	}
	if ((row_distance == 4 && col_distance <= 4) || (row_distance <= 4 && col_distance == 4)) {
		return 2;
	}
	return 0;
}


void initialize_game(void) {
	// Initialize board with empty spaces
	for (int i = 0; i < BOARD_SPACE; i++) {
		board[i] = '.';
	}

	// Place walls
	for (int i = 0; i < BOARD_SPACE; i++) {

		if (grade_border(i) == 1) {
			board[i] = '#';
		}
		if (grade_border(i) == 2) {
			board[i] = '#';
		}

	}
	// Place player
	board[player_pos] = 'P';

	// Place courses


	// Place X
	board[BOARD_SPACE - 1] = 'X';
}

void print_board(void) {
	printf("\n");
	for (int i = 0; i < BOARD_SPACE; i++) {
		printf("%c ", board[i]);
		if ((i + 1) % BOARD_SIZE == 0) {
			printf("\n");
		}
	}

}

void move_player(char direction) {
	int new_pos = player_pos;

	switch (direction) {
		case 'w':
		case 'W':
			if (player_pos >= BOARD_SIZE)
				new_pos -= BOARD_SIZE;
			break;
		case 'a':
		case 'A':
			if (player_pos % BOARD_SIZE != 0)
				new_pos--;
			break;
		case 's':
		case 'S':
			if (player_pos < BOARD_SPACE - BOARD_SIZE)
				new_pos += BOARD_SIZE;
			break;
		case 'd':
		case 'D':
			if ((player_pos + 1) % BOARD_SIZE != 0)
				new_pos++;
			break;
		default:
			printf("Invalid direction!\n");
			return;
	}

	if ((grade_border(new_pos) == 1 && first_year_ects == FIRST_GRADE_ECTS_REQUIRED) ||
		(grade_border(new_pos) == 2 && second_year_ects == SECOND_GRADE_ECTS_REQUIRED) ||
		(grade_border(new_pos) == 0)) {

		board[player_pos] = '.';
		player_pos = new_pos;
		board[player_pos] = 'P';
		total_moves++;

	}
}
