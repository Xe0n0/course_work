//
//  ChessEngine.h
//  BlackWhiteChess
//
//  Created by wuhaotian on 1/4/14.
//  Copyright (c) 2014 wuhaotian. All rights reserved.
//

#ifndef BlackWhiteChess_ChessEngine_h
#define BlackWhiteChess_ChessEngine_h
#include <vector>

#define CEEmpty 3
#define CEWhite 0
#define CEBlack 1
#define CEInternal 4

class ChessEngine {
    
public:
  void init(); // start or restart a new game
  
  //try to set color on (x, y). return false if cannot flip any chess piece
  bool tap(int x, int y, int color);
  
  //use naive AI to place a piece. return false if cannot play
  bool play(int color);
  
  //matrix to save color data, retrieve after any change.
  std::vector<std::vector<int> > table;
  
  //score for black
  int scoreBlack;
  
  //score for white
  int scoreWhite;
  
  //current available place to place piece. 0 indicates game ends.
  int empty_slot;
  
private:
  
  //re-calculate scores and empty_slot
  void collectScore();
};

#endif
