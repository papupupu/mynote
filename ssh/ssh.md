## 创建密钥
~~~ bash 
#会创建一把私钥和公钥
ssh-keygen -t(选择加密类型) rsa -C 'email' -f(存放的地址和名字) ~/.ssh/keyname.rsa
:<< B
私钥只有一把，留给自己，公钥给别人，别人接受你的公钥说明对方给了你向他单向
  传输消息的
B 
~~~
## config配置
``` bash
#TencentCloud
Host tencent #远程别名
    HostName 150.158.193.150 #实际名
    User ubuntu #用户名
    #Port remote_port1
    PreferredAuthentications publickey #登陆类型： 公钥
    IdentityFile ~/.ssh/TencentCloud.peo #私钥文件的地址

# gitee
Host gitee.com
    HostName gitee.com
    PreferredAuthentications publickey
    IdentityFile ~/.ssh/gitee_id_rsa

# github
Host github.com
    HostName github.com
    PreferredAuthentications publickey
    IdentityFile ~/.ssh/github_id_rsa

```
## 上传公钥
将.pub文件上传，对方接受你的公钥表示对方给了你单向向它通信的权限

