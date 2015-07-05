#include "arduino.h"
#include "FairingRobot.h"

// コンストラクタ (IRPIN, データポイント1, データポイント2)
//FairingRobot::FairingRobot ()
//{
//}

// 初期化
void FairingRobot::init()
{
    // モーターを逆転するときにstop()を入れるためのフラグ
    this->forwardFlag = 0;
    this->backFlag    = 0;
    this->rightFlag   = 0;
    this->leftFlag    = 0;
    this->stopFlag    = 0;
}

void FairingRobot::setIrPin(const int somePin)
{
    pinMode(somePin, INPUT);
    irPin = somePin;
}

void FairingRobot::setMotorR(const int rmPin1, const int rmPin2)
{
    this->rmPin1 = rmPin1;
    this->rmPin2 = rmPin2;

    pinMode(this->rmPin1, OUTPUT);
    pinMode(this->rmPin2, OUTPUT);
}

void FairingRobot::setMotorL(const int lmPin1, const int lmPin2)
{
    this->lmPin1 = lmPin1;
    this->lmPin2 = lmPin2;

    pinMode(this->lmPin1, OUTPUT);
    pinMode(this->lmPin2, OUTPUT);
}


void FairingRobot::goForward()
{
    // 別の命令のフラグを初期化
    this->backFlag = 0;
    this->rightFlag = 0;
    this->leftFlag = 0;

    // 同じ命令2回呼び出しを防止
    if (this->forwardFlag == 0)
    {
        this->stopFlag = 1;
        stop();
        delayMicroseconds(100);
    }

    // 前進
    digitalWrite(this->lmPin1, HIGH);
    digitalWrite(this->lmPin2, LOW);
    digitalWrite(this->rmPin1, HIGH);
    digitalWrite(this->rmPin2, LOW);
    Serial.println("Go forward");
    this->forwardFlag = 1;
    this->stopFlag = 0;
}

void FairingRobot::goBack()
{
    // 別の命令のフラグを初期化
    this->forwardFlag = 0;
    this->rightFlag = 0;
    this->leftFlag = 0;

    // 同じ命令2回呼び出しを防止
    if (this->backFlag == 0)
    {
        this->stopFlag = 1;
        stop();
        delayMicroseconds(100);
    }

    // 後退
    digitalWrite(this->lmPin1, LOW);
    digitalWrite(this->lmPin2, HIGH);
    digitalWrite(this->rmPin1, LOW);
    digitalWrite(this->rmPin2, HIGH);
    Serial.println("Go back");
    this->backFlag = 1;
    this->stopFlag = 0;
}

void FairingRobot::turnRight()
{
    // 別の命令のフラグを初期化
    this->backFlag = 0;
    this->forwardFlag = 0;
    this->leftFlag = 0;

    // 同じ命令2回呼び出しを防止
    if (this->rightFlag == 0)
    {
        this->stopFlag = 1;
        stop();
        delayMicroseconds(100);
    }

    // 右
    digitalWrite(this->lmPin1, HIGH);
    digitalWrite(this->lmPin2, LOW);
    digitalWrite(this->rmPin1, LOW);
    digitalWrite(this->rmPin2, LOW);
    Serial.println("Turn right");
    this->rightFlag = 1;
    this->stopFlag = 0;
}

void FairingRobot::turnLeft()
{
    // 別の命令のフラグを初期化
    this->backFlag = 0;
    this->rightFlag = 0;
    this->forwardFlag = 0;

    // 同じ命令2回呼び出しを防止
    if (this->leftFlag == 0)
    {
        this->stopFlag = 1;
        stop();
        delayMicroseconds(100);
    }

    // 左
    digitalWrite(this->lmPin1, LOW);
    digitalWrite(this->lmPin2, LOW);
    digitalWrite(this->rmPin1, HIGH);
    digitalWrite(this->rmPin2, LOW);
    Serial.println("Turn left");
    this->leftFlag = 1;
    this->stopFlag = 0;
}

void FairingRobot::stop()
{
    digitalWrite(this->lmPin1, LOW);
    digitalWrite(this->lmPin2, LOW);
    digitalWrite(this->rmPin1, LOW);
    digitalWrite(this->rmPin2, LOW);
    if (this->stopFlag == 0) {
        Serial.println("Stop");
    }
}

void FairingRobot::brake()
{
    digitalWrite(this->lmPin1, HIGH);
    digitalWrite(this->lmPin2, HIGH);
    digitalWrite(this->rmPin1, HIGH);
    digitalWrite(this->rmPin2, HIGH);
    
}


// 指定した部分の赤外線信号(配列)を取得する関数
int FairingRobot::getIrValue(char somePoint) {
    getIr(); 
    int signValue = this->IrData[somePoint-1];
    return signValue;
}

// 赤外線データを表示
void FairingRobot::showIrValue() {
    int val = getIr();
    for(int i=0;i<val;i++) {
        Serial.print(this->IrData[i], BIN);
    }
    Serial.print(" ( ");
    for(int i=0;i<val;i++) {
        Serial.print(this->IrData[i]);
        Serial.print(" ");
    }
    Serial.print(")");
    Serial.println();
}

// 赤外線信号を受信して、IrDataに格納 
int FairingRobot::getIr()
{
    unsigned long t;
    int i,j,k;
    int cnt;
    int x;
    char *pIrBit;

    if(digitalRead(this->irPin)==LOW) {
        t = micros();
        while(digitalRead(this->irPin)==LOW);
        t = micros() - t;
    }
  
    if(t >= 3400){
        i = 0;
        while(digitalRead(this->irPin)== HIGH);
        while(1){
            while(digitalRead(this->irPin)== LOW);
            t = micros();
            cnt = 0;
            while(digitalRead(this->irPin)== HIGH){
                delayMicroseconds(10);
                cnt++;
                if(cnt >= 1200){
                    break;
                }
            }
            t = micros() - t;
            if (t >= 10000) break;
            if (t >= 1000) this->IrBit[i] = 1;
            else           this->IrBit[i] = 0;
            i++;
        }
        this->IrBit[i] = 0;
        pIrBit = &IrBit[0];
        x = i / 8;

        for (j=0; j<x; j++) {
            this->IrData[j] = 0;
            for (k=0; k<8; k++) {
                if(*pIrBit == 1) bitSet(this->IrData[j],k);
                pIrBit++;
            }
        }
    }
    // IrDataに格納した配列の数を返す。
    return j;
}


