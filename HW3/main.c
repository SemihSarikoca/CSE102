#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

void map();
void gameplay();
void gamemenu();
int control(int x1,int y1,int x2,int y2);

int main(){
    gamemenu();
    return 0;
}

void map(int cols, int rows, int char_pos_x, int char_pos_y, int door_pos_x, int door_pos_y){ /*part1*/
    int i,j;
    for(i=0; i<=cols*2; i++) /*prints the up wall*/
        printf("-");
    printf("\n");
	for(i=0; i<rows; i++){
		for(j=0; j<cols; j++){
			if(i==char_pos_y && j==char_pos_x){ /*prints players position*/
				printf("|C");
			}
			else if(i==door_pos_y && j==door_pos_x){ /*prints the exit*/
				printf("|D");
			}
			else{
				printf("| ");
			}
		}
		printf("|\n"); 
	}
    for(i=0; i<=cols*2; i++) /*prints the down wall*/
        printf("-");
    printf("\n");
}

void gameplay(){ /*part2*/
	int x,y,x1,y1,x2,y2;
	char move;
	do{
        printf("Enter the x and y axis of the map (5-10):\n"); /*taking map size from user*/
        scanf("%d %d",&x,&y);
    }while(x<5 || x>10 || y<5 || y>10);
    srand(time(NULL)); /*creates random starting points*/
    x1=rand()%x;
	y1=rand()%y;
    x2=rand()%x;
    y2=rand()%y;
    int counter=0, completed=0;
    do{ /*moving algorithm with the input from user*/
        if(!completed)
            map(x,y, x1, y1, x2, y2); //print the map with every step until completed value become 1
        scanf(" %c",&move); // take user imput
        switch(move){ //moving algorithm
            case UP:
                y1 -=1;
                break;
            case DOWN:
                y1 +=1;
                break;    
            case LEFT:
                x1 -=1;
                break;
            case RIGHT:
                x1 +=1;
                break;
            default:
                printf("Use w,a,s,d to move\n"); //for invalid imput back to loop again
                continue;
        }
        if(x1<0 || x1>=x || y1<0 || y1>=y){ /* warn the user if he is hitting the wall */
            if(x1<0)
                x1 +=1;
            else if(x1>=x)
                x1 -=1;
            else if(y1<0)
                y1 +=1;
            else
                y1 -=1;
            printf("Warning! You cannot pass through the wall.\n"); //if player hit the wall go back to the loop again so counter doesn't add up
            continue;
        }
        counter+=1; //count evey step
        completed=control(x1,y1,x2,y2); //checking if user reach the door
    }while(!completed); /*loop until player reaches the door*/
    printf("Congratulations! You have complated the game.\n");
    printf("Total move needed to complate: %d\n",counter);
    printf("Returning to the menu...\n\n");
}

int control(int x1,int y1,int x2,int y2){ /*part3*/
	int flag = !((x1!=x2) || (y1!=y2)); /*if player reaches the estimated point result will be 1 otherwise result will be 0*/
	return flag; /*return result*/
}

void gamemenu(){ /*part4*/
	int option;
    do{ /*printing menu after 1,2 option in a loop. 3rd option to stop the loop*/
    	printf("Welcome to the 2D puzzle game!\n");
        printf("1. New Game\n");
        printf("2. Help\n");
        printf("3. Exit\n");
        scanf("%d",&option);
        if(option == 2){
            printf("\nGameplay:\nThe character is able to move one space in any of the four cardinal directions: up, down, left, and right. Diagonal moves are not allowed. The user will input their desired move using the following keys: 'a' for left, 'd' for right, 'w' for up, and 's' for down. The game ends when the character reaches the door.\n\n");
        }
        else if(option == 3){
            printf("Exiting the game, goodbye...\n");
        }
        else if(option == 1){
            gameplay();
        }
        else{
            printf("Chose one of the options! -> 1 - 2 - 3\n");
        }
    }while(option != 3);
}