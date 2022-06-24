// Assignment 1 20T1 COMP1511: Minesweeper
// minesweeper.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0 (2020-03-08): Assignment released.
// Version 1.0.1 (2020-03-08): Fix punctuation in comment.
// Version 1.0.2 (2020-03-08): Fix second line of header comment to say minesweeper.c

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>


// Possible square states.
#define VISIBLE_SAFE    0
#define HIDDEN_SAFE     1
#define HIDDEN_MINE     2

// The size of the starting grid.
#define SIZE 8

// The possible command codes.
#define DETECT_ROW              1
#define DETECT_COL              2
#define DETECT_SQUARE           3
#define REVEAL_SQUARE           4
#define GAMEPLAY_MODE           5
#define DEBUG_MODE              6
#define REVEAL_RADIAL           7


//Checks if all the places have been explored
bool checkWin(int minefield[SIZE][SIZE]){
    bool win = true;

    int i;
    int j;
    for(i=0; i<SIZE; i++){
        
        for(j=0; j<SIZE; j++){
            if(minefield[i][j] == HIDDEN_SAFE){
                win = false;
                return win;
            }
        }
    }
    return win;
}

//if user steps on a mine then he will lose
bool checkLoss(int row, int col, int minefield[SIZE][SIZE]){
    if(minefield[row][col] == HIDDEN_MINE){
        return true;
    }
    return false;
}

//initializes the minefield
void initialise_field(int minefield[SIZE][SIZE]){
    int i;
    int j;
    for(i=0; i<SIZE; i++){
        
        for(j=0; j<SIZE; j++){
            minefield[i][j] = HIDDEN_SAFE;
        }
    }
}

//This function is to check all the adjacent hidden mines from visible safe
bool adjacentMinesFromVisibleSafe(int row, int col, int minefield[SIZE][SIZE]){
    bool row7, row0, col0, col7, rc70, rc07, rc00, rc77;
    
    row7 = (minefield[row - 1][col] == VISIBLE_SAFE || minefield[row][col + 1] == VISIBLE_SAFE|| minefield[row][col - 1] == VISIBLE_SAFE ||
            minefield[row - 1][col + 1] == VISIBLE_SAFE ||minefield[row - 1][col - 1] == VISIBLE_SAFE);

    row0 = (minefield[row + 1][col] == VISIBLE_SAFE || minefield[row][col + 1] == VISIBLE_SAFE
        || minefield[row][col - 1] == VISIBLE_SAFE || minefield[row + 1][col + 1] == VISIBLE_SAFE || 
        minefield[row + 1][col - 1] == VISIBLE_SAFE );
    
    col0 = 
    (minefield[row + 1][col] == VISIBLE_SAFE || minefield[row - 1][col] == VISIBLE_SAFE 
    || minefield[row][col + 1] == VISIBLE_SAFE
     || minefield[row + 1][col + 1] == VISIBLE_SAFE || minefield[row - 1][col + 1] == VISIBLE_SAFE );
        
    col7 = 
    (minefield[row + 1][col] == VISIBLE_SAFE || minefield[row - 1][col] == VISIBLE_SAFE 
        || minefield[row][col - 1] == VISIBLE_SAFE  ||
        minefield[row + 1][col - 1] == VISIBLE_SAFE || minefield[row - 1][col - 1] == VISIBLE_SAFE);
    
    rc00 =  (minefield[row + 1][col] == VISIBLE_SAFE || minefield[row][col + 1] == VISIBLE_SAFE
        || minefield[row + 1][col + 1] == VISIBLE_SAFE );

    rc77 = ( minefield[row - 1][col] == VISIBLE_SAFE
        || minefield[row][col - 1] == VISIBLE_SAFE || minefield[row - 1][col - 1] == VISIBLE_SAFE);

    rc07 = (minefield[row + 1][col] == VISIBLE_SAFE 
        || minefield[row][col - 1] == VISIBLE_SAFE  || 
        minefield[row + 1][col - 1] == VISIBLE_SAFE );

    rc70 = (minefield[row - 1][col] == VISIBLE_SAFE || minefield[row][col + 1] == VISIBLE_SAFE||
        minefield[row - 1][col + 1] == VISIBLE_SAFE );

    

    if((row == 0) && (col == 0)){

        return rc00;
    }
    else if(row==0 && col==7){

        return rc07;
    }
    else if(row == 7 && col ==0){

        return rc70;
    }
    else if(row == 7 && col == 7){

        return rc77;
    }
    else if(row == 0){

        return row0;
    }
    else if(row==7){
          
        return row7;
    }
    else if(col == 0){
          
        return col0;
    }
    else if(col==7){
          
        return col7;
    }
    else if(row>0 && row<7 && col>0 && col<7){
     if (minefield[row + 1][col] == VISIBLE_SAFE || minefield[row - 1][col] == VISIBLE_SAFE || minefield[row][col + 1] == VISIBLE_SAFE
        || minefield[row][col - 1] == VISIBLE_SAFE || minefield[row + 1][col + 1] == VISIBLE_SAFE || minefield[row - 1][col + 1] == VISIBLE_SAFE ||
        minefield[row + 1][col - 1] == VISIBLE_SAFE || minefield[row - 1][col - 1] == VISIBLE_SAFE) {
       return true;
    }
    }
    return false;
}


