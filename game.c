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
int isA_validPiece(char input[], char playerSymbol); 
int isA_validMove(char input[], char playerSymbol);
int isVictory(char winnerSymbol);

int isA_validInput(char input[]);

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
    char input[1024] = {'\0'};

    resetBoard();

    do
    {
        do 
        {
            system("cls");
            printsBoard();

            printf("\n\nSelect a Piece: ");
            fgets(input, 1024, stdin);

            if(isA_validPiece(input, 'X') == 0)
            {
                printf("\nInvalid Input!");
                getch();
            }
            else 
                break;
        }
        while(1);
        /*
        do 
        {
            system("cls");
            printsBoard();

            printf("\n\nSelect the Piece: ");
            fgets(input, 1024, stdin);

            if(isA_validPiece(input, 'X') == 0)
            {

            }
            else 
                break;
        }
        while(1);
        */
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
int isA_validPiece(char input[], char playerSymbol)
{
    input[strlen(input) - 1] = '\0'; 
    strupr(input);
    //remove \n in last char and puts in upper case

    if(isA_validInput(input) == 0) return 0;

    if(board[(input[1] - '0') - 1][input[0] - 65] != playerSymbol)
        return 0;

    return 1;
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

//Checks if it is a valid board input. Like: A2, B5, C4, etc.
int isA_validInput(char input[])
{
    if(strlen(input) != 2) return 0; 
    else if(input[0] < 'A' || input[0] > 'H') return 0;
    else if((input[1] - '0') < 1 || (input[1] - '0') > 8) return 0;
    else return 1;
    //the " - '0' " converts to an integer
}