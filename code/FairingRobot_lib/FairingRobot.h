#ifndef FairingRobot_h
#define FairingRobot_h
#include "arduino.h"

// IR Class
class FairingRobot
{
    public:

        // コンストラクタ
        //FairingRobot();
        // 初期化
        void init();
        void setMotorR(const int rm1, const int rm2);
        void setMotorL(const int lm1, const int lm2);
        void setIrPin(const int somePin);

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