void print_debug_minefield(int minefield[SIZE][SIZE]){
    // printf("\n\n");
    int i;
    int j;
    for(i=0; i<SIZE; i++){
        printf("\n\t\t\t");
        
        for(j=0; j<SIZE; j++){
            printf("%d", minefield[i][j]);
            printf("   ");
        }
    }
    printf("\n\n\n");
}

void print_gameplay_minefield(int minefield[SIZE][SIZE], bool Loss){
    char Visible_Safe[] = "   ", Hidden_Safe[] = "## ";
    char array[][3]={"00","01", "02", "03", "04", "05", "06", "07"};
    int Hidden_Mine=0;
    if(Loss == false){
        printf("\n\n");
        printf("\t\t\t\t\t.  .");
        printf("\n\t\t\t\t\t \\/\n\n");
    }
    else{
        printf("\n\n");
        printf("\t\t\t\t\t.  .");
        printf("\n\t\t\t\t\t /\\ \n\n");
    }
    printf("\n\t\t\t");
    printf("     00 01 02 03 04 05 06 07 \n\t\t\t");
    printf("     ----------------------- \n");
    int row;
    int col;  
    for(row=0; row<SIZE; row++){
        printf("\t\t\t%s",array[row]);
        printf("  |");
          
        for(col=0; col<SIZE; col++){
            if(minefield[row][col] == HIDDEN_SAFE)
                printf("%s",Hidden_Safe);
            else if(minefield[row][col] == VISIBLE_SAFE){
                printf("%s",Visible_Safe);
            }
            else{
             bool check =   adjacentMinesFromVisibleSafe(row, col, minefield);
                if (check){
            if(Hidden_Mine<10){
                printf("0%d",Hidden_Mine);
                printf(" ");
                Hidden_Mine++;
            }
            else{
                printf("%d",Hidden_Mine);
                printf(" ");
                Hidden_Mine++;
            }
        }

        else if(Loss == false){
            printf("%s",Hidden_Safe);
        }
        else if(Loss == true){
            printf("() ");
        }
            }
        }
        printf("|\n");
    }
}

int detectRow(int row, int minefield[SIZE][SIZE]){
    int rowMines=0;
    int i;
    for(i=0; i<SIZE; i++){
        if(minefield[row][i] == HIDDEN_MINE){
            rowMines++;
        }
    }
    return rowMines;
}

int detectColumn(int column, int minefield[SIZE][SIZE]){
    int columnMine = 0;
    int i;
    for( i=0; i<SIZE; i++){
        if(minefield[i][column] == HIDDEN_MINE){
            columnMine++;
        }
    }
    return columnMine;
}

int detectSquare(int row, int col, const int size, int minefield[SIZE][SIZE]){
    int mines=0;
    int COL = col;
    int ROW = row;

    row = ROW-(size-1)/2;
    col = COL-(size-1)/2;
    if(row<0 || col < 0){
        if(row<0)
            row =0;

        if(col<0)
            col=0;
    }
    for(; row<ROW+size-1; row++){
        for(col = COL-(size-1)/2; col<COL+size-1; col++){
            if(minefield[row][col] == HIDDEN_MINE){
                mines++;
            }
        }
    }
    return mines;
}

