#include "Piezas.h"
#include <vector>
/** CLASS Piezas
 * Class for representing a Piezas vertical board, which is roughly based
 * on the game "Connect Four" where pieces are placed in a column and 
 * fall to the bottom of the column, or on top of other pieces already in
 * that column. For an illustration of the board, see:
 *  https://en.wikipedia.org/wiki/Connect_Four
 *
 * Board coordinates [row,col] should match with:
 * [2,0][2,1][2,2][2,3]
 * [1,0][1,1][1,2][1,3]
 * [0,0][0,1][0,2][0,3]
 * So that a piece dropped in column 2 should take [0,2] and the next one
 * dropped in column 2 should take [1,2].
**/


/**
 * Constructor sets an empty board (default 3 rows, 4 columns) and 
 * specifies it is X's turn first
**/
Piezas::Piezas()
{
    std::vector<Piece> row;
    turn = X;
    for(int i=0; i<BOARD_ROWS; i++){
        board.push_back(row);
        for(int j=0; j<BOARD_COLS; j++){
            board[i].push_back(Blank);
        }
    }
}

/**
 * Resets each board location to the Blank Piece value, with a board of the
 * same size as previously specified
**/
void Piezas::reset()
{
    for(int i=0; i<BOARD_ROWS; i++){
        for(int j=0; j<BOARD_COLS; j++){
            board[i][j]=Blank;
        }
    }
}

/**
 * Places a piece of the current turn on the board, returns what
 * piece is placed, and toggles which Piece's turn it is. dropPiece does 
 * NOT allow to place a piece in a location where a column is full.
 * In that case, placePiece returns Piece Blank value 
 * Out of bounds coordinates return the Piece Invalid value
 * Trying to drop a piece where it cannot be placed loses the player's turn
**/ 
Piece Piezas::dropPiece(int column)
{
    if(pieceAt(0,column)==Blank){
        board[0][column]=turn;
        if(turn==X){
            turn=O;
        }else if(turn==O){
            turn=O;
        }
        return board[0][column];
    }else if(pieceAt(1,column)==Blank){
        board[1][column]=turn;
        if(turn==X){
            turn=O;
        }else if(turn==O){
            turn=O;
        }
        return board[1][column];
    }else if(pieceAt(2,column)==Blank){
        board[2][column]=turn;
        if(turn==X){
            turn=O;
        }else if(turn==O){
            turn=O;
        }
        return board[2][column];
    }else if(pieceAt(2,column)==Invalid){
        if(turn==X){
            turn=O;
        }else if(turn==O){
            turn=O;
        }
        return Invalid;
    }else{
        if(turn==X){
            turn=O;
        }else if(turn==O){
            turn=O;
        }
        return Blank;
    }
}

/**
 * Returns what piece is at the provided coordinates, or Blank if there
 * are no pieces there, or Invalid if the coordinates are out of bounds
**/
Piece Piezas::pieceAt(int row, int column)
{
    if((row>=BOARD_ROWS||column>=BOARD_COLS)||(row<0||column<0)){
        return Invalid;
    }else if(board[row][column]!=X||board[row][column]!=O){
        return Blank;
    }else{
        return board[row][column];
    }
}

/**
 * Returns which Piece has won, if there is a winner, Invalid if the game
 * is not over, or Blank if the board is filled and no one has won ("tie").
 * For a game to be over, all locations on the board must be filled with X's 
 * and O's (i.e. no remaining Blank spaces). The winner is which player has
 * the most adjacent pieces in a single line. Lines can go either vertically
 * or horizontally. If both X's and O's have the same max number of pieces in a
 * line, it is a tie.
**/
Piece Piezas::gameState()
{
    //Piece curWinner=Blank;
    Piece lastPiece=Blank;
    int highCountX=1;
    int highCountO=1;
    int numConsec=1;
    
    if(board[0][0]==' '||board[0][1]==' '||board[0][2]==' '||board[0][3]==' '||board[1][0]==' '||board[1][1]==' '||board[1][2]==' '||board[1][3]==' '||board[2][0]==' '||board[2][1]==' '||board[2][2]==' '||board[2][3]==' '){//empty cell
        return Invalid;
    }else{
        for(int i=0;i<BOARD_ROWS;i++){//checks each row for consecutive pieces
            lastPiece=Blank;
            numConsec=1;
            for(int j=0;j<BOARD_COLS;j++){
                if(lastPiece==board[i][j]){
                    numConsec++;
                    if(lastPiece==X && numConsec>highCountX){
                        highCountX=numConsec;
                    }else if(lastPiece==O && numConsec>highCountO){
                        highCountO=numConsec;
                    }
                }else{
                    lastPiece=board[i][j];
                    numConsec=1;
                }
            }
        }
        
        for(int i=0;i<BOARD_COLS;i++){//checks each col for consecutive pieces
            lastPiece=Blank;
            numConsec=1;
            for(int j=0;j<BOARD_ROWS;j++){
                if(lastPiece==board[j][i]){
                    numConsec++;
                    if(lastPiece==X && numConsec>highCountX){
                        highCountX=numConsec;
                    }else if(lastPiece==O && numConsec>highCountO){
                        highCountO=numConsec;
                    }
                }else{
                    lastPiece=board[j][i];
                    numConsec=1;
                }
            }
        }
        
        /*if((board[0][0]==board[0][1]&&board[0][1]==board[0][2]&&board[0][2]==board[0][3])){//row 1
            if(board[0][0]==X){
                highCountX=4;
            }else if(board[0][0]==O){
                highCountO=4;
            }
        }
        if((board[1][0]==board[1][1]&&board[1][1]==board[1][2]&&board[1][2]==board[1][3])){//row 2
            if(board[1][0]==X){
                highCountX=4;
            }else if(board[1][0]==O){
                highCountO=4;
            }
        }
        if((board[2][0]==board[2][1]&&board[2][1]==board[2][2]&&board[2][2]==board[2][3])){//row 3
            if(board[2][0]==X){
                highCountX=4;
            }else if(board[2][0]==O){
                highCountO=4;
            }
        }*/
        
        if(highCountX==highCountO){
            return Blank;
        }else if(highCountX>highCountX){
            return X;
        }else if(highCountX<highCountO){
            return O;
        }
    }
}