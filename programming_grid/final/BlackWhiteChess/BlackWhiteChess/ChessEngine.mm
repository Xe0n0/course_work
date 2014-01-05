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
#include <algorithm>
#include <utility>

void ChessEngine::init() {
  
  table.clear();
  table.resize(8, std::vector<int>(8, CEEmpty));

  table[3][3] = CEWhite;
  table[3][4] = CEBlack;
  table[4][3] = CEBlack;
  table[4][4] = CEWhite;
    
  scoreWhite = 2;
  scoreBlack = 2;

}

void ChessEngine::collectScore()
{
  
  scoreWhite = 0;
  scoreBlack = 0;
  empty_slot = 0;
  
  for (auto v : table) {
    for (auto c : v) {
      switch (c) {
        case CEBlack:
          scoreBlack++;
          break;
        case CEWhite:
          scoreWhite++;
          break;
        default:
          empty_slot++;
          break;
      }
    }
  }
}

bool ChessEngine::play(int color)
{
    
    std::vector<std::pair<int, int> > v;
    for (int i = 0; i < 8; ++i)
        for (int j = 0; j < 8; ++j)
        {
            if (table[i][j] != CEEmpty) {
                continue;
            }
            v.push_back(std::make_pair(i, j));
        }
    
    std::random_shuffle(v.begin(), v.end());
    
    for (auto p : v)
    {
        if (tap(p.first, p.second, color)) {
            return true;
        }
    }
    
    return false;
}


bool ChessEngine::tap(int x, int y, int color) {
  
  if (table[x][y] != CEEmpty) return false;

  table[x][y] = color;
  bool can_flip = false;
  
  
  std::function<bool(int, int)> search = [&](int dx, int dy){

      bool found = false;

      int i = x + dx;
      int j = y + dy;
      
      int last = table[x][y];

    while (i >= 0 && i < 8 &&
          j >= 0 && j < 8)
    {
        if (table[i][j] == CEEmpty) {
            break;
        }

        if (table[i][j] == color) {
            
            if (last != color and
              (abs(i - x) > 1 or abs(j - y) > 1)) {
                
              found = true;
              
                int k = i, l = j;
                while (k != x or l != y) {
                    
                    table[k][l] = color;
                    k -= dx;
                    l -= dy;
                }
            }
                
        }
        
        last = table[i][j];
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
  else
    collectScore();
  return can_flip;
}
