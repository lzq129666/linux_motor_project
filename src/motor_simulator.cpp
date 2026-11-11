#include "motor_simulator.h"
#include "motor_state.h"
#include "motor.h"

MotorSimulator::MotorSimulator(double max_rpm ,double tau ){
    if(max_rpm < 0) max_rpm_ = 1500;
    if(tau < 0) tau_ = 0.5;
    output_ = 0.0;
    load_rpm_ = 0.0;
    realtime_speed_ = 0.0;
    max_rpm_ = max_rpm;
    tau_ = tau;
}

void MotorSimulator::setLoad(double load_rpm){
    load_rpm_ = load_rpm;
}

void MotorSimulator::setControlOutput(double output){
    if(output < 0) output_ = 0;
    if(output > 1) output_ = 1;
    output_ = output;
}

void MotorSimulator::update(double dt){
    if( dt < 0) return;
    double motor_drive_rpm = output_ * max_rpm_;
    //实时转速=下一次转速 = 当前转速 + (时间步长 / 时间常数) * (理想驱动转速 - 当前转速 - 负载)
    realtime_speed_ += (dt/tau_)*(motor_drive_rpm - load_rpm_ - realtime_speed_);
    if(realtime_speed_ < 0){
        realtime_speed_ = 0;
    }
}

double MotorSimulator::getSpeed() const{
    return realtime_speed_;
}

void MotorSimulator::reset(){
    output_ = 0.0;
    load_rpm_ = 0.0;
    realtime_speed_ = 0.0;
}