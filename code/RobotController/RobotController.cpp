#include "arduino.h"
#include "RobotController.h"

RobotController::RobotController()
{
    // モーターを逆転するときにstop()を入れるためのフラグ
    forwardFlag = 0;
    backFlag    = 0;
    rightFlag   = 0;
    leftFlag    = 0;
    stopFlag    = 0;
}

void RobotController::setIrPin(int irpin)
{
    pinMode(irpin, INPUT);
    irPin = irpin;
}

void RobotController::setMotorPin(int rmpin1,int rmpin2, int lmpin1, int lmpin2)
{
    rmPin1 = rmpin1;
    rmPin2 = rmpin2;
    lmPin1 = lmpin1;
    lmPin2 = lmpin2;

    pinMode(rmPin1, OUTPUT);
    pinMode(rmPin2, OUTPUT);
    pinMode(lmPin1, OUTPUT);
    pinMode(lmPin2, OUTPUT);
}

void RobotController::goForward()
{
    // 別の命令のフラグを初期化
    backFlag = 0;
    rightFlag = 0;
    leftFlag = 0;

    // 同じ命令2回呼び出しを防止
    if (forwardFlag == 0)
    {
        stopFlag = 1;
        stop();
        delayMicroseconds(100);
    }

    // 前進
    digitalWrite(lmPin1, LOW);
    digitalWrite(lmPin2, HIGH);
    digitalWrite(rmPin1, LOW);
    digitalWrite(rmPin2, HIGH);
    Serial.println("Go forward");
    forwardFlag = 1;
    stopFlag = 0;
}

void RobotController::goBack()
{
    // 別の命令のフラグを初期化
    forwardFlag = 0;
    rightFlag = 0;
    leftFlag = 0;

    // 同じ命令2回呼び出しを防止
    if (backFlag == 0)
    {
        stopFlag = 1;
        stop();
        delayMicroseconds(100);
    }

    // 後退
    digitalWrite(lmPin1, HIGH);
    digitalWrite(lmPin2, LOW);
    digitalWrite(rmPin1, HIGH);
    digitalWrite(rmPin2, LOW);
    Serial.println("Go back");
    backFlag = 1;
    stopFlag = 0;
}

void RobotController::turnRight()
{
    // 別の命令のフラグを初期化
    backFlag = 0;
    forwardFlag = 0;
    leftFlag = 0;

    // 同じ命令2回呼び出しを防止
    if (rightFlag == 0)
    {
        stopFlag = 1;
        stop();
        delayMicroseconds(100);
    }

    // 右
    digitalWrite(lmPin1, LOW);
    digitalWrite(lmPin2, HIGH);
    digitalWrite(rmPin1, LOW);
    digitalWrite(rmPin2, LOW);
    Serial.println("Turn right");
    rightFlag = 1;
    stopFlag = 0;
}

void RobotController::turnLeft()
{
    // 別の命令のフラグを初期化
    backFlag = 0;
    rightFlag = 0;
    forwardFlag = 0;

    // 同じ命令2回呼び出しを防止
    if (leftFlag == 0)
    {
        stopFlag = 1;
        stop();
        delayMicroseconds(100);
    }

    // 左
    digitalWrite(lmPin1, LOW);
    digitalWrite(lmPin2, LOW);
    digitalWrite(rmPin1, LOW);
    digitalWrite(rmPin2, HIGH);
    Serial.println("Turn left");
    leftFlag = 1;
    stopFlag = 0;
}

void RobotController::stop()
{
    digitalWrite(lmPin1, LOW);
    digitalWrite(lmPin2, LOW);
    digitalWrite(rmPin1, LOW);
    digitalWrite(rmPin2, LOW);
    if (stopFlag == 0) {
        Serial.println("Stop");
    }
}

void RobotController::brake()
{
    digitalWrite(lmPin1, HIGH);
    digitalWrite(lmPin2, HIGH);
    digitalWrite(rmPin1, HIGH);
    digitalWrite(rmPin2, HIGH);
    
}


// 指定した部分の赤外線信号(配列)を取得する関数
int RobotController::getIrValue(char somePoint) {
    getIr(); 
    int signValue = IrData[somePoint-1];
    return signValue;
}

// 赤外線データを表示
void RobotController::showIrValue() {
    int val = getIr();
    for(int i=0;i<val;i++) {
        Serial.print(IrData[i], BIN);
    }
    Serial.print(" ( ");
    for(int i=0;i<val;i++) {
        Serial.print(IrData[i]);
        Serial.print(" ");
    }
    Serial.print(")");
    Serial.println();
}

// 赤外線信号を受信して、IrDataに格納 
int RobotController::getIr()
{
    unsigned long t;
    int i,j,k;
    int cnt;
    int x;
    char *pIrBit;

    if(digitalRead(irPin)==LOW) {
        t = micros();
        while(digitalRead(irPin)==LOW);
        t = micros() - t;
    }
  
    if(t >= 3400){
        i = 0;
        while(digitalRead(irPin)== HIGH);
        while(1){
            while(digitalRead(irPin)== LOW);
            t = micros();
            cnt = 0;
            while(digitalRead(irPin)== HIGH){
                delayMicroseconds(10);
                cnt++;
                if(cnt >= 1200){
                    break;
                }
            }
            t = micros() - t;
            if (t >= 10000) break;
            if (t >= 1000) IrBit[i] = 1;
            else           IrBit[i] = 0;
            i++;
        }
        IrBit[i] = 0;
        pIrBit = &IrBit[0];
        x = i / 8;

        for (j=0; j<x; j++) {
            IrData[j] = 0;
            for (k=0; k<8; k++) {
                if(*pIrBit == 1) bitSet(IrData[j],k);
                pIrBit++;
            }
        }
    }
    // IrDataに格納した配列の数を返す。
    return j;
}


