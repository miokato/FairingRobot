#include <FairingRobot.h>

#define FORWARD xxx // ①
#define BACK    xxx // ②
#define RIGHT   xxx // ③
#define LEFT    xxx // ④
#define STOP    xxx // ⑤

// myRobot(ピン番号)
FairingRobot myRobot(2);

void setup() {
    Serial.begin(9600);
    myRobot.init(3,4,5,6);
}

void loop() {
  
    int number = myRobot.getIrValue(xxx);

    if(number){
        switch(number) {
            case FORWARD :
                myRobot.goForward(); //① 前へ進む
                break;
            case BACK :
                myRobot.goBack();    //② 後ろへ進む
                break;
            case RIGHT :
                myRobot.turnRight(); //③ 右へ曲がる
                break;
            case LEFT :
                myRobot.turnLeft();  //④ 左へ曲がる
                break;
            case STOP :
                myRobot.stop();       //⑤ 止める
                break;
        }
    }
}  

