[toc]
# 创建仓库
## 初始化仓库

* 初始化
  ~~~shell
  git init
  ~~~

* 加入远程库链接
  ~~~shell
  git remote add remote-name URL
  ~~~
  (https**的话每次都要用户名密码,**ssh**的话需要将本地的公钥**id_rsa.pub**添加进入git仓库**个人公钥**中)

* 此时
  ~~~bash
  git remote -vv
  ~~~
  可查看远程仓库名
## 此时无分支 ,创建第一支本地分支

  *创建同名远程
   ~~~bash
  git push -u  remote-name branch-name
  ~~~
  将本地分支与推送仓库远程分支(远程分支原本不存,push后新建,名字同 branch-name)
## 创建新的本地分支

  * 创建前用当前本地分支中**git stash**将**add后但没有commit**的内容存进stash中,

  * 法一 
  ```bash
  git branch new-branch-name 
  ```
  即使是 **远程有与当前分支同名** 的分支，此时创建的分支依旧是复制当前分支,且**不切换**到该分支

  * 法二
  ~~~bash
  git checkout  -b new-branch-name
  ~~~
  创建新本地分支,如果有**远程同名分支**,**复制远程该分支并与其关联**

  * **应该要先同步再进行后面**如果想改变本地分支跟踪的远程分支
  ~~~bash
  git branch --set-upstream-to=remote-repo/remote-branch
  ~~~
  即可改变跟踪成新的远程分支

  * 如果远程分支不存在,直接
  ~~~bash
  git push -u remote-repo/remote-branch branch
  ~~~
  创建并且改到跟踪新的远程分支

  * 此时如果想要将已经创建好的本地分支和已经存在的元程分支联系起来
  ~~~bash
  git branch --set-upstream-to=repo_name/<远程分支名称> <本地分支名称>
  ~~~

