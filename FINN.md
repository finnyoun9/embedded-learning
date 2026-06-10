# Finn（杨一帆）— 个人上下文

> 把这个文件放在任何设备的 `~/FINN.md` 或项目根目录，AI 智能体会自动读取。
> 我会持续更新这个文件，你按需阅读。

---

## 基本信息

- **名字**：Finn / 杨一帆
- **角色**：软件工程师
- **行业背景**：扫地机器人行业从业者，懂底层原理，重心在工程实现
- **GitHub**：[finnyoun9](https://github.com/finnyoun9)

---

## 设备 & 环境

| 设备 | 角色 | 系统 |
|------|------|------|
| Mac（主力） | 项目管理、视觉开发、日常编码 | macOS 26.x |
| Mac Linux VM | ROS2 学习与开发 | Ubuntu (虚拟机) |
| Windows | STM32 嵌入式开发 (Keil) | Windows |
| 树莓派 5 | ROS2 部署 + Linux 嵌入式 | ✅ 已拥有 |

- **主目录**：`/Users/finn`
- **项目目录**：`/Users/finn/Projects`
- **Hermes Agent**：`~/.hermes/`，profile 为 `default`
- **Claude Code**：`~/.claude/`，通过 DeepSeek API 调用

---

## 技术栈

### 主力
- **Node.js / TypeScript** — strict mode, ESM, Vitest, Playwright, ESLint + Prettier
- **嵌入式** — STM32 HAL, FreeRTOS, ROS2 (Jazzy), Raspberry Pi
- **Python** — OpenCV, YOLO, 数据分析

### 会用
- Git / GitHub（学习中，偏好自动化流程）
- arm-none-eabi-gcc, OpenOCD, ST-Link, QEMU, PlatformIO, picocom, CMake（macOS 工具链已配好）

### 兴趣方向
- 扫地机器人全栈（硬件→嵌入式→上位机→SLAM→导航）
- 计算机视觉（OpenCV、线激光三角测量、ToF、LDS）
- 自动化与智能体（AI agent 工作流、多机器人协作）

---

## 活跃项目

### 1. 🤖 robot-vacuum-lab — 从零造扫地机器人（capstone 项目）
- **仓库**：[cv-learning-roadmap](https://github.com/finnyoun9/cv-learning-roadmap) (public)
- **架构**：树莓派 5 (ROS2 Humble) ←UART→ STM32 (电机/IMU/传感器/电池)
- **五轨并行**：
  - **Track A (STM32/Windows)** — 江科大课程 → 平衡车 → PID → 串口协议 → 扫地机外设
  - **Track B (ROS2/VM→Pi)** — ROS2 核心 → TF2 → 传感器驱动 → SLAM → Nav2 → 行为树
  - **Track C (感知/Mac)** — OpenCV/YOLO → 线激光三角测量 → LDS → ToF → 传感器融合
  - **Track D (硬件)** — 底盘 → 供电 → 安装布线（等前三轨出成果）
  - **Track E (集成)** — Pi-STM32 联调 → 全系统 ROS2 → 自主清扫 Demo
- **预算**：~1,600-1,800 元，分阶段采购
- **仓库**：`cv-learning-roadmap`、`embedded-learning`、`vacuum-subsystem`

### 2. 🧠 metabot — 飞书 → Claude Code 多机器人桥接
- **技术栈**：Node.js / TypeScript
- **路径**：`/Users/finn/Projects/metabot`

### 3. 🤖 feishu-claude-bot — 飞书 → Claude 单机器人
- **技术栈**：Node.js / TypeScript
- **路径**：`/Users/finn/Projects/feishu-claude-bot`

### 4. 📱 xiaohongshu-auto — 小红书 Playwright 自动化
- **技术栈**：TypeScript + Playwright
- **路径**：`/Users/finn/Projects/xiaohongshu-auto`

### 5. 📚 embedded-learning — 嵌入式学习笔记 & 代码
- **路径**：`/Users/finn/Projects/embedded-learning`

### 6. 🎬 心理学短视频 — 心理学选题库
- **平台**：小红书 / 短视频
- **风格**：学术概念 + 机制解释 + 扎心总结（"换句话说"）
- **路径**：`/Users/finn/Projects/心理学/心理学选题库.md`

---

## AI 智能体配置

### Hermes Agent
- **配置**：`~/.hermes/`
- **模型**：DeepSeek deepseek-v4-pro（主）/ deepseek-v4-flash（子代理）
- **飞书集成**：App ID `cli_aa9ffe25babadcc4`，用户 `ou_27dcb648b1620695e194417481fa69e1`
- **记忆**：Holographic（本地 SQLite + FTS5 + HRR），`~/.hermes/memory_store.db`
- **嵌入式开发 skill**：`~/.hermes/skills/embedded/embedded-macos/SKILL.md`

### Claude Code
- **路径**：`~/.claude/`
- **API**：通过 DeepSeek API（`ANTHROPIC_BASE_URL=https://api.deepseek.com/anthropic`）
- **Skills**：53 个，含飞书系列 `lark-*`
- **工作区**：7 个项目，5 个 MEMORY.md 记忆文件
- **昵称**：叫它"咪咪"（Mimi）

---

## 工作偏好

- 🌐 **语言**：和我用中文交流，代码、变量名、commit message 用英文
- ⚡ **风格**：简洁直接，能自主推进就别一步步问。做完了汇报结果。
- 🔧 **Git**：帮我自动完成完整 Git 流程（init → .gitignore → GitHub repo → push），别一步步确认
- 📦 **代码规范**：Node/TS 项目用 strict mode + ESM + ESLint + Prettier，提交前格式化
- 🧪 **测试**：写代码要带测试（Vitest）

---

## 当前学习重点

1. **ROS2** — 核心概念、TF2、SLAM、Nav2（Track B）
2. **STM32 进阶** — 平衡车 → PID 控制 → 串口通信协议（Track A）
3. **计算机视觉** — 线激光三角测量、ToF 传感器、多传感器融合（Track C）
4. **Git** — 完整工作流（branch、PR、CI）

---

## 常用提示词模板

### 嵌入式学习推进（主模板）

```
我的目标是 2026 年 4 月从追觅科技 TSE 跳槽到深圳做嵌入式工程师（软件或硬件方向）。

请直接动手推进我的学习项目，不要只给计划——跑代码、连硬件、写文档、推 GitHub。
我给你最大权限，可以调用我电脑上所有工具和资源。

当前硬件：树莓派 5、STM32 (Blue Pill)、Arduino、逻辑分析仪、DP100 数控电源、VL53L0X ToF、OV7670 摄像头、零散传感器模块。
目标仓库：https://github.com/finnyoun9/embedded-learning（所有产出即时提交推送）
学习路线 & 求职调研见仓库 planning/ 目录。

请：
1. 搜索深圳嵌入式岗位最新技能要求，如有变化直接更新我的学习计划
2. 基于现有硬件推进当前阶段项目（裸机驱动 → FreeRTOS → ROS2 → CAN）
3. 每完成一步都写好文档（README + 原理说明），提交到 GitHub
4. 帮我用逻辑分析仪、DP100 等工具验证，产出可展示的波形图和数据

加油，干就完了。
```

---

## 笔记

- 这份文件是给 AI 智能体看的"关于我"上下文——不是简历，是让智能体在开始工作前快速了解我是谁、在做什么、怎么做。
- 放在 `~/FINN.md`，Hermes 和 Claude Code 都能读取。
- 有新项目、换设备、改变偏好时更新这个文件。
