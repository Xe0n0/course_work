//
//  XNViewController.m
//  BlackWhiteChess
//
//  Created by wuhaotian on 1/4/14.
//  Copyright (c) 2014 wuhaotian. All rights reserved.
//

#import "XNViewController.h"
#import "XNChessButton.h"
#import "ChessEngine.h"

@interface XNViewController ()

@property (assign, nonatomic) ChessEngine *engine;
@property (strong, nonatomic) NSMutableArray *arrayBtns;
@property (assign, nonatomic) int color;
@end

@implementation XNViewController

- (void)startGame
{
    self.engine->init();
    [self updateView];
}

- (void)viewDidLoad
{
    [super viewDidLoad];
  
  int base_y = 50;
  int base_x = 0;
    UIImageView *imv_bg = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"ChessBoard.png"]];
  [imv_bg.po_frameBuilder moveWithOffsetY:base_y];
  
    [self.view addSubview:imv_bg];
  
    self.color = CEBlack;
    self.engine = new ChessEngine();
    self.arrayBtns = [NSMutableArray array];
  
    
    __weak __block XNViewController *weak_self = self;
  
    //add buttons to view
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            
            XNChessButton *btn = [XNChessButton buttonWithType:UIButtonTypeRoundedRect];
            btn.frame = CGRectMake(base_x, base_y, 40, 40);
          [btn.po_frameBuilder moveWithOffsetX:i * 40 offsetY:j * 40];
          btn.backgroundColor = [UIColor clearColor];
          
          
            //set button information
            btn.x = i;
            btn.y = j;
            
            //add button click call back
            [btn addEventHandler:^(XNChessButton *sender, UIEvent *event) {
              
                //use game engine to judge if we can tap
                if (weak_self.engine->tap(sender.x, sender.y, weak_self.color)) {
                  
                    //update buttons
                    [weak_self updateView];
                  
                    //let engine play next round
                    double delayInSeconds = 0.2;
                    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
                    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
                      if (weak_self.engine->play(!weak_self.color)) {
                          [weak_self updateView];
                      }
                      else {
                          [weak_self updateResult];
                      }
                    });
                }
                
            } forControlEvent:UIControlEventTouchUpInside];
            
            [self.view addSubview:btn];
            [self.arrayBtns addObject:btn];
        }
    }
    
    [self.buttonNewGame addEventHandler:^(id sender, UIEvent *event) {
        [weak_self startGame];
    } forControlEvent:UIControlEventTouchUpInside];
    
    [self startGame];
}

- (void)updateResult
{
  
  NSString *r;
  
      if (self.engine->scoreBlack > self.engine->scoreWhite)
        r = @"You Win!";
      else if (self.engine->scoreBlack < self.engine->scoreWhite)
        r = @"You Lose!";
      else
        r = @"Draw!";
  self.labelInfo.text = r;
  
}


- (void)updateView
{
    [self.arrayBtns enumerateObjectsUsingBlock:^(XNChessButton* obj, NSUInteger idx, BOOL *stop) {
        
        switch (self.engine->table[obj.x][obj.y]) {
            case CEBlack:
                [obj setBackgroundImage:[UIImage imageNamed:@"Blue.png"] forState:UIControlStateNormal];
                break;
            case CEWhite:
                [obj setBackgroundImage:[UIImage imageNamed:@"Green.png"] forState:UIControlStateNormal];
                break;
            case CEEmpty:
                [obj setBackgroundImage:nil forState:UIControlStateNormal];
                break;
                
            default:
                break;
        }
    }];
    
    
    self.labelInfo.text = [NSString stringWithFormat:@"Score Black: %d\nScore White: %d",
                           self.engine->scoreBlack, self.engine->scoreWhite];
  
  if (self.engine->empty_slot == 0)
      [self updateResult];
  
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
