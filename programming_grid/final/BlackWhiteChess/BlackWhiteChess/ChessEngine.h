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
    void init();
    bool tap(int x, int y, int color);
    bool play(int color);
    std::vector<std::vector<int> > table;
    int scoreBlack;
    int scoreWhite;
};

#endif
