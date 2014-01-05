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

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.color = CEBlack;
    self.engine = new ChessEngine();
    self.arrayBtns = [NSMutableArray array];
    int base_x = 10;
    int base_y = 40;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            
            XNChessButton *btn = [XNChessButton buttonWithType:UIButtonTypeRoundedRect];
            btn.frame = CGRectMake(base_x, base_y, 35, 35);
            [btn.po_frameBuilder moveWithOffsetX:i * 35 offsetY:j * 35];
            
            btn.layer.cornerRadius = btn.frame.size.width / 2;
            
            btn.x = i;
            btn.y = j;
            
            __weak __block XNViewController *weak_self = self;
            
            [btn addEventHandler:^(XNChessButton *sender, UIEvent *event) {
                
                if (weak_self.engine->tap(sender.x, sender.y, weak_self.color)) {
                    
                    [weak_self updateColors];
                    //weak_self.color = !weak_self.color;
                    weak_self.engine->play(!weak_self.color);
                    [weak_self updateColors];
                }
                
            } forControlEvent:UIControlEventTouchUpInside];
            
            [self.view addSubview:btn];
            [self.arrayBtns addObject:btn];
        }
    }
    self.engine->init();
    
    [self updateColors];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)updateColors
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
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
