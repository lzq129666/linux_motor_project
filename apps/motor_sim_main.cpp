#include "motor_simulator.h"
#include "pid_controller.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>

int main()
{
    std::ofstream csv_file("logs/motor_test.csv");
    csv_file << "time,target,actual,output,load\n";//创建csv文件并写入表头
    // 1. 创建电机模型和 PID 控制器
    MotorSimulator sim(1500.0, 0.5); // 最大 1500 转，惯性 0.5 秒
    // 尝试调整 Kp, Ki, Kd 看看效果
    PID_Controller pid(0.02, 0.01, 0.0); 

    double target_rpm = 800.0; // 我们的目标转速
    double dt = 0.01;          // 每步 10 毫秒

    std::cout << "=== 阶段 3：PID 闭环控制测试 ===\n";
    std::cout << "目标转速: " << target_rpm << " rpm\n\n";

    // 模拟 500 个时间步（总共 5 秒）
    for (int i = 0; i <= 1000; ++i)
    {   
        double Feedforward;
        Feedforward = target_rpm/1500; //前馈算油门
        if(i == 500) sim.setLoad(300);//突然加负载扰动
        // A. 获取电机的实际转速
        double actual_rpm = sim.getSpeed();

        // B. 把目标转速和实际转速交给 PID 算一算，得到新的“油门”
        double output = pid.update(target_rpm, actual_rpm, dt);
        
        //前馈加pid就是总输出
        double total_output = Feedforward + pid.update(target_rpm, actual_rpm, dt);
        total_output = std::clamp(total_output, 0.0, 1.0);
        
        // C. 把算出来的油门，塞给电机模型
        sim.setControlOutput(total_output);

        // D. 推演一步物理时间（电机转速发生变化）
        sim.update(dt);

        csv_file << std::fixed << std::setprecision(2);
        csv_file << (i * dt) << "," 
            << target_rpm << "," 
            << actual_rpm << "," 
            << output << "," 
            << (i >= 500 ? 300.0 : 0.0) << "\n"; //这里的300是负载转速

        // 每隔 0.5 秒（50步）打印一次状态
        if (i % 50 == 0)
        {
            std::cout << "时间: " << std::fixed << std::setprecision(1) << (i * dt) << " 秒 | "
                      << "实际转速: " << std::setprecision(1) << actual_rpm << " rpm | "
                      << "PID输出(油门): " << std::setprecision(3) << output << "\n";
        }
    }
    csv_file.close();
    return 0;
}