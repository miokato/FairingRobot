//
//  ViewController.m
//  RobotCarController
//
//  Created by miokato on 4/25/15.
//  Copyright (c) 2015 mio_k. All rights reserved.
//

#import "ViewController.h"
#import "Konashi.h"

@interface ViewController ()

typedef NS_ENUM(NSInteger, OpratingMode){
    modeForward,
    modeBack,
    modeLeft,
    modeRight,
    modeStop
};

@property (weak, nonatomic) IBOutlet UILabel *state;
@property BOOL isForward;
@property OpratingMode mode;

@end



@implementation ViewController


- (void)viewDidLoad {
    [super viewDidLoad];
    if (! [Konashi isReady]) {
        
        [Konashi addObserver:self selector:@selector(ready) name:KONASHI_EVENT_READY];

    }


}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


- (IBAction)konashiFind:(UIButton *)sender {
    [Konashi find];
    [Konashi pinMode:S1 mode:INPUT];
    [Konashi pinPullup:S1 mode:PULLUP];

}

- (void)ready {
    
    [Konashi initialize];
    
    // Motor Pins
    [Konashi pinMode:PIO0 mode:OUTPUT];
    [Konashi pinMode:PIO1 mode:OUTPUT];
    [Konashi pinMode:PIO2 mode:OUTPUT];
    [Konashi pinMode:PIO3 mode:OUTPUT];
    [Konashi pinMode:PIO4 mode:OUTPUT];
    // sw init
    self.isForward = false;
    
    
}

// 前進
- (IBAction)goForward:(UIButton *)sender {
    if (self.mode!=modeForward) {
        [Konashi digitalWrite:PIO1 value:HIGH];
        [Konashi digitalWrite:PIO2 value:LOW];
        [Konashi digitalWrite:PIO3 value:HIGH];
        [Konashi digitalWrite:PIO4 value:LOW];
        self.state.text = @"Forward";
    }
    self.mode = modeForward;
}

// 後退
- (IBAction)goBack:(UIButton *)sender {
    if (self.mode!=modeBack) {
        [Konashi digitalWrite:PIO1 value:LOW];
        [Konashi digitalWrite:PIO2 value:HIGH];
        [Konashi digitalWrite:PIO3 value:LOW];
        [Konashi digitalWrite:PIO4 value:HIGH];
        self.state.text = @"Back";
    }
    self.mode = modeBack;
}



// 左
- (IBAction)left:(UIButton *)sender {
    if (self.mode!=modeLeft) {
        [Konashi digitalWrite:PIO1 value:HIGH];
        [Konashi digitalWrite:PIO2 value:LOW];
        [Konashi digitalWrite:PIO3 value:LOW];
        [Konashi digitalWrite:PIO4 value:LOW];
        self.state.text = @"Left";
    }
    self.mode = modeLeft;
}


// 右
- (IBAction)right:(UIButton *)sender {
    if (self.mode!=modeRight) {
        [Konashi digitalWrite:PIO1 value:LOW];
        [Konashi digitalWrite:PIO2 value:LOW];
        [Konashi digitalWrite:PIO3 value:HIGH];
        [Konashi digitalWrite:PIO4 value:LOW];
        self.state.text = @"Right";
    }
    self.mode = modeRight;

}

// ストップ
- (IBAction)stop:(UIButton *)sender {
    if (self.mode!=modeStop) {
        [Konashi digitalWrite:PIO1 value:LOW];
        [Konashi digitalWrite:PIO2 value:LOW];
        [Konashi digitalWrite:PIO3 value:LOW];
        [Konashi digitalWrite:PIO4 value:LOW];
        self.state.text = @"Stop";
    }
    self.mode = modeStop;
}


@end
