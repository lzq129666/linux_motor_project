#include "motor_simulator.h"
#include <iostream>
#include <iomanip>

int main()
{
    // 创建电机模型：最大 1500 转，惯性时间常数 0.5 秒
    MotorSimulator sim(1500.0, 0.5);

    std::cout << "=== 阶段 2：测试电机惯性模型 ===\n";
    
    // 假设我们猛踩油门，输出 1.0（满功率）
    sim.setControlOutput(1.0);
    std::cout << "给满输出，理论目标转速: 1500 rpm\n\n";

    // 模拟 100 个时间步，每步 10 毫秒（总共 1 秒）
    double dt = 0.01; // 10ms
    
    for (int i = 0; i <= 100; ++i)
    {
        // 每隔 10 步（0.1 秒）打印一次状态
        if (i % 10 == 0)
        {
            std::cout << "时间: " << std::fixed << std::setprecision(2) << (i * dt) << " 秒, "
                      << "当前实际转速: " << std::setprecision(2) << sim.getSpeed() << " rpm\n";
        }

        // 更新物理模型，推动时间前进
        sim.update(dt);
    }

    return 0;
}