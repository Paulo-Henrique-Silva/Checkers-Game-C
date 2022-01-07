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
void rules(void);

void resetBoard(void);
void printsBoard(void);
int isA_validPiece(char pieceIn_board[], char playerSymbol); 
int isA_validMove(char posIn_board[], char posTo_move[]);
void isA_validKing(char pos[], char playerSymbol);
int isVictory(void);
int isTie(void);

int isA_validBoard_space(char input[]);

char board[8][8] = {'\0'};

enum menuOptions {Pvp = 1, GameRules, Exitprogram};

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
        
        case GameRules:
            rules();
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
    printf("\n\t\t\t\t[2] - Game Rules");
    printf("\n\t\t\t\t[3] - Exit");

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
        playerTurn_symb = (playerTurn_symb == PLAYER1_MEN) ? PLAYER2_MEN : PLAYER1_MEN;

        //reads until is a valid player piece
        while(1)
        {
            system("cls");
            printsBoard();
            
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

            if(isA_validMove(pieceIn_board, posTo_move) != 0)
            {
                isA_validKing(posTo_move, playerTurn_symb);
                break; 
            }

            printf("\nInvalid Input!");
            getch();   
        }
    }
    while(isVictory() == 0 || isTie() == 0);

    system("cls");
    printsBoard();
    printf("\n\nEND GAME!");
    (isTie()) ? printf("\nIt's a TIE!") : printf("\nPLAYER '%c' WINS!", playerTurn_symb);
    printf("\n\nThank you for Play :) - Paulo");
}

void rules(void)
{
    system("cls");
    printf("\t\t\t\t\t     RULES");
    printf("\n\t\t\t-----------------------------------------------------");

    printf("\n\n\t    - Checkers is a 1vs1 Game played in a Board(8x8), with 24 pieces on it. ");
    printf("\n\t    - The Main objective of Checkers is to Capture all Enemies Pieces.");

    printf("\n\n\t\t\t\t '%c' - Player 1 Men", PLAYER1_MEN);
    printf("\n\t\t\t\t '%c' - Player 1 King", PLAYER1_KING);
    printf("\n\t\t\t\t '%c' - Player 2 Men", PLAYER2_MEN);
    printf("\n\t\t\t\t '%c' - Player 2 King", PLAYER2_KING);

    printf("\n\nIn this Program: ");
    printf("\n\n1 - 'X' Men can just move 1 Board house Forwards and 'O' Backwards - (Bottom-Up).");
    printf("\n2 - Men can move 2 houses if are capturing an Enemies Piece.");
    printf("\n3 - Kings can Move in all diagonals, how many houses it wants.");
    printf("\n4 - Pieces can Capture Enemies Pieces in its Inverse Moviment Way.");
    printf("\n5 - It's Optional to Capture an Enemies Piece.");
    printf("\n6 - The game will automatically end, as a Tie, if:"); 
    printf("\n-> There are Only Kings and 20 moviments were madee without a Piece getting Capture or");
    printf("\n-> A Player Pieces are totally Blocked and cannot Move.");

    printf("\n\nBug: A Piece cannot capture more than one Piece at once(Men and Kings).");
}

