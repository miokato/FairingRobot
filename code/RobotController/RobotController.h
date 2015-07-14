#ifndef RobotController_h
#define RobotController_h
#include "arduino.h"


// IR Class
class RobotController {
    public:
        RobotController();
        void setIrPin(int irpin);
        void setMotorPin(int rmpin1,int rmpin2,int lmpin1,int lmpin2);

        // ロボット動作
        void goForward();           // 前進
        void goBack();              // 後退
        void turnRight();           // 右
        void turnLeft();            // 左
        void stop();                // ストップ
        void brake();               // ブレーキ
        int  getIrValue(char num); // 指定した位置の赤外線信号を受信 
        void showIrValue();           // 赤外線信号をすべて表示

    private:

        // 赤外線信号を受信してIrDataに格納
        int  getIr();

        // IRピン
        int irPin;
        char IrBit[64];
        unsigned char IrData[12];

        // モーターピン
        int rmPin1;
        int rmPin2;
        int lmPin1;
        int lmPin2;

        // 信号を切り替えるときにたてるフラグ
        bool forwardFlag;
        bool backFlag;
        bool rightFlag;
        bool leftFlag;
        bool stopFlag;
};

#endif
