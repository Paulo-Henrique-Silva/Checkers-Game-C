#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define PLAYER1 'x'
#define PLAYER2 'o'
#define ISBLACK(i, j) ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))

int menu(void);
void playerVs_player(void);

void resetBoard(void);
void printsBoard(void);
int isA_validPiece(char pieceIn_board[], char playerSymbol); 
int isA_validMove(char posIn_board[], char posTo_move[], char playerSymbol);
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
    playerTurn_symb = '\0',
    pieceIn_board[1024] = {'\0'},
    posTo_move[1024] = {'\0'};

    resetBoard();

    do
    {
        //changes players turns
        //starts with player1
        if(playerTurn_symb == PLAYER1)
            playerTurn_symb = PLAYER2;
        else
            playerTurn_symb = PLAYER1;

        //reads until is a valid player piece
        while(1)
        {
            system("cls");
            printsBoard();
            
            //printf("\n\nTEST = %d", board[2][8]);
            printf("\n\nPlayer %c", playerTurn_symb);
            printf("\nSelect a Piece: ");
            fgets(pieceIn_board, 1024, stdin);

            if(isA_validPiece(pieceIn_board, playerTurn_symb) != 0)
                break; 
                
            printf("\nInvalid Input!");
            getch();   
        }

        while(1)
        {
            system("cls");
            printsBoard();
            
            printf("\n\nMove your Selected Piece: ");
            fgets(posTo_move, 1024, stdin);

            if(isA_validMove(pieceIn_board, posTo_move, playerTurn_symb) != 0)
                break; 

            printf("\nInvalid Input!");
            getch();   
        }
    }
    while(isVictory(playerTurn_symb) == 0);

    system("cls");
    printsBoard();
    printf("\n\nEND GAME!");
    printf("\nPlayer '%c' Wins!", playerTurn_symb);
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
    char posIn_board[3] = {'\0'};

    if(isA_validBoard_space(pieceIn_board) == 0) return 0;
    
    //converts to matriz form, that is
    //A3 -> (2,0)
    posIn_board[0] = pieceIn_board[0] - 65;
    posIn_board[1] = pieceIn_board[1] - '0' - 1;

    if(board[posIn_board[1]][posIn_board[0]] != playerSymbol)
        return 0;

    //checks if the piece is blocked
    if 
    (
        playerSymbol == PLAYER1 && 

        //if it is not blocked by a board wall or a piece(right)
        ((board[posIn_board[1] + 1][posIn_board[0] + 1] == ' ' &&
        (posIn_board[0] + 1) >= 0 && (posIn_board[0] + 1) <= 7) ||
        
        //if it is not blocked by a board wall or a piece(left)
        (board[posIn_board[1] + 1][posIn_board[0] - 1] == ' ' &&
        (posIn_board[0] - 1) >= 0 && (posIn_board[0] - 1) <= 7) ||

        //if it cans get an enemies piece to move(right)
        (board[posIn_board[1] + 1][posIn_board[0] + 1] == PLAYER2 &&
        board[posIn_board[1] + 2][posIn_board[0] + 2] == ' ') ||
        
        //if it cans get an enemies piece to move(left)
        (board[posIn_board[1] + 1][posIn_board[0] - 1] == PLAYER2 &&
        board[posIn_board[1] + 2][posIn_board[0] - 2] == ' '))
    )
        return 1;

    if //same logic, for player2
    (
        playerSymbol == PLAYER2 &&

        ((board[posIn_board[1] - 1][posIn_board[0] + 1] == ' ' && 
        (posIn_board[0] + 1) >= 0 && (posIn_board[0] + 1) <= 7) ||

        (board[posIn_board[1] - 1][posIn_board[0] - 1] == ' ' &&
        (posIn_board[0] - 1) >= 0 && (posIn_board[0] - 1) <= 7) ||

        (board[posIn_board[1] - 1][posIn_board[0] + 1] == PLAYER1 &&
        board[posIn_board[1] - 2][posIn_board[0] + 2] == ' ') ||

        (board[posIn_board[1] - 1][posIn_board[0] - 1] == PLAYER1 &&
        board[posIn_board[1] - 2][posIn_board[0] - 2] == ' '))
    )
        return 1;

    //if any case matches, it means that the piece is blocked
    return 0;
}