//resets the board if the correct pieces
void resetBoard(void)
{
    int i, j;

    //i and j are with +1 because is more easy to determinate if it is black
    //the black spaces are in houses with i and j equal to an odd num or an even num
    for(i = 7; i >= 0; i--)
    {
        for(j = 0; j < 8; j++)
        {
            if(i > 4 && ISBLACK((i + 1), (j + 1)))
                board[i][j] = PLAYER2_MEN;
            else if(i < 3 && ISBLACK((i + 1), (j + 1)))
                 board[i][j] = PLAYER1_MEN;
            else
                board[i][j] = ' ';
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
    int diagonalCount,
    rowIncre = 0, colIncre = 0;

    char pos[3] = {'\0'};
    
    if(isA_validBoard_space(pieceIn_board) == 0) return 0;
    
    //converts to matriz form, that is
    //A3 -> (2,0)
    pos[0] = pieceIn_board[0] - 65;
    pos[1] = pieceIn_board[1] - '0' - 1;

    if(playerSymbol == PLAYER1_MEN)
    {
        if
        (
            board[pos[1]][pos[0]] != PLAYER1_MEN &&
            board[pos[1]][pos[0]] != PLAYER1_KING
        )
            return 0;
    }
    else //player 2
    {
        if
        (
            board[pos[1]][pos[0]] != PLAYER2_MEN &&
            board[pos[1]][pos[0]] != PLAYER2_KING
        )
            return 0;
    }

    //checks if the piece is blocked in four diagonals
    for(diagonalCount = 1; diagonalCount < 5; diagonalCount++)
    {
        switch(diagonalCount)
        {
            case 1:
                rowIncre = 1, colIncre = 1; //checks rt upper diagonal
                break;
            case 2:
                rowIncre = 1, colIncre = -1; //lt upper diagonal
                break;
            case 3:
                rowIncre = -1, colIncre = 1; //rt lower
                break;
            case 4:
                rowIncre = -1, colIncre = -1; //lt lower
                break;
        }

        switch(board[pos[1]][pos[0]])
        {
            case PLAYER1_MEN:

                if //if the piece can move one house forwards
                (
                    rowIncre > 0 && //p1 can't move backwards in board
                    board[pos[1] + rowIncre][pos[0] + colIncre] == ' ' &&
                    IS_IN_BOARD((pos[1] + rowIncre), (pos[0] + colIncre))
                )
                    return 1;
                else if //if the piece can capture an enemies piece
                (
                    (board[pos[1] + rowIncre][pos[0] + colIncre] == PLAYER2_MEN ||
                    board[pos[1] + rowIncre][pos[0] + colIncre] == PLAYER2_KING) && 
                    board[pos[1] + 2 * rowIncre][pos[0] + 2 * colIncre] == ' ' &&
                    IS_IN_BOARD((pos[1] + 2 * rowIncre), (pos[0] + 2 * colIncre))
                )
                    return 1;

                break; //exit switch and restarts with other increment

            case PLAYER2_MEN: //same logic

                if 
                (
                    rowIncre < 0 &&
                    board[pos[1] + rowIncre][pos[0] + colIncre] == ' ' &&
                    IS_IN_BOARD((pos[1] + rowIncre), (pos[0] + colIncre))
                )
                    return 1;
                else if
                (
                    (board[pos[1] + rowIncre][pos[0] + colIncre] == PLAYER1_MEN ||
                    board[pos[1] + rowIncre][pos[0] + colIncre] == PLAYER1_KING) && 
                    board[pos[1] + 2 * rowIncre][pos[0] + 2 * colIncre] == ' ' &&
                    IS_IN_BOARD((pos[1] + 2 * rowIncre), (pos[0] + 2 * colIncre))
                )
                    return 1;
                
                break;

            case PLAYER1_KING:

                if //kings don't have limitations of which diagonal can move
                (
                    board[pos[1] + rowIncre][pos[0] + colIncre] == ' ' &&
                    IS_IN_BOARD((pos[1] + rowIncre), (pos[0] + colIncre))
                )
                    return 1;
                else if
                (
                    (board[pos[1] + rowIncre][pos[0] + colIncre] == PLAYER2_MEN ||
                    board[pos[1] + rowIncre][pos[0] + colIncre] == PLAYER2_KING) && 
                    board[pos[1] + 2 * rowIncre][pos[0] + 2 * colIncre] == ' ' &&
                    IS_IN_BOARD((pos[1] + 2 * rowIncre), (pos[0] + 2 * colIncre))
                )
                    return 1;
                
                break;

            case PLAYER2_KING:

                if
                (
                    board[pos[1] + rowIncre][pos[0] + colIncre] == ' ' &&
                    IS_IN_BOARD((pos[1] + rowIncre), (pos[0] + colIncre))
                )
                    return 1;
                else if
                (
                    (board[pos[1] + rowIncre][pos[0] + colIncre] == PLAYER1_MEN ||
                    board[pos[1] + rowIncre][pos[0] + colIncre] == PLAYER1_KING) && 
                    board[pos[1] + 2 * rowIncre][pos[0] + 2 * colIncre] == ' ' &&
                    IS_IN_BOARD((pos[1] + 2 * rowIncre), (pos[0] + 2 * colIncre))
                )
                    return 1;

                break;
        }
    }

    //if any case matches it means that the piece is blocked and can't be moved
    //therefore, it's not a valid piece
    return 0;
}

//Checks if the piece can moves to that space in board
//if it can, moves the piece
int isA_validMove(char posIn_board[], char posTo_move[])
{
    int rowCounter = 0, colCounter = 0, rowIncre = 0, colIncre = 0;

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

    //checks which diagonal is the destination
    if(destiPos[1] > initPos[1] && destiPos[0] > initPos[0]) //rt upr diagonal
    {
        rowIncre = 1, colIncre = 1;
    }
    else if(destiPos[1] > initPos[1] && destiPos[0] < initPos[0]) //lt upr diagonal
    {
        rowIncre = 1, colIncre = -1;
    }
    else if(destiPos[1] < initPos[1] && destiPos[0] > initPos[0]) //rt lwr diagonal
    {
        rowIncre = -1, colIncre = 1;
    }
    else if(destiPos[1] < initPos[1] && destiPos[0] < initPos[0]) //lt lwr diagonal
    {
        rowIncre = -1, colIncre = -1;
    }
    else 
        return 0; //it means it is not a diagonal. Then it is not a possible move

    //Checks piece's possible moves
    switch(board[initPos[1]][initPos[0]])
    {
        case PLAYER1_MEN:

            if //if it wants to move just one house forwards
            (
                rowIncre > 0 &&
                initPos[1] + rowIncre == destiPos[1] && 
                initPos[0] + colIncre == destiPos[0]
            )
            {
                board[initPos[1]][initPos[0]] = ' ';
                board[destiPos[1]][destiPos[0]] = PLAYER1_MEN;
                return 1;
            }
            else if //if it wants to caputure an enemies piece(forwards or backwards)
            (
                (board[initPos[1] + rowIncre][initPos[0] + colIncre] == PLAYER2_MEN ||
                board[initPos[1] + rowIncre][initPos[0] + colIncre] == PLAYER2_KING) &&
                initPos[1] + 2 * rowIncre == destiPos[1] && 
                initPos[0] + 2 * colIncre == destiPos[0]
            )
            {
                board[initPos[1]][initPos[0]] = ' ';
                board[initPos[1] + rowIncre][initPos[0] + colIncre] = ' ';
                board[destiPos[1]][destiPos[0]] = PLAYER1_MEN;
                return 1;
            }
            else 
                return 0; //it means it is not a valid move

        case PLAYER2_MEN: //same logic

            if
            (
                rowIncre < 0 &&
                initPos[1] + rowIncre == destiPos[1] && 
                initPos[0] + colIncre == destiPos[0]
            )
            {
                board[initPos[1]][initPos[0]] = ' ';
                board[destiPos[1]][destiPos[0]] = PLAYER2_MEN;
                return 1;
            }
            else if
            (
                (board[initPos[1] + rowIncre][initPos[0] + colIncre] == PLAYER1_MEN ||
                board[initPos[1] + rowIncre][initPos[0] + colIncre] == PLAYER1_KING) &&
                initPos[1] + 2 * rowIncre == destiPos[1] && 
                initPos[0] + 2 * colIncre == destiPos[0]
            )
            {
                board[initPos[1]][initPos[0]] = ' ';
                board[initPos[1] + rowIncre][initPos[0] + colIncre] = ' ';
                board[destiPos[1]][destiPos[0]] = PLAYER2_MEN;
                return 1;
            }
            else 
                return 0;
        
        case PLAYER1_KING:

            //goes through the diagonal to check if the destination is valid
            rowCounter = initPos[1], colCounter = initPos[0];

            while(1) 
            {
                rowCounter+=rowIncre, colCounter+=colIncre;
                //if it is an empty space, without a piece blocking it
                if(rowCounter == destiPos[1] && colCounter == destiPos[0]) 
                {
                    board[initPos[1]][initPos[0]] = ' ';
                    board[destiPos[1]][destiPos[0]] = PLAYER1_KING;
                    return 1;
                }
                else if //if it is to capture an enemies piece
                (
                    (board[rowCounter][colCounter] == PLAYER2_MEN || 
                    board[rowCounter][colCounter] == PLAYER2_KING) &&
                    (destiPos[1] == rowCounter + rowIncre && 
                    destiPos[0] == colCounter + colIncre)
                )
                {
                    board[initPos[1]][initPos[0]] = ' ';
                    board[rowCounter][colCounter] = ' ';
                    board[destiPos[1]][destiPos[0]] = PLAYER1_KING;
                    return 1;
                }
                else if(board[rowCounter][colCounter] != ' ')
                    return 0; //if it reached this point, it means it isn't a valid move
            }

        case PLAYER2_KING: //same logic

            rowCounter = initPos[1], colCounter = initPos[0];

            while(1) 
            {
                rowCounter+=rowIncre, colCounter+=colIncre;

                if(rowCounter == destiPos[1] && colCounter == destiPos[0]) 
                {
                    board[initPos[1]][initPos[0]] = ' ';
                    board[destiPos[1]][destiPos[0]] = PLAYER2_KING;
                    return 1;
                }
                else if
                (
                    (board[rowCounter][colCounter] == PLAYER1_MEN || 
                    board[rowCounter][colCounter] == PLAYER1_KING) &&
                    (destiPos[1] == rowCounter + rowIncre && 
                    destiPos[0] == colCounter + colIncre) 
                )
                {
                    board[initPos[1]][initPos[0]] = ' ';
                    board[rowCounter][colCounter] = ' ';
                    board[destiPos[1]][destiPos[0]] = PLAYER2_KING;
                    return 1;
                }
                else if(board[rowCounter][colCounter] != ' ')
                    return 0;
            }
    }
}

//If the piece that has just moved is a new king, the function creates a king 
void isA_validKing(char pos[], char playerSymbol)
{
    char piecePos[3] = {'\0'};

    piecePos[0] = pos[0] - 65; 
    piecePos[1] = pos[1] - '0' - 1; 

    if(playerSymbol == PLAYER1_MEN && piecePos[1] == 7) //creates a king in top
        board[piecePos[1]][piecePos[0]] = PLAYER1_KING;
    else if(playerSymbol == PLAYER2_MEN && piecePos[1] == 0) //creates a king in bot
        board[piecePos[1]][piecePos[0]] = PLAYER2_KING;
}

//Checks if the game has ended
//if there is a least one piece of the other player, it means that the game has not ended
int isVictory(void)
{
    int i, j, numOf_p1_pieces = 0, numOf_p2_pieces = 0;

    for(i = 0; i < 8; i++)
    {
        for(j = 0; j < 8; j++)
        {
            if(board[i][j] == PLAYER1_MEN || board[i][j] == PLAYER1_KING)
                numOf_p1_pieces++;
            else if(board[i][j] == PLAYER2_MEN || board[i][j] == PLAYER2_KING)
                numOf_p2_pieces++;
            
            //if there are already more than 1 piece, there is no need to continue the loops
            if(numOf_p1_pieces > 0 && numOf_p2_pieces > 0)
                return 0;
        }
    }

    //if it reached this point, it means there is one player without piece
    //therefore, it's victory
    return 1; 
}

int isTie(void)
{
    return 0;
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