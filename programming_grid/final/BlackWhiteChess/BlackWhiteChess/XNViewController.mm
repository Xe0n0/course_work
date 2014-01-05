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
    
    self.color = CEBlack;
    self.engine = new ChessEngine();
    self.arrayBtns = [NSMutableArray array];
    int base_x = 20;
    int base_y = 80;
    
    __weak __block XNViewController *weak_self = self;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            
            XNChessButton *btn = [XNChessButton buttonWithType:UIButtonTypeRoundedRect];
            btn.frame = CGRectMake(base_x, base_y, 35, 35);
            [btn.po_frameBuilder moveWithOffsetX:i * 35 offsetY:j * 35];
            
            btn.layer.cornerRadius = btn.frame.size.width / 2;
            
            btn.x = i;
            btn.y = j;
            
            
            [btn addEventHandler:^(XNChessButton *sender, UIEvent *event) {
                
                if (weak_self.engine->tap(sender.x, sender.y, weak_self.color)) {
                    
                    [weak_self updateView];
                    //weak_self.color = !weak_self.color;
                    double delayInSeconds = 0.2;
                    dispatch_time_t popTime = dispatch_time(DISPATCH_TIME_NOW, (int64_t)(delayInSeconds * NSEC_PER_SEC));
                    dispatch_after(popTime, dispatch_get_main_queue(), ^(void){
                        if (weak_self.engine->play(!weak_self.color))
                          [weak_self updateView];
                        else
                          [weak_self updateResult];
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
  
}


- (void)updateView
{
    [self.arrayBtns enumerateObjectsUsingBlock:^(XNChessButton* obj, NSUInteger idx, BOOL *stop) {
        
        switch (self.engine->table[obj.x][obj.y]) {
            case CEBlack:
                obj.backgroundColor = [UIColor blackColor];
                break;
            case CEWhite:
                obj.backgroundColor = [UIColor whiteColor];
                break;
            case CEEmpty:
                obj.backgroundColor = [UIColor colorWithWhite:0.3 alpha:0.2];
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
