#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define VAT_RATE_ADDED 1.18
#define STUDENT_DISCOUNT 0.125
#define BIG_PURCHASE_DISCOUNT 0.10
#define BIG_PURCHASE 150.0
#define USER_NO 220104004038 
#define MENU_SIZE 12 //number of the items in the menu

void food_ordering_assistance();
void print_menu();
void order_and_receipt();
void print_receipt();

void game_rps();

int main() {
    food_ordering_assistance();
    game_rps();
    return 0;
}
//part1 start
void print_menu(){ //show menu on terminal screen
    FILE *file;
    file = fopen("menu.txt", "r");
    
    if(file == NULL){
        printf("Menu file not found.\n");
        exit(1);
    }
    
    char c;
    int lineCounter = 1;
    int spaceFlag = 0; //flag for space character after the scape it's igrnore the rest of them (price part)
    
    printf("Products:\n");
    printf("%d. ",lineCounter);
    while((c=fgetc(file)) != EOF){
        if(c == '\n'){
            lineCounter++;
            printf("\n%d. ",lineCounter); //numerate every line so user pick between them
            spaceFlag = 0;
        }
        else if(c == ' '){
            spaceFlag++;
        }
        else if(spaceFlag == 0){
            printf("%c", c);
        }
    }
    printf("\n");
    fclose(file);
}
void order_and_receipt(){
    FILE *menu_file;
    FILE *receipt_file;
    
    menu_file = fopen("menu.txt", "r");
    receipt_file = fopen("receipt.txt", "w");
    //just in case put them to be sure
    if(menu_file == NULL){ 
        printf("Menu file not found.\n");
        exit(1);
    }
    if(receipt_file == NULL){
        printf("Receipt file not found.\n");
        exit(1);
    }

    char product_name[50], student;
    float price, total_price = 0.00, student_discount = 0.00, b_purchase_discount = 0.00;
    int lineNo, itemNo, quantity;
    
    time_t t; //date and time
    t = time(NULL);
    struct tm tm = *localtime(&t);
    fprintf(receipt_file,"%ld            %02d.%02d.%04d/%02d:%02d\n", USER_NO, tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_hour, tm.tm_min);//userno, date and time
    fprintf(receipt_file,"----------------------------------------\n");
    fprintf(receipt_file,"PRODUCT                        PRICE(TL)\n");
    fprintf(receipt_file,"----------------------------------------\n");
    while(1){
        printf("Please choose a product (Press 0 for stop the order): ");
        if(scanf("%d", &itemNo) != 1 || itemNo > MENU_SIZE || itemNo < 0){
            printf("\nError: The product you want is not available! Pick new one.\n");
            scanf("%*s"); //cleaning the buffer
            continue;
        }
        if(itemNo == 0){
            do{
                printf("Are you a student? (Y/N): ");
                scanf(" %c", &student);
                if(student != 'Y' && student != 'N'){ //warn user 
                    printf("Invalid input. Please enter Y or N.\n");
                }
            }while (student != 'Y' && student != 'N'); //if player does not chose one of the Y/N program warn them and ask again
            break;
        }
        printf("How many servings do you want? ");
        if(scanf("%d", &quantity) != 1){
            printf("\nError: Enter proper quantity!\n");
            scanf("%*s"); //cleaning the buffer
            continue;
        }
        lineNo = 1;
        fseek(menu_file, 0, SEEK_SET); //every loop read the menu file from the start
        while(fscanf(menu_file, "%s %f", product_name, &price) != EOF){ 
            if(lineNo == itemNo){ 
                total_price += quantity * price; //add each order to total price 
                fprintf(receipt_file, "%-2d* %-25s %10.2f\n", quantity, product_name, quantity * price); //printing receipt line by line
                break;
            }
            lineNo++;
        }
    }
    //printing the receipt process
    fprintf(receipt_file, "Total:%34.2f\n", total_price);
    if(student == 'Y'){ //Student discount if available
        fprintf(receipt_file, "Student discount:%23.2f\n", total_price * STUDENT_DISCOUNT);
        student_discount = total_price * STUDENT_DISCOUNT;
    }
    if(total_price >= BIG_PURCHASE){ //big purchase discount if available
        fprintf(receipt_file, "Big purchase discount:%18.2f\n", total_price * BIG_PURCHASE_DISCOUNT);
        b_purchase_discount = total_price * BIG_PURCHASE_DISCOUNT;
    }
    fprintf(receipt_file,"----------------------------------------\n");
    fprintf(receipt_file, "Price:%34.2f\n", total_price - student_discount - b_purchase_discount); //discounted price
    fprintf(receipt_file, "Price + VAT:%28.2f\n", total_price * VAT_RATE_ADDED); //tax added price
    
    fclose(menu_file);
    fclose(receipt_file);
}
void print_receipt(){
    FILE *receipt;
    receipt = fopen("receipt.txt", "r");
    if(receipt == NULL){
        printf("Receipt file not found.\n");
        exit(1);
    }
    char c;
    while((c=fgetc(receipt)) != EOF){ //reading from the receipt.txt and print everything to the terminal
        printf(" %c", c);
    }
    fclose(receipt);
}
void food_ordering_assistance(){ //everything is in one function for conveniance
    print_menu();
    order_and_receipt();
    print_receipt();
}
//part1 end
//part2 start
void game_rps(){
    int user, computer;
    char run = 'Y';
    srand(time(NULL));
    printf("Welcome to rock, paper, scissors game!\n");
    while(run == 'Y'){ //run again until user press 'N' to stop
        printf("1-Rock 2-Paper 3-Scissors\n");
        scanf(" %d",&user);//user choice
        printf("You chose ");
        switch(user){//print what the user choose
            case 1:
                printf("Stone");
                break;
            case 2:
                printf("Paper");
                break;
            case 3:
                printf("Scissors");
                break;
            default:
                printf("Invalid choice");
                break;
        }
        computer = rand()%3+1; //copmuters random choice
        printf(". I chose ");
        switch(computer){//print what the computer choose
            case 1:
                printf("Stone");
                break;
            case 2:
                printf("Paper");
                break;
            case 3:
                printf("Scissors");
                break;
            default:
                printf("Invalid choice");
                break;
        }
        if(user==computer){//print endings of the game using if else statements
            printf(". It's a tie!\n");
        }
        else if((computer==1 && user==3)||(computer==2 && user==1)||(computer==3 && user==2)){
            printf(". You lost!\n");
        }
        else{
            printf(". You won!\n");
        }
        do{
            printf("Do you want to play again(Y/N):\n");
            scanf(" %c",&run);
            if(run!='Y' && run!='N'){
                printf("Error: Only options are Y(yes)/N(no)\n");//warn user to choose correctly
            }
        }while(run!='Y' && run!='N'); //make sure to user pick options available
    }
    printf("Goodbye!\n");
}
//part2 end