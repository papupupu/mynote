## 源代码安装程序

### 下载源代码
* 从官网下载相应的源代码，格式一般为tar.gz 或 tar.bz2 

### 解压源代码
* 将下载好的包解压，命令为

```bash
#具体命令根据tar.xx有所不同
#解压到当前文件夹,-I是列出解压的文件有哪些
tar -I zstd -xf xx.tar.zst 
#解压到指定文件夹
tar -I zstd -xf xx.tar.zst -C /path/to/extract
```

### 移动解压文件至~/opt/或者/opt中
~~~bash
sudo mv file /opt/ 
~~~


### ./install
进入文件执./install或者./application-name


### 添加到bin目录
```bash
#本地用户创建软链接
sudo ln -s /opt/your/executable   ~/.local/bin/name
#全局创建软链接
sudo ln -s /opt/your/executable   /local/bin/name
```

#### 出现本地的～/.local/bin/不生效
显然 ~/.local/bin/没有加入到path中，稳妥的办法，加入到本地用户中的~/.profile中
```bash
nvim ~/.profile
# set PATH so it includes user's private bin if it exists
if [ -d "$HOME/.local/bin" ] ; then
    PATH="$HOME/.local/bin:$PATH"
fi
#或者直接
echo 'export PATH="$HOME/.local/bin:$PATH"' >> ~/.bash_profile
```

### 添加图标
* 用户级别安装
```bash
cd ~/.local/share/applications/
# 创建你的.desktop文件
nvim xx.desktop
#写入,以clah为例子，更改为executable以及coin路径即可
[Desktop Entry]
Name=Clash 
Exec=/home/papupupu/.local/bin/clash
Icon=/home/papupupu/.local/share/icons/clash.png
Type=Application
StartupNotify=true
```
