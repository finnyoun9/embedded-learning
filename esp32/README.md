# ESP32 学习笔记

基于 PlatformIO + Arduino 框架的 ESP32 开发学习。

## 环境

- **开发板**: ESP32-D0WD-V3 (DevKit)
- **工具链**: PlatformIO Core 6.1.19, espressif32 @ 7.0.1
- **框架**: Arduino (framework-arduinoespressif32 @ 3.20017)
- **串口**: /dev/cu.usbserial-1110, 115200 bps

## 常用命令

```bash
pio run                     # 编译
pio run -t upload           # USB 烧录
pio run -t upload --upload-port <IP>  # OTA 无线烧录
pio device monitor          # 串口监视器
```

## 学习路线

### 1. GPIO 基础
- **串口输出** — `Serial.begin()` / `Serial.println()`, 嵌入式最基本的调试手段
- **按键输入** — `pinMode(pin, INPUT_PULLUP)`, 内置上拉电阻
- **PWM 呼吸灯** — `analogWrite(pin, 0-255)`, LED 渐亮渐灭

### 2. 无线通信
- **WiFi + Web 服务器** — `WiFi.begin()` + `WebServer`, 在浏览器控制 LED
- **MQTT 协议** — `PubSubClient`, IoT 设备间通信标准协议。发布传感器数据，订阅控制指令。Broker: test.mosquitto.org
- **OTA 无线烧录** — `ArduinoOTA`, WiFi 推送固件，无需 USB。注意事项：避免 `delay()` 阻塞 OTA

### 3. 传感器与执行器
- **超声波测距 HC-SR04** — `pulseIn()` 测量脉冲宽度 + 声速换算距离
- **无源蜂鸣器** — `tone(pin, freq)` 频率输出，串联 1KΩ 限流保护 GPIO

### 4. 显示与接口
- **I2C 总线 + OLED** — `Wire` 库, SSD1306 128x64 单色屏, 两线地址寻址
- **三大接口对比**

| 接口 | 线数 | 速度 | 典型场景 |
|------|------|------|---------|
| UART | 2 (TX+RX) | 慢 | 调试串口、GPS 模块 |
| I2C | 2 (SDA+SCL) | 中 | 多设备总线、传感器、小屏 |
| SPI | 4 (MOSI+MISO+SCK+CS) | 最快 | 高速屏、SD 卡 |

### 5. 多模块整合
- **倒车雷达项目** — 超声波测距 + OLED 显示距离 + 蜂鸣器分级报警 (SAFE/WARNING/DANGER)

### 6. 双核 RTOS
- **FreeRTOS** — `xTaskCreatePinnedToCore()` 将任务绑到不同核心，`xQueueCreate()` 核间安全传递数据

### 7. 文件系统
- **LittleFS** — Flash 当成磁盘用，存储 WiFi 配置、网页 HTML、启动日志、持久化状态

## 项目文件

```
blink/
├── platformio.ini          # 项目配置（USB + OTA 双环境）
├── src/
│   └── main.cpp            # 主程序（LittleFS 综合演示）
├── lib/
│   ├── SSD1306/            # 自写 OLED 驱动（I2C, 5x8 字体）
│   └── PubSubClient/       # 自写 MQTT 客户端
```

## 硬件清单

| 模块 | 型号 | 接口 | 引脚 |
|------|------|------|------|
| LED | 板载 | GPIO | D2 |
| 超声波传感器 | HC-SR04 | GPIO | TRIG=D5, ECHO=D18 |
| OLED 屏幕 | SSD1306 0.96" | I2C | SCL=D22, SDA=D21 |
| 无源蜂鸣器 | 8Ω 1.5W | PWM | D25 (串联 1KΩ) |
