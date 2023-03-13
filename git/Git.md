# 创建仓库

* 初始化仓库
  * **git init**
  * **git remote add remote-name URL**(**https**的话每次都要用户名密码,**ssh**的话需要将本地的公钥**id_rsa.pub**添加进入git仓库**个人公钥**中)
  * 此时**git remote -vv**可查看远程仓库名 


* 此时无分支 ,创建本地分支
  * **git push -u  remote-name branch-name** 将本地分支与推送仓库远程分支(远程分支原本不存,push后新建,名字同 branch-name)

* 创建新的本地分支
  * 创建前用当前本地分支中**git stash**将**add后但没有commit**的内容存进stash中,
  * **git checkout  -b new-branch-name**,创建新本地分支
  * **应该要先同步再进行后面**如果想改变本地分支跟踪的远程分支**git branch --set-upstream-to=remote-repo/remote-branch**即可改变跟踪成新的远程分支
  * 如果远程分支不存在,直接**git push -u remote-repo/remote-branch branch**创建并且改到跟踪新的远程分支
  * 此时如果想要将已经创建好的本地分支和已经存在的元程分支联系起来git branch --set-upstream-to=repo_name/<远程分支名称> <本地分支名称>
    
# 创建并初始化仓库
~~~ bash
git init 
~~~
## ssh_rsa 链接
~~~ bash
#注意url是远程ssh链接,这样可以实现ssh免密登陆,具体如何配置ssh,前往ssh笔记中查看
git remote add -f  orgin(远程别名) ssh_url 
git fetch
git push -u origin(远程库别名) branch(本地分支名) 
~~~

## https 链接
~~~ bash
#如果使用的https的链接，现在github已经取消账户密码登陆了，取而代之的是token即令牌登陆
git remote add orgin(本地仓库远程的别名) https_url
#查看远程
git remote -v
#先git fetch
git fetch
git push -u origin(远程库别名) branch(本地分支名) 
~~~

# 创建新的本地分支
~~~ bash

#创建前用当前本地分支中,将add后但没有commit的内容存进stash中,
git stash
#创建新本地分支
git checkout  -b new-branch-name
#应该要先同步(即 git fetch)再进行后面**如果想改变本地分支跟踪的远程分支
#即可改变跟踪成新的远程分支
git branch --set-upstream-to=remote-repo/remote-branch
#如果远程分支不存在,直接**
git push -u remote-repo/remote-branch branch #创建并且改到跟踪新的远程分支
#此时如果想要将已经创建好的本地分支和已经存在的元程分支联系起来
git branch --set-upstream-to=repo_name/<远程分支名称> <本地分支名称>
  