//Checks if the piece can moves to that space in board
//if it can, moves the piece
int isA_validMove(char posIn_board[], char posTo_move[], char playerSymbol)
{
    char 
    initPos[3] = {'\0'}, 
    destiPos[3] = {'\0'};

    if
    (
        isA_validBoard_space(posTo_move) == 0 || 
        isA_validBoard_space(posIn_board) == 0
    ) 
        return 0;

    //converts to matrix form
    initPos[0] = posIn_board[0] - 65;
    initPos[1] = posIn_board[1] - '0' - 1;
    destiPos[0] = posTo_move[0] - 65;
    destiPos[1] = posTo_move[1] - '0' - 1;

    //if it is not empty 
    if(board[destiPos[1]][destiPos[0]] != ' ')
        return 0;
    
    if(playerSymbol == PLAYER1)
    {
        if //if the player can get an enemies piece(right)
        (
            destiPos[0] == initPos[0] + 2 && destiPos[1] == initPos[1] + 2 
            && board[initPos[1] + 1][initPos[0] + 1] == PLAYER2  
        )
        {
            board[destiPos[1]][destiPos[0]] = PLAYER1;
            board[initPos[1]][initPos[0]] = ' ';
            board[initPos[1] + 1][initPos[0] + 1] = ' ';
            return 1;
        }
        else if //if the player can get enemie's piece(left)
        (
            destiPos[0] == initPos[0] - 2 && destiPos[1] == initPos[1] + 2 && 
            board[initPos[1] + 1][initPos[0] - 1] == PLAYER2
        )
        {
            board[destiPos[1]][destiPos[0]] = PLAYER1;
            board[initPos[1]][initPos[0]] = ' ';
            board[initPos[1] + 1][initPos[0] - 1] = ' ';
            return 1;
        }
        else if //just move, left or right
        (
            (destiPos[0] == initPos[0] + 1 && destiPos[1] == initPos[1] + 1) ||
            (destiPos[0] == initPos[0] - 1 && destiPos[1] == initPos[1] + 1) 
        )
        {
            board[destiPos[1]][destiPos[0]] = PLAYER1;
            board[initPos[1]][initPos[0]] = ' ';
            return 1;
        }
    }
    else //player2 - same logic
    {
        if
        (
            destiPos[0] == initPos[0] + 2 && destiPos[1] == initPos[1] - 2 
            && board[initPos[1] - 1][initPos[0] + 1] == PLAYER1  
        )
        {
            board[destiPos[1]][destiPos[0]] = PLAYER2;
            board[initPos[1]][initPos[0]] = ' ';
            board[initPos[1] - 1][initPos[0] + 1] = ' ';
            return 1;
        }
        else if
        (
            destiPos[0] == initPos[0] - 2 && destiPos[1] == initPos[1] - 2 && 
            board[initPos[1] - 1][initPos[0] - 1] == PLAYER1
        )
        {
            board[destiPos[1]][destiPos[0]] = PLAYER2;
            board[initPos[1]][initPos[0]] = ' ';
            board[initPos[1] - 1][initPos[0] - 1] = ' ';
            return 1;
        }
        else if
        (
            (destiPos[0] == initPos[0] + 1 && destiPos[1] == initPos[1] - 1) ||
            (destiPos[0] == initPos[0] - 1 && destiPos[1] == initPos[1] - 1) 
        )
        {
            board[destiPos[1]][destiPos[0]] = PLAYER2;
            board[initPos[1]][initPos[0]] = ' ';
            return 1;
        }
    }

    //if any case matches, it means that it is not a valid move
    return 0;
}

//Checks if the game has ended
//if there is a least one piece of the other player, it means that the game has not ended
int isVictory(char winnerSymbol)
{
    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
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
    //remove last char \n(if it has it) and put in upper case

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