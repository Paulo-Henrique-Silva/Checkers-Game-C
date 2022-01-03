#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

#define PLAYER1 'X'
#define PLAYER2 'O'

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

    //reset the board array
    for(j = 0; j < 8; j++)
    {
        for(i = 0; i < 8; i++)
            board[i][j] = ' ';
    }
}

//prints the board in screen with the line and rows counter
void printsBoard(void)
{
    int rowCounter = 8, lineCounter = 1,
    i, j;

    for(j = 7; j >= 0; j--)
    {
        printf("\n\t\t\t  +---+---+---+---+---+---+---+---+\n\t\t\t");
        printf("%d ", rowCounter--);

        for(i = 7; i >= 0; i--) printf("| %c ", board[i][j]);

        printf("|");
    }

    printf("\n\t\t\t  +---+---+---+---+---+---+---+---+\n\t\t\t ");
    for(lineCounter = 1; lineCounter < 9; lineCounter++) printf("   %d", lineCounter);
}