1. ### 常用命令
ls　　             显示文件或目录
      -l              列出文件详细信息l(list)
      -a             列出当前目录下所有文件及目录，包括隐藏的a(all)
mkdir             创建目录
      -p            创建目录，若无父目录，则创建p(parent)
cd                 切换目录
touch             创建空文件
echo              创建带有内容的文件。
cat                查看文件内容
cp                 拷贝
mv                移动或重命名
rm                删除文件
     -r            递归删除，可删除子目录及文件
     -f            强制删除
find              在文件系统中搜索某文件 find   -name april*
wc                统计文本中行数、字数、字符数
grep             在文本文件中查找某个字符串 $ grep ‘test’ aa bb cc
rmdir           删除空目录
tree             树形结构显示目录，需要安装tree包
pwd              显示当前目录
ln                  创建链接文件
more、less   分页显示文本文件内容
head、tail    显示文件头、尾内容
ctrl+alt+F1    命令行全屏模式

### 系统管理命令

stat               显示指定文件的详细信息，比ls更详细
who               显示在线登陆用户
whoami            显示当前操作用户
hostname          显示主机名
uname             显示系统信息
top                 动态显示当前耗费资源最多进程信息
ps                   显示瞬间进程状态 ps -aux

    找出与 cron 与 syslog 这两个服务有关的 PID 号码

[root@linux ~]# ps aux | egrep '(cron|syslog)'
du                   查看目录大小 du -h /home带有单位显示目录信息
df                   查看磁盘大小 df -h 带有单位显示磁盘信息
ifconfig          查看网络情况
ping                测试网络连通
netstat          显示网络状态信息
man                命令不会用了，找男人  如：man ls
clear              清屏
alias               对命令重命名 如：alias showmeit=”ps -aux” ，另外解除使用unalias showmeit
kill                 杀死进程，可以先用ps 或 top命令查看进程的id，然后再用kill命令杀死进程。
打包压缩相关命令
gzip：
bzip2：
tar:                  打包压缩
       -c              归档文件
       -x              压缩文件
       -z              gzip压缩文件
       -j              bzip2压缩文件
       -v              显示压缩或解压缩过程 v(view)
       -f              使用档名
例：
tar -cvf /home/abc.tar /home/abc              只打包，不压缩
tar -zcvf /home/abc.tar.gz /home/abc        打包，并用gzip压缩
tar -jcvf /home/abc.tar.bz2 /home/abc      打包，并用bzip2压缩
关机/重启机器


shutdown
       -r             关机重启
       -h             关机不重启
       now          立刻关机

halt               关机
reboot          重启
Linux管道

将一个命令的标准输出作为另一个命令的标准输入。也就是把几个命令组合起来使用，后一个命令除以前一个命令的结果。

例：grep -r “close” /home/* | more       在home目录下所有文件中查找，包括close的文件，并分页输出。

用户及用户组管理

/etc/passwd    存储用户账号
/etc/group       存储组账号
/etc/shadow    存储用户账号的密码
/etc/gshadow  存储用户组账号的密码
useradd          用户名
userdel           用户名
adduser         用户名
groupadd       组名
groupdel        组名
passwd root     给root设置密码
su root

su – root 

/etc/profile     系统环境变量
bash_profile     用户环境变量
.bashrc              用户环境变量
su user              切换用户，加载配置文件.bashrc
su – user            切换用户，加载配置文件/etc/profile ，加载bash_profile
