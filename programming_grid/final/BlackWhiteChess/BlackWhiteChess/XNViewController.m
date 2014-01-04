//
//  XNViewController.m
//  BlackWhiteChess
//
//  Created by wuhaotian on 1/4/14.
//  Copyright (c) 2014 wuhaotian. All rights reserved.
//

#import "XNViewController.h"
#import "XNChessButton.h"

@interface XNViewController ()

@end

@implementation XNViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    int base_x = 10;
    int base_y = 40;
    
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            
            XNChessButton *btn = [XNChessButton buttonWithType:UIButtonTypeRoundedRect];
            btn.frame = CGRectMake(base_x, base_y, 35, 35);
            [btn.po_frameBuilder moveWithOffsetX:i * 35 offsetY:j * 35];
            
            btn.layer.cornerRadius = btn.frame.size.width / 2;
            btn.layer.backgroundColor = [UIColor blackColor].CGColor;
            
            btn.tag = i * 10 + j;
            
            [btn addEventHandler:^(id sender, UIEvent *event) {
                
                
            } forControlEvent:UIControlEventTouchUpInside];
            
            [self.view addSubview:btn];
        }
    }
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

@end