bool adjacentMines(int row, int col, int minefield[SIZE][SIZE]){
    bool row7, row0, col0, col7, rc70, rc07, rc00, rc77;
    
    row7 = (minefield[row - 1][col] == HIDDEN_MINE || minefield[row][col + 1] == HIDDEN_MINE|| minefield[row][col - 1] == HIDDEN_MINE ||
            minefield[row - 1][col + 1] == HIDDEN_MINE ||minefield[row - 1][col - 1] == HIDDEN_MINE);

    row0 = (minefield[row + 1][col] == HIDDEN_MINE || minefield[row][col + 1] == HIDDEN_MINE
        || minefield[row][col - 1] == HIDDEN_MINE || minefield[row + 1][col + 1] == HIDDEN_MINE || 
        minefield[row + 1][col - 1] == HIDDEN_MINE );
    
    col0 = 
    (minefield[row + 1][col] == HIDDEN_MINE || minefield[row - 1][col] == HIDDEN_MINE 
    || minefield[row][col + 1] == HIDDEN_MINE
     || minefield[row + 1][col + 1] == HIDDEN_MINE || minefield[row - 1][col + 1] == HIDDEN_MINE );
        
    col7 = 
    (minefield[row + 1][col] == HIDDEN_MINE || minefield[row - 1][col] == HIDDEN_MINE 
        || minefield[row][col - 1] == HIDDEN_MINE  ||
        minefield[row + 1][col - 1] == HIDDEN_MINE || minefield[row - 1][col - 1] == HIDDEN_MINE);
    
    rc00 =  (minefield[row + 1][col] == HIDDEN_MINE || minefield[row][col + 1] == HIDDEN_MINE
        || minefield[row + 1][col + 1] == HIDDEN_MINE );

    rc77 = ( minefield[row - 1][col] == HIDDEN_MINE
        || minefield[row][col - 1] == HIDDEN_MINE || minefield[row - 1][col - 1] == HIDDEN_MINE);

    rc07 = (minefield[row + 1][col] == HIDDEN_MINE 
        || minefield[row][col - 1] == HIDDEN_MINE  || 
        minefield[row + 1][col - 1] == HIDDEN_MINE );

    rc70 = (minefield[row - 1][col] == HIDDEN_MINE || minefield[row][col + 1] == HIDDEN_MINE||
        minefield[row - 1][col + 1] == HIDDEN_MINE );

    

    if(row == 0 && col == 0){
        if(rc00 == true)
            minefield[row][col] = VISIBLE_SAFE;
        return rc00;
    }
    else if(row==0 && col==7){
        if(rc07 == true)
            minefield[row][col] = VISIBLE_SAFE;
        return rc07;
    }
    else if(row == 7 && col ==0){
        if(rc70 == true)
            minefield[row][col] = VISIBLE_SAFE;
        return rc70;
    }
    else if(row == 7 && col == 7){
        if(rc77 == true)
            minefield[row][col] = VISIBLE_SAFE;
        return rc77;
    }
    else if(row == 0){
        if(row0 == true)
            minefield[row][col] = VISIBLE_SAFE;
        return row0;
    }
    else if(row==7){
        if(row7 == true)
            minefield[row][col] = VISIBLE_SAFE;
        return row7;
    }
    else if(col == 0){
        if(col0 == true)
            minefield[row][col] = VISIBLE_SAFE;
        return col0;
    }
    else if(col==7){
        if(col7 == true)
            minefield[row][col] = VISIBLE_SAFE;
        return col7;
    }
    else if(row>0 && row<7 && col>0 && col<7){
     if (minefield[row + 1][col] == HIDDEN_MINE || minefield[row - 1][col] == HIDDEN_MINE || minefield[row][col + 1] == HIDDEN_MINE
        || minefield[row][col - 1] == HIDDEN_MINE || minefield[row + 1][col + 1] == HIDDEN_MINE || minefield[row - 1][col + 1] == HIDDEN_MINE ||
        minefield[row + 1][col - 1] == HIDDEN_MINE || minefield[row - 1][col - 1] == HIDDEN_MINE) {
        minefield[row][col] = VISIBLE_SAFE; return true;
    }
    }
    return false;
}
void revealSquare(int row, int col, int minefield[SIZE][SIZE]){
    int size = 3;
    int COL = col;
    int ROW = row;


    bool check = adjacentMines(row, col, minefield);
    if(check==true)
        return;

    if(minefield[row][col] == VISIBLE_SAFE) return;

    row = ROW-(size-1)/2;
    col = COL-(size-1)/2;
    if(row<0 || col < 0){
        if(row<0)
            row =0;

        if(col<0)
            col=0;
    }
    for(; row<ROW+size-1; row++){
        for(col = COL-(size-1)/2; col<COL+size-1; col++){
            if(minefield[row][col] == HIDDEN_SAFE){
                minefield[row][col] = VISIBLE_SAFE;
            }
        }
    }
}


