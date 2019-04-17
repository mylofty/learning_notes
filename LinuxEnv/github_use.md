#github学习
##一、github基本配置
1、本地配置github
（1）、创建ssh rsa密钥： 
```
ssh-keygen -t rsa -C "1576926131@qq.com"
```
之后会在home/dzm/.ssh/ 目录下生成公钥和私钥。之后把公钥保存到github的key中。
（2）、测试是否可以访问 ssh -T git@github.com （报错broken pipe也没问题）
2、配置user，email
```
git config --global user.name "mylofty" //设置用户名 
git config --global user.email "1576926131@qq.com" //设置邮箱
```
3、在github上创建一个仓库
4、将github上的仓库clone到本地，然后便可以使用了

## git常用命令
###1、上传下载
```
1、git	add .	//将所有文件保存到暂存区
2、git 	status	//查看当前版本状态，是否修改过
3、git	commit	--m 'xxx'	//将暂存区的文件提交到本地的当前分支
4、git	push	(origin master)	//将当期分支提交到远程origin主机的master分支上
5、git	pull		(origin master)	//将远程分支origin拉取到当前master分支并且进行自动合并 == fetch+merge

```

###2、分支处理
```
1、git branch (-a)		//显示本地(所有)分支
2、git branch --merged		//显示所有已经合并到本分支的分支
3、git branch --no-merged	//显示所有未合并到本分支的分支
4、git branch -d origin/master		//删除分支

11、git checkout -b master_copy	//新建分支：从当前分支生成新的master_copy分支，并切换到该分支
12、git	checkout master_copy2			//切换分支：从当前分支切换成master_copy2分支
13、git checkout -b devel origin/develop	//从远程分支develop中生成本地分支devel

```


###3、查看区别与合并
```
1、git fetch			//获取所有远程分支到本地（不更新本地分支）
// 通过git branch -a先查看下获取到的远程分支的名字
2、git diff	origin/master （filename）		//比较当前分支与origin/master分支（中文件filename）的区别
3、git diff			//比较工作区和暂存区的区别，add之前和之后的区别
4、git diff --cached //比较暂存区和版本库（最近一次commit之后）的区别

```
