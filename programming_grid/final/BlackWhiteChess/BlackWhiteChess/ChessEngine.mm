//
//  ChessEngine.c
//  BlackWhiteChess
//
//  Created by wuhaotian on 1/4/14.
//  Copyright (c) 2014 wuhaotian. All rights reserved.
//

#include "ChessEngine.h"
#include <functional>
#include <cmath>
#include <iostream>

void ChessEngine::init() {
  table.clear();
  table.resize(8, std::vector<int>(8, CEEmpty));

  table[3][3] = CEWhite;
  table[3][4] = CEBlack;
  table[4][3] = CEBlack;
  table[4][4] = CEWhite;

}


bool ChessEngine::tap(int x, int y, int color) {
  
  if (table[x][y] != CEEmpty) return false;

  table[x][y] = color;
  bool can_flip = false;
  
  
  std::function<bool(int, int)> search = [&](int dx, int dy){

      bool found = false;
      bool has_other = false;

      int i = x + dx;
      int j = y + dy;
      
      int last = table[x][y];

    while (i >= 0 && i < 8 &&
          j >= 0 && j < 8)
    {

        if (table[i][j] == CEEmpty) {
            
            if (last == table[x][y] and
              (abs(i - x) > 1 or abs(j - y) > 1)
                and has_other) {
                
              found = true;
            }
                
            
            
            break;
        }
        else if (table[i][j] != table[x][y]) {
            
            has_other = true;
        }
        
        last = table[i][j];
      i += dx;
      j += dy;
    }

    i = x + dx;
    j = y + dy;
      
    if (found)
        
    while (i >= 0 && i < 8 &&
          j >= 0 && j < 8)
    {


      if (table[i][j] == CEEmpty)
        break;

      table[i][j] = table[x][y];
      i += dx;
      j += dy;
    }

    return found;
  };

  
  can_flip |= search(-1, -1);
  can_flip |= search(1, -1);
  can_flip |= search(-1, 1);
  can_flip |= search(1, 1);
  can_flip |= search(0, 1);
  can_flip |= search(0, -1);
  can_flip |= search(1, 0);
  can_flip |= search(-1, 0);

  if (!can_flip) table[x][y] = CEEmpty;
  return can_flip;
}
