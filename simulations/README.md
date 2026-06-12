# Simulations

理论仿真脚本，用 Python + matplotlib 可视化电路行为。

## analog/

| 脚本 | 内容 | 对应理论 |
|------|------|----------|
| `rc_filter.py` | RC 低通滤波器：幅频/相频/瞬态/充电曲线 | 一阶 RC 电路，截止频率 fc=1/(2πRC) |
| `diode_iv.py` | 1N4148 二极管伏安特性曲线 | Shockley 方程，膝点电压，单向导电性 |
| `analog_trilogy.py` | BJT 放大 + 运放电路 + LDO 稳压器 | 三合一：共射放大/反相-同相-比较器/串联稳压 |

## view_wave.py

逻辑分析仪 VCD → PNG 波形图工具。

```bash
sigrok-cli -d fx2lafw --samples 2M -c samplerate=1M --channels D0 -o capture.sr
sigrok-cli -i capture.sr -O vcd -o capture.vcd
python3 simulations/view_wave.py capture.vcd capture.png
```
