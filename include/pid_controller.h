#pragma once


//pid主要利用误差，也就是目标输出以及实际输出的差值来进行算法控制，最后得出控制电机的output
//也就是电机用多大劲

class PID_Controller{
    public:
        PID_Controller(double kp,double ki,double kd,
                    double max_output = 1.0,double min_output = 0.0);
        double update(double target,double measured,double dt);
        void reset();
    
    private:
        double kp_;
        double ki_;
        double kd_;
        double max_output_;
        double min_output_;
        double integral_; //累计积分，配合Ki；
        double prev_measurement_; //上一时刻记录的值，算变化率；
        bool has_prev_measurement_; //告诉微分刚开始启动时没有上一时刻的值
};