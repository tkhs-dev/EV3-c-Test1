/**
 * This sample program balances a two-wheeled Segway type robot such as Gyroboy in EV3 core set.
 *
 * References:
 * http://www.hitechnic.com/blog/gyro-sensor/htway/
 * http://www.cs.bgu.ac.il/~ami/teaching/Lejos-2013/classes/src/lejos/robotics/navigation/Segoway.java
 */

#include "ev3api.h"
#include "app.h"

#include "libcpp-test.h"

#define DEBUG

#ifdef DEBUG
#define _debug(x) (x)
#else
#define _debug(x)
#endif

class Motor {
public:
    Motor(motor_port_t port,motor_type_t type) {
        Port=port;
        Type=type;

        ev3_motor_config(port,type);
    }

    motor_port_t getPort() {
        return Port;
    }
    motor_type_t getType(){
        return Type;
    }

    //override
    int32_t getCounts (){
        return ev3_motor_get_counts(Port);
    }
    int getPower (){
        return ev3_motor_get_power(Port);
    }
    void resetCounts(){
        ev3_motor_reset_counts(Port);
    }
    void Rrotate (int degrees, uint32_t speed_abs, bool_t blocking ){
        ev3_motor_rotate(Port,degrees,speed_abs,blocking);
    }
    void setPower (int power){
        ev3_motor_set_power(Port,power);
    }
    void stop(bool_t brake){
        ev3_motor_stop(Port,brake);
    }


private:
    motor_type_t Type;
    motor_port_t Port;
};

class Steering {
public:
    Steering(Motor *left,Motor *right){
        Left=left;
        Right=right;
    }
    void moveSteering(int power,int turn_rutio){
        ev3_motor_steer(Left->getPort(),Right->getPort(),power,turn_rutio);
    }

private:
    Motor *Left;
    Motor *Right;
};

//基本設定
    //ポート設定
    Motor *LeftMotor;
    Motor *RightMotor;
    Steering *Steer;

void main_task(intptr_t unused) {
    //don't override
    initialize();

    //以下書き換え可
    LeftMotor->Rrotate(360,100,false);
}
void initialize(){
    //メンバー初期化
    LeftMotor = new Motor(EV3_PORT_B,LARGE_MOTOR);
    RightMotor = new Motor(EV3_PORT_C,LARGE_MOTOR);
    Steer = new Steering(LeftMotor,RightMotor);
}
