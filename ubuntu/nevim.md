# 安装neovim 
* [github of neovim](https://github.com/neovim/neovim)
* 从此下载稳定最新版 [最新版](https://github.com/neovim/neovim/releases/tag/stable
)
* Download nvim-linx64.deb
* Run nvim

  
# [配置教程](https://www.bilibili.com/video/BV1Td4y1578E/?spm_id_from=333.1007.top_right_bar_window_history.content.click&vd_source=69f2e70a5704c07cf83cb057eda790b8)
~~~
cd ~/.config/
将仓库git clone https://github.com/eggtoopain/Neovim-Configuration-Tutorial   
cd 仓库
rm .git -rf
cd ..
mv  -r 仓库名 nvim
~~~
# 安装插件
* 上面已经帮你配置安装好了packer
* 后面想安装插件只需要在nevim /nvim/lua/plugins/plugins-setup.lua中
startup 下面 use '仓库名' 比如 use 'folke/tokyonight.nvim' --安装主题插件
* 如果要使用刚刚的主题 需要
~~~
nvim /nvim/lua/core/options.lua中使用加入
Lua vim.cmd[[colorscheme tokyonight]]
~~~
如果想用该主题中的moon皮肤则，
* 将上面改为
~~~
Lua vim.cmd[[colorscheme tokyonight-moon]]
使用：so，nvim配置生效
~~~
# 快捷键设置
~~~ bash 
nvim /home/papupupu/.config/nvim/lua/core/keymaps.lua
#下面加上
#插件快捷键设置
keymap.set("n"(模式), "<leader>md"(需要的键位), ":MarkdownPreview"(替换的键位))
~~~

