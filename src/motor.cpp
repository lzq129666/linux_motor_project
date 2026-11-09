#include "motor.h"
#include <iostream>
#include <iomanip>

Motor::Motor(const std::string& id){
    state_.motor_id = id; //初始化 设置电机id
}

void Motor::start(){
    state_.running = true; //运行电机
}

void Motor::stop(){
    state_.running = false; //停止电机
    state_.output = 0.0; //当前停止电机时直接将电机转速设为0，后续需更改
}

bool Motor::setTargetSpeed(double rpm){
    // 第一版仿真规定目标转速范围为 0～1500 rpm。
    if(rpm > 1500 || rpm < 0){
        std::cout << "转速设定错误,转速须在0~1500rpm";
        return false;
    }
    else{
        state_.target_rpm = rpm; //设置目标转速
        return true;
    }
}

void Motor::printMotorStatus() const{           //打印电机状态
    std::cout << std::fixed << std::setprecision(2);
    std::cout << "电机ID" << state_.motor_id << std::endl
    << "目标转速" << state_.target_rpm << std::endl
    << "实际转速" << state_.actual_rpm << std::endl 
    << "电机输出" << state_.output << std::endl
    << "电机状态" << (state_.running ? "运行" : "停止") ;
}

const MotorState& Motor::getMotorState() const{
    return state_;
}
