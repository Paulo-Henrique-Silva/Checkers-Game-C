#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define PLAYER1 'X'
#define PLAYER2 'O'
#define ISBLACK(i, j) ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))

int menu(void);
void playerVs_player(void);

void resetBoard(void);
void printsBoard(void);
int isA_validPiece(char pieceIn_board[], char playerSymbol); 
int isA_validMove(char input[], char pieceIn_board[], char playerSymbol);
void movePiece(char pieceInit_pos[], char pieceDesti_pos[]);
int isVictory(char winnerSymbol);

int isA_validBoard_space(char input[]);

char board[8][8] = {'\0'};

enum menuOptions {Pvp = 1, Exitprogram};

int main()
{
    int operation = 0;

    do
    {
      switch(operation = menu())  
      {
        case Pvp:
            playerVs_player();
            break;
        
        case Exitprogram:
            printf("\nExiting...");
            break;
      }

      getch(); //stops the program before closes it
    }
    while(operation != Exitprogram);

    return 0;
}

//Shows the game menu and gets the user input
int menu(void)
{
    char input[1024] = {'\0'};

    system("cls"); //cleans the screen
    printf("\n\t\t\t\t  CHECKERS GAME");
    printf("\n\n\t\t\t\t[1] - Play (Player vs Plaver)");
    printf("\n\t\t\t\t[2] - Exit");

    printf("\n\nType the Operation: ");
    fgets(input, 1024, stdin);

    return atoi(input); //gets as a str and returns as an integer
}

void playerVs_player(void)
{
    char 
    pieceIn_board[1024] = {'\0'},
    spaceTo_move[1024] = {'\0'};

    resetBoard();

    do
    {
        //reads until is a valid player piece
        while(1)
        {
            system("cls");
            printsBoard();

            printf("\n\nSelect a Piece: ");
            fgets(pieceIn_board, 1024, stdin);

            if(isA_validPiece(pieceIn_board, 'X') != 0)
                break; 
                
            printf("\nInvalid Input!");
            getch();   
        }

        while(1)
        {
            system("cls");
            printsBoard();
            
            printf("\n\nMove your Selected Piece: ");
            fgets(spaceTo_move, 1024, stdin);

            if(isA_validMove(pieceIn_board, spaceTo_move, 'X') != 0)
            {
                movePiece(pieceIn_board, spaceTo_move);
                break; 
            }

            printf("\nInvalid Input!");
            getch();   
        }
    }
    while(isVictory('X') == 0);

    printf("\nEND GAME!");
}

//resets the board if the correct pieces
void resetBoard(void)
{
    int i, j;

    //i and j are with +1 because is more easy to determinate if it is black
    //the black spaces are in houses with i and j equal to an odd num or an even num
    for(i = 8; i > 0; i--)
    {
        for(j = 1; j < 9; j++)
        {
            if(i > 5 && ISBLACK(i, j))
                board[i-1][j-1] = PLAYER2;
            else if(i < 4 && ISBLACK(i, j))
                 board[i-1][j-1] = PLAYER1;
            else
                board[i-1][j-1] = ' ';
        }
    }
}

//prints the board in screen with the line and rows counter
void printsBoard(void)
{
    int rowCounter = 8, rows, columns;

    for(rows = 7; rows >= 0; rows--)
    {
        printf("\n\t\t\t\t  +---+---+---+---+---+---+---+---+\n\t\t\t\t");

        printf("%d ", rowCounter--); //shows the numbers next to the board
        for(columns = 0; columns < 8; columns++) 
            printf("| %c ", board[rows][columns]);

        printf("|");
    }

    printf("\n\t\t\t\t  +---+---+---+---+---+---+---+---+");
    printf("\n\t\t\t\t    A   B   C   D   E   F   G   H  ");
}

//Checks if it's a valid player piece
int isA_validPiece(char pieceIn_board[], char playerSymbol)
{
    if(isA_validBoard_space(pieceIn_board) == 0) return 0;

    if(board[(pieceIn_board[1] - '0') - 1][pieceIn_board[0] - 65] != playerSymbol)
        return 0;

    return 1;
}

//checks if the piece can moves to that space in board
int isA_validMove(char pieceIn_board[], char placeTo_move[], char playerSymbol)
{
    if
    (
        isA_validBoard_space(placeTo_move) == 0 || 
        isA_validBoard_space(pieceIn_board) == 0
    ) 
        return 0;

    //checks if it is superior
    if((placeTo_move[1] - '0') != ((pieceIn_board[1] - '0') + 1)) 
        return 0; 

    //checks if it is in diagonals
    if
    (
        ((placeTo_move[0] - 65) != (pieceIn_board[0] - 65 + 1)) && 
        ((placeTo_move[0] - 65) != (pieceIn_board[0] - 65 - 1)) 
    ) 
        return 0; 

    return 1;
}

//Swamp in board to move the piece
void movePiece(char pieceInit_pos[], char pieceDesti_pos[])
{
    char 
    temp = '\0', initMatrix[3] = {'\0'}, 
    destiMatrix[3] = {'\0'};

    //converts to matrix form
    initMatrix[0] = pieceInit_pos[0] - 65;
    initMatrix[1] = pieceInit_pos[1] - '0' - 1;
    destiMatrix[0] = pieceDesti_pos[0] - 65;
    destiMatrix[1] = pieceDesti_pos[1] - '0' - 1;

    //swamp the spaces in board
    temp = board[initMatrix[1]][initMatrix[0]];
    board[initMatrix[1]][initMatrix[0]] = board[destiMatrix[1]][destiMatrix[0]];
    board[destiMatrix[1]][destiMatrix[0]] = temp;
}

//Checks if the game has ended
//if there is a least one piece of the other player, it means that the game has not ended
int isVictory(char winnerSymbol)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 9; j++)
        {
            if(board[i][j] != winnerSymbol && board[i][j] != ' ')
                return 0;
        }
    }

    return 1;
}

//Checks if the input is like: A3, C5, E7, etc.
int isA_validBoard_space(char input[])
{
    strupr(input);
    if(strchr(input, '\n') != NULL) input[strlen(input) - 1] = '\0';
    //remove last char and put in upper case

    if(strlen(input) != 2) 
        return 0; 
    else if(input[0] < 'A' || input[0] > 'H') 
        return 0;
    else if((input[1] - '0') < 1 || (input[1] - '0') > 8) 
        return 0;
    else 
        return 1;
    //the " - '0' " converts to an integer
}