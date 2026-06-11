# 硬件外设清单 & 学习路线

> 最后更新：2026-06-11  
> 持续补充中，后面买了新东西会继续往这里加。

---

## 一、MCU / 开发板

| # | 设备 | 说明 | 学习状态 |
|---|------|------|----------|
| 1 | **STM32 江科大全套件** | 含主板 + 各种传感器/模块 + **平衡车项目（带遥控器）** | 🔵 当前主线 |
| 2 | **Arduino 开发板** | Arduino UNO 或兼容板 | ⚪ 待开始 |
| 3 | **ESP32 开发板** | WiFi/BLE 双模，适合 IoT。开发环境：VSCode + PlatformIO (Arduino 框架) | 🟢 已上手（blink + 逻辑分析仪） |

**学习顺序**：STM32（裸机 + FreeRTOS）→ Arduino（快速原型）→ ESP32（无线通信）

---

## 二、烧录 & 调试工具

| # | 设备 | 用途 |
|---|------|------|
| 4a | **ST-Link V2** | STM32 烧录/调试 |
| 4b | **USB 转 TTL** | 串口通信（UART） |
| 4c | **面包板** | 免焊接电路搭建 |

---

## 三、电机

| # | 类型 | 用途 |
|---|------|------|
| 5a | **直流电机（DC Motor）** | 基础驱动，PWM 调速 |
| 5b | **步进电机（Stepper）** | 精确角度控制 |
| 5c | **无刷电机（BLDC）** | 高性能驱动，面试重点项目 |

**学习顺序**：直流 → 步进 → 无刷（BLDC 是面试核心）

---

## 四、逻辑分析仪使用指南

**硬件**：24MHz 8CH（Saleae 兼容，CY7C68013A），macOS 通过 `sigrok-cli` + PulseView 使用。

### 快速上手

```bash
# 1. 检测设备
sigrok-cli --scan
# 应显示：fx2lafw - Saleae Logic with 8 channels

# 2. 采集信号（例：CH1/D0 接 ESP32 GPIO2）
sigrok-cli -d fx2lafw --samples 3M -c samplerate=1M --channels D0 -o capture.sr

# 3. 生成波形图
sigrok-cli -i capture.sr -O vcd -o capture.vcd
python3 scripts/view_wave.py capture.vcd capture.png

# 4. 协议解码（在 PulseView 中 File→Open capture.sr → 加解码器）
```

### 常用协议接线

| 协议 | 通道 | sigrok-cli 参数 |
|------|------|----------------|
| I2C | CH1=SCL, CH2=SDA | `-P i2c:scl=1:sda=2` |
| SPI | CH1=CLK, CH2=MISO, CH3=MOSI, CH4=CS | `-P spi:clk=1:miso=2:mosi=3:cs=4` |
| UART | CH1=RX | `-P uart:rx=1:baudrate=115200` |

⚠️ **GND 必须接被测电路 GND，否则波形全乱。**

---

## 五、传感器 & 外设

| # | 设备 | 用途 |
|---|------|------|
| 6 | **OV7670 摄像头** | FIFO 摄像头模组，图像采集 |

---

## 六、测量 & 输出

| # | 设备 | 用途 |
|---|------|------|
| 7a | **万用表** | 电压/电流/电阻/通断测量 |
| 7b | **逻辑分析仪** | 24MHz 8CH（Saleae 兼容），信号时序分析 |
| 7c | **小喇叭** | 音频输出 / PWM 蜂鸣 |

---

## 七、接线 & 工具

| # | 设备 | 用途 |
|---|------|------|
| 8a | **剥线钳** | 剥线皮 |
| 8b | **2.54mm 端子全套** | 含压端子钳，可自制杜邦线 |
| 8c | **杜邦线 / 细线** | 配合端子钳自制连接线 |

> 有了压端子工具，可以直接用细线 + 2.54 端子自制杜邦线，调试接线更灵活。

---

## 学习路线总览

```
STM32 裸机（江科大套件）
  ├── GPIO、定时器、中断、PWM
  ├── 直流电机驱动
  ├── 步进电机驱动
  ├── 串口通信（UART / TTL）
  └── 平衡车项目（综合实战）
      │
      ▼
FreeRTOS（在 STM32 上）
  │
  ▼
BLDC 无刷电机（FOC 控制）★ 面试核心
  │
  ▼
Arduino（快速原型验证）
  │
  ▼
ESP32（WiFi/BLE 通信）
  │
  ▼
OV7670 摄像头（图像采集）
```

---

## 变更日志

| 日期 | 变更 |
|------|------|
| 2026-06-11 | 新增文档；新增逻辑分析仪使用指南 + `view_wave.py` 脚本；ESP32 状态更新为已上手 |
| 2026-06-11 | 初始创建，整理全套外设清单及学习路线 |
