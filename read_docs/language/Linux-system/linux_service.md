### chkconfig
chkconfig命令主要用来更新（启动或停止）和查询系统服务的运行级信息。谨记chkconfig不是立即自动禁止或激活一个服务，它只是简单的改变了符号连接。

--add 　增加所指定的系统服务，让chkconfig指令得以管理它
--del 　删除所指定的系统服务，不再由chkconfig指令管理 --list 列出所有的系统服务 --level httpd 2345 on #设置httpd在运行级别为2、3、4、5的情况下都是on（开启）的状态 chkconfig mysqld on #设定mysqld在各等级为on，“各等级”包括2、3、4、5等级

### 防火墙

-A INPUT -s 121.205.165.83/32 -p tcp -m tcp --dport 80 -j ACCEPT
