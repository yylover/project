


## 动态连接

1. gcc -fPIC -c max.c
2. gcc -shared -o libmax.so max.o
3. gcc ./dl.c -L. -lmax
4. ./a.out

## 动态加载

1. gcc ./dl.c -lmax
2.
