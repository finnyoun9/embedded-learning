# STM32 扫地机器人学习指南

> 最后更新：2026-05-26

---

## 学习入口（从这里开始）

学习 STM32 扫地机器人，最怕的是资料不全、没人带、遇到问题卡住。本文整理了目前（2026年5月）资料最齐全的资源，以 **B站视频教程** 为主线，图文博客为补充，确保你每一步都跟得下来。

### 学习路径总览

```
阶段一：STM32 智能小车基础（2-3周）
  → 跟着 B站"好家伙VCC"保姆级视频，从点亮LED到PID走直线

阶段二：扫地机器人专项（2-3周）
  → 加上清扫机构、完善避障策略、实现弓字形路径

阶段三：进阶功能（选做，2-4周）
  → WiFi/App控制、沿墙清扫、自动回充、栅格地图
```

---

## 阶段一：STM32 智能小车基础（先学会走）

### 主线教程：B站「好家伙VCC」全网最详细 STM32 智能小车

这是目前中文互联网上**最适合新手**的 STM32 智能小车教程，手把手保姆级，有视频有代码有原理图，跟着做就能跑通。

| 项目 | 详情 |
|------|------|
| B站合集 | [BV16x4y1M7EN](https://www.bilibili.com/video/BV16x4y1M7EN/) |
| 主控 | STM32F103C8T6（蓝色小板，十几块钱） |
| 开发方式 | STM32CubeMX + HAL库 + Keil MDK |
| 视频量 | 20+ 章节、12+ 小时 |
| 配套资料 | 原理图、PCB文件、完整代码工程（夸克网盘下载） |
| 资料链接 | https://pan.quark.cn/s/959b889e058b |

#### 章节内容（与扫地机器人直接相关的重点标注 ★）

| 章节 | 内容 | 重要度 |
|------|------|--------|
| 第1-2章 | 小车硬件介绍、GPIO与中断 | ★★ |
| 第3-4章 | OLED显示、串口通信 | ★★ |
| 第5-6章 | PWM控制电机、电机驱动详解 | ★★★ |
| 第7-8章 | 编码器测速、PID速度控制 | ★★★ |
| 第9章 | PID参数整定方法 | ★★★ |
| 第10-11章 | 小车基础运动（前后左右）、OLED显示速度 | ★★★ |
| 第12章 | ADC采集电压（电池电量检测） | ★★ |
| 第13章 | 红外循迹（PID循迹） | ★★ |
| 第14章 | 蓝牙遥控（手机APP遥控） | ★★★ |
| 第15章 | 超声波避障 | ★★★ |
| 第16章 | 超声波跟随 | ★ |
| 第17章 | MPU6050陀螺仪（走直线、转90度） | ★★★ |
| 第18章 | 综合功能整合 | ★★★ |
| 第19章 | OpenMV视觉循迹 | ★ |
| 第20章 | 电磁循迹（选学） | ★ |

> **建议**：至少跟完第1-15章和第17章，这些是扫地机器人的核心基础。第19-20章可以后面再看。

#### 同步发布平台（遇到问题可去这些地方找答案）

- CSDN博客：搜索"好家伙VCC"
- 博客园：[cnblogs.com/haojiahuoVCC](https://www.cnblogs.com/haojiahuoVCC/)
- 21ic论坛：[完整教程贴](https://bbs.21ic.com/icview-3396550-1-1.html)
- 电子发烧友：[V3.3.0 HAL库详细笔记](https://m.elecfans.com/article/4938993.html)
- 51hei论坛：[硬件介绍+源码](http://www.51hei.com/bbs/forum.php?mod=viewthread&tid=237201)

---

## 阶段二：扫地机器人专项

基础小车跑通后，加入清扫功能，把它变成真正的扫地机器人。

### 主线教程一：B站开源扫地机器人视频（有完整资料）

| 视频 | BV号 | 播放量 | 特点 |
|------|------|--------|------|
| STM32智能蓝牙扫地机器人（开源） | [BV1A3pxzHEkn](https://www.bilibili.com/video/BV1A3pxzHEkn/) | 8万+ | 蓝牙APP+超声波避障+双模式 |
| 【开源】32B.基于STM32智能蓝牙扫地机器人 | [BV1Gj8bzFEeB](https://www.bilibili.com/video/BV1Gj8bzFEeB/) | 7.7万+ | 蓝牙遥控+自动避障 |
| 基于STM32扫地机器人实物设计 | [BV1QyBKBcENz](https://www.bilibili.com/video/BV1QyBKBcENz/) | - | 实物运行展示 |

> **获取资料方式**：在B站视频下三连+关注，评论区留言获取代码+原理图+PCB资料包。

### 主线教程二：MCUClub 项目资料站（资料最全）

MCUClub 上有多个 STM32 扫地机器人项目，每个都带完整资料包（C程序+原理图+设计报告+实物照片）：

| 项目编号 | 主控 | 核心功能 | 资料地址 |
|----------|------|----------|----------|
| dz-641 | STM32F103C8T6 | 舵机+超声波避障、红外循迹、蓝牙遥控、继电器吸尘 | [mcuclub.cn/archives/50495](https://www.mcuclub.cn/archives/50495) |
| dz-1108 | STM32F103C8T6 | 语音识别、干拖/湿拖/扫地、超声波避障、OLED显示 | [mcuclub.cn/archives/47943](https://www.mcuclub.cn/archives/47943) |
| dz-443 | STM32F103C8T6 | 超声波避障、GPS定位、蓝牙、自由/循迹双模式 | [mcuclub.cn/archives/48690](https://www.mcuclub.cn/archives/48690) |

> dz-641 功能最贴近"扫地机器人"三个字——有吸尘控制、有避障、有循迹、有蓝牙遥控，推荐作为扫地专项的首选参考资料。

### 主线教程三：工程级博客（深入理解架构）

| 文章 | 亮点 | 地址 |
|------|------|------|
| 基于STM32的工程级扫地机器人方案 | 分层架构、FSM状态机、弓字形路径、PID差速修正 | [CSDN](https://blog.csdn.net/yuan19997/article/details/161107161) / [博客园](https://www.cnblogs.com/45234ynn/p/20033393) |
| NullCXX三MCU协同架构（2026年2月） | 3颗STM32分工协作、工程化处理（散热/电源/隔离）、完整协议栈 | [CSDN](https://blog.csdn.net/flink9streamer/article/details/155756528) |
| 基于STM32的智能扫地机器人（含A*+DFS） | 栅格地图、A*路径规划、DFS全覆盖 | [CSDN](https://blog.csdn.net/ZSW1218/article/details/161265446) |
| 微信公众号：STM32智能扫地机器人 | PWM驱动、蓝牙HC-05、位置式PID完整代码 | [微信文章](https://mp.weixin.qq.com/s?__biz=Mzk0MTcxNjk1Mw==&mid=2247493829) |

---

## 阶段三：进阶功能（选做）

基础扫地机器人跑通后，按兴趣选择方向深入：

| 功能 | 难度 | 参考资源 |
|------|------|----------|
| 沿墙清扫 | ⭐⭐ | 好家伙VCC第15章超声波避障基础上改进，侧向保持恒定距离 |
| WiFi/App控制 | ⭐⭐ | ESP8266 + MQTT协议，好家伙VCC系列有ESP8266相关内容 |
| 自动回充 | ⭐⭐⭐ | 红外引导对接，需额外硬件 |
| 栅格地图 | ⭐⭐⭐ | 编码器+MPU6050定位 + DFS/BFS遍历 |
| 语音控制 | ⭐⭐ | 参考 dz-1108 项目的语音识别方案 |
| 实时系统 | ⭐⭐⭐ | 好家伙VCC系列支持RTOS版本，或参考51hei的FreeRTOS开源程序 |

---

## 系统架构设计

```
┌──────────────────────────────────────┐
│           应用层 (App/HMI)           │
│   蓝牙APP / WiFi MQTT / OLED显示     │
├──────────────────────────────────────┤
│           决策层                     │
│   状态机 (FSM) / 路径规划 / 避障     │
├──────────────────────────────────────┤
│           感知层                     │
│   超声波 │ 红外悬崖 │ MPU6050 │ 编码器 │
├──────────────────────────────────────┤
│           执行层                     │
│   电机PWM驱动 │ 吸尘控制 │ 边刷控制  │
├──────────────────────────────────────┤
│           硬件层                     │
│   STM32 + TB6612 + 传感器 + 电池     │
└──────────────────────────────────────┘
```

### 核心硬件选型

| 功能 | 推荐型号 | 理由 |
|------|----------|------|
| 主控 | **STM32F103C8T6** | 成本低（十几块），所有教程都基于它，资料最多 |
| 电机驱动 | **TB6612FNG** | 比 L298N 效率高、体积小，好家伙VCC教程同款 |
| 电机 | 带编码器的直流减速电机 | 实现PID速度闭环，走直线的前提 |
| 超声波 | HC-SR04 × 3（左/中/右） | 覆盖约 120° 前方视野 |
| 红外悬崖检测 | TCRT5000 × 3（底盘前缘） | 检测台阶/楼梯，防跌落 |
| 姿态传感器 | MPU6050（六轴） | 获取偏航角，辅助走直线和精确转90° |
| 蓝牙 | HC-05 或 JDY-31 | 手机APP遥控 |
| WiFi（进阶） | ESP8266（ESP-01S） | MQTT协议远程控制 |
| 显示 | 0.96寸 OLED（SSD1306） | 显示状态/电量/速度 |
| 电池 | 7.4V 18650锂电池组 (2S) | 供电持久，可充电 |

---

## 功能实现——按难度递进

### 第一级：底盘运动（最基础）

**目标**：走直线、转固定角度

```c
// PID 速度闭环 —— 扫地机器人能走直线的关键
void Motor_PID_Update(void) {
    int16_t speed_L = Encoder_Read(LEFT);
    int16_t speed_R = Encoder_Read(RIGHT);
    int16_t err = speed_L - speed_R;        // 差速 = 偏移量

    // 增量式 PI，10ms 调用一次
    int16_t adjust = Kp * err + Ki * err_integral;
    err_integral += err;
    if (err_integral > 500)  err_integral = 500;   // 积分限幅
    if (err_integral < -500) err_integral = -500;

    PWM_Set(LEFT,  target + adjust);
    PWM_Set(RIGHT, target - adjust);
}
```

> 跟学视频：好家伙VCC 第7-9章（编码器测速 → PID控制 → PID整定）

### 第二级：避障

**目标**：不撞墙、不摔下楼梯

```c
// 三级响应策略
if (ultra_center < 15.0f) {
    Robot_Stop();
    Robot_Backward(300ms);
    // 随机转向，防止卡死在角落
    (rand() & 1) ? Robot_TurnLeft(90) : Robot_TurnRight(90);
} else if (ultra_center < 30.0f) {
    // 减速并向更空旷的方向微调
    speed = SLOW_SPEED;
    if (ultra_left > ultra_right) yaw += 15;
    else                            yaw -= 15;
} else {
    speed = NORMAL_SPEED;   // 正常直行
}
```

> 跟学视频：好家伙VCC 第15章（超声波避障）

### 第三级：状态机

**目标**：让机器人"知道自己在干什么"

```c
typedef enum {
    STATE_IDLE,           // 待机
    STATE_CLEANING,       // 清扫直行
    STATE_AVOIDING,       // 避障后退
    STATE_TURNING,        // 转向中
    STATE_EDGE_FOLLOW,    // 沿墙清扫
    STATE_RETURNING,      // 回充
} State;

void FSM_Run(void) {
    State next = current;
    sensors = Read_All_Sensors();

    switch (current) {
    case STATE_CLEANING:
        if (sensors.cliff)      next = STATE_AVOIDING;
        if (sensors.obstacle)   next = STATE_AVOIDING;
        if (sensors.wall_left)  next = STATE_EDGE_FOLLOW;
        break;
    case STATE_AVOIDING:
        if (back_timeout())     next = STATE_TURNING;
        break;
    case STATE_TURNING:
        if (turn_done())        next = STATE_CLEANING;
        break;
    }
    current = next;
}
```

> 参考：好家伙VCC 第18章（综合功能整合），教你如何把各个模块串起来

### 第四级：路径规划

#### 弓字形（Bow Pattern）—— 推荐先从它入手

最实用且最容易实现的覆盖式清扫算法：

```
→→→→→→→→→→→
            ↓
←←←←←←←←←←←
↓
→→→→→→→→→→→
```

**逻辑**：
1. 直行清扫直到碰到障碍
2. 右转 90°，前进一个"机身宽度"
3. 再右转 90°，反向直行
4. 重复

> 参考博客：工程级扫地机器人方案（博客园/CSDN），有详细伪代码

#### 栅格地图（进阶）

- 将房间划分为 15×15cm 的栅格
- 编码器 + MPU6050 推算当前位置
- 状态：0 = 未清扫 / 1 = 已清扫 / 2 = 障碍物
- 遍历策略：DFS 优先去未清扫的相邻格子

> 参考：CSDN「基于STM32的智能扫地机器人（含A*算法+DFS）」

---

## 软件框架模板

```c
// 所有逻辑在固定周期中断中执行，清晰不乱
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
    if (htim->Instance != TIM2) return;  // TIM2 = 10ms tick

    Sensors_Update();       // 步骤1：读所有传感器、编码器
    FSM_Run();              // 步骤2：状态机决策
    Motor_PID_Update();     // 步骤3：电机控制输出
}
```

### FreeRTOS 任务划分（可选）

| 任务 | 周期 | 职责 |
|------|------|------|
| `SensorTask` | 50ms | 采集所有传感器数据 |
| `ControlTask` | 20ms | 运行状态机 + 路径规划 |
| `CommTask` | 100ms | 蓝牙/WiFi 通信 |

---

## 推荐学习路线（约 4-6 周）

| 周次 | 目标 | 跟学资源 | 产出 |
|------|------|----------|------|
| 第1周 | 底盘能走直线 | 好家伙VCC第1-9章 | 电机 + PID闭环调通 |
| 第2周 | 蓝牙遥控 + 避障 | 好家伙VCC第10-15章 | 手机控制 + 不撞墙 |
| 第3周 | MPU6050走直线 + 弓字形路径 | 好家伙VCC第17-18章 + 博客 | 覆盖矩形区域 |
| 第4周 | 加入清扫机构 | B站开源视频(BV1A3pxzHEkn) + dz-641资料 | 能扫能走 |
| 第5周 | 状态机整合 + 沿墙清扫 | 博客园工程级方案 | 多种模式切换 |
| 第6周 | 栅格地图 + 自动回充（选做） | CSDN(A*+DFS文章) | 全覆盖 + 自动回家 |

> **关键原则**：每个阶段跑通一个独立可运行的结果，不要同时调多个新功能。

---

## 需要的硬件清单

| 器件 | 规格 | 数量 | 参考价格 |
|------|------|------|----------|
| STM32最小系统板 | STM32F103C8T6 | 1 | ~15元 |
| 电机驱动模块 | TB6612FNG | 1 | ~8元 |
| 带编码器减速电机 | 6V/12V，减速比1:30~1:50 | 2 | ~25元/个 |
| 超声波模块 | HC-SR04 | 3 | ~3元/个 |
| 红外避障模块 | TCRT5000 | 3 | ~2元/个 |
| 蓝牙模块 | HC-05 或 JDY-31 | 1 | ~10元 |
| MPU6050 | 六轴陀螺仪+加速度计 | 1 | ~8元 |
| OLED屏幕 | 0.96寸 SSD1306 I2C | 1 | ~10元 |
| 小车底盘 | 亚克力板/3D打印 | 1 | ~20元 |
| 轮胎 | 适配电机的橡胶轮 | 2 | ~10元/个 |
| 万向轮 | 小牛眼轮 | 1-2 | ~3元/个 |
| 电池 | 7.4V 18650 2S + 充电模块 | 1套 | ~30元 |
| 吸尘电机 | 12V 小型离心风机 | 1 | ~15元 |
| 继电器模块 | 1路5V | 1 | ~3元 |
| 杜邦线/排针 | 公母各一盒 | 若干 | ~10元 |
| **合计** | | | **~250元** |

---

## 调试注意事项

| 问题 | 原因 | 解决方案 |
|------|------|----------|
| 走不直 | 电机差异/轮子打滑 | PID闭环控制，先校准编码器系数 |
| 超声波误判 | 多探头同时发射互相串扰 | **分时触发**，不要同时发射 |
| 卡在角落 | 避障逻辑太简单 | 后退后加**随机转向**，别固定转90° |
| 电机启动瞬间系统复位 | 电机启动电流大导致电压骤降 | 电机电源端并联 **4700μF 大电容** |
| 漏扫严重 | 纯随机碰撞 | 改用弓字形或栅格规划 |
| 电池续航差 | 电机效率低/无休眠机制 | 增加待机状态，使用高效驱动芯片 |
| MPU6050 角度漂移 | 温漂、积分累积误差 | 定时校准零偏，或结合编码器做融合 |

---

## 遇到问题去哪里求助

| 渠道 | 说明 |
|------|------|
| B站视频评论区 | 好家伙VCC系列评论区很活跃，问题基本有人回 |
| [51hei论坛](http://www.51hei.com/bbs/) | 国内最大单片机论坛，搜索关键词基本都有 |
| [21ic论坛](https://bbs.21ic.com/) | 电子工程师社区 |
| [CSDN](https://blog.csdn.net/) | 搜索"STM32 扫地机器人"找相关博客 |
| 相关QQ群 | 在B站视频置顶评论/资料包里通常有群号 |

---

## 全部参考资源索引

### B站视频（主线，优先看）
- [好家伙VCC - 全网最详细STM32智能小车（20+章，HAL库）](https://www.bilibili.com/video/BV16x4y1M7EN/)
- [STM32智能蓝牙扫地机器人（开源）8万播放](https://www.bilibili.com/video/BV1A3pxzHEkn/)
- [【开源】32B.基于STM32智能蓝牙扫地机器人 7.7万播放](https://www.bilibili.com/video/BV1Gj8bzFEeB/)
- [基于STM32扫地机器人实物设计](https://www.bilibili.com/video/BV1QyBKBcENz/)

### MCUClub 项目资料（完整源码+原理图+报告）
- [dz-641 基于STM32的扫地机器人设计](https://www.mcuclub.cn/archives/50495)
- [dz-1108 智能扫地机器人的设计与实现](https://www.mcuclub.cn/archives/47943)
- [dz-443 智能扫地机器人的设计与实现](https://www.mcuclub.cn/archives/48690)

### 博客文章（深入理解）
- [基于STM32的工程级扫地机器人方案（博客园）](https://www.cnblogs.com/45234ynn/p/20033393)
- [基于STM32的工程级扫地机器人方案（CSDN）](https://blog.csdn.net/yuan19997/article/details/161107161)
- [NullCXX三MCU协同架构（CSDN 2026）](https://blog.csdn.net/flink9streamer/article/details/155756528)
- [基于STM32的智能扫地机器人-含A*算法+DFS（CSDN）](https://blog.csdn.net/ZSW1218/article/details/161265446)
- [基于STM32F103ZE扫地机器人-步进电机+超声波+WiFi（CSDN）](https://blog.csdn.net/2501_93693767/article/details/154687967)
- [基于STM32设计的扫地机器人（掘金）](https://juejin.cn/post/7520506652526264366)
- [微信公众号：基于STM32智能扫地机器人（含完整代码）](https://mp.weixin.qq.com/s?__biz=Mzk0MTcxNjk1Mw==&mid=2247493829)

### 论坛
- [51hei论坛 - 开源程序（带FreeRTOS）](http://www.51hei.com/bbs/dpj-240636-1.html)
- [21ic论坛 - 好家伙VCC教程贴](https://bbs.21ic.com/icview-3396550-1-1.html)

### 开源项目（辅助参考）
- [GitHub: cleaningRobot (最精简)](https://github.com/Luminary-S/cleaningRobot)
- [GitHub: Mini-Robot-Cleaner (英文文档好)](https://github.com/jamesyoung-15/Mini-Robot-Cleaner)
- [GitHub: stm32_sweep (功能全)](https://github.com/MrZHU-py/stm32_sweep)
