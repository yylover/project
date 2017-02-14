

bzero() 不推荐使用，使用memset代替，是memset的一个宏

string.h
void *memcpy(void *dest, const void *src, size_t n);

3. malloc calloc
malloc 分配空间，但是不会初始化值。
void * malloc(int n); //从堆上获取指定字节的内存空间。malloc分配得到的内存是未初始化的。因此需要使用：
void * memset (void * p,int c,int n) ;//初始化为指定字符c
void free (void * p); //实现释放内存的功能
void *calloc(int n,int size);//也是堆上获取size x字节空间，并返回该空间的首地址，如果失败，返回NULL。但是空间是经过初始化的。
void * realloc(void * p,int n);//p是指向堆内存空间的指针，即由malloc函数,calloc() realloc()函数分配的指针。如果n小于原来的大小，那么保持原有的状态不变；如果大于原来的空间，那么，将指向空间的内容依次赋值到新的内存空间上。p之前指向的空间将被释放。
realloc()//重新分配内存空间，必须是malloc() collar() realloc()之后调用 之前的函数指针会自动释放。
calloc() //空间会进行初始化
free()// 释放malloc和colic() 释放内存空间

4. assert 是宏，不是函数。断言失败，是什么现象
