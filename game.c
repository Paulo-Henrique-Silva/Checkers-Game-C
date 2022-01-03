#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define PLAYER1 'X'
#define PLAYER2 'O'
#define ISBLACK(i, j) ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))

int menu(void);
void playerVs_player(void);

void resetBoard(void);
void printsBoard(void);

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
    system("cls");
    resetBoard();
    printsBoard();
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