void revealRadial(int row, int col, int minefield[SIZE][SIZE]){
    int ROW = row, COL= col;

    if(minefield[row][col] == VISIBLE_SAFE) return;
    bool check=false;
    int i;
    for( i=0; i<SIZE; i++){  

        if(row<0 || col < 0 || row>=SIZE || col>=SIZE){
            break;
        }
        check = adjacentMines(row, col, minefield);
        if(check){
            break;
        }
        minefield[row][col] = VISIBLE_SAFE;
        row++;col++;
    }
    
    check = false;
    row=ROW; col = COL;
    
    for(i=0; i<SIZE; i++){  

        if(row<0 || col < 0 || row>=SIZE || col>=SIZE){
            break;
        }
        check = adjacentMines(row, col, minefield);
        if(check){
            break;
        }
        minefield[row][col] = VISIBLE_SAFE;
        row++;
    }

    check = false;
    row=ROW; col = COL;

    for(i=0; i<SIZE; i++){  

        if(row<0 || col < 0 || row>=SIZE || col>=SIZE){
            break;
        }
        check = adjacentMines(row, col, minefield);
        if(check){
            break;
        }
        minefield[row][col] = VISIBLE_SAFE;
        row++;col--;
    }

    check = false;
    row=ROW; col = COL;
    for(i=0; i<SIZE; i++){  

        if(row<0 || col < 0 || row>=SIZE || col>=SIZE){
            break;
        }
        check = adjacentMines(row, col, minefield);
        if(check){
            break;
        }
        minefield[row][col] = VISIBLE_SAFE;
        col--;
    }

    check = false;
    row=ROW; col = COL;
    for(i=0; i<SIZE; i++){  

        if(row<0 || col < 0 || row>=SIZE || col>=SIZE){
            break;
        }
        check = adjacentMines(row, col, minefield);
        if(check){
            break;
        }
        minefield[row][col] = VISIBLE_SAFE;
        row--;col--;
    }

    check = false;
    row=ROW; col = COL;
    for( i=0; i<SIZE; i++){  

        if(row<0 || col < 0 || row>=SIZE || col>=SIZE){
            break;
        }
        check = adjacentMines(row, col, minefield);
        if(check){
            break;
        }
        minefield[row][col] = VISIBLE_SAFE;
        row--;
    }

    check = false;
    row=ROW; col = COL;
    for(i=0; i<SIZE; i++){  

        if(row<0 || col < 0 || row>=SIZE || col>=SIZE){
            break;
        }
        check = adjacentMines(row, col, minefield);
        if(check){
            break;
        }
        minefield[row][col] = VISIBLE_SAFE;
        row--;col++;
    }

    check = false;
    row=ROW; col = COL;
    for(i=0; i<SIZE; i++){  

        if(row<0 || col < 0 || row>=SIZE || col>=SIZE){
            break;
        }
        check = adjacentMines(row, col, minefield);
        if(check){
            break;
        }
        minefield[row][col] = VISIBLE_SAFE;
        col++;
    }
}


void reverseArray(int minefield[SIZE][SIZE])
{
    int col;
    for(col=0; col<SIZE; col++){
    int i=SIZE-1;
    int j=i-1;
    int temp=minefield[SIZE-1][col];
    while(j>=0 && i>=0){
        minefield[i][col]=minefield[j][col];
        j--;
        i--;
            }
        minefield[i][col]=temp;
    }
}

void First_click(int row, int col, int minefield[SIZE][SIZE]){
    if(minefield[row][col] == HIDDEN_MINE){
        reverseArray(minefield);
    }
    else{
        return;
    }
}



