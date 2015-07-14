#include "RobotController.h"

#define FORWARD 1
#define BACK    2
#define RIGHT   3
#define LEFT    4
#define STOP    5

// myrobot(ピン番号)
RobotController myrobot;

void setup() {
    Serial.begin(9600);
    myrobot.setIrPin(2);
    myrobot.setMotorPin(4,5,6,7);
    analogWrite(3, 64); // ロボットの速度を指定 (0-255)
}

void loop() {

    // myrobot.showIrValue();
  
    int value = myrobot.getIrValue(3);

    if(value){
        switch(value) {
            case FORWARD :
                myrobot.goForward(); //① 前へ進む
                break;
            case BACK :
                myrobot.goBack();    //② 後ろへ進む
                break;
            case RIGHT :
                myrobot.turnRight(); //③ 右へ曲がる
                break;
            case LEFT :
                myrobot.turnLeft();  //④ 左へ曲がる
                break;
            case STOP :
                myrobot.stop();       //⑤ 止める
                break;
        }
    }
}  

