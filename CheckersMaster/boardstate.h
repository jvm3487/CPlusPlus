#ifndef BOARDSTATE_H
#define BOARDSTATE_H
#include "userinput.h"
#include "piece.h"
#include "struct.h"



class BoardState{
 private:
  Piece board[8][8];
  int userColor; // 1-> red, 0 -> black
  int compColor;
  int turn; //0 <- user, 1 <- computer
  int startOfUserTurn; // 0 <- start of turn, 1 <- player has further moves -- used for both computer and user
  int lastX; //gives the coordinate of the last piece that moved
  int lastY; //gives the coordinate of the last piece that moved
  int moveCounter; //changes everytime the turn changes
  int numUserPieces; //number of user pieces
  int numCompPieces;
 public:
  BoardState(int color);
  BoardState & operator=(BoardState & rhs);
  ~BoardState(){}
  bool checkLegality(UserInput& input);
  bool checkLegalJump(UserInput & input);
  bool checkNoJumps();
  bool checkRegMove(UserInput & input);
  int getTurn();
  int getLastX();
  int getLastY();
  int getCompColor();
  int getStartOfUserTurn();
  void updateBoard(UserInput & input);
  bool checkFurther(UserInput & input);
  Piece getPiece(int x, int y);
  void changeTurn();
  void changeStep(int change, int x, int y);
  void PossibleMoves(allMoves * comp, int checkPiece);
  UserInput * comMoreMove(Coor start);
  void emptyBoard();
  bool winLoss();
  int checkMoveValue(int depth);
  jumpCompare detJumpOrder(UserInput & currentMove, int depth);
  jumpCompare detJumpOrderHelper(jumpCompare lowerMove, int depth);
  int getMoveCounter();
  bool endGameWin();
  void saveBoard(int difficulty, bool timerOn, int minutes, int seconds);
  int * loadBoard();
  int getUserPieces();
  int getCompPieces();
};

#endif // BOARDSTATE_H
