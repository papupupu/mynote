[toc]
## 创建密钥
* 注意要下面的操作要加入参数-f,为钥匙命名，方便后续管理
~~~ bash 
#会创建一把私钥和公钥
ssh-keygen -t(选择加密类型) rsa -C 'email' -f(存放的地址和名字) ~/.ssh/keyname.rsa
:<< B
私钥只有一把，留给自己，公钥给别人，别人接受你的公钥说明对方给了你向他单向
  传输消息的
B 
~~~
## config配置
### IP地址的配置(以腾讯云的配置为例子)
* 将腾讯云配置到了ssh的config中的话，直接
``` bash
#在~/.ssh/config中添加
Host tencent #远程别名
    HostName 150.158.193.150 #实际名
    User ubuntu #用户名
    #Port remote_port1
    PreferredAuthentications publickey #登陆类型： 公钥
    IdentityFile ~/.ssh/TencentCloud.peo #私钥文件的地址

#之后直接
ssh ubuntu(用户名)@tencent(自己设置的别名)
```

* 如果没有配置的话，要ssh连接远程,操作如下
``` bash
#配置了config的做法
ssh ubuntu(用户名)@tencent(自己设置的别名)
#如果没有在config中没有对对于的Hostername配置别名Hoster,那直接用下面的做法
ssh ubuntu(用户名)@IP地址
```

### github以及gitee的配置
* 这样你的github和gitee就可以用ssh免密码进行操作了
``` bash
#在~/.ssh/config中添加
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
### github仓库的ssh密钥配置
* 目的是为了每个仓库都有一个自己的独有的密钥
详细的配置说明可看[官方文档](https://docs.github.com/en/authentication/connecting-to-github-with-ssh/managing-deploy-keys#deploy-keys)
``` bash

```
### 将新的密钥加入到ssh缓存中去
* 这一步好像不是必须，但是我出现了
~~~ bash
Permission denied (publickey)
~~~
* 这是因为新的密钥没有加入本地ssh环境中，所以为了避免，建议每次新建密钥后，都将其添加ssh环境中
操作如下
``` bash
ssh-add ~/.ssh/key_name_id_rsa(即私钥的文件地址)
```
## 上传公钥
将.pub文件上传，对方接受你的公钥表示对方给了你单向向它通信的权限

