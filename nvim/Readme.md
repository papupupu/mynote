# 配置
* 自动补全的配置在./lua/plugins/lsp.lua中
```lua
#哪些语言在这里安装
  ensure_installed = 
```
或者是在nvim中
```
:Mason
#查看安装的语言
:/查找想安装的语言名
i
```

* 补全的设置在./lua/plugins/cmp.lua中
```
Ctrl + b 下滑浏览补全信息
Ctrl + f 上滑浏览补全信息
Ctrl + e 取消补全信息
```

* 增加更多自动补全插件
``` 
nvim ./lua/plugins/cmp.lua
#在source中加入插件
sources = cmp.config.sources
```

# 操作
## 文件操作
* 增加文件，nvim-tree中输入a，即add,增加文件
* 删除文件，nvim-tree中输入d，即delete,删除文件
* 重命名文件，nvim-tree中输入r，即rename,重命名文件
* 复制文件，nvim-tree中输入c，即copy,复制文件
* 查找文件， n模式下，<leard>ff,

## 查找
* 查找文件内容<leard>fg
* 查找文件<leard>ff
