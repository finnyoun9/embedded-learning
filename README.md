# Embedded Learning — 嵌入式系统学习与项目展示

> 🎯 **目标**：从扫地机器人测试工程师转型深圳嵌入式工程师（2026年4月）
> 
> 本仓库记录从 STM32 裸机编程到 ROS2 机器人系统的完整学习路径。
> 包含实战代码、硬件笔记、传感器驱动、项目文档。

---

## 🛠 硬件资源

| 设备 | 用途 | 状态 |
|------|------|------|
| STM32F103C8T6 (Blue Pill) | 裸机/RTOS 主控 | ✅ 活跃 |
| Raspberry Pi 5 | Linux + ROS2 上位机 | ✅ 活跃 |
| Arduino | 快速原型 | 📦 待用 |
| VL53L0X ToF 测距 | I2C 距离传感器 | ✅ 已有驱动 |
| OV7670 摄像头 | 图像采集 | 📦 待调试 |
| 逻辑分析仪 | 协议调试 (I2C/SPI/UART/CAN) | ✅ 活跃 |
| DP100 数控电源 | 功耗分析 | ✅ 活跃 |
| ST-Link V2 | 烧录/调试 | ✅ 活跃 |

---

## 📂 仓库结构

```
embedded-learning/
├── README.md                    ← 你在这里
├── CHANGELOG.md                 ← 更新日志
├── .gitignore
│
├── projects/                    ← 实战项目代码
│   └── stm32/
│       ├── 01-blink/            ← 裸机 GPIO + SysTick
│       └── 02-oled-i2c/         ← 裸机 I2C + SSD1306 驱动
│
├── notes/                       ← 学习笔记 & 路线规划
│   ├── STM32扫地机器人学习指南.md
│   ├── ROS2学习路线.md
│   ├── RaspberryPi科学上网配置.md
│   └── 飞书CLI使用笔记.md
│
├── hardware/                    ← 硬件参考（datasheet、引脚图）
├── tools/                       ← 工具使用文档（逻辑分析仪、DP100、OpenOCD）
├── vendor/                      ← 第三方 SDK（VL53L0X、OV7670）
├── ros2/                        ← ROS2 学习与代码
│   └── ROS2学习路线.md
│
└── planning/                    ← 学习计划 & 求职调研
    ├── README.md                ← 项目路线图总览
    ├── project-roadmap.md       ← 4 阶段实战项目路线
    └── shenzhen-job-market.md   ← 深圳嵌入式岗位调研
```

---

## 🚀 当前进度

### ✅ 已掌握

- **裸机寄存器编程**：GPIO 控制、SysTick 定时器、中断处理
- **I2C 通信**：SSD1306 OLED 驱动（自主编写，非库调用）
- **ARM Cortex-M3 基础**：向量表、链接脚本、时钟树配置
- **工具链**：arm-none-eabi-gcc + CMake + OpenOCD + ST-Link（纯命令行，无 IDE 依赖）
- **ROS2 基础**：话题、节点、TF2、Gazebo 仿真

### 🔨 进行中

- VL53L0X ToF 传感器 I2C 驱动（裸机寄存器级）
- ROS2 机器人仿真（SLAM + Nav2）

### 📋 待启动

- [ ] FreeRTOS 多任务传感器采集
- [ ] STM32 ↔ Pi 5 串口通信协议
- [ ] 差分驱动底盘 PID 控制
- [ ] 逻辑分析仪 I2C/SPI 波形分析
- [ ] DP100 功耗分析

---

## 🔧 开发环境

| 工具 | 版本/路径 |
|------|----------|
| arm-none-eabi-gcc | 16.1.0 (`/opt/homebrew/bin/`) |
| CMake | 4.3.3 |
| OpenOCD | 0.12.0 |
| ST-Link | 1.8.0 |
| PlatformIO | 6.1.19 |
| ROS2 | Jazzy (UTM Ubuntu 24.04 VM) |
| 串口 | picocom 3.1 |

**纯命令行工具链，不依赖 Keil/IAR。**

---

## 📖 语言约定

- 📝 文档 & 笔记：**中文**
- 💻 代码、变量名、commit message：**English**
- 🔧 命令 & 终端输出：**English**

---

## 📊 统计

![GitHub last commit](https://img.shields.io/github/last-commit/finnyoun9/embedded-learning)
![GitHub repo size](https://img.shields.io/github/repo-size/finnyoun9/embedded-learning)

---

## 🔗 相关链接

- [GitHub Profile](https://github.com/finnyoun9)
- [ROS2 学习路线](ros2/ROS2学习路线.md)
- [STM32 扫地机器人学习指南](notes/STM32扫地机器人学习指南.md)
- [4 阶段实战项目路线](planning/project-roadmap.md)
- [深圳嵌入式岗位调研](planning/shenzhen-job-market.md)

---

> *"Talk is cheap. Show me the code."* — Linus Torvalds
