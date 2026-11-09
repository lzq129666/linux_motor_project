#pragma once
#include <string>

//motorstate仅保存电机状态

struct MotorState
{
    std::string motor_id = "motor_01";
    double target_rpm = 0.0;     //目标转速，单位rpm
    double actual_rpm = 0.0;     //实际转速，单位rpm
    double output = 0;           //电机输出，约定范围[0,1]
    bool running = false;        //表示停止状态
}; 

