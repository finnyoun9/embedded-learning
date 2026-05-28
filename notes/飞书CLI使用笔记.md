<title>飞书 CLI 简明使用指南</title>

# 飞书 CLI 简明使用指南

> 本文档介绍如何通过 Claude Code 控制飞书 CLI (lark-cli) 来操作飞书开放平台。

---

## 环境信息

- **CLI 版本**: lark-cli v1.0.40
- **安装路径**: \~/.npm-global/bin/lark-cli
- **登录用户**: 杨一帆
- **安装方式**: npm install -g @larksuite/cli

---

## 常用命令速查

### 授权与配置

```Bash
# 查看当前登录状态
lark-cli auth status

# 登录（推荐模式）
lark-cli auth login --recommend

# 初始化配置
lark-cli config init --new

```

### 知识库（Wiki）

```Bash
# 列出所有知识库空间
lark-cli wiki +space-list

# 列出空间下的节点（文档树）
lark-cli wiki +node-list --space-id <space_id>

# 列出某个节点下的子节点
lark-cli wiki +node-list --space-id <space_id> --parent-node-token <node_token>

# 获取节点详情
lark-cli wiki +node-get --params '{"node_token":"<token>"}'

# 创建新文档
lark-cli wiki +node-create --space-id <space_id> --title "标题" --obj-type docx

```

### 云文档（Docs）

```Bash
# 创建文档（v2 API）
lark-cli docs +create --api-version v2 --title "标题" --markdown "内容"

# 更新文档（v1 API 覆盖模式）
lark-cli docs +update --doc <url或token> --mode overwrite --markdown "新内容"

# 获取文档内容（v2 API）
lark-cli docs +fetch --api-version v2 --doc <url或token>

```

### 多维表格（Base）

```Bash
# 列出 Base
lark-cli base +list

# 查看表结构
lark-cli base +table-list --base-token <token>

# 读取记录
lark-cli base +record-list --base-token <token> --table-id <table_id>

```

### 通讯录（Contact）

```Bash
# 搜索用户
lark-cli contact +search-user --query "用户名"

```

### 即时通讯（IM）

```Bash
# 发送消息
lark-cli im message create --params '{"receive_id":"<open_id>","msg_type":"text","content":"{\"text\":\"你好\"}"}'

# 获取群聊列表
lark-cli im chat list

```

### 云盘（Drive）

```Bash
# 上传文件
lark-cli drive +upload --file <本地路径> --parent-token <文件夹token>

# 下载文件
lark-cli drive +download --file-token <文件token>

```

### 日历（Calendar）

```Bash
# 查看日程
lark-cli calendar +agenda

# 列出日历
lark-cli calendar +calendar-list

```

---

## 全局参数

| 参数 | 说明 |
|-|-|
| --as user/bot | 指定调用身份 |
| --format json/table/csv | 输出格式 |
| --page-all | 自动翻页 |
| --jq  / -q  | jq 过滤 JSON |
| --dry-run | 仅打印请求不执行 |

---

## 常用技巧

### 1. 用 jq 过滤输出

```Bash
# 只提取名称和 ID
lark-cli wiki +space-list -q '.data.spaces[] | {name, space_id}'

```

### 2. 表格格式输出

```Bash
lark-cli wiki +space-list --format table

```

### 3. 在 Claude Code 中调用

Claude Code 已安装飞书技能，可以直接用自然语言描述操作，Claude 会自动翻译成 lark-cli 命令。例如：

- "帮我列出所有知识库" → lark-cli wiki +space-list
- "在产品评估部知识库新建一个文档" → lark-cli wiki +node-create
- "搜索一个同事" → lark-cli contact +search-user

---

## 更多资源

- 飞书开放平台: https://open.feishu.cn
- CLI 源码: https://github.com/larksuite/cli
- API 文档: https://open.feishu.cn/document/
