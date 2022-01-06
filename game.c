#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

#define PLAYER1_MEN 'x'
#define PLAYER2_MEN 'o'
#define PLAYER1_KING 'X'
#define PLAYER2_KING 'O'
#define ISBLACK(i, j) ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))

/* 
- Positions in board to understand the preprocessors

    |UPR_2ND_LT|          |   |          |UPR_2ND_RT|
    |          |UPR_1ST_LT|   |UPR_1ST_RT|          |
    |          |          |pos|          |          |
    |          |LWR_1ST_LT|   |LWR_1ST_RT|          |
    |LWR_2ND_LT|          |   |          |LWR_2ND_RT|

 -Returns a value in board based in a position
*/

#define UPR_1ST_RT_VAL(pos) (board[pos[1] + 1][pos[0] + 1])
#define UPR_2ND_RT_VAL(pos) (board[pos[1] + 2][pos[0] + 2])
#define UPR_1ST_LT_VAL(pos) (board[pos[1] + 1][pos[0] - 1])
#define UPR_2ND_LT_VAL(pos) (board[pos[1] + 2][pos[0] - 2])

#define LWR_1ST_RT_VAL(pos) (board[pos[1] - 1][pos[0] + 1])
#define LWR_2ND_RT_VAL(pos) (board[pos[1] - 2][pos[0] + 2])
#define LWR_1ST_LT_VAL(pos) (board[pos[1] - 1][pos[0] - 1])
#define LWR_2ND_LT_VAL(pos) (board[pos[1] - 2][pos[0] - 2])

//returns if the position is in that space in board, based in other pos
#define IS_IN_UPR_1ST_RT(pos, pos_cmp) ((pos_cmp[1] == pos[1] + 1) && (pos_cmp[0] == pos[0] + 1))
#define IS_IN_UPR_2ND_RT(pos, pos_cmp) ((pos_cmp[1] == pos[1] + 2) && (pos_cmp[0] == pos[0] + 2))
#define IS_IN_UPR_1ST_LT(pos, pos_cmp) ((pos_cmp[1] == pos[1] + 1) && (pos_cmp[0] == pos[0] - 1))
#define IS_IN_UPR_2ND_LT(pos, pos_cmp) ((pos_cmp[1] == pos[1] + 2) && (pos_cmp[0] == pos[0] - 2))

#define IS_IN_LWR_1ST_RT(pos, pos_cmp) ((pos_cmp[1] == pos[1] - 1) && (pos_cmp[0] == pos[0] + 1))
#define IS_IN_LWR_2ND_RT(pos, pos_cmp) ((pos_cmp[1] == pos[1] - 2) && (pos_cmp[0] == pos[0] + 2))
#define IS_IN_LWR_1ST_LT(pos, pos_cmp) ((pos_cmp[1] == pos[1] - 1) && (pos_cmp[0] == pos[0] - 1))
#define IS_IN_LWR_2ND_LT(pos, pos_cmp) ((pos_cmp[1] == pos[1] - 2) && (pos_cmp[0] == pos[0] - 2))

