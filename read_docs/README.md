


1. php 安装

rpm -Uvh https://mirror.webtatic.com/yum/el6/latest.rpm
yum install php56w php56w-fpm php56w-mbstring php56w-pgsql php56w-pecl-redis

2. openresty 

yum install readline-devel pcre-devel openssl-devel gcc
wget https://openresty.org/download/openresty-1.11.2.1.tar.gz

make && make install

ln -sf /usr/local/openresty/bin/openresty /usr/local/bin/openresty

3. beanstalk

wget https://github.com/kr/beanstalkd/archive/v1.10.tar.gz


4. redis 

5. postgresql

yum install http://yum.postgresql.org/9.5/redhat/rhel-7-x86_64/pgdg-redhat95-9.5-2.noarch.rpm
yum install postgresql95-server postgresql95-contrib
service postgresql-9.5 initdb
chkconfig postgresql-9.5 on

#初始化数据库和用户

5. 

