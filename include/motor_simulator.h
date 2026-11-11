#pragma once

//这是搞电机仿真的程序 虚拟一个包含物理特性的电机 比如电机响应延迟tau 以及负载
//主要是update是用来仿真实现电机转速的程序，
//实时转速=下一次转速 = 当前转速 + (时间步长 / 时间常数) * (理想驱动转速 - 当前转速 - 负载)
//理想驱动速度就需要用到output了，output就是控制电机用多大劲

class MotorSimulator{
    public:
        MotorSimulator(double max_rpm = 1500.0,double tau = 0.5);//max_rpm最大转速对应output=1.0，tau时间常数对应电机响应快慢
        void setControlOutput(double output); //设置控制输出
        void setLoad(double load_rpm); //设置负载扰动
        void update(double dt); //执行一个仿真时间步，dt是距离上次更新的时间差
        double getSpeed() const; //获取电机实际转速
        void reset(); //重置电机状态，使得转速归零
    
    private:
        double max_rpm_;
        double output_;
        double load_rpm_; 
        double realtime_speed_;
        double tau_;
};