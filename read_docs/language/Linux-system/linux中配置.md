### fd
#### 查看当前系统使用的文件描述符总数
 cat /proc/sys/fs/file-nr
#### 某个进程打开的文件描述符总数
$ll /proc/pid/fd
$lsof | grep pid| wc -l
#### 查看当前系统默认的进程fd限制
$ulimit -n
$ulimit -a #查看所有限制
$cat /proc/pid/limits

```
1. 只影响当前session,当终端重新连接或当前用户退出，配置就失效了
    #ulimit -SHn 2048
2. 如果想要永久生效，这编辑/etc/security/limits.conf文件
* hard nofile 2048
* soft nofile 2048

3. 注意，内核参数对文件描述符也有限制，如果大于内核的限制，也不可以
    *查看内核参数
        #sysctl -a | grep file-max
    *修改
        #sysctl -w file-max=65535
```

#### 修改限制
ulimit -HSn 4096

### selinux

#### 查看状态
/usr/sbin/sestatus -v
getenforce #
#### 临时关闭
setenforce 0
#### 修改配置文件
/etc/selinux/config #

### 内核