int main(void) {
    int totalMines; 
    bool Loss = false, Win = false;
    int help=3, row, col, size, mines;
    int input;
    int minefield[SIZE][SIZE];
    char mode='d';
    int firstClick=0;
    initialise_field(minefield);
    printf("Welcome to minesweeper!\n");
    printf("How many mines? ");
    scanf("%d", &totalMines);
    printf("Enter pairs:\n");
    
    

    int** co_ordinates = (int**)malloc(totalMines * sizeof(int*));
    int i;
    for (i = 0; i < totalMines; i++){
        co_ordinates[i] = (int*)malloc(2 * sizeof(int));
    }
    
    // TODO: Scan in the number of pairs of mines.
    srand(time(0));
    
    for(i=0; i<totalMines; i++){
        
        scanf("%d", &co_ordinates[i][0]);//= rand() % SIZE;
        scanf("%d", &co_ordinates[i][1]);//= rand()%SIZE;
    }

    for(i=0; i<totalMines; i++){
        minefield[co_ordinates[i][0]][co_ordinates[i][1]] = HIDDEN_MINE;
    }
    // TODO: Scan in the pairs of mines and place them on the grid.

    // printf("\nENTER GAME MODE(Debug('d')/ Gamepaly('g')): ");
    // scanf("%s",&mode);


    printf("Game Started\n");  
    while(!(Win || Loss)){
        if(mode == 'd')
            print_debug_minefield(minefield);
        else if(mode == 'g')
            print_gameplay_minefield(minefield, false);
    
    printf("\n\nVISIBLE_SAFE    0\t\tHIDDEN_SAFE     1\t\tHIDDEN_MINE     2\n");

        printf("\nDETECT_ROW              1");
        printf("\nDETECT_COL              2");
        printf("\nDETECT_SQUARE           3");
        printf("\nREVEAL_SQUARE           4");
        printf("\nGAMEPLAY_MODE           5");
        printf("\nDEBUG_MODE              6");
        printf("\nREVEAL_RADIAL           7\n");
        printf("\nENTER THE COMMAND FROM ABOVE\n");
        scanf("%d", &input);
        

        if(input == 1 || input == 2 || input==3){
            if(input==1 && help>0){
                printf("\nENTER ROW: ");
                scanf("%d", &row);
                mines = detectRow(row, minefield);
                printf("\nTOTAL MINES IN ROW #%d",row);
                printf(" ARE/IS %d",mines);
                printf("\n");
                help--;
                printf("\nREMAINING HINTS: %d",help);
                printf("\n");
            }

            else if(input == 2 && help>0){
                printf("\nENTER COLUMN: ");
                scanf("%d", &col);
                mines = detectColumn(col, minefield);
                printf("\nTOTAL MINES IN COLUMN #%d",col);
                printf(" ARE/IS %d",mines);
                printf("\n");
                help--;
                printf("\nREMAINING HINTS: %d",help);
                printf("\n");
            }

            else if(input == 3 && help >0){
                printf("\nENTER ROW: ");
                scanf("%d", &row);

                printf("\nENTER COLUMN: ");
                scanf("%d", &col);
                printf("\nENTER THE SIZE OF SQUARE: ");
                scanf("%d", &size);
                mines = detectSquare(row, col, size, minefield);
                printf("There are %d",mines);
                printf(" mine(s) in the square centered at row %d",row);
                printf(" , column %d",col);
                printf(" of size %d",size);
                printf("\n");
                help--;
                printf("\nREMAINING HINTS: %d",help);
                printf("\n");
            }

            else{
                printf("\nHELP ALREDY USED\n");
            }

        }

        else if(input == 4){
            printf("\nENTER ROW: ");
            scanf("%d", &row);
            printf("\nENTER COLUMN: ");
            scanf("%d", &col);
            if(firstClick==0){
                First_click(row, col, minefield);
            }
            firstClick++;
            Loss = checkLoss(row, col, minefield);
            if(Loss){
                break;
            }
            revealSquare(row, col, minefield);
            Win = checkWin(minefield);
            if(Win){
                break;
            }

        }

        else if(input == 5){
            mode = 'g';
        }
        else if(input == 6){
            mode = 'd';
        }

        else if(input == 7){
            printf("\nENTER ROW: ");
            scanf("%d", &row);
            printf("\nENTER COLUMN: ");
            scanf("%d", &col);
            if(firstClick==0){
                First_click(row, col, minefield);
            }
            firstClick++;
            Loss = checkLoss(row, col, minefield);
            if(Loss){
                break;
            }

            revealRadial(row, col, minefield);
            Win = checkWin(minefield);
            if(Win)
                break;
        }
        else{
            printf("\nWRONG INPUT\n");
        }
    }

    if(Loss){
        print_gameplay_minefield(minefield, Loss);
        int j, k, rows=12;
    for(i = 1; i <= rows * 2 - 1; i++)
    {
        if(i != rows)
        {
            for(j = 1; j <= rows; j++)
            {
                if(j == rows)
                {
                    printf("*");
                }
                printf(" ");
                
            }
        }
        else
        {
            for(k = 1; k <= rows * 2 - 1; k++)
            {
                printf("*");
            }
        }
        printf("\n");
        
    }	
        printf("\n\n********BANG*********\n");
        printf("\n\n\nYOU LOST\n\n");
    }
    if(Win){
        print_gameplay_minefield(minefield, false);
        printf("\n\nHURRAY\n");
        printf("\nYOU WON\n");
    }

    return 0;
}

