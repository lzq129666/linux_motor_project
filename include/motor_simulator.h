#pragma once


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