/*
    WALL
     |
     |
     | X | <- The program interpers like an empty space, but it is out game board
  pos|
     |

- Therefore, this prepocessors says to program to not consider the space, if returns false
*/
#define IS_IN_BOARD(posI, posJ) ((posI >= 0 && posI <= 7) && (posJ >= 0 && posJ <= 7))

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
        //starts with player1_MEN
        playerTurn_symb = (playerTurn_symb == PLAYER1_MEN) ? PLAYER2_MEN : PLAYER1_MEN;

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
            
            printf("\n\nPlayer %c", playerTurn_symb);
            printf("\nMove your Selected Piece: ");
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
    printf("\nPLAYER '%c' WINS!", playerTurn_symb);
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
                board[i-1][j-1] = PLAYER2_MEN;
            else if(i < 4 && ISBLACK(i, j))
                 board[i-1][j-1] = PLAYER1_MEN;
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
    switch(playerSymbol)
    {
        case PLAYER1_MEN:
            if 
            (
                //if it is not blocked by a board wall or a piece(right)
                (UPR_1ST_RT_VAL(posIn_board) == ' ' && 
                IS_IN_BOARD(posIn_board[1] + 1, posIn_board[0] + 1)) ||
                
                //if it is not blocked by a board wall or a piece(left)
                (UPR_1ST_LT_VAL(posIn_board) == ' ' &&
                IS_IN_BOARD(posIn_board[1] + 1, posIn_board[0] - 1)) ||

                //if it cans get an enemies piece to move(right)
                (UPR_1ST_RT_VAL(posIn_board) == PLAYER2_MEN && UPR_2ND_RT_VAL(posIn_board) == ' ' && 
                IS_IN_BOARD(posIn_board[1] + 2, posIn_board[0] + 2)) ||
                
                //if it cans get an enemies piece to move(left)
                (UPR_1ST_LT_VAL(posIn_board) == PLAYER2_MEN && UPR_2ND_LT_VAL(posIn_board) == ' ' &&
                IS_IN_BOARD(posIn_board[1] + 2, posIn_board[0] - 2))
            )
                return 1;
            
            return 0; //if any case matches, it means that it is not a valid piece
        
        case PLAYER2_MEN: //same logic, for player2_MEN
            if 
            (
                (LWR_1ST_RT_VAL(posIn_board) == ' ' && 
                IS_IN_BOARD(posIn_board[1] - 1, posIn_board[0] + 1)) ||

                (LWR_1ST_LT_VAL(posIn_board) == ' ' && 
                IS_IN_BOARD(posIn_board[1] - 1, posIn_board[0] - 1)) ||

                (LWR_1ST_RT_VAL(posIn_board) == PLAYER1_MEN && LWR_2ND_RT_VAL(posIn_board) == ' ' &&
                IS_IN_BOARD(posIn_board[1] - 2, posIn_board[0] + 2)) ||

                (LWR_1ST_LT_VAL(posIn_board) == PLAYER1_MEN && LWR_2ND_LT_VAL(posIn_board) == ' ' &&
                IS_IN_BOARD(posIn_board[1] - 2, posIn_board[0] - 2))
            )
                return 1;
           
            return 0;
    }
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

    switch(playerSymbol)
    {
        case PLAYER1_MEN:

            //if the player can get an enemies piece(right)
            if(IS_IN_UPR_2ND_RT(initPos, destiPos) && UPR_1ST_RT_VAL(initPos) == PLAYER2_MEN)
            {
                board[destiPos[1]][destiPos[0]] = PLAYER1_MEN;
                board[initPos[1]][initPos[0]] = ' ';
                UPR_1ST_RT_VAL(initPos) = ' ';
                return 1;
            } 
            //if the player can get enemie's piece(left)
            else if(IS_IN_UPR_2ND_LT(initPos, destiPos) && UPR_1ST_LT_VAL(initPos) == PLAYER2_MEN)
            {
                board[destiPos[1]][destiPos[0]] = PLAYER1_MEN;
                board[initPos[1]][initPos[0]] = ' ';
                UPR_1ST_LT_VAL(initPos) = ' ';
                return 1;
            }
            //just move, left or right
            else if(IS_IN_UPR_1ST_RT(initPos, destiPos) || IS_IN_UPR_1ST_LT(initPos, destiPos))
            {
                board[destiPos[1]][destiPos[0]] = PLAYER1_MEN;
                board[initPos[1]][initPos[0]] = ' ';
                return 1;
            }

            return 0; //if any case matches, it means that it is not a valid move

        case PLAYER2_MEN: //same logic

            if(IS_IN_LWR_2ND_RT(initPos, destiPos) && LWR_1ST_RT_VAL(initPos) == PLAYER1_MEN)
            {
                board[destiPos[1]][destiPos[0]] = PLAYER2_MEN;
                board[initPos[1]][initPos[0]] = ' ';
                LWR_1ST_RT_VAL(initPos) = ' ';
                return 1;
            }
            else if(IS_IN_LWR_2ND_LT(initPos, destiPos) && LWR_1ST_LT_VAL(initPos) == PLAYER1_MEN)
            {
                board[destiPos[1]][destiPos[0]] = PLAYER2_MEN;
                board[initPos[1]][initPos[0]] = ' ';
                LWR_1ST_LT_VAL(initPos) = ' ';
                return 1;
            }
            else if(IS_IN_LWR_1ST_RT(initPos, destiPos) || IS_IN_LWR_1ST_LT(initPos, destiPos))
            {
                board[destiPos[1]][destiPos[0]] = PLAYER2_MEN;
                board[initPos[1]][initPos[0]] = ' ';
                return 1;
            }

            return 0;
    }
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