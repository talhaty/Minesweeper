// Assignment 1 20T1 COMP1511: Minesweeper
// minesweeper.c
//
// This program was written by YOUR-NAME-HERE (z5555555)
// on INSERT-DATE-HERE
//
// Version 1.0.0 (2020-03-08): Assignment released.
// Version 1.0.1 (2020-03-08): Fix punctuation in comment.
// Version 1.0.2 (2020-03-08): Fix second line of header comment to say minesweeper.c

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <cstring>
#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <time.h>

using namespace std;

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


bool checkWin(int minefield[SIZE][SIZE]){
    bool win = true;

    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            if(minefield[i][j] == HIDDEN_SAFE){
                win = false;
                return win;
            }
        }
    }
    return win;
}

bool checkLoss(int row, int col, int minefield[SIZE][SIZE]){
    if(minefield[row][col] == HIDDEN_MINE){
        return true;
    }
    return false;
}
void initialise_field(int minefield[SIZE][SIZE]){
    for(int i=0; i<SIZE; i++){
        for(int j=0; j<SIZE; j++){
            minefield[i][j] = HIDDEN_SAFE;
        }
    }
}

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

    

    if(row == 0 && col == 0){

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
    system("Color 04");
    cout<<"\n\n";
    for(int i=0; i<SIZE; i++){
        cout<<"\n\t\t\t";
        for(int j=0; j<SIZE; j++){
            cout<<minefield[i][j]<<"   ";
        }
    }
    cout<<"\n\n\n";
}

void print_gameplay_minefield(int minefield[SIZE][SIZE], bool Loss = false){
    system("Color 04");
    string Visible_Safe = "   ", Hidden_Safe = "## ";
    string array[8]={"00","01", "02", "03", "04", "05", "06", "07"};
    int Hidden_Mine=0;
    if(Loss == false){
        cout<<"\n\n";
        cout<<"\t\t\t\t\t.  ."
            <<"\n\t\t\t\t\t \\/\n\n";
    }
    else{
        cout<<"\n\n";
        cout<<"\t\t\t\t\t.  ."
            <<"\n\t\t\t\t\t /\\ \n\n";
    }
    cout<<endl<<"\t\t\t";
    cout<<"     00 01 02 03 04 05 06 07 \n\t\t\t"
        <<"     ----------------------- \n";
    for(int row=0; row<SIZE; row++){
        cout<<"\t\t\t"<<array[row]<<"  |";
            
        for(int col=0; col<SIZE; col++){
            if(minefield[row][col] == HIDDEN_SAFE)
                cout<<Hidden_Safe;
            else if(minefield[row][col] == VISIBLE_SAFE){
                cout<<Visible_Safe;
            }
            else{
             bool check =   adjacentMinesFromVisibleSafe(row, col, minefield);
                if (check){
            if(Hidden_Mine<10){
                cout<<'0'<<Hidden_Mine<<' ';
                Hidden_Mine++;
            }
            else{
                cout<<Hidden_Mine<<' ';
                Hidden_Mine++;
            }
        }

        else if(Loss == false){
            cout<<Hidden_Safe;
        }
        else if(Loss == true){
            cout<<"() ";
        }
            }
        }
        cout<<"|\n";
    }
}

int detectRow(int row, int minefield[SIZE][SIZE]){
    int rowMines=0;
    for(int i=0; i<SIZE; i++){
        if(minefield[row][i] == HIDDEN_MINE){
            rowMines++;
        }
    }
    return rowMines;
}

