#pragma once       
#include "motor_state.h"
#include <string>
//这是电机的控制程序 启动、停止、设置转速什么的 

class Motor{
    
    public:
        explicit Motor(const std::string& id);//创建电机对象时设置id
        void start();                   //启动电机 motor类里面的函数名不需要加motor
        void stop();                    //停止电机
        bool setTargetSpeed(double rpm);    //设置目标转速，成功时返回true失败false
        void printMotorStatus() const;      //在终端打印电机状态，const表示只读
        const MotorState& getMotorState() const; //只读电机状态且不能进行修改
    
    private:
        MotorState state_; //私有变量加个_  

};