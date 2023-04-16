Question:

请你为我用markdown格式告诉我tmux常用命令以及~/.config/tmux的配置

Answer:

## Tmux常用命令

- `tmux new -s <session-name>` 创建新会话
- `tmux a -t <session-name>` 进入会话
- `tmux ls` 列出所有会话
- `tmux kill-session -t <session-name>` 结束某个会话
- `tmux split-window` 垂直分割窗格
- `tmux split-window -h` 水平分割窗格
- `tmux select-pane -<h|j|k|l>` 移动光标到不同的窗格
- `tmux resize-pane -<D|U|L|R> <size>` 调整窗格大小
- `tmux setw -g mode-keys vi` 使用vi风格的快捷键
- `tmux list-keys` 查看所有快捷键
- `tmux detach` 退出当前会话但不删除
- 'source-file ~/.tmux.conf' 在session中使用使配置生效

## ~/.config/tmux的配置

```bash
# 开启鼠标模式
set -g mouse on

# 使用vi风格的快捷键
setw -g mode-keys vi

# 设置状态栏颜色
set -g status-bg colour235
set -g status-fg colour136
set -g status-left '#[fg=white]#H #[fg=yellow]::#[fg=white]#S'

# 设置默认绑定前缀
unbind C-b
set -g prefix C-a
bind C-a send-prefix

# 允许使用鼠标选择窗格
set -g mouse-select-pane on

# 设置窗口列表颜色
set -g window-status-style bg=colour235,fg=colour137
set -g window-status-current-style bg=colour237,fg=colour136
```

<hr/>

# Tmux快捷键：

- `prefix`键：在默认情况下，该键位于 `C-b` 上，按下该键之后再按其他键就可以执行相应的命令。
- `prefix ?`：列出所有快捷键
- `prefix c`：创建新窗口
- `prefix &`：杀死当前窗口
- `prefix ,`：重命名当前窗口
- `prefix $`：重命名当前session
- `prefix w`：列出所有窗口
- `prefix n`：打开下一个窗口
- `prefix p`：打开上一个窗口
- `prefix %`：将当前窗口垂直分割
- `prefix "`：将当前窗口水平分割
- `prefix arrow key`：在窗格之间移动
- `prefix z`：最大化或最小化当前窗格
- `prefix d`：将当前会话分离
- `prefix &`：将当前window关闭
- `prefix x`：将当前panne关闭

上面的这些快捷键只是Tmux的一小部分功能，更多详细的操作可以上网查找相关文档或手册。
<hr/>
