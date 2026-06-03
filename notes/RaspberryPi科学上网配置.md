# Raspberry Pi 科学上网配置

> 在树莓派上独立运行代理客户端，不再依赖 Mac 共享代理。

---

## 环境信息

- **设备**: Raspberry Pi 5 (aarch64)
- **系统**: Debian 12 Bookworm
- **代理客户端**: Mihomo v1.19.6 (Clash.Meta 继任者)
- **代理端口**: HTTP/SOCKS5 混合端口 7890, DNS 1053, Web API 9090
- **配置目录**: `~/.config/mihomo/`

---

## 架构

```
终端/浏览器  →  Mihomo(127.0.0.1:7890)  →  机场节点(VMess/WebSocket)  →  目标网站
```

所有流量经本地 Mihomo 加密后走机场节点出去。Pi 重启后 Mihomo 自动启动。

---

## 关键文件

| 文件 | 作用 |
|------|------|
| `~/.config/mihomo/config.yaml` | 代理主配置（节点列表、代理组、分流规则、DNS） |
| `~/.config/mihomo/update-sub.sh` | 订阅更新脚本 |
| `~/.config/mihomo/geoip.metadb` | GeoIP 数据库（分流用） |
| `~/.config/mihomo/geosite.dat` | GeoSite 数据库（域名分流用） |
| `/etc/systemd/system/mihomo.service` | systemd 服务（开机自启） |
| `/etc/systemd/system/mihomo-update.timer` | 每日凌晨 4:07 自动更新订阅 |
| `~/.ssh/config` | SSH 代理配置（GitHub 走 SOCKS5 443 端口） |

---

## 常用操作

### 查看代理状态

```bash
systemctl status mihomo
```

### 启动 / 重启 / 停止

```bash
sudo systemctl start mihomo
sudo systemctl restart mihomo
sudo systemctl stop mihomo
```

### 手动更新订阅

```bash
~/.config/mihomo/update-sub.sh
```

### 查看日志

```bash
journalctl -u mihomo -f        # 实时
journalctl -u mihomo -n 50     # 最近 50 行
```

### 测试代理是否正常

```bash
curl -x http://127.0.0.1:7890 https://www.google.com -o /dev/null -w "%{http_code}"
# 返回 200 或 302 表示正常
```

---

## Web 可视化面板

Mihomo 内置 Yacd Dashboard，在 Pi 浏览器访问：

```
http://127.0.0.1:9090/ui/
```

可以查看节点列表、切换线路、测速。

---

## 环境变量

写入 `~/.bashrc`，新终端自动生效：

```bash
export http_proxy=http://127.0.0.1:7890
export https_proxy=http://127.0.0.1:7890
export all_proxy=socks5://127.0.0.1:7891
export no_proxy=localhost,127.0.0.1,::1,10.51.33.0/24,192.168.0.0/16,.local
```

apt 和 npm 也单独配置了代理，指向 `127.0.0.1:7890`。

---

## GitHub SSH 配置

SSH 不走环境变量，需要单独配置 `~/.ssh/config`：

```
Host github.com
    HostName ssh.github.com
    Port 443
    User git
    IdentityFile ~/.ssh/id_ed25519
    ProxyCommand nc -X 5 -x 127.0.0.1:7890 %h %p
```

要点：
- 用 SOCKS5 (`-X 5`) 而非 HTTP CONNECT，兼容性更好
- 走 443 端口（`ssh.github.com`），绕过 22 端口封锁
- 密钥 `id_ed25519` 关联 `finnyoun9@gmail.com`

测试连接：

```bash
ssh -T git@github.com
# Hi finnyoun9! You've successfully authenticated...
```

---

## 更换订阅地址

编辑 `~/.config/mihomo/update-sub.sh`，修改 `SUB_URL` 变量，然后执行：

```bash
nano ~/.config/mihomo/update-sub.sh   # 改订阅链接
~/.config/mihomo/update-sub.sh         # 更新并重启
```

---

## GeoIP/GeoSite 数据库更新

Mihomo 启动时自动从 GitHub 下载。如果启动卡住（鸡生蛋问题），手动下载：

```bash
# 先确保代理可用
export http_proxy=http://127.0.0.1:7890
export https_proxy=http://127.0.0.1:7890

# 下载 geoip
curl -L -o ~/.config/mihomo/geoip.metadb \
  "https://github.com/MetaCubeX/meta-rules-dat/releases/download/latest/geoip.metadb"

# 下载 geosite
curl -L -o ~/.config/mihomo/geosite.dat \
  "https://github.com/MetaCubeX/meta-rules-dat/releases/download/latest/geosite.dat"
```

---

## 已知问题

- `apt.sing-box.app` 源走代理会 TLS 握手失败（不影响正常使用）
- 机场节点不稳定，部分节点会超时（已配置自动选择最优节点）
- `nc -X connect` (HTTP CONNECT) 在此环境中不稳定，统一用 `-X 5` (SOCKS5)

---

> 配置日期：2026-06-03
