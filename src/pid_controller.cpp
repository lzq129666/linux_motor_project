#include "pid_controller.h"
#include <algorithm>

//初始化列表
PID_Controller::PID_Controller(double kp, double ki, double kd, 
                                double max_output, double min_output):
                                kp_(kp),ki_(ki),kd_(kd),max_output_(max_output),
                                min_output_(min_output),integral_(0.0),prev_measurement_(0.0)
                                ,has_prev_measurement_(false)
{
}

double PID_Controller::update(double target,double measured,double dt){
    if(dt <= 0.0) return 0.0; //dt必须大于0
    double error = target - measured;//计算误差

    double proposed_integral = integral_ + error * dt;//计算积分项

    double derivative = 0.0; //计算微分项
    if(has_prev_measurement_){
        derivative = (measured - prev_measurement_)/ dt;
    }

    //计算原始输出（没有限幅时） 经典pid控制公式
    double raw_output = kp_*error + ki_*proposed_integral - kd_*derivative;

    //积分饱和判断
    bool integral_saturation = (raw_output > max_output_ && error > 0) ||
                                (raw_output < min_output_ && error < 0);
    if(!integral_saturation){
        integral_ = proposed_integral; //不饱和才接受本次积分
    }
    //计算最终输出（有限幅时） 经典pid控制公式
    double final_output = kp_*error + ki_*integral_ - kd_*derivative;
    final_output = std::clamp(final_output, min_output_, max_output_);
    //记录本次测量值
    prev_measurement_ = measured;
    has_prev_measurement_ = true;
    return final_output;
}

void PID_Controller::reset(){
    has_prev_measurement_ = false;
    prev_measurement_ = 0.0;
    integral_ = 0.0;
}