int detectColumn(int column, int minefield[SIZE][SIZE]){
    int columnMine = 0;
    for(int i=0; i<SIZE; i++){
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
    for(int i=0; i<SIZE; i++){  

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
    for(int i=0; i<SIZE; i++){  

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
    for(int i=0; i<SIZE; i++){  

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
    for(int i=0; i<SIZE; i++){  

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
    for(int i=0; i<SIZE; i++){  

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
    for(int i=0; i<SIZE; i++){  

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
    for(int i=0; i<SIZE; i++){  

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
    for(int i=0; i<SIZE; i++){  

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
    for(int col=0; col<SIZE; col++){
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
    cin>>totalMines;
    
    int** co_ordinates = new int*[totalMines];
    for (int i = 0; i < totalMines; i++) {
        co_ordinates[i] = new int[2];
    }
    
    // TODO: Scan in the number of pairs of mines.
    srand(time(0));
    
    for(int i=0; i<totalMines; i++){
        
        co_ordinates[i][0] = rand() % SIZE; co_ordinates[i][1] = rand()%SIZE;
    }

    for(int i=0; i<totalMines; i++){
        minefield[co_ordinates[i][0]][co_ordinates[i][1]] = HIDDEN_MINE;
    }
    // TODO: Scan in the pairs of mines and place them on the grid.

    cout<<"\nENTER GAME MODE(Debug('d')/ Gamepaly('g')): ";
    cin>>mode;

    printf("Game Started\n");
    if(mode == 'd')
        print_debug_minefield(minefield);
    else if(mode == 'g')
        print_gameplay_minefield(minefield);
    cout<<"\n\nVISIBLE_SAFE    0\t\tHIDDEN_SAFE     1\t\tHIDDEN_MINE     2\n"

            <<"\nDETECT_ROW              1"
            <<"\nDETECT_COL              2"
            <<"\nDETECT_SQUARE           3"
            <<"\nREVEAL_SQUARE           4"
            <<"\nGAMEPLAY_MODE           5"
            <<"\nDEBUG_MODE              6"
            <<"\nREVEAL_RADIAL           7\n";
    
    while(!(Win || Loss)){
        
        cout<<"\nENTER THE COMMAND FROM ABOVE\n";
        cin>>input;
        

        if(input == 1 || input == 2 || input==3){
            if(input==1 && help>0){
                cout<<"\nENTER ROW: ";
                cin>>row;
                mines = detectRow(row, minefield);
                cout<<"\nTOTAL MINES IN ROW #"<<row<<" ARE/IS "<<mines<<endl;
                help--;
                cout<<"\nREMAINING HINTS: "<<help<<endl;
            }

            else if(input == 2 && help>0){
                cout<<"\nENTER COLUMN: ";
                cin>>col;
                mines = detectColumn(col, minefield);
                cout<<"\nTOTAL MINES IN COLUMN #"<<col<<" ARE/IS "<<mines<<endl;
                help--;
                cout<<"\nREMAINING HINTS: "<<help<<endl;
            }

            else if(input == 3 && help >0){
                cout<<"\nENTER ROW: ";
                cin>>row;
                cout<<"\nENTER COLUMN: ";
                cin>>col;
                cout<<"\nENTER THE SIZE OF SQUARE: ";
                cin>>size;
                mines = detectSquare(row, col, size, minefield);
                cout<<"There are "<<mines<<" mine(s) in the square centered at row "<<row<<" , column "<<col<<" of size "<<size<<endl;
                help--;
                cout<<"\nREMAINING HINTS: "<<help<<endl;
            }

            else{
                cout<<"\nHELP ALREDY USED\n";
            }

        }

        else if(input == 4){
            cout<<"\nENTER ROW: ";
            cin>>row;
            cout<<"\nENTER COLUMN: ";
            cin>>col;
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
            if(mode == 'd')
                print_debug_minefield(minefield);
            else if(mode == 'g')
                print_gameplay_minefield(minefield);

            cout<<"\n\nVISIBLE_SAFE    0\t\tHIDDEN_SAFE     1\t\tHIDDEN_MINE     2\n"

            <<"\nDETECT_ROW              1"
            <<"\nDETECT_COL              2"
            <<"\nDETECT_SQUARE           3"
            <<"\nREVEAL_SQUARE           4"
            <<"\nGAMEPLAY_MODE           5"
            <<"\nDEBUG_MODE              6"
            <<"\nREVEAL_RADIAL           7\n";
        }

        else if(input == 5){
            mode = 'g';
            print_gameplay_minefield(minefield);
        }
        else if(input == 6){
            mode = 'd';
            print_debug_minefield(minefield);
        }

        else if(input == 7){
            cout<<"\nENTER ROW: ";
            cin>>row;
            cout<<"\nENTER COLUMN: ";
            cin>>col;
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
            if(mode == 'd')
                print_debug_minefield(minefield);
            else if(mode == 'g')
                print_gameplay_minefield(minefield);

            cout<<"\n\nVISIBLE_SAFE    0\t\tHIDDEN_SAFE     1\t\tHIDDEN_MINE     2\n"

            <<"\nDETECT_ROW              1"
            <<"\nDETECT_COL              2"
            <<"\nDETECT_SQUARE           3"
            <<"\nREVEAL_SQUARE           4"
            <<"\nGAMEPLAY_MODE           5"
            <<"\nDEBUG_MODE              6"
            <<"\nREVEAL_RADIAL           7\n";
        }
        else{
            cout<<"\nWRONG INPUT\n";
        }
    }

    if(Loss){
        print_gameplay_minefield(minefield, Loss);
        int i, j, k, rows=12;
    for(i = 1; i <= rows * 2 - 1; i++)
    {
        if(i != rows)
        {
            for(j = 1; j <= rows; j++)
            {
                if(j == rows)
                {
                    cout << "*";
                    Sleep(100);
                }
                cout << " ";
                
            }
        }
        else
        {
            for(k = 1; k <= rows * 2 - 1; k++)
            {
                cout << "*";
                Sleep(100);
            }
        }
        cout << "\n";
        
    }	
        cout<<"\n\n********BANG*********\n";
        cout<<"\n\n\nYOU LOST\n\n";
    }
    if(Win){
        print_gameplay_minefield(minefield);
        cout<<"\n\nHURRAY\n";
        cout<<"\nYOU WON\n";
    }

    system("pause");
    return 0;
